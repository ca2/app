#include <cassert>
#include <fstream>
#include <iterator>
#include <string>


std::string read_file(const char * pszPath)
{

   std::ifstream stream(pszPath, std::ios::binary);

   return {
      std::istreambuf_iterator<char>(stream),
      std::istreambuf_iterator<char>()};

}


int main()
{

   const auto applicationHeader = read_file("acme/platform/application.h");
   const auto engineHeader = read_file("bred/graphics3d/engine.h");
   const auto engineSource = read_file("bred/graphics3d/engine.cpp");

   assert(applicationHeader.find(
      "m_bPerformanceDiagnostics{false};") !=
      std::string::npos);
   assert(applicationHeader.find(
      "m_iPerformanceDiagnosticsIntervalMilliseconds{1000};") !=
      std::string::npos);
   assert(applicationHeader.find(
      "m_uPerformanceDiagnosticsGeneration{0};") !=
      std::string::npos);

   assert(engineHeader.find(
      "void set_gpu_performance_diagnostics(bool bEnabled);") !=
      std::string::npos);
   assert(engineHeader.find(
      "bool gpu_performance_diagnostics_enabled() const;") !=
      std::string::npos);
   assert(engineHeader.find(
      "void set_gpu_performance_diagnostics_interval(::i32 iMilliseconds);") !=
      std::string::npos);
   assert(engineHeader.find(
      "::i32 gpu_performance_diagnostics_interval() const;") !=
      std::string::npos);

   assert(engineSource.find(
      "maximum(100, minimum(60'000, iMilliseconds))") !=
      std::string::npos);
   assert(engineSource.find(
      "m_gpu.m_bPerformanceDiagnostics.exchange(") !=
      std::string::npos);
   assert(engineSource.find(
      "m_gpu.m_iPerformanceDiagnosticsIntervalMilliseconds.store(") !=
      std::string::npos);
   assert(engineSource.find(
      "m_gpu.m_uPerformanceDiagnosticsGeneration.fetch_add(") !=
      std::string::npos);
   assert(engineSource.find("::std::memory_order_relaxed") !=
      std::string::npos);

   return 0;

}
