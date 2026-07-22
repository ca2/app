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

   const auto source = read_file("aura/graphics/write_text/font_list.cpp");
   const auto textBoxSource = read_file("aura/graphics/write_text/text_box.cpp");

   const auto updateExtents = section(
      source,
      "void font_list::update_extents()",
      "void font_list::layout()");
   const auto textBoxUpdate = section(
      textBoxSource,
      "void text_box::update(",
      "} // namespace write_text");

   assert(updateExtents.find("acquire_memory_graphics") != std::string::npos);
   assert(updateExtents.find("fork_count") == std::string::npos);
   assert(updateExtents.find("create_memory_graphics") == std::string::npos);
   assert(updateExtents.find("update_extents(pfontlistdata, plistitem, pgraphics") != std::string::npos);
   assert(updateExtents.find("begin_layer_scope") == std::string::npos);
   assert(textBoxUpdate.find("acquire_graphics") != std::string::npos);
   assert(textBoxUpdate.find("auto layerscope = graphicslease.begin_layer_scope()") != std::string::npos);
   assert(textBoxUpdate.find("layerscope.close();") != std::string::npos);
   assert(textBoxUpdate.find("m_pimage->g()") == std::string::npos);
   assert(source.find("[gpu.performance.font_enumeration]") != std::string::npos);

   return 0;

}
