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
   const auto layerSource = read(gpu / "layer.cpp");

   const auto begin = layerSource.find("layer::texture(bool bRenderTarget)");
   const auto end = layerSource.find("return ptexturesite;", begin);

   assert(begin != std::string::npos);
   assert(end != std::string::npos);

   const auto texture = layerSource.substr(begin, end - begin);

   assert(texture.find(
      "textureflags.m_bWithDepth =\n"
      "            m_pgpurenderer->m_pgpucontext->m_escene == ::gpu::e_scene_3d;") !=
      std::string::npos);

   return 0;

}
