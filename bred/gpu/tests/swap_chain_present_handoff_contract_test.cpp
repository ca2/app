#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read(const std::filesystem::path & path)
   {

      std::ifstream stream(path);
      assert(stream);
      return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};

   }


   std::string section(const std::string & text, const std::string & begin, const std::string & end)
   {

      const auto first = text.find(begin);
      const auto last = text.find(end, first);
      assert(first != std::string::npos);
      assert(last != std::string::npos);
      return text.substr(first, last - first);

   }


} // namespace


int main()
{

   const auto gpu = std::filesystem::path(__FILE__).parent_path().parent_path();
   const auto source = read(gpu / "swap_chain.cpp");
   const auto output = section(
      source,
      "void swap_chain::do_output(::gpu::texture_site * pgputexturesite)",
      "void swap_chain::create_images()");

   const auto signalFinished = output.find(
      "pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(framesync.m_pgpusemaphoreRenderFinished);");
   const auto presentWait = output.find(
      "m_gpusemaphoreaWait.add_unique(framesync.m_pgpusemaphoreRenderFinished);");
   const auto submit = output.find(
      "pcommandbufferSwapChain.commit();");
   const auto present = output.find("\n            swap_buffers();");

   assert(signalFinished != std::string::npos);
   assert(presentWait != std::string::npos);
   assert(submit != std::string::npos);
   assert(present != std::string::npos);
   assert(signalFinished < presentWait);
   assert(presentWait < submit);
   assert(submit < present);

   return 0;

}
