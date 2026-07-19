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

   const auto header = read_file("gpu_opengl/texture.h");
   const auto source = read_file("gpu_opengl/texture.cpp");

   assert(header.find("void read_pixels(::pixmap * ppixmap) override;") !=
      std::string::npos);
   assert(header.find(
      "void write_pixels(const ::pixmap * ppixmap) override;") !=
      std::string::npos);

   const auto state = section(
      source,
      "class scoped_pixel_transfer_state",
      "GLenum pixmap_pixel_format(");
   assert(state.find("GL_READ_FRAMEBUFFER_BINDING") != std::string::npos);
   assert(state.find("GL_DRAW_FRAMEBUFFER_BINDING") != std::string::npos);
   assert(state.find("GL_RENDERBUFFER_BINDING") != std::string::npos);
   assert(state.find("GL_TEXTURE_BINDING_2D") != std::string::npos);
   assert(state.find("GL_PACK_ALIGNMENT") != std::string::npos);
   assert(state.find("GL_PACK_ROW_LENGTH") != std::string::npos);
   assert(state.find("GL_UNPACK_ALIGNMENT") != std::string::npos);
   assert(state.find("GL_UNPACK_ROW_LENGTH") != std::string::npos);

   const auto format = section(
      source,
      "GLenum pixmap_pixel_format(",
      "} // namespace");
   assert(format.find("GL_BGRA") != std::string::npos);
   assert(format.find("GL_RGBA") != std::string::npos);
   assert(format.find("error_not_supported") != std::string::npos);

   const auto read = section(
      source,
      "void texture::read_pixels(",
      "void texture::write_pixels(");
   assert(read.find("glBindFramebuffer(GL_READ_FRAMEBUFFER") !=
      std::string::npos);
   const auto attach = read.find("glFramebufferTexture2D(");
   const auto readFramebuffer = read.find("GL_READ_FRAMEBUFFER", attach);
   assert(attach != std::string::npos);
   assert(readFramebuffer != std::string::npos);
   assert(read.find("glCheckFramebufferStatus(GL_READ_FRAMEBUFFER)") !=
      std::string::npos);
   assert(read.find("glReadPixels(") != std::string::npos);
   assert(read.find("ppixmap->vertical_swap();") != std::string::npos);

   const auto write = source.substr(source.find("void texture::write_pixels("));
   assert(write.find("pixmapFlipped.copy(ppixmap);") != std::string::npos);
   assert(write.find("pixmapFlipped.vertical_swap();") != std::string::npos);
   assert(write.find("glTexSubImage2D(") != std::string::npos);
   assert(write.find("GL_UNPACK_ROW_LENGTH") != std::string::npos);

   return 0;

}
