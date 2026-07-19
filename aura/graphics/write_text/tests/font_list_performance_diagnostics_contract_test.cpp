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

   const auto header = read_file("aura/graphics/write_text/font_list.h");
   const auto source = read_file("aura/graphics/write_text/font_list.cpp");

   assert(header.find("m_uPerformanceDrawPasses") != std::string::npos);
   assert(header.find("m_uPerformanceItemsExamined") != std::string::npos);
   assert(header.find("m_uPerformanceVisibleItems") != std::string::npos);
   assert(header.find("m_uPerformancePreviewUpdates") != std::string::npos);
   assert(header.find("m_uPerformanceCachedDraws") != std::string::npos);
   assert(source.find("gpu.performance.font_list") != std::string::npos);

   const auto wide = section(
      source,
      "void font_list::_001OnDrawWide(",
      "void font_list::_001OnDrawSingleColumn(");
   const auto single = section(
      source,
      "void font_list::_001OnDrawSingleColumn(",
      "void font_list::_001OnDraw(");

   assert(wide.find("record_font_item_examined()") != std::string::npos);
   assert(wide.find("record_visible_font_item()") != std::string::npos);
   assert(wide.find("record_font_preview_update(") != std::string::npos);
   assert(wide.find("record_cached_font_preview_draw(") != std::string::npos);
   assert(single.find("record_font_item_examined()") != std::string::npos);
   assert(single.find("record_visible_font_item()") != std::string::npos);
   assert(single.find("record_font_preview_update(") != std::string::npos);
   assert(single.find("record_cached_font_preview_draw(") != std::string::npos);

   return 0;

}
