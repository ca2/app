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

   return 0;

}
