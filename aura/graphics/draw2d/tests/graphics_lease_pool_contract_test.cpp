#include <cassert>
#include <fstream>
#include <iterator>
#include <sstream>
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


   std::string function_slice(
      const std::string & source,
      const std::string & signature,
      const std::string & nextSignature)
   {

      const auto begin = source.find(signature);

      assert(begin != std::string::npos);

      const auto end = source.find(nextSignature, begin + signature.length());

      assert(end != std::string::npos);

      return source.substr(begin, end - begin);

   }


   std::string active_lines(const std::string & source)
   {

      std::string active;
      std::string line;
      std::istringstream stream(source);

      while (std::getline(stream, line))
      {

         const auto first = line.find_first_not_of(" \t");

         if (first == std::string::npos || line.compare(first, 2, "//") == 0)
         {

            continue;

         }

         const auto comment = line.find("//");

         active.append(line, 0, comment);
         active.push_back('\n');

      }

      return active;

   }


   std::size_t require_after(
      const std::string & source,
      const std::string & token,
      std::size_t previous)
   {

      const auto position = source.find(token, previous);

      assert(position != std::string::npos);
      assert(position >= previous);

      return position + token.length();

   }


} // namespace


int main()
{

   const auto leaseHeader = read_file("aura/graphics/draw2d/graphics_lease.h");
   const auto leaseSource = read_file("aura/graphics/draw2d/graphics_lease.cpp");
   const auto scopeHeader = read_file("aura/graphics/draw2d/graphics_layer_scope.h");
   const auto scopeSource = read_file("aura/graphics/draw2d/graphics_layer_scope.cpp");
   const auto draw2dHeader = read_file("aura/graphics/draw2d/draw2d.h");
   const auto draw2dSource = read_file("aura/graphics/draw2d/draw2d.cpp");
   const auto graphicsHeader = read_file("aura/graphics/draw2d/graphics.h");
   const auto bitmapHeader = read_file("aura/graphics/draw2d/bitmap.h");
   const auto imageHeader = read_file("aura/graphics/image/image.h");
   const auto imageSource = read_file("aura/graphics/image/image.cpp");
   const auto gpuImageSource = read_file("bred/gpu/image.cpp");
   const auto windowSource = read_file("aura/windowing/window.cpp");
   const auto windowGraphicsHeader = read_file("aura/graphics/graphics/graphics.h");
   const auto windowGraphicsSource = read_file("aura/graphics/graphics/graphics.cpp");
   const auto direct2dDraw2dSource = read_file(
      "../../operating_system/operating_system-windows_common/draw2d_direct2d/draw2d.cpp");
   const auto direct2dGraphicsSource = read_file(
      "../../operating_system/operating_system-windows_common/draw2d_direct2d/graphics.cpp");
   const auto direct2dBitmapSource = read_file(
      "../../operating_system/operating_system-windows_common/draw2d_direct2d/bitmap.cpp");
   const auto direct2dImageSource = read_file(
      "../../operating_system/operating_system-windows_common/draw2d_direct2d/image.cpp");
   const auto helloMultiverseImageSource = read_file(
      "../app-core/hello_multiverse/the_image.cpp");

   assert(leaseHeader.find("graphics_lease(const graphics_lease &) = delete;") != std::string::npos);
   assert(leaseHeader.find("graphics_lease(graphics_lease &&") != std::string::npos);
   assert(leaseHeader.find("void close();") != std::string::npos);
   assert(draw2dHeader.find("acquire_memory_graphics") != std::string::npos);
   assert(draw2dHeader.find("acquire_image_graphics") != std::string::npos);
   assert(draw2dHeader.find("m_graphicsaMemoryPoolIdle") != std::string::npos);
   assert(graphicsHeader.find("on_acquire_memory_graphics") != std::string::npos);
   assert(graphicsHeader.find("on_release_memory_graphics") != std::string::npos);
   assert(draw2dSource.find("[draw2d.graphics_pool]") != std::string::npos);
   assert(imageHeader.find("::draw2d::graphics_lease acquire_graphics") != std::string::npos);
   assert(imageHeader.find("m_bDestinationGraphicsLeaseActive") != std::string::npos);
   assert(imageHeader.find("m_pacmeuserinteractionAffinity") != std::string::npos);
   assert(graphicsHeader.find("m_pacmeuserinteractionAffinity") != std::string::npos);
   assert(bitmapHeader.find(
      "::acme::user::interaction * pacmeuserinteractionAffinity")
      != std::string::npos);
   assert(imageSource.find("compare_exchange_strong") != std::string::npos);
   assert(imageSource.find("end_destination_graphics_lease") != std::string::npos);
   assert(gpuImageSource.find("has_active_destination_graphics_lease()") != std::string::npos);
   assert(scopeHeader.find("graphics_layer_scope(const graphics_layer_scope &) = delete;") != std::string::npos);
   assert(scopeHeader.find("graphics_layer_scope(graphics_layer_scope &&") != std::string::npos);
   assert(scopeHeader.find("void close();") != std::string::npos);
   assert(scopeSource.find("on_begin_layer_scope") != std::string::npos);
   assert(scopeSource.find("on_end_layer_scope") != std::string::npos);
   assert(scopeSource.find("mark_damaged") != std::string::npos);
   assert(leaseHeader.find("graphics_layer_scope begin_layer_scope();") != std::string::npos);
   assert(leaseHeader.find("m_bLayerScopeActive") != std::string::npos);
   assert(leaseSource.find("cannot close a graphics lease with an active layer scope") != std::string::npos);
   assert(graphicsHeader.find("virtual void on_begin_layer_scope();") != std::string::npos);
   assert(graphicsHeader.find("virtual void on_end_layer_scope();") != std::string::npos);

   const auto direct2dAllocation = active_lines(function_slice(
      direct2dDraw2dSource,
      "::draw2d::graphics_pointer draw2d::do_allocation_strategy(",
      "void draw2d::do_release_to_pool_strategy("));

   const auto direct2dImageAllocation = function_slice(
      direct2dAllocation,
      "if (::is_set(pimage))",
      "else");

   assert(direct2dImageAllocation.find("create_graphics(pdraw2dhost)") != std::string::npos);

   const auto memoryGraphicsAcquire = active_lines(function_slice(
      draw2dSource,
      "::draw2d::graphics_lease draw2d::_acquire_memory_graphics(",
      "::draw2d::graphics_lease draw2d::acquire_image_graphics("));

   std::size_t memoryGraphicsAcquireOrder = 0;
   memoryGraphicsAcquireOrder = require_after(
      memoryGraphicsAcquire,
      "pimage->m_pgraphicsOwned",
      memoryGraphicsAcquireOrder);
   memoryGraphicsAcquireOrder = require_after(
      memoryGraphicsAcquire,
      "if (!pgraphics)",
      memoryGraphicsAcquireOrder);
   require_after(
      memoryGraphicsAcquire,
      "m_graphicsaMemoryPoolIdle",
      memoryGraphicsAcquireOrder);

   const auto imageAcquire = active_lines(function_slice(
      imageSource,
      "::draw2d::graphics_lease image::acquire_graphics(",
      "::draw2d::graphics_lease image::_acquire_graphics("));

   std::size_t imageAffinityOrder = 0;
   imageAffinityOrder = require_after(
      imageAcquire,
      "pacmeuserinteractionAffinityExplicit",
      imageAffinityOrder);
   imageAffinityOrder = require_after(
      imageAcquire,
      "m_pacmeuserinteractionAffinity",
      imageAffinityOrder);
   imageAffinityOrder = require_after(
      imageAcquire,
      "dynamic_cast<::acme::user::interaction *>(pdraw2dhost)",
      imageAffinityOrder);
   require_after(
      imageAcquire,
      "main_acme_user_interaction()",
      imageAffinityOrder);

   assert(memoryGraphicsAcquire.find(
      "on_acquire_memory_graphics(pimage, size, pacmeuserinteractionAffinity)")
      != std::string::npos);

   const auto graphicsRelease = active_lines(function_slice(
      read_file("aura/graphics/draw2d/graphics.cpp"),
      "void graphics::on_release_memory_graphics()",
      "void graphics::create_for_window_draw2d("));

   assert(graphicsRelease.find(
      "m_pacmeuserinteractionAffinity.release()") != std::string::npos);

   const auto direct2dAcquire = active_lines(function_slice(
      direct2dGraphicsSource,
      "void graphics::on_acquire_memory_graphics(",
      "void graphics::on_release_memory_graphics()"));

   std::size_t direct2dAcquireOrder = 0;
   direct2dAcquireOrder = require_after(
      direct2dAcquire,
      "pimage->create_bitmap(pacmeuserinteractionAffinity)",
      direct2dAcquireOrder);
   direct2dAcquireOrder = require_after(
      direct2dAcquire,
      "::draw2d::graphics::on_acquire_memory_graphics",
      direct2dAcquireOrder);
   require_after(
      direct2dAcquire,
      "m_pdevicecontext->SetTarget",
      direct2dAcquireOrder);

   const auto direct2dRawDraw = active_lines(function_slice(
      direct2dGraphicsSource,
      "void graphics::_draw_raw(",
      "void graphics::_stretch_raw("));

   std::size_t direct2dRawDrawOrder = 0;
   direct2dRawDrawOrder = require_after(
      direct2dRawDraw,
      "pimage->create_bitmap(m_pacmeuserinteractionAffinity)",
      direct2dRawDrawOrder);
   require_after(
      direct2dRawDraw,
      "pimage->get_bitmap()",
      direct2dRawDrawOrder);

   const auto direct2dRawStretch = active_lines(function_slice(
      direct2dGraphicsSource,
      "void graphics::_stretch_raw(",
      "void graphics::flush()"));

   std::size_t direct2dRawStretchOrder = 0;
   direct2dRawStretchOrder = require_after(
      direct2dRawStretch,
      "pimage->create_bitmap(m_pacmeuserinteractionAffinity)",
      direct2dRawStretchOrder);
   require_after(
      direct2dRawStretch,
      "pimage->get_bitmap()",
      direct2dRawStretchOrder);

   const auto direct2dBitmapForImage = active_lines(function_slice(
      direct2dBitmapSource,
      "void bitmap::create_bitmap_for_image(",
      "void bitmap::CreateBitmap("));

   assert(direct2dBitmapForImage.find("acme_windowing_window()")
      != std::string::npos);
   assert(direct2dBitmapForImage.find("->m_pacmewindowingwindow")
      == std::string::npos);
   assert(direct2dBitmapForImage.find("task_interaction()")
      == std::string::npos);

   const auto baseRenderTargetCreation = active_lines(function_slice(
      imageSource,
      "void image::create_as_render_target(",
      "void image::initialize("));

   assert(baseRenderTargetCreation.find(
      "m_pacmeuserinteractionAffinity = puserinteraction")
      != std::string::npos);

   const auto direct2dRenderTargetCreation = active_lines(function_slice(
      direct2dImageSource,
      "void image::create_as_render_target(",
      "void image::initialize("));

   assert(direct2dRenderTargetCreation.find(
      "m_pacmeuserinteractionAffinity = puserinteraction")
      != std::string::npos);

   assert(helloMultiverseImageSource.find(
      "pgraphics->m_puserinteractionDraw2dGraphics->post(")
      == std::string::npos);
   assert(helloMultiverseImageSource.find(
      "pacmeuserinteractionAffinity->post(")
      != std::string::npos);

   assert(windowGraphicsHeader.find("virtual void on_end_layout();") != std::string::npos);
   assert(windowGraphicsHeader.find("virtual void on_end_draw();") != std::string::npos);
   assert(windowGraphicsHeader.find("virtual void on_end(::e_graphics egraphics);") != std::string::npos);

   const auto graphicsEnd = function_slice(
      windowGraphicsSource,
      "void graphics::on_end(::e_graphics egraphics)",
      "bool graphics::buffer_lock_round_swap_key_buffers()");

   assert(graphicsEnd.find("update_screen()") == std::string::npos);

   const auto drawFrame = active_lines(function_slice(
      windowSource,
      "void window::draw_frame()",
      "void window::frame_layout_stage("));

   assert(drawFrame.find("pgraphics->send(") == std::string::npos);
   assert(drawFrame.find("main_sendø()") != std::string::npos);

   std::size_t order = 0;
   order = require_after(drawFrame, "on_begin_layout()", order);
   order = require_after(drawFrame, "acquire_graphics()", order);
   order = require_after(drawFrame, "frame_layout_stage(pgraphics)", order);
   order = require_after(drawFrame, "on_end_layout()", order);
   order = require_after(drawFrame, "on_begin_draw()", order);
   order = require_after(drawFrame, "acquire_graphics()", order);
   order = require_after(drawFrame, "frame_draw_stage(pgraphics)", order);
   order = require_after(drawFrame, "pgraphics->on_end_draw(this)", order);
   order = require_after(drawFrame, "on_end_draw()", order);
   order = require_after(drawFrame, "update_screen()", order);

   assert(drawFrame.find("update_screen()", order) == std::string::npos);

   return 0;

}
