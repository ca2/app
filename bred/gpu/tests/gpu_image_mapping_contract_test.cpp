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


   std::string section(
      const std::string & source,
      const std::string & beginMarker,
      const std::string & endMarker)
   {

      const auto begin = source.find(beginMarker);
      const auto end = source.find(endMarker, begin);

      assert(begin != std::string::npos);
      assert(end != std::string::npos);
      assert(begin < end);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto textureHeader = read_file("bred/gpu/texture.h");
   const auto textureSource = read_file("bred/gpu/texture.cpp");
   const auto imageSource = read_file("bred/gpu/image.cpp");

   assert(textureHeader.find(
      "virtual void read_pixels(::pixmap * ppixmap);") !=
      std::string::npos);
   assert(textureHeader.find(
      "virtual void write_pixels(const ::pixmap * ppixmap);") !=
      std::string::npos);

   const auto baseRead = section(
      textureSource,
      "void texture::read_pixels(",
      "void texture::write_pixels(");
   const auto baseWrite = section(
      textureSource,
      "void texture::write_pixels(",
      "bool texture::is_in_shader_sampling_state(");
   assert(baseRead.find("throw ::not_implemented();") != std::string::npos);
   assert(baseWrite.find("throw ::not_implemented();") != std::string::npos);

   const auto getGraphics = section(
      imageSource,
      "::draw2d::graphics * image::get_graphics() const",
      "::gpu::texture * image::gpu_texture() const");
   assert(getGraphics.find("unmap();") != std::string::npos);
   assert(getGraphics.find("return _get_graphics();") != std::string::npos);

   const auto map = section(
      imageSource,
      "void image::map(",
      "void image::unmap()");
   const auto sendRead = map.find("pgpucontext->send(");
   const auto wait = map.find("wait_fence();", sendRead);
   const auto staging = map.find("pixmap::create(", wait);
   const auto stagingMemory = map.find("m_memoryMap", staging);
   const auto read = map.find("read_pixels(pthis);", stagingMemory);
   const auto mapped = map.find("m_bMapped = true;", read);
   assert(sendRead != std::string::npos);
   assert(wait != std::string::npos);
   assert(staging != std::string::npos);
   assert(stagingMemory != std::string::npos);
   assert(read != std::string::npos);
   assert(mapped != std::string::npos);
   assert(sendRead < wait && wait < staging && staging < stagingMemory &&
      stagingMemory < read && read < mapped);
   assert(map.find("throw ::not_implemented") == std::string::npos);
   assert(map.find("if (m_bMapped)") <
      map.find("m_bPerformanceDiagnostics"));
   assert(map.find("read_pixels(pthis);") <
      map.find("record_performance_map_transition("));

   const auto unmap = imageSource.substr(
      imageSource.find("void image::unmap()"));
   const auto sendWrite = unmap.find("pgpucontext->send(");
   const auto write = unmap.find("write_pixels(pthis);", sendWrite);
   const auto fence = unmap.find("defer_fence();", write);
   const auto pixmapUnmap = unmap.find("pixmap::unmap();", fence);
   const auto unmapped = unmap.find("m_bMapped = false;", pixmapUnmap);
   assert(sendWrite != std::string::npos);
   assert(write != std::string::npos);
   assert(fence != std::string::npos);
   assert(pixmapUnmap != std::string::npos);
   assert(unmapped != std::string::npos);
   assert(sendWrite < write && write < fence && fence < pixmapUnmap &&
      pixmapUnmap < unmapped);
   assert(unmap.find("throw ::not_implemented") == std::string::npos);
   assert(unmap.find("if (!m_bMapped)") <
      unmap.find("m_bPerformanceDiagnostics"));
   assert(unmap.find("write_pixels(pthis);") <
      unmap.find("record_performance_unmap_transition("));

   assert(imageSource.find("gpu.performance.image_mapping") !=
      std::string::npos);
   assert(imageSource.find("m_uPerformanceMapGeneration") !=
      std::string::npos);
   assert(imageSource.find("current_task_name()") !=
      std::string::npos);
   assert(imageSource.find("s_uMapTransitionSequence.fetch_add") !=
      std::string::npos);
   assert(imageSource.find("< 64") != std::string::npos);

   return 0;

}
