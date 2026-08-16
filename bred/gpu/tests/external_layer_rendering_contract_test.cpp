#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read(const std::filesystem::path & path)
   {

      std::ifstream stream(path, std::ios::binary);
      assert(stream);
      return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};

   }


   std::string section(
      const std::string & source,
      const std::string & beginMarker,
      const std::string & endMarker)
   {

      const auto begin = source.find(beginMarker);
      const auto end = source.find(endMarker, begin);
      assert(begin != std::string::npos);
      assert(end != std::string::npos);
      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto gpu = std::filesystem::path(__FILE__).parent_path().parent_path();
   const auto compositorHeader = read(gpu / "compositor.h");
   const auto compositorSource = read(gpu / "compositor.cpp");
   const auto layerHeader = read(gpu / "layer.h");
   const auto layerSource = read(gpu / "layer.cpp");
   const auto rendererSource = read(gpu / "renderer.cpp");
   const auto contextSource = read(gpu / "context.cpp");

   assert(compositorHeader.find(
      "virtual bool renders_layer_externally(::gpu::layer * pgpulayer);") !=
      std::string::npos);
   assert(compositorSource.find(
      "bool compositor::renders_layer_externally(::gpu::layer * pgpulayer)") !=
      std::string::npos);
   assert(layerHeader.find("bool m_bExternalRendering = false;") !=
      std::string::npos);

   const auto initializeLayer = section(
      layerSource,
      "void layer::initialize_gpu_layer(",
      "void layer::layer_start()");
   assert(initializeLayer.find("m_bExternalRendering = false;") !=
      std::string::npos);

   const auto startLayer = section(
      rendererSource,
      "void renderer::on_start_layer(layer* pgpulayer)",
      "void renderer::on_end_layer(layer* player)");
   const auto query = startLayer.find("renders_layer_externally(pgpulayer)");
   const auto externalState = startLayer.find("pgpulayer->start_layer_render();", query);
   const auto ordinaryBegin = startLayer.find("on_begin_render(pgpulayer);", externalState);
   const auto contextHook = startLayer.find("m_pgpucontext->on_start_layer(pgpulayer);", ordinaryBegin);
   const auto backendBegin = startLayer.find("_on_begin_render(pgpulayer);", contextHook);
   assert(query != std::string::npos);
   assert(externalState != std::string::npos);
   assert(ordinaryBegin != std::string::npos);
   assert(contextHook != std::string::npos);
   assert(backendBegin != std::string::npos);
   assert(query < externalState && externalState < ordinaryBegin);
   assert(ordinaryBegin < contextHook && contextHook < backendBegin);
   assert(startLayer.find("if (!pgpulayer->m_bExternalRendering)", query) !=
      std::string::npos);

   const auto endRender = section(
      rendererSource,
      "void renderer::on_end_render(::gpu::layer * pgpulayer)",
      "void renderer::_on_begin_render");
   const auto layerEnd = endRender.find("pgpulayer->layer_end();");
   const auto externalGuard = endRender.find(
      "if (!pgpulayer->m_bExternalRendering)", layerEnd);
   const auto backendEnd = endRender.find("_on_end_render(pgpulayer);", externalGuard);
   const auto submit = endRender.find("layer_end_submit();", backendEnd);
   const auto stateEnd = endRender.find("pgpulayer->end_layer_render();", submit);
   assert(layerEnd < externalGuard);
   assert(externalGuard < backendEnd && backendEnd < submit && submit < stateEnd);

   const auto contextStart = section(
      contextSource,
      "void context::on_start_layer(::gpu::layer * pgpulayer)",
      "void context::on_end_layer(::gpu::layer * pgpulayer)");
   assert(contextStart.find("auto ptexturesite = pgpulayer->texture(true);") <
      contextStart.find("on_start_layer_before_begin_render(pgpulayer);"));

   const auto contextEnd = section(
      contextSource,
      "void context::on_end_layer(::gpu::layer * pgpulayer)",
      "void context::on_create_texture");
   assert(contextEnd.find("if (!pgpulayer->m_bExternalRendering)") <
      contextEnd.find("insert_gpu_fence(true)"));

   return 0;

}
