#include <cassert>
#include <fstream>
#include <iterator>
#include <string>


int main()
{

   std::ifstream stream("bred/gpu/device.cpp", std::ios::binary);

   const std::string source{
      std::istreambuf_iterator<char>(stream),
      std::istreambuf_iterator<char>()};

   const auto iStart = source.find("void device::start_frame()");
   const auto iEnd = source.find("void device::end_frame()", iStart);

   assert(iStart != std::string::npos);
   assert(iEnd != std::string::npos);

   const auto function = source.substr(iStart, iEnd - iStart);
   const auto iClear = function.find("m_postframecontextregistry.clear();");
   const auto iReset = function.find("start_stacking_layers();");
   const auto iNewFrame = function.find("m_pgpucontextMain->on_new_frame();");

   assert(iClear != std::string::npos);
   assert(iReset != std::string::npos);
   assert(iNewFrame != std::string::npos);
   assert(iClear < iReset);
   assert(iReset < iNewFrame);

   return 0;

}
