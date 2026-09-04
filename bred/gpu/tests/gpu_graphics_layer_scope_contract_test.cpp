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
   assert(source.find("if (::is_set(puserinteractionContext))") != std::string::npos);
   assert(source.find("window_attachment::get(puserinteraction)") != std::string::npos);
   assert(source.find("GPU graphics layer has no window attachment.") != std::string::npos);
   assert(source.find("m_pointTarget = rectangleFrame.origin();") != std::string::npos);
   assert(source.find("m_sizeTarget = rectangleFrame.size();") != std::string::npos);

   return 0;

}
