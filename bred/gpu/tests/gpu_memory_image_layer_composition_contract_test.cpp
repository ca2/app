#include <cassert>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read_file(const char * pszPath)
   {

      std::ifstream stream(pszPath, std::ios::binary);

      return {
         std::istreambuf_iterator<char>(stream),
         std::istreambuf_iterator<char>()};

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
      assert(begin < end);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto layerHeader = read_file("bred/gpu/layer.h");
   const auto layerSource = read_file("bred/gpu/layer.cpp");
   const auto graphicsHeader = read_file("bred/gpu/graphics.h");
   const auto graphicsSource = read_file("bred/gpu/graphics.cpp");
   const auto rendererSource = read_file("bred/gpu/renderer.cpp");

   assert(layerHeader.find(
      "bool m_bIncludeInFrameComposition = true;") !=
      std::string::npos);

   const auto initializeLayer = section(
      layerSource,
      "void layer::initialize_gpu_layer(",
      "void layer::layer_start()");
   assert(initializeLayer.find(
      "m_bIncludeInFrameComposition = true;") !=
      std::string::npos);

   assert(graphicsHeader.find(
      "void on_start_layer_before_begin_render(::gpu::layer * pgpulayer) override;") !=
      std::string::npos);

   const auto imageLayerPolicy = section(
      graphicsSource,
      "void graphics::on_start_layer_before_begin_render(",
      "void graphics::on_begin_layer_scope()");
   assert(imageLayerPolicy.find(
      "::gpu::compositor::on_start_layer_before_begin_render(pgpulayer);") !=
      std::string::npos);
   assert(imageLayerPolicy.find("if (m_pimage)") != std::string::npos);
   assert(imageLayerPolicy.find(
      "pgpulayer->m_bIncludeInFrameComposition = false;") !=
      std::string::npos);
   assert(imageLayerPolicy.find("m_eoutput") == std::string::npos);
   assert(imageLayerPolicy.find("e_output_gpu_buffer") == std::string::npos);

   const auto rendererEndLayer = section(
      rendererSource,
      "void renderer::end_layer(bool bClosingLayer)",
      "void renderer::wait_swap_chain_command_buffer_ready()");
   const auto layerArraySnapshot = rendererEndLayer.find(
      "auto pgpulayera2 = m_pgpucontext->m_pgpudevice->m_pgpulayera;");
   const auto filterLoop = rendererEndLayer.find(
      "for (auto pgpulayer : *pgpulayera2)",
      layerArraySnapshot);
   const auto filterPredicate = rendererEndLayer.find(
      "pgpulayer->m_bIncludeInFrameComposition",
      filterLoop);
   const auto filteredAdd = rendererEndLayer.find(
      "gpulayera.add(pgpulayer);",
      filterPredicate);
   const auto completionWait = rendererEndLayer.find(
      "for (auto pgpulayer: gpulayera)",
      filteredAdd);
   const auto merge = rendererEndLayer.find(
      "merge_layers(pgpucommandbuffer, ptextureBackBuffer, &gpulayera);",
      completionWait);
   const auto semaphoreLoop = rendererEndLayer.find(
      "for (auto &pgpulayer: gpulayera)",
      merge);

   assert(layerArraySnapshot != std::string::npos);
   assert(filterLoop != std::string::npos);
   assert(filterPredicate != std::string::npos);
   assert(filteredAdd != std::string::npos);
   assert(completionWait != std::string::npos);
   assert(merge != std::string::npos);
   assert(semaphoreLoop != std::string::npos);
   assert(layerArraySnapshot < filterLoop);
   assert(filterLoop < filterPredicate);
   assert(filterPredicate < filteredAdd);
   assert(filteredAdd < completionWait);
   assert(completionWait < merge);
   assert(merge < semaphoreLoop);
   assert(rendererEndLayer.find("gpulayera = *pgpulayera2;") ==
      std::string::npos);
   const auto compositionFilter = rendererEndLayer.substr(
      layerArraySnapshot,
      completionWait - layerArraySnapshot);
   assert(compositionFilter.find("e_output_gpu_buffer") ==
      std::string::npos);

   return 0;

}
