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


} // namespace


int main()
{

   const auto gpu = std::filesystem::absolute(__FILE__).parent_path().parent_path();
   const auto source = read(gpu / "image.cpp");

   const auto unmapBegin = source.find(
      "void image::_unmap(::image_pixmap_lease * pimagepixmaplease)");
   const auto unmapEnd = source.find("void image::on_load_image(", unmapBegin);

   assert(unmapBegin != std::string::npos);
   assert(unmapEnd != std::string::npos);

   const auto unmap = source.substr(unmapBegin, unmapEnd - unmapBegin);
   const auto dispatch = unmap.find("pgpucontext->send(");
   const auto contextLock = unmap.find("::gpu::context_lock contextlock(pgpucontext);");
   const auto upload = unmap.find(
      "pgputexture->write_pixels(pthis->m_ppixmapOwned, {});");
   const auto fence = unmap.find("pgputexture->defer_fence();", upload);

   assert(dispatch != std::string::npos);
   assert(contextLock != std::string::npos);
   assert(upload != std::string::npos);
   assert(fence != std::string::npos);
   assert(dispatch < contextLock);
   assert(contextLock < upload);
   assert(upload < fence);

   return 0;

}
