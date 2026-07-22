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

      auto begin = source.find(beginMarker);
      assert(begin != std::string::npos);

      auto end = source.find(endMarker, begin + beginMarker.size());
      assert(end != std::string::npos);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto source = read_file("gpu_opengl/renderer.cpp");
   const auto beginRender = section(
      source,
      "void renderer::_on_begin_render(::gpu::layer * pgpulayer)",
      "void renderer::on_begin_render(");

   assert(beginRender.find(
      "m_pgpucontext->current_target_texture(pgpulayer)") !=
      std::string::npos);
   assert(beginRender.find(
      "pgpurendertarget->current_texture(pgpulayer)") ==
      std::string::npos);

   return 0;

}
