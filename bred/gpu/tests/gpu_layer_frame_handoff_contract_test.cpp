#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read(const std::filesystem::path & path)
   {

      std::ifstream stream(path);
      assert(stream);
      return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};

   }


   std::string section(const std::string & text, const std::string & begin, const std::string & end)
   {

      const auto first = text.find(begin);
      const auto last = text.find(end, first);
      assert(first != std::string::npos);
      assert(last != std::string::npos);
      return text.substr(first, last - first);

   }


} // namespace


int main()
{

   const auto gpu = std::filesystem::path(__FILE__).parent_path().parent_path();
   const auto layerHeader = read(gpu / "layer.h");
   const auto layerSource = read(gpu / "layer.cpp");
   const auto rendererSource = read(gpu / "renderer.cpp");
   const auto renderTargetSource = read(gpu / "render_target.cpp");

   assert(layerHeader.find("m_ptextureDrawing") != std::string::npos);
   assert(layerHeader.find("m_ptextureReady") != std::string::npos);
   assert(layerHeader.find("m_mutexTextureSnapshot") != std::string::npos);
   assert(layerHeader.find("m_iFrameIndexReady") != std::string::npos);
   assert(layerHeader.find("::pointer < ::gpu::texture > composition_texture()") != std::string::npos);

   const auto initialize = section(
      layerSource,
      "void layer::initialize_gpu_layer(",
      "void layer::layer_start()");
   const auto selectFrame = initialize.find("m_iFrameIndex = iFrameIndex;");
   const auto releaseDrawing = initialize.find("m_ptextureDrawing.release();");
   assert(selectFrame != std::string::npos);
   assert(releaseDrawing != std::string::npos);
   assert(selectFrame < releaseDrawing);

   const auto texture = section(
      layerSource,
      "::pointer < texture >& layer::texture(bool bRenderTarget)",
      "::pointer < texture >& layer::source_texture()");
   assert(texture.find("auto & ptexture = m_ptextureDrawing;") != std::string::npos);
   assert(texture.find("m_texturea.element_at_grow") == std::string::npos);
   assert(texture.find("get_frame_index3()") == std::string::npos);

   const auto completion = section(
      layerSource,
      "void layer::layer_on_after_submit()",
      "::pointer < texture >& layer::texture(bool bRenderTarget)");
   const auto waitForCopy = completion.find("pgpufence->wait_gpu_fence();");
   const auto publishReadyTexture = completion.find("m_ptextureReady = m_ptextureDrawing;");
   const auto publishCompletion = completion.find("finished_manual_reset_happening()->set_happening();");
   assert(waitForCopy != std::string::npos);
   assert(publishReadyTexture != std::string::npos);
   assert(publishCompletion != std::string::npos);
   assert(waitForCopy < publishReadyTexture);
   assert(publishReadyTexture < publishCompletion);

   const auto compositionTexture = section(
      layerSource,
      "::pointer < ::gpu::texture > layer::composition_texture()",
      "::pointer < texture >& layer::source_texture()");
   assert(compositionTexture.find("m_mutexTextureSnapshot") != std::string::npos);
   assert(compositionTexture.find("return m_ptextureReady;") != std::string::npos);

   const auto copy = section(
      rendererSource,
      "void renderer::layer_end_copy()",
      "void renderer::layer_end_submit()");
   assert(copy.find("m_gpusemaphoreaLayerReady") == std::string::npos);
   assert(copy.find("&pgpulayer->m_pgpufence,\n            nullptr") != std::string::npos);

   const auto compose = section(
      renderTargetSource,
      "::gpu::texture * render_target::do_render()",
      "void render_target::initialize_render_target");
   assert(compose.find("m_gpusemaphoreaLayerReady") == std::string::npos);

   return 0;

}
