#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read(const std::filesystem::path & path)
   {

      std::ifstream stream(path, std::ios::binary);
      assert(stream);
      return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};

   }


} // namespace


int main()
{

   const auto gpuOpenGl = std::filesystem::absolute(__FILE__).parent_path().parent_path();
   const auto header = read(gpuOpenGl / "wgl_context.h");
   const auto source = read(gpuOpenGl / "wgl_context.cpp");

   assert(header.find("critical_section m_criticalsectionContextCurrent;") !=
      std::string::npos);

   const auto constructorBegin = source.find("wgl_context::wgl_context()");
   const auto constructorEnd = source.find("wgl_context::~wgl_context()", constructorBegin);

   assert(constructorBegin != std::string::npos);
   assert(constructorEnd != std::string::npos);
   assert(source.substr(constructorBegin, constructorEnd - constructorBegin).find(
      "defer_create_synchronization();") != std::string::npos);

   const auto selectBegin = source.find("void wgl_context::select()");
   const auto selectEnd = source.find("void wgl_context::unselect()", selectBegin);
   const auto unselectEnd = source.find(
      "ATOM g_atomGlWindowClass", selectEnd);

   assert(selectBegin != std::string::npos);
   assert(selectEnd != std::string::npos);
   assert(unselectEnd != std::string::npos);

   const auto select = source.substr(selectBegin, selectEnd - selectBegin);
   const auto unselect = source.substr(selectEnd, unselectEnd - selectEnd);

   const auto ownershipGate = select.find("m_criticalsectionContextCurrent.lock();");
   const auto lock = select.find("synchronous_lock synchronouslock(");
   const auto ownershipCheck = select.find("if (m_taskindex)");
   const auto makeCurrent = select.find("wglMakeCurrent(m_hdc, m_hglrc)");
   const auto selected = select.find("m_bContextSelected = true;");
   const auto failureRelease = select.find(
      "m_criticalsectionContextCurrent.unlock();", selected);

   assert(ownershipGate != std::string::npos);
   assert(lock != std::string::npos);
   assert(ownershipCheck != std::string::npos);
   assert(makeCurrent != std::string::npos);
   assert(selected != std::string::npos);
   assert(failureRelease != std::string::npos);
   assert(ownershipGate < lock);
   assert(lock < ownershipCheck);
   assert(ownershipCheck < makeCurrent);
   assert(makeCurrent < selected);

   const auto unselectLock = unselect.find("synchronous_lock synchronouslock(");
   const auto releaseCurrent = unselect.find("wglMakeCurrent(nullptr, nullptr)");
   const auto clearSelected = unselect.find("m_bContextSelected = false;");
   const auto ownershipRelease = unselect.find(
      "m_criticalsectionContextCurrent.unlock();", clearSelected);

   assert(unselectLock != std::string::npos);
   assert(releaseCurrent != std::string::npos);
   assert(clearSelected != std::string::npos);
   assert(ownershipRelease != std::string::npos);
   assert(unselectLock < releaseCurrent);
   assert(releaseCurrent < clearSelected);
   assert(clearSelected < ownershipRelease);

   return 0;

}
