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


} // namespace


int main()
{

   const auto gpu = std::filesystem::path(__FILE__).parent_path().parent_path();
   const auto source = read(gpu / "renderer.cpp");
   const auto begin = source.find("void renderer::on_end_render(::gpu::layer * pgpulayer)");
   const auto end = source.find("void renderer::_on_begin_render", begin);

   assert(begin != std::string::npos);
   assert(end != std::string::npos);

   const auto onEndRender = source.substr(begin, end - begin);
   const auto firstSwapChainGuard = onEndRender.find(
      "if (m_papplication->m_gpu.m_bUseSwapChainWindow)");
   const auto secondSwapChainGuard = onEndRender.find(
      "if (m_papplication->m_gpu.m_bUseSwapChainWindow)",
      firstSwapChainGuard + 1);
   const auto layerEnd = onEndRender.find("pgpulayer->layer_end();");

   assert(firstSwapChainGuard != std::string::npos);
   assert(secondSwapChainGuard != std::string::npos);
   assert(layerEnd != std::string::npos);
   assert(layerEnd < secondSwapChainGuard);
   assert(onEndRender.find("pgpulayer->layer_end();", layerEnd + 1) ==
      std::string::npos);

   return 0;

}
