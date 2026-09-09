#include <fstream>
#include <iterator>
#include <string>
#include <cstdio>
#include <cstdlib>

static void require(bool ok, const char * message)
{
   if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}
static std::string read(const char * path)
{
   std::ifstream file(path, std::ios::binary);
   require(file.good(), path);
   return {std::istreambuf_iterator<char>(file), {}};
}
static std::string section(const std::string & text, const char * begin, const char * end)
{
   const auto a = text.find(begin), b = text.find(end, a + 1);
   require(a != std::string::npos && b != std::string::npos, begin);
   return text.substr(a, b - a);
}
static void ordered(const std::string & text, const char * first, const char * second)
{
   const auto a = text.find(first), b = text.find(second);
   require(a != std::string::npos && b != std::string::npos && a < b, first);
}

int main()
{
   // Run from the SceneFoundry main workspace.
   const auto allocation = section(read("source/app/bred/gpu/draw2d.cpp"),
      "::draw2d::graphics_pointer draw2d::do_allocation_strategy(", "} // namespace gpu");
   require(allocation.find("return create_memory_graphics(size, pacmeuserinteractionAffinity);") != std::string::npos,
      "GPU allocation must initialize the context with the requested size and affinity");
   require(allocation.find("create_from_graphics(") == std::string::npos,
      "GPU allocation must not snapshot unbound graphics into the destination image");
   const auto acquire = section(read("source/app/aura/graphics/draw2d/draw2d.cpp"),
      "::draw2d::graphics_lease draw2d::_acquire_memory_graphics(",
      "::draw2d::graphics_lease draw2d::acquire_image_graphics(");
   ordered(acquire, "do_allocation_strategy(pacmeuserinteractionAffinity, pimage, size)",
      "on_acquire_memory_graphics(bExternalRendering, pimage, size, pacmeuserinteractionAffinity)");
   const auto binding = section(read("source/app/bred/gpu/graphics.cpp"),
      "void graphics::on_acquire_memory_graphics(", "void graphics::on_release_memory_graphics()");
   ordered(binding, "pimage->update_bitmap_as_render_target(", "set_target_image(pimage);");
   ordered(binding, "pimage->m_eacquire == ::draw2d::e_acquire_load", "defer_write_pixels(");
   require(binding.find("m_pgputexturesiteTarget->m_pgputextureSite = pgpubitmap->gpu_texture(") != std::string::npos,
      "Graphics must render into the requested image's GPU texture");
   const auto imageTransition = section(read("source/app/bred/gpu/graphics.cpp"),
      "auto pgpucommandbufferState = pcontext->beginSingleTimeCommands();",
      "set_gpu_shader(pgpucommandbuffer, pgpushaderImage);");
   ordered(imageTransition,
      "pgputextureSource->set_state(pgpucommandbufferState, ::gpu::e_texture_state_shader_read);",
      "pgpucommandbufferState.commit();");
   require(imageTransition.find("pgpucommandbufferState.commit();") < imageTransition.find('}'),
      "The source transition must be committed before the lease leaves scope and cancels");
   std::puts("GPU image allocation and source-transition submission contracts passed.");
}
