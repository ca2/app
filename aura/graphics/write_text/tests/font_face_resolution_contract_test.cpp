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

   const auto face = read_file("aura/graphics/write_text/font_face.h");
   const auto header = read_file("aura/graphics/write_text/write_text.h");
   const auto source = read_file("aura/graphics/write_text/write_text.cpp");

   assert(face.find("struct CLASS_DECL_AURA font_face_request") != std::string::npos);
   assert(face.find("m_strFamily") != std::string::npos);
   assert(face.find("m_fontweight") != std::string::npos);
   assert(face.find("m_bItalic") != std::string::npos);
   assert(face.find("struct CLASS_DECL_AURA font_face_source") != std::string::npos);
   assert(face.find("m_path") != std::string::npos);
   assert(face.find("m_iFaceIndex") != std::string::npos);
   assert(face.find("m_strResolvedFamily") != std::string::npos);
   assert(header.find("virtual bool resolve_font_face(") != std::string::npos);
   assert(source.find("write_text::resolve_font_face(") != std::string::npos);
   assert(source.find("get_font_path_from_name") != std::string::npos);
   assert(source.find("m_iFaceIndex = 0") != std::string::npos);

   return 0;

}
