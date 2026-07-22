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

   const auto header = read_file("aura/graphics/draw2d/draw2d.h");
   const auto source = read_file("aura/graphics/draw2d/draw2d.cpp");

   assert(header.find("virtual bool write_text_supports_raster_fonts();") != std::string::npos);
   assert(header.find("virtual bool write_text_supports_legacy_gdi_fonts();") != std::string::npos);
   assert(source.find("bool draw2d::write_text_supports_raster_fonts()") != std::string::npos);

   const auto capability = source.find("bool draw2d::write_text_supports_raster_fonts()");
   const auto nextMethod = source.find("bool draw2d::graphics_context_supports_single_buffer_mode()", capability);

   assert(capability != std::string::npos);
   assert(nextMethod != std::string::npos);

   const auto implementation = source.substr(capability, nextMethod - capability);

   assert(implementation.find("return true;") != std::string::npos);

   const auto legacyCapability = source.find("bool draw2d::write_text_supports_legacy_gdi_fonts()");
   const auto methodAfterLegacyCapability = source.find(
      "bool draw2d::graphics_context_supports_single_buffer_mode()",
      legacyCapability);

   assert(legacyCapability != std::string::npos);
   assert(methodAfterLegacyCapability != std::string::npos);

   const auto legacyImplementation = source.substr(
      legacyCapability,
      methodAfterLegacyCapability - legacyCapability);

   assert(legacyImplementation.find("return true;") != std::string::npos);

   return 0;

}
