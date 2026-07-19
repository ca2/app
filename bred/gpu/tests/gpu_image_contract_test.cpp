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


} // namespace


int main()
{

   const auto header = read_file("bred/gpu/image.h");
   const auto source = read_file("bred/gpu/image.cpp");
   const auto renderer = read_file("bred/gpu/renderer.cpp");
   const auto cmake = read_file("bred/CMakeLists.txt");
   const auto project = read_file("bred/bred.vcxproj");

   assert(header.find("virtual public ::image::image") != std::string::npos);
   assert(header.find("::pointer < ::gpu::texture > m_pgputexture;") !=
      std::string::npos);
   assert(header.find("::gpu::texture * gpu_texture() const;") !=
      std::string::npos);
   assert(header.find("void initialize_gpu_image(") != std::string::npos);
   assert(header.find("::draw2d::graphics * get_graphics() const override;") !=
      std::string::npos);

   assert(source.find("return _get_graphics();") != std::string::npos);
   assert(source.find("throw ::not_implemented();") == std::string::npos);
   assert(source.find("m_pgputexture =") != std::string::npos);

   const auto destroy = source.find("void image::destroy()");
   const auto destroyGraphics = source.find(
      "::image::image::destroy();", destroy);
   const auto destroyTexture = source.find(
      "m_pgputexture.release();", destroy);
   assert(destroy != std::string::npos);
   assert(destroyGraphics != std::string::npos);
   assert(destroyTexture != std::string::npos);
   assert(destroyGraphics < destroyTexture);

   const auto createImageTexture = renderer.find(
      "renderer::create_image_texture");
   assert(createImageTexture != std::string::npos);
   const auto renderTarget = renderer.find(
      "textureflags.m_bRenderTarget = true;", createImageTexture);
   const auto shaderResource = renderer.find(
      "textureflags.m_bShaderResource = true;", createImageTexture);
   assert(renderTarget != std::string::npos);
   assert(shaderResource != std::string::npos);

   assert(cmake.find("gpu/image.cpp") != std::string::npos);
   assert(cmake.find("gpu/image.h") != std::string::npos);
   assert(project.find("gpu\\image.cpp") != std::string::npos);
   assert(project.find("gpu\\image.h") != std::string::npos);

   return 0;

}
