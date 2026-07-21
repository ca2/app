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

   const auto leaseHeader = read_file("aura/graphics/draw2d/graphics_lease.h");
   const auto draw2dHeader = read_file("aura/graphics/draw2d/draw2d.h");
   const auto draw2dSource = read_file("aura/graphics/draw2d/draw2d.cpp");
   const auto graphicsHeader = read_file("aura/graphics/draw2d/graphics.h");

   assert(leaseHeader.find("graphics_lease(const graphics_lease &) = delete;") != std::string::npos);
   assert(leaseHeader.find("graphics_lease(graphics_lease &&") != std::string::npos);
   assert(leaseHeader.find("void close();") != std::string::npos);
   assert(draw2dHeader.find("acquire_memory_graphics") != std::string::npos);
   assert(draw2dHeader.find("acquire_image_graphics") != std::string::npos);
   assert(draw2dHeader.find("m_graphicsaMemoryPoolIdle") != std::string::npos);
   assert(graphicsHeader.find("on_acquire_memory_graphics") != std::string::npos);
   assert(graphicsHeader.find("on_release_memory_graphics") != std::string::npos);
   assert(draw2dSource.find("[draw2d.graphics_pool]") != std::string::npos);

   return 0;

}
