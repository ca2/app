#include <cassert>
#include <fstream>
#include <iterator>
#include <string>

static std::string read(const char * path)
{
   std::ifstream file(path, std::ios::binary);
   assert(file.good());
   return {std::istreambuf_iterator<char>(file), {}};
}

// Source-contract test. Run from source/app; does not replace the UI retest.
int main()
{
   const auto enumeration = read("aura/graphics/write_text/font_enumeration.cpp");
   const auto list = read("aura/graphics/write_text/font_list.cpp");
   const auto color = read("core/graphics/color_selector.cpp");
   assert(enumeration.find("[font.enumeration] failed; partial_count=") != std::string::npos);
   assert(enumeration.find("[font.enumeration] finished count=") != std::string::npos);
   assert(list.find("[font.extent] failed family=") != std::string::npos);
   assert(list.find("[font.list.load] begin enumerated=") != std::string::npos);
   assert(list.find(" populated=") != std::string::npos);
   assert(list.find(" first_missing=") != std::string::npos);
   assert(list.find("[font.list.load] layout_finished total_width=") != std::string::npos);
   const auto measurement = list.find("static ::f64_size font_enumeration_get_text_extent(");
   const auto failure = list.find("catch (const ::exception & exception)", measurement);
   assert(list.find("throw;", failure) < list.find("static ::i64 font_list_performance_steady_nanoseconds()", failure));
   // Replacing the image must invalidate the cached H/S, or an unchanged color
   // causes rebuild_luminance() to return without writing the new allocation.
   const auto allocation = color.find("m_pimageLuminance = image()->create_image({ m_rectangleColors.width() / 8,");
   assert(allocation != std::string::npos);
   const auto pending = color.find("m_bPendingLuminanceRebuild = true;", allocation);
   assert(color.find("m_dLastLuminanceH = -1.0;", allocation) < pending);
   assert(color.find("m_dLastLuminanceS = -1.0;", allocation) < pending);
}
