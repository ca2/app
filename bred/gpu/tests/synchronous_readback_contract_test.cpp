#include <fstream>
#include <iterator>
#include <string>
#include <cstdio>
#include <cstdlib>

static void require(bool ok, const char *message) {
   if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}
static std::string read(const char *path) {
   std::ifstream input(path, std::ios::binary);
   require(input.good(), path);
   return {std::istreambuf_iterator<char>(input), {}};
}
static std::string section(const std::string &source, const char *start, const char *end) {
   const auto first = source.find(start);
   require(first != std::string::npos, start);
   const auto last = source.find(end, first + 1);
   require(last != std::string::npos, end);
   return source.substr(first, last - first);
}
static void ordered(const std::string &source, const char *a, const char *b) {
   const auto first = source.find(a), last = source.find(b);
   require(first != std::string::npos && last != std::string::npos && first < last, a);
}
int main() {
   // Run from the SceneFoundry main workspace.
   const auto texture = read("source/app-graphics3d/gpu_vulkan/texture.cpp");
   const auto pixels = section(texture, "void texture::read_pixels(", "void texture::generate_mipmap(");
   const char *rawSignature = "void texture::read_pixels(::gpu::command_buffer * commands,";
   const char *commit = "commands->m_pgpucommandbufferlease->commit();";
   require(pixels.find(rawSignature) != std::string::npos,
           "readback must accept a raw command buffer pointer");
   ordered(pixels, "!commands || !commands->m_pgpucommandbufferlease", "_record_readback(");
   ordered(pixels, "_record_readback(commands, pbuffer, pointOutput, ppixmap->size());", commit);
   ordered(pixels, commit, "vkMapMemory(");
   ordered(pixels, "vkMapMemory(", "vkInvalidateMappedMemoryRanges(");
   ordered(pixels, "vkInvalidateMappedMemoryRanges(", "ppixmap->copy(");
   require(pixels.find("unmap_guard") != std::string::npos, "mapping must be exception safe");
   const auto record = section(texture, "void texture::_record_readback(", "::gpu::buffer * texture::get_read_back_buffer(");
   require(record.find(".width = (uint32_t)sizeRead.cx") != std::string::npos &&
           record.find(".height = (uint32_t)sizeRead.cy") != std::string::npos,
           "copy extent must match destination, not the full source texture");
   require(record.find("bytes > pbuffer->m_size") != std::string::npos,
           "readback buffer bounds must be checked");
   ordered(record, "vkCmdCopyImageToBuffer(", "hostRead.dstAccessMask = VK_ACCESS_HOST_READ_BIT;");
   const auto context = read("source/app-graphics3d/gpu_vulkan/context.cpp");
   const auto endCommands = section(context, "void context::_endSingleTimeCommands(", "//endSingleTimeCommands(");
   ordered(endCommands, "submit_command_buffer(nullptr);", "wait_gpu_fence();");
   const auto engine = read("source/app/bred/graphics3d/engine_instance.cpp");
   for (const auto &caller : {engine, read("source/app/bred/gpu/image.cpp")}) {
      const auto at = caller.find("pgputexture->read_pixels(pgpucommandbuffer,");
      require(at != std::string::npos, "readback caller missing");
      require(caller.substr(at, 240).find("pgpucommandbuffer.commit();") == std::string::npos,
              "caller must not submit the consumed lease a second time");
   }
   require(engine.find("graphics3d draw_layer failed: impact_serial=") != std::string::npos,
           "render failure must identify the affected impact");
   require(engine.find("catch (const ::exception & e)") != std::string::npos &&
           engine.find("catch (const ::std::exception & e)") != std::string::npos &&
           engine.find("reportFailure(\"Unknown rendering exception\")") != std::string::npos,
           "render failure types must not be silently swallowed");
   require(engine.find("detail != lastError.as_string()") != std::string::npos,
           "repeated failures must not flood the log");
   const auto gl = read("source/app/gpu_opengl/texture.cpp");
   const auto glRead = section(gl, "void texture::read_pixels(", "void texture::");
   require(glRead.find(rawSignature) != std::string::npos, "OpenGL must use the raw-pointer API too");
   ordered(glRead, "!commands || !commands->m_pgpucommandbufferlease", commit);
   ordered(glRead, commit, "glReadPixels(");

   const auto lease = read("source/app/bred/gpu/command_buffer_lease.cpp");
   const auto createLease = section(lease, "command_buffer_lease::command_buffer_lease(::pointer", "command_buffer_lease::command_buffer_lease(command_buffer_lease &&");
   ordered(createLease, "if (m_pgpucommandbuffer->m_pgpucommandbufferlease)", "m_pgpucommandbuffer->m_pgpucommandbufferlease = this;");
   const auto moveLease = section(lease, "command_buffer_lease::command_buffer_lease(command_buffer_lease &&", "command_buffer_lease::~command_buffer_lease()");
   ordered(moveLease, "::transfer(commandbufferlease.m_pgpucommandbuffer)", "m_pgpucommandbuffer->m_pgpucommandbufferlease = this;");
   const auto commitLease = section(lease, "void command_buffer_lease::commit()", "void command_buffer_lease::cancel()");
   ordered(commitLease, "::transfer(m_pgpucommandbuffer)", "pgpucommandbuffer->m_pgpucommandbufferlease = nullptr;");
   ordered(commitLease, "pgpucommandbuffer->m_pgpucommandbufferlease = nullptr;", "->_endSingleTimeCommands(");
   const auto cancelLease = lease.substr(lease.find("void command_buffer_lease::cancel()"));
   ordered(cancelLease, "m_pgpucommandbuffer->m_pgpucommandbufferlease = nullptr;", "m_pgpucommandbuffer.release();");
   const auto destroyLease = section(lease, "command_buffer_lease::~command_buffer_lease()", "void command_buffer_lease::commit()");
   require(destroyLease.find("cancel();") != std::string::npos, "destruction must clear the backlink through cancel");
   const auto commandHeader = read("source/app/bred/gpu/command_buffer.h");
   require(commandHeader.find("m_pgpucommandbufferlease = nullptr;") != std::string::npos,
           "unleased buffers must start with a null lease link");
   const auto dx = read("operating_system/operating_system-windows_common/gpu_directx11/texture.cpp");
   const auto dxRead = section(dx, "void texture::read_pixels(", "IDXGISurface *texture::__get_dxgi_surface()");
   ordered(dxRead, "commandContext->m_pd3d11devicecontext->CopyResource(", "pgpucommandbuffer->m_pgpucommandbufferlease->commit();");
   ordered(dxRead, "pgpucommandbuffer->m_pgpucommandbufferlease->commit();", "->Map(");
   ordered(dxRead, "->Map(", "ppixmap->copy(ppixmap->size(),");
   require(dxRead.find("(size_t)pointOutput.y * mapped.RowPitch + (size_t)pointOutput.x * 4") != std::string::npos,
           "DirectX 11 readback must respect source-region offsets and row pitch");
   require(dxRead.find("unmap_guard") != std::string::npos, "DirectX 11 mapping must be exception safe");
   std::puts("Raw-pointer readback ordering, active-lease lifecycle, bounds, single submission, and error diagnostics passed.");
}
