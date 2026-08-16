#include <cassert>
#include <fstream>
#include <sstream>
#include <string>


static std::string read_file(const char * path)
{

   std::ifstream stream(path, std::ios::binary);
   assert(stream);
   std::ostringstream output;
   output << stream.rdbuf();
   return output.str();

}


static std::string section(
   const std::string & source,
   const std::string & beginMarker,
   const std::string & endMarker)
{

   const auto begin = source.find(beginMarker);
   assert(begin != std::string::npos);
   const auto end = source.find(endMarker, begin + beginMarker.size());
   assert(end != std::string::npos);
   return source.substr(begin, end - begin);

}


int main()
{

   const auto source = read_file(
      "source/app/bred/user/user/graphics3d.cpp");
   const auto statistics = section(
      source,
      "void graphics3d::draw_gpu_statistics(",
      "void graphics3d::_001OnNcClip(");

   const auto attachmentLookup = statistics.find(
      "::gpu::window_attachment::get(this)");
   const auto serialDeclaration = statistics.find(
      "::collection::index iFrameSerial = -1;");
   const auto attachmentBranch = statistics.find(
      "if (pgpuwindowattachment)", serialDeclaration);
   const auto authoritativeSerial = statistics.find(
      "iFrameSerial = pgpuwindowattachment->m_iFrameSerial2;",
      attachmentBranch);
   const auto fallbackBranch = statistics.find(
      "else", authoritativeSerial);
   const auto fallbackCounter = statistics.find(
      "iFrameSerial = ++m_iFrameCounter;", fallbackBranch);
   const auto formattedSerial = statistics.find(
      "strText.formatf(\"øçåJErDgTBS__!!; %lld\", (::i64)iFrameSerial);",
      fallbackCounter);

   assert(attachmentLookup != std::string::npos);
   assert(serialDeclaration != std::string::npos);
   assert(attachmentLookup < serialDeclaration);
   assert(serialDeclaration < attachmentBranch);
   assert(attachmentBranch < authoritativeSerial);
   assert(authoritativeSerial < fallbackBranch);
   assert(fallbackBranch < fallbackCounter);
   assert(fallbackCounter < formattedSerial);
   assert(statistics.find("m_iCurrentFrame3") == std::string::npos);

   return 0;

}
