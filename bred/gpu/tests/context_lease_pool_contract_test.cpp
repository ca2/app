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

   const auto leaseHeader = read_file("bred/gpu/context_lease.h");
   const auto leaseSource = read_file("bred/gpu/context_lease.cpp");
   const auto deviceHeader = read_file("bred/gpu/device.h");
   const auto deviceSource = read_file("bred/gpu/device.cpp");

   assert(leaseHeader.find("context_lease(const context_lease &) = delete;") != std::string::npos);
   assert(leaseHeader.find("context_lease & operator=(const context_lease &) = delete;") != std::string::npos);
   assert(leaseHeader.find("context_lease(context_lease &&") != std::string::npos);
   assert(leaseHeader.find("void close();") != std::string::npos);
   assert(leaseHeader.find("void mark_damaged();") != std::string::npos);
   assert(leaseSource.find("return_draw2d_context") != std::string::npos);
   assert(deviceHeader.find("acquire_draw2d_context") != std::string::npos);
   assert(deviceHeader.find("m_contextaDraw2dIdle") != std::string::npos);
   assert(deviceSource.find("[gpu.context_pool]") != std::string::npos);
   assert(deviceSource.find("on_resize(size)") != std::string::npos);

   return 0;

}
