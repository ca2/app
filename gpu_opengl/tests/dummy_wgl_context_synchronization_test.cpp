#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>


namespace
{


   std::string read_text(const std::filesystem::path & path)
   {

      std::ifstream stream(path, std::ios::binary);
      assert(stream.is_open());

      std::ostringstream output;
      output << stream.rdbuf();
      return output.str();

   }


   std::string function_body(
      const std::string & source,
      const std::string & signature,
      const std::string & nextSignature)
   {

      const auto begin = source.find(signature);
      assert(begin != std::string::npos);

      const auto end = source.find(nextSignature, begin + signature.size());
      assert(end != std::string::npos);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto testPath = std::filesystem::absolute(__FILE__);
   const auto gpuOpenGlPath = testPath.parent_path().parent_path();

   const auto approach = read_text(gpuOpenGlPath / "approach.cpp");
   const auto wglHeader = read_text(gpuOpenGlPath / "wgl_context.h");
   const auto wglSource = read_text(gpuOpenGlPath / "wgl_context.cpp");

   const auto initialize = function_body(
      approach,
      "void approach::initialize(",
      "void approach::defer_init_gpu_library(");

   assert(initialize.find("defer_create_synchronization();") !=
      std::string::npos);

   const auto getter = function_body(
      approach,
      "approach::dummy_wgl_context()",
      "//void approach::gpu_on_before_create_window");

   const auto getterLock = getter.find(
      "synchronous_lock synchronouslock(this->synchronization()");
   const auto getterCheck = getter.find("if (!m_pwglcontextDummy)");
   const auto getterCreate = getter.find(
      "m_pwglcontextDummy->create_dummy_wgl_context();");

   assert(getterLock != std::string::npos);
   assert(getterCheck != std::string::npos);
   assert(getterCreate != std::string::npos);
   assert(getterLock < getterCheck);
   assert(getterCheck < getterCreate);

   const auto createContext = function_body(
      wglSource,
      "void wgl_context::_create_wgl_context(",
      "void wgl_context::create_offscreen_wgl_context(");

   const auto shareLock = createContext.find(
      "synchronous_lock synchronouslock(pgpuapproach->synchronization()");
   const auto rootGuard = createContext.find(
      "if (!pgpuapproach->m_hglrcShare)");
   const auto rootCreate = createContext.find(
      "wglCreateContextAttribsARB(m_hdc, nullptr, contextAttribs)");
   const auto rootAssign = createContext.find(
      "pgpuapproach->m_hglrcShare = hglrcShare;");
   const auto childCreate = createContext.find(
      "wglCreateContextAttribsARB(m_hdc, pgpuapproach->m_hglrcShare, contextAttribs)");

   assert(shareLock != std::string::npos);
   assert(rootGuard != std::string::npos);
   assert(rootCreate != std::string::npos);
   assert(rootAssign != std::string::npos);
   assert(childCreate != std::string::npos);
   assert(shareLock < rootGuard);
   assert(rootGuard < rootCreate);
   assert(rootCreate < rootAssign);
   assert(rootAssign < childCreate);
   assert(createContext.find("pgpuapproach->m_hglrcShare = hglrc;") ==
      std::string::npos);

   const auto approachDestructor = function_body(
      approach,
      "approach::~approach()",
      "void approach::initialize(");

   const auto destructorLock = approachDestructor.find(
      "synchronous_lock synchronouslock(this->synchronization()");
   const auto rootDelete = approachDestructor.find(
      "wglDeleteContext(m_hglrcShare)");
   const auto rootClear = approachDestructor.find(
      "m_hglrcShare = nullptr;");

   assert(destructorLock != std::string::npos);
   assert(rootDelete != std::string::npos);
   assert(rootClear != std::string::npos);
   assert(destructorLock < rootDelete);
   assert(rootDelete < rootClear);

   assert(wglHeader.find(
      "#include \"acme/parallelization/synchronous_lock.h\"") !=
      std::string::npos);
   assert(wglHeader.find(
      "::pointer < ::gpu_opengl::approach > m_pgpuapproach;") !=
      std::string::npos);
   assert(wglHeader.find("synchronous_lock m_synchronouslock;") !=
      std::string::npos);

   const auto scopedConstructor = function_body(
      wglSource,
      "scoped_dummy_wgl_context::scoped_dummy_wgl_context(",
      "scoped_dummy_wgl_context::~scoped_dummy_wgl_context(");

   const auto approachMember = scopedConstructor.find("m_pgpuapproach(");
   const auto lifetimeLock = scopedConstructor.find(
      "m_synchronouslock(m_pgpuapproach->synchronization()");
   const auto select = scopedConstructor.find(
      "pwglcontextDummy->select();");
   const auto loadExtensions = scopedConstructor.find(
      "defer_load_wgl_extensions(pparticle);");
   const auto cleanup = scopedConstructor.find("catch (...)");
   const auto cleanupUnselect = scopedConstructor.find(
      "pwglcontextDummy->unselect();", cleanup);

   assert(approachMember != std::string::npos);
   assert(lifetimeLock != std::string::npos);
   assert(select != std::string::npos);
   assert(loadExtensions != std::string::npos);
   assert(cleanup != std::string::npos);
   assert(cleanupUnselect != std::string::npos);
   assert(approachMember < lifetimeLock);
   assert(lifetimeLock < select);
   assert(select < loadExtensions);

   const auto scopedDestructor = wglSource.substr(
      wglSource.find("scoped_dummy_wgl_context::~scoped_dummy_wgl_context("));

   assert(scopedDestructor.find(
      "m_pgpuapproach->dummy_wgl_context()->unselect();") !=
      std::string::npos);

   return 0;

}
