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

   const auto header = read_file("bred/gpu/graphics.h");
   const auto source = read_file("bred/gpu/graphics.cpp");

   assert(header.find("m_pgpulayerBeforeLayerScope") != std::string::npos);
   assert(header.find("void on_begin_layer_scope() override;") != std::string::npos);
   assert(header.find("void on_end_layer_scope() override;") != std::string::npos);
   assert(source.find("::gpu::current_layer()") != std::string::npos);
   assert(source.find("::gpu::set_current_layer") != std::string::npos);
   assert(source.find("::draw2d::graphics::on_begin_layer_scope()") != std::string::npos);
   assert(source.find("::draw2d::graphics::on_end_layer_scope()") != std::string::npos);

   return 0;

}
