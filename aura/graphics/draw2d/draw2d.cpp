#include "framework.h"
#include "lock.h"
#include "acme/graphics/image/image32.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/graphics/draw2d/host.h"
#include "aura/graphics/image/encoding_options.h"
#include "aura/graphics/image/array.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/imaging.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/graphics/image/drawing.h"
#include "aura/user/user/interaction.h"
#include "graphics.h"
#include "host.h"
#include "brush.h"
#include "draw2d.h"
#include "task_tool.h"
#include <chrono>


bool g_bDraw2dDisableReferencingDebugging = false;


//
//
//namespace aura
//{
//
//
//   extern CLASS_DECL_AURA string_map_base < i32_to_string > * g_pmapFontFaceName;
//
//
//   extern CLASS_DECL_AURA critical_section * g_pcsFont;
//
//
//} // namespace aura


namespace draw2d
{


   ::f64 draw2d::g_dEmboss = 2.0;


   draw2d::draw2d()
   {

      m_pimpl = nullptr;
      m_bUseGraphicsPool = true;

   }


   draw2d::~draw2d()
   {

   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::platform::department::initialize(pparticle);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      construct_newø(m_pimagea);

      //estatus = 

      construct_newø(m_papi);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //lock::__s_initialize();

      //return estatus;

   }


   void draw2d::add_object(::draw2d::object * pobject)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_objecta.add(pobject);

   }


   void draw2d::erase_object(::draw2d::object * pobject)
   {
      
      if(::is_null(this))
      {
         
         return;
         
      }

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_objecta.erase(pobject);

   }


   void draw2d::add_image(::image::image *pimage)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      m_pimagea->add_image(pimage);

   }


   void draw2d::erase_image(::image::image *pimage)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      if (m_pimagea)
      {

         m_pimagea->erase_image(pimage);

      }

   }


   void draw2d::add_graphics(graphics * pgraphics)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      m_graphicsa.add(pgraphics);

   }


   void draw2d::erase_graphics(graphics * pgraphics)
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      m_graphicsa.erase(pgraphics);

   }


   //::pointer< ::mutex > draw2d::get_object_list_mutex()
   //{

   //   return m_pmutexObjectList;

   //}


   //::pointer< ::mutex > draw2d::get_image_list_mutex()
   //{

   //   return m_pmutexImageList;

   //}


   //::pointer< ::mutex > draw2d::get_graphics_context_list_mutex()
   //{

   //   return m_pmutexGraphicsContextList;

   //}


   //void draw2d::on_before_create_window(::windowing::window* pwindow)
   //{


   //}


   //void draw2d::on_create_window(::windowing::window * pwindow)
   //{


   //}


   void draw2d::clear_all_objects_os_data()
   {

      clear_object_list_os_data();
      clear_image_list_os_data();
      clear_graphics_context_list_os_data();

   }


   void draw2d::clear_object_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

      for (auto & pparticle : m_objecta)
      {

         pparticle->destroy_os_data();

      }

   }


   void draw2d::clear_image_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionImageList);

      for (auto & pimage : m_pimagea->imagea())
      {

         pimage->destroy_os_data();

      }

   }


   void draw2d::clear_graphics_context_list_os_data()
   {

      critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

      for (auto & pgraphics : m_graphicsa)
      {

         pgraphics->destroy_os_data();

      }

   }

   ::draw2d::graphics * draw2d::get_thread_graphics(int iSlot)
   {

      auto taskindex = current_task_index();

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & pgraphics = m_mapThreadPathGraphics[taskindex].atø(iSlot);

      synchronouslock.unlock();

      if(defer_constructø(pgraphics))
      {

         pgraphics->create_memory_graphics({256, 256});

      }

      return pgraphics;

   }


   api & draw2d::api()
   {

      return *m_papi;

   }


   class ::write_text::write_text * draw2d::write_text()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if(!m_pwritetext)
      {

         if (application()->m_bWriteText)
         {

            initialize_write_text();

            synchronouslock.unlock();


            //if (!estatus)
            //{

            //   information() << "Couldn't construct aaa_memory_new write_text.";

            //   return estatus;

            //}

            //estatus =

            m_pwritetext->init1();

            //if (!estatus)
            //{

            //   information() << "Couldn't initialize write_text (init1).";

            //   return estatus;

            //}

            //if (::succeeded(estatus))
            //{

            factory()->add_factory_item_with_custom_id < ::draw2d::task_tool_item >(::atom(::e_task_tool_draw2d));

            //}

            //return estatus;


         }

      }

      return m_pwritetext;

   }


   void draw2d::init1()
   {

      //if (!
      ::platform::department::init1();

      //{

      //   return false;

      //}


      //return true;

   }


   void draw2d::process_init()
   {

      ::platform::department::process_init();

      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //if (!m_papi->open())
      //{

      //   return false;

      //}

      //return true;

   }


   void draw2d::init()
   {

      //if (!)
      ::platform::department::init();
      //{

      //   return false;

      //}

      //return true;

   }


   bool draw2d::write_text_supports_raster_fonts()
   {

      return true;

   }


   bool draw2d::write_text_supports_legacy_gdi_fonts()
   {

      return true;

   }


   bool draw2d::graphics_context_supports_single_buffer_mode()
   {

      return true;

   }


   bool draw2d::graphics_context_does_full_redraw()
   {

      return false;

   }


   void draw2d::term()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         try
         {

            if (m_papi)
            {

               m_papi->destroy();

            }

         }
         catch (...)
         {

         }

         m_alpha_spread__24CC_filterMap.erase_all();

         m_alpha_spread__32CC_filterMap.erase_all();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionObjectList);

         m_objecta.clear();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionImageList);

         m_pimagea->m_imagea.clear();

      }

      {

         critical_section_lock criticalsectionlock(&m_criticalsectionGraphicsContextList);

            m_graphicsa.clear();

      }

   }


   void draw2d::destroy()
   {

      shutdown_memory_graphics_pool();

      m_papi.release();

      //lock::__s_finalize();

      if (m_pimagea)
      {

         m_pimagea->m_imagea.erase_all();

         m_pimagea.release();

      }

         m_objecta.erase_all();

         m_pwritetext.release();

         m_papi.release();

         m_alpha_spread__24CC_filterMap.clear();

         m_alpha_spread__32CC_filterMap.clear();

      //}

      m_graphicsa.erase_all();

      //auto estatus = 
      ::platform::department::destroy();

      //return estatus;

   }


   ::draw2d::graphics_pointer draw2d::create_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = pdraw2dhost->createø< ::draw2d::graphics>();

      pgraphics->m_pdraw2dhost = pdraw2dhost;

      return ::transfer(pgraphics);

   }


   ::draw2d::graphics_pointer draw2d::create_memory_graphics(::draw2d::host * pdraw2dhost)
   {

      auto pgraphics = create_graphics(pdraw2dhost);

      auto sizeModernOnePixel = ::i32_size{ 1920, 1080 };

      pgraphics->create_memory_graphics(sizeModernOnePixel);

      return pgraphics;

   }


   namespace
   {


      ::i64 memory_graphics_pool_steady_nanoseconds()
      {

         return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
            ::std::chrono::steady_clock::now().time_since_epoch()).count();

      }


      void update_memory_graphics_pool_high_water(
         ::std::atomic<::u64> & highWater,
         ::u64 uActive)
      {

         auto uHighWater = highWater.load(::std::memory_order_relaxed);

         while (uActive > uHighWater
            && !highWater.compare_exchange_weak(
               uHighWater,
               uActive,
               ::std::memory_order_relaxed))
         {

         }

      }


   } // namespace


   ::draw2d::graphics_lease draw2d::acquire_memory_graphics(
      const ::i32_size & size, ::draw2d::host *pdraw2dhost)
   {

      return _acquire_memory_graphics(pdraw2dhost, size, nullptr);

   }


   ::draw2d::graphics_pointer draw2d::do_allocation_strategy(::draw2d::host *pdraw2dhost, ::image::image *pimage,
                                                              const ::i32_size &size)
   {

      auto pgraphics = create_graphics(pdraw2dhost);
    
      pgraphics->create_memory_graphics(size);

      return pgraphics;

   }


   ::draw2d::graphics_lease draw2d::_acquire_memory_graphics(
      ::draw2d::host * pdraw2dhost,
      const ::i32_size & size,
      ::image::image * pimage)
   {
      
      if (!pdraw2dhost)
      {

         pdraw2dhost = m_papplication->m_pacmeuserinteractionMain.cast < ::draw2d::host >();

      }

      if (!pdraw2dhost || size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      //if (!m_bUseGraphicsPool)
      //{

      //   if (!pimage->m_pgraphicsOwned)
      //   {

      //      pimage->create_owned_graphics();

      //   }

      //   return {this, pimage->m_pgraphicsOwned, pimage, false};

      //}

      if (m_bMemoryGraphicsPoolShuttingDown.load(::std::memory_order_acquire))
      {

         throw ::exception(error_wrong_state, "memory graphics pool is shutting down");

      }

      ::draw2d::graphics_pointer pgraphics;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (m_bMemoryGraphicsPoolShuttingDown.load(::std::memory_order_relaxed))
         {

            throw ::exception(error_wrong_state, "memory graphics pool is shutting down");

         }

         for (::collection::index i = 0; i < m_graphicsaMemoryPoolIdle.get_count(); ++i)
         {

            auto pgraphicsCandidate = m_graphicsaMemoryPoolIdle[i];

            if (pgraphicsCandidate->is_memory_graphics_pool_compatible(pdraw2dhost))
            {

               pgraphics = pgraphicsCandidate;
               m_graphicsaMemoryPoolIdle.erase_at(i);
               break;

            }

         }

      }

      auto bReused = pgraphics.is_set();

      if (!bReused)
      {

         if (m_bMemoryGraphicsPoolShuttingDown.load(::std::memory_order_acquire))
         {

            throw ::exception(error_wrong_state, "memory graphics pool is shutting down");

         }

         pgraphics = do_allocation_strategy(pdraw2dhost, pimage, size);

      }

      if (m_bMemoryGraphicsPoolShuttingDown.load(::std::memory_order_acquire))
      {

         throw ::exception(error_wrong_state, "memory graphics pool is shutting down");

      }

      pgraphics->on_acquire_memory_graphics(pimage, size);

      auto uActive = m_uMemoryGraphicsPoolActive.fetch_add(
         1,
         ::std::memory_order_relaxed) + 1;

      update_memory_graphics_pool_high_water(
         m_uMemoryGraphicsPoolHighWater,
         uActive);

      if (m_papplication
         && m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         m_uMemoryGraphicsPoolAcquisitions.fetch_add(1, ::std::memory_order_relaxed);

         if (bReused)
         {

            m_uMemoryGraphicsPoolReuses.fetch_add(1, ::std::memory_order_relaxed);

         }
         else
         {

            m_uMemoryGraphicsPoolCreations.fetch_add(1, ::std::memory_order_relaxed);

         }

         report_memory_graphics_pool_diagnostics_if_due();

      }

      return {this, pgraphics, pimage, false};

   }


   ::draw2d::graphics_lease draw2d::acquire_image_graphics(
      ::image::image * pimage,
      ::draw2d::host * pdraw2dhost)
   {

      if (!pimage || !pdraw2dhost || pimage->size().is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      return _acquire_memory_graphics(
         pdraw2dhost,
         pimage->size(),
         pimage);

   }


   

   void draw2d::do_release_to_pool_strategy(::draw2d::graphics_pointer &pgraphics)
   {

      m_graphicsaMemoryPoolIdle.add(pgraphics);

      pgraphics.release();

   }



   void draw2d::return_memory_graphics(
      ::draw2d::graphics_pointer pgraphics,
      ::image::image_pointer pimage,
      bool bDamaged)
   {

      if (!pgraphics)
      {

         return;

      }

      //if (!m_bUseGraphicsPool)
      //{

      //   if (::is_set(pimage))
      //   {

      //      if (pimage->m_pgraphicsOwned)
      //      {

      //         if (pimage->m_pgraphicsOwned != pgraphics)
      //         {

      //            throw ::exception(error_wrong_state);

      //         }

      //         return;

      //      }

      //   }

      //}

      try
      {

         pgraphics->on_release_memory_graphics();

      }
      catch (...)
      {

         if (pimage)
         {

            pimage->end_destination_graphics_lease();

         }

         throw;

      }

      if (pimage)
      {

         pimage->end_destination_graphics_lease();

      }

      auto bShuttingDown = m_bMemoryGraphicsPoolShuttingDown.load(
         ::std::memory_order_acquire);

      if (!bDamaged && !bShuttingDown)
      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (!m_bMemoryGraphicsPoolShuttingDown.load(::std::memory_order_relaxed))
         {

            do_release_to_pool_strategy(pgraphics);

         }

      }

      auto uActive = m_uMemoryGraphicsPoolActive.load(::std::memory_order_relaxed);

      while (uActive > 0
         && !m_uMemoryGraphicsPoolActive.compare_exchange_weak(
            uActive,
            uActive - 1,
            ::std::memory_order_relaxed))
      {

      }

      if (m_papplication
         && m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         report_memory_graphics_pool_diagnostics_if_due();

      }

   }


   void draw2d::shutdown_memory_graphics_pool()
   {

      if (m_bMemoryGraphicsPoolShuttingDown.exchange(
         true,
         ::std::memory_order_acq_rel))
      {

         return;

      }

      ::pointer_array<::draw2d::graphics> graphicsaIdle;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         while (m_graphicsaMemoryPoolIdle.has_element())
         {

            graphicsaIdle.add(m_graphicsaMemoryPoolIdle.pop());

         }

      }

      graphicsaIdle.erase_all();

   }


   void draw2d::report_memory_graphics_pool_diagnostics_if_due()
   {

      if (!m_papplication
         || !m_papplication->m_gpu.m_bPerformanceDiagnostics.load(
            ::std::memory_order_relaxed))
      {

         return;

      }

      auto uGeneration =
         m_papplication->m_gpu.m_uPerformanceDiagnosticsGeneration.load(
            ::std::memory_order_relaxed);
      auto uGenerationLast =
         m_uMemoryGraphicsPoolDiagnosticsGenerationLast.load(
            ::std::memory_order_relaxed);

      if (uGeneration != uGenerationLast)
      {

         m_uMemoryGraphicsPoolDiagnosticsGenerationLast.store(
            uGeneration,
            ::std::memory_order_relaxed);
         m_iMemoryGraphicsPoolNextReportNanoseconds.store(
            0,
            ::std::memory_order_relaxed);

      }

      auto iNowNanoseconds = memory_graphics_pool_steady_nanoseconds();
      auto iDeadlineNanoseconds =
         m_iMemoryGraphicsPoolNextReportNanoseconds.load(
            ::std::memory_order_relaxed);

      if (iNowNanoseconds < iDeadlineNanoseconds)
      {

         return;

      }

      auto iIntervalMilliseconds = maximum(
         100,
         minimum(
            60'000,
            m_papplication->m_gpu.m_iPerformanceDiagnosticsIntervalMilliseconds.load(
               ::std::memory_order_relaxed)));
      auto iNextNanoseconds = iNowNanoseconds
         + (::i64) iIntervalMilliseconds * 1'000'000;

      if (!m_iMemoryGraphicsPoolNextReportNanoseconds.compare_exchange_strong(
         iDeadlineNanoseconds,
         iNextNanoseconds,
         ::std::memory_order_relaxed))
      {

         return;

      }

      ::collection::count cIdle;

      {

         _synchronous_lock synchronouslock(
            this->synchronization(),
            DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         cIdle = m_graphicsaMemoryPoolIdle.get_count();

      }

      information() << "[draw2d.graphics_pool] acquisitions="
         << m_uMemoryGraphicsPoolAcquisitions.exchange(0, ::std::memory_order_relaxed)
         << " reuses="
         << m_uMemoryGraphicsPoolReuses.exchange(0, ::std::memory_order_relaxed)
         << " creations="
         << m_uMemoryGraphicsPoolCreations.exchange(0, ::std::memory_order_relaxed)
         << " active="
         << m_uMemoryGraphicsPoolActive.load(::std::memory_order_relaxed)
         << " high_water="
         << m_uMemoryGraphicsPoolHighWater.load(::std::memory_order_relaxed)
         << " idle=" << cIdle;

   }


   ::draw2d::brush_pointer draw2d::create_solid_brush(const ::color::color & color)
   {

      ::draw2d::brush_pointer pbrush;

      constructø(pbrush);

      pbrush->create_solid(color);

      return pbrush;

   }




   // should not call axis class implementation because draw2d::draw2d is inside a n-furcation of user::draw2d
   void draw2d::term_instance()
   {

      try
      {

         ::platform::department::term_instance();

      }
      catch (...)
      {

         output_error_message("except", "except", ::user::e_message_box_ok);

      }

      //return ::success;

   }


   void draw2d::embossed_text_out(
      ::draw2d::graphics_pointer & pgraphics,
      const ::i32_rectangle & rectangle,
      const ::scoped_string & scopedstrText,
      ::image::fastblur & blur,
      ::image::image_pointer & imageBlur,
      ::write_text::font * pfont,
      const ::e_align & ealign,
      const ::e_draw_text & edrawtext,
      const ::color::color & colorText,
      const ::color::color & colorGlow,
      ::i32 iSpreadRadius,
      ::i32 iBlurRadius,
      ::i32 iBlur,
      bool bUpdate,
      const ::color_filter & colorfilter)
   {

      if (scopedstrText.is_empty())
      {

         throw ::exception(error_null_pointer);

      }

      auto pred = [&](::draw2d::graphics * pgraphicsParam)
      {

            pgraphicsParam->set(pfont);
            pgraphicsParam->_DrawText(scopedstrText, rectangle, ealign, edrawtext);

      };

      ///bool bRaspiBilbo = scopedstrText.case_insensitive_begins("bilbo-raspi-");

      //if (!bRaspiBilbo)
      {

         emboss_predicate(pgraphics, rectangle, pred, blur, imageBlur, colorGlow, iSpreadRadius, iBlurRadius, iBlur,
                          bUpdate, colorfilter);
      }

      auto opacity = colorfilter.opacity();

      auto pbrushText = createø < ::draw2d::brush >();

      pbrushText->create_solid(colorText & opacity);

      pgraphics->set(pbrushText);
      pgraphics->set(pfont);
      pgraphics->_DrawText(scopedstrText, rectangle, ealign, edrawtext);

      //return true;


   }


void draw2d::emboss_predicate(
   ::draw2d::graphics_pointer & pgraphics,
   const ::i32_rectangle & rectangle,
   const ::function < void(::draw2d::graphics *) > & functionDraw,
   ::image::fastblur & blur,
   ::image::image_pointer & pimageBlur,
   ::color::color crGlow,
   ::i32 iSpreadRadius,
   ::i32 iBlurRadius,
   ::i32 iBlur,
   bool bUpdate,
   const ::color_filter & colorfilter)
{

   ::i32 iR = iSpreadRadius + iBlurRadius + iBlur + 1;

   ::i32_rectangle rectangleEmboss = rectangle;

   rectangleEmboss.left -= (::i32)(iR * g_dEmboss);
   rectangleEmboss.top -= (::i32)(iR * g_dEmboss);
   rectangleEmboss.right += (::i32)(iR * g_dEmboss);
   rectangleEmboss.bottom += (::i32)(iR * g_dEmboss);

   if (bUpdate || !pimageBlur->is_ok())
   {

      ::i32 iEffectiveSpreadRadius = iSpreadRadius;

      ::i32 iEffectiveBlurRadius = iBlurRadius;

      const ::i32_size & size = rectangleEmboss.size();

      //pimageBlur->initialize(rectangleEmboss, iEffectiveBlurRadius);

      //pimageBlur->fill(0, 0, 0, 0);

      ::i32_rectangle rectangleCache;

      rectangleCache.left = (::i32)(iR * g_dEmboss);
      rectangleCache.top = (::i32)(iR * g_dEmboss);
      rectangleCache.right = rectangleCache.left + rectangle.width();

      rectangleCache.bottom = rectangleCache.top + rectangle.height();

      ::image::image_pointer pimage;

      //auto estatus =

      constructø(pimage);

      //if (!estatus)
      //{

      //   return false;

      //}

      //estatus =

      pimage->create(size);

      //if (!estatus)
      //{

      //   return false;

      //}

      pimage->fill_byte(0);

      auto pbrushText = createø < ::draw2d::brush >();

      pbrushText->create_solid(argb(255, 255, 255, 255));

      auto pgraphicsImage = pimage->acquire_graphics(pgraphics->m_puserinteractionDraw2dGraphics);

      pgraphicsImage->set(pbrushText);

      auto shift = rectangleCache.top_left() - rectangle.top_left();

      auto extent = rectangleCache.size();

      pgraphicsImage->shift_impact_area(shift, extent);

      functionDraw(pgraphicsImage);

      pgraphicsImage->shift_impact_area(-shift, extent);

      auto psystem = system();

      pimageBlur->create(size);

      blur.initialize(pimageBlur->size(), iEffectiveBlurRadius);

      auto pgraphicsBlur = pimageBlur->acquire_graphics(pgraphics->m_puserinteractionDraw2dGraphics);

      imaging()->channel_spread_set_color(pgraphicsBlur, {}, size, pgraphicsImage, {}, ::color::e_channel_red,
                                          iEffectiveSpreadRadius, argb(255, 255, 255, 255));

      for (iptr i = 0; i < iBlur; i++)
      {
         
         blur.blur(pimageBlur);

      }

      pimageBlur->set_rgb(crGlow);

      pimageBlur->mult_alpha();

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   ::image::image_source imagesource(pimageBlur);

   ::image::image_drawing_options imagedrawingoptions(rectangleEmboss);

   imagedrawingoptions = colorfilter;

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

   //return true;

}


   void draw2d::alpha_spread__24CC(
      ::u8 * lpbDst, ::i32 xDest, ::i32 yDest, ::i32 wDest, ::i32 cx, ::i32 cy,
      ::u8 * lpbSrc, ::i32 xSrc, ::i32 ySrc, ::i32 wSrc,
      ::u8 bMin, ::i32 iRadius)
   {
      __UNREFERENCED_PARAMETER(xDest);
      __UNREFERENCED_PARAMETER(yDest);
      __UNREFERENCED_PARAMETER(xSrc);
      __UNREFERENCED_PARAMETER(ySrc);
      ::i32 iFilterW = iRadius * 2 + 1;
      ::i32 iFilterH = iRadius * 2 + 1;
      ::i32 iFilterHalfW = iFilterW / 2;
      ::i32 iFilterHalfH = iFilterH / 2;
      ::i32 iFilterArea = iFilterW * iFilterH;
      //::i32 divisor;
      ::u8 * lpbSource;
      ::u8 * lpbSource_1;
      ::u8 * lpbSource_2;
      ::u8 * lpwDestination;
      ::u8 * lpFilter;
      ::u8 * pFilter;


      ::i32 i;
      ::i32 x;
      ::i32 y;
      ::i32 x1;
      ::i32 y1;
      ::i32 x2;
      ::i32 y2;

      ::i32 iRadius2 = iRadius * iRadius;
      ::i32 r2;

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];

      if (filter.is_set())
      {

         pFilter = filter->begin();

      }
      else
      {

         filter = allocateø memory();

         filter->set_size(iFilterArea);

         pFilter = filter->begin();

         for (y = 0; y <= iFilterHalfH; y++)
         {

            for (x = 0; x <= iFilterHalfW; x++)
            {

               x1 = iFilterHalfW - x;

               y1 = iFilterHalfH - y;

               r2 = x1 * x1 + y1 * y1;

               if (r2 <= iRadius2)
               {

                  i = 1;

               }
               else
               {

                  i = 0;

               }

               pFilter[x + y * iFilterW] = (::u8)i;

               pFilter[iFilterW - 1 - x + y * iFilterW] = (::u8)i;

               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (::u8)i;

               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (::u8)i;

            }

         }

      }

      synchronouslock.unlock();

      ::i32 maxx1 = cx;
      ::i32 maxy1 = cy;
      ::i32 max3x1 = maxx1 * 3;


      ::u32 dwR;
      ::u32 dwG;
      ::u32 dwB;


      ::i32 iFilterXLowerBound;
      ::i32 iFilterXUpperBound;
      ::i32 iFilterYLowerBound;
      ::i32 iFilterYUpperBound;

      ::i32 yLowerBound[4];
      ::i32 yUpperBound[4];
      ::i32 xLowerBound[4];
      ::i32 xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfW;
      yUpperBound[3] = cy - 1;

      ::i32 xL;
      ::i32 xU;
      ::i32 yL;
      ::i32 yU;

      bool bSpread;
      ::u32 bMin3 = bMin * 3;


      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 > (cy - iFilterHalfH))
            {
               iFilterYUpperBound = iFilterH - (y1 - (cy - iFilterHalfH)) - 1;
            }
            else
            {
               iFilterYUpperBound = iFilterH - 1;
            }

            lpbSource = lpbSrc + (wSrc * maximum(y2, 0));

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 3;
            lpwDestination = lpbDst + (wDest * y1) + x1 * 3;
            for (; x1 <= xU;)
            {
               if (x1 < iFilterHalfH)
               {
                  iFilterXLowerBound = iFilterHalfH - x1;
               }
               else
               {
                  iFilterXLowerBound = 0;
               }
               if (x1 > (cx - iFilterHalfH + 1))
               {
                  iFilterXUpperBound = iFilterH - (x1 - (cx - iFilterHalfH + 1));
               }
               else
               {
                  iFilterXUpperBound = iFilterH - 1;
               }

               lpbSource_1 = lpbSource + maximum(x2, 0);


               dwR = 0;
               dwG = 0;
               dwB = 0;
               bSpread = false;
               for (::i32 yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (::i32 xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        dwB = lpbSource_2[0];
                        dwG = lpbSource_2[1];
                        dwR = lpbSource_2[2];

                        if (dwR + dwG + dwB > bMin3)
                        {
                           *((::u32 *)lpwDestination) |= 0x00ffffff;
                           goto breakFilter;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 3;
                  }
               }
            breakFilter:
               lpwDestination += 3;
               x1++;
               x2 += 3;
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      ::i32 iFilterHalfWidth = iFilterW / 2;
      ::i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      /// divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2);

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDest * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            dwR = 0;
            dwG = 0;
            dwB = 0;
            bSpread = false;
            for (::i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
               for (::i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {
                  if (*lpFilter >= 1)
                  {
                     dwB = lpbSource_2[0];
                     dwG = lpbSource_2[1];
                     dwR = lpbSource_2[2];

                     if (dwR + dwG + dwB > bMin3)
                     {
                        bSpread = true;
                        break;
                     }
                  }
                  lpFilter++;
                  lpbSource_2 += 3;
               }
            }

            if (bSpread)
            {
               *((::u32 *)lpwDestination) |= 0x00ffffff;
               lpwDestination += 3;
            }
            else
            {
               lpwDestination += 3;
            }
            x1 += 3;
            x2 += 3;
         }
         y1++;
         y2++;
      }

   }


   bool draw2d::channel_spread__32CC(::image::image *pimageDst, ::image::image *pimageSrc, ::i32 iChannel, ::i32 iRadius, const ::color::color & colorSpreadSetColor)
   {

      pimageDst->map();

      pimageSrc->map();

      ::i32 iFilterW = iRadius * 2 + 1;
      ::i32 iFilterH = iRadius * 2 + 1;
      ::i32 iFilterHalfW = iRadius;
      ::i32 iFilterHalfH = iRadius;
      ::i32 iFilterArea = iFilterW * iFilterH;
      //::i32 divisor = iFilterW * iFilterH;
      ::u8 * lpbSource;
      ::u8 * lpbSource_1;
      ::u8 * lpbSource_2;
      ::u8 * lpwDestination;
      ::u8 * lpFilter;
      ::u8 * pFilter;

      ::i32 i;
      ::i32 x;
      ::i32 y;
      ::i32 x1;
      ::i32 y1;
      ::i32 x2;
      ::i32 y2;

      ::i32 iRadiusSquare = iRadius * iRadius;
      ::i32 rSquare;


      image32_t u32SpreadSetColor(colorSpreadSetColor, pimageDst->m_colorindexes);


      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];

      if (filter.is_set())
      {
         pFilter = filter->begin();
      }
      else
      {
         filter = allocateø memory();
         filter->set_size(iFilterArea);
         pFilter = filter->begin();
         for (y = 0; y < iFilterH; y++)
         {
            for (x = 0; x < iFilterW; x++)
            {
               x1 = iFilterHalfW - x;
               y1 = iFilterHalfH - y;
               rSquare = x1 * x1 + y1 * y1;
               if (rSquare <= iRadiusSquare)
                  i = 1;
               else
                  i = 0;
               pFilter[x + y * iFilterW] = (::u8)i;
            }
         }
      }

      synchronouslock.unlock();

      ::i32 cx = pimageDst->width();
      ::i32 cy = pimageDst->height();

      if (cx != pimageSrc->width() || cy != pimageSrc->height())
         return false;

      ::u8 * lpbDst = (::u8 *)pimageDst->data();
      ::u8 * lpbSrc = (::u8 *)pimageSrc->data();

      //::i32 wSrc = cx * 4;
      //::i32 wDst = cx * 4;
      ::i32 wSrc = pimageSrc->scan_size();
      ::i32 wDst = pimageDst->scan_size();

      ::i32 maxx1 = cx;
      ::i32 maxy1 = cy;
      //   ::i32 maxy2 = cy - iFilterW;
      //   ::i32 maxy3 = cy - iFilterW / 2;
      ::i32 max3x1 = maxx1 * 4;
      //   ::i32 max3x2 = (maxx1 - iFilterH) * 4;
      //   ::i32 max3x3 = (maxx1 - iFilterH / 2) * 4;
      //::i32 w = cx * 4;

      pimageDst->pixmap_t::copy(pimageSrc);
      //::memory_copy(lpbDst,lpbSrc,cx * cy * 4);


      ::i32 iFilterXLowerBound;
      ::i32 iFilterXUpperBound;
      ::i32 iFilterYLowerBound;
      ::i32 iFilterYUpperBound;

      ::i32 yLowerBound[4];
      ::i32 yUpperBound[4];
      ::i32 xLowerBound[4];
      ::i32 xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfH;
      yUpperBound[3] = cy - 1;

      ::i32 xL;
      ::i32 xU;
      ::i32 yL;
      ::i32 yU;


      ::i32 xMax = cx - 1;
      ::i32 yMax = cy - 1;

      // limits due the filter
      ::i32 xMaxFilterBound = xMax - iFilterHalfW;
      ::i32 yMaxFilterBound = yMax - iFilterHalfH;

      ::i32 xFilterMax = iFilterW - 1;
      ::i32 yFilterMax = iFilterH - 1;

      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 > yMaxFilterBound)
            {
               iFilterYUpperBound = yFilterMax - (y1 - yMaxFilterBound);
            }
            else
            {
               iFilterYUpperBound = yFilterMax;
            }

            lpbSource = lpbSrc + wSrc * y2;

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 4;
            lpwDestination = lpbDst + (wDst * y1) + x1 * 4;
            if (*((::u32 *)lpwDestination) != 0xffffffff)
            {
               for (; x1 <= xU; x1++)
               {
                  if (x1 < iFilterHalfH)
                  {
                     iFilterXLowerBound = iFilterHalfH - x1;
                  }
                  else
                  {
                     iFilterXLowerBound = 0;
                  }
                  if (x1 > xMaxFilterBound)
                  {
                     iFilterXUpperBound = xFilterMax - (x1 - xMaxFilterBound);
                  }
                  else
                  {
                     iFilterXUpperBound = xFilterMax;
                  }

                  lpbSource_1 = lpbSource + maximum(x2, 0) + iChannel;


                  for (::i32 yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {
                     lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                     lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                     for (::i32 xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                     {
                        if (*lpFilter >= 1)
                        {
                           if (lpbSource_2[0] > 0)
                           {
                              *((image32_t *)lpwDestination) = u32SpreadSetColor;
                              goto breakFilter;
                           }
                        }
                        lpFilter++;
                        lpbSource_2 += 4;
                     }
                  }
               breakFilter:
                  lpwDestination += 4;
                  x2 += 4;
               }
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      ::i32 iFilterHalfWidth = iFilterW / 2;
      ::i32 iFilterHalfWidthBytes = iFilterHalfWidth * 4;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      //divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2) + iChannel;

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDst * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            if (*((::u32 *)lpwDestination) != 0xffffffff)
            {
               for (::i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (::i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        if (lpbSource_2[0] > 0)
                        {
                           *((image32_t *)lpwDestination) = u32SpreadSetColor;
                           goto breakFilter2;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 4;
                  }
               }
            }
         breakFilter2:
            lpwDestination += 4;
            x1 += 4;
            x2 += 4;
         }
         y1++;
         y2++;
      }

      return true;
   }


   void draw2d::initialize_write_text()
   {

      if(m_pwritetext)
      {

         return;

      }

      ::e_status estatus = ::success;

      try
      {

         auto & pfactoryWriteText = write_text_factory();

         if (pfactoryWriteText)
         {

            pfactoryWriteText->merge_to_global_factory();

         }
         else
         {

            output_error_message("Failed to initialize write_text library.");

            //pfactoryWriteText = (const ::extended::status &) error_failed;

         }

      }
      catch (...)
      {

         estatus = error_exception;

      }

      //if (!estatus)
      //{

      //   information() << "write_text factory_item exchange has failed.\n\nSome reasons:\n   - No write_text library present;\n   - Failure to open any suitable write_text library.";

      //   //return estatus;

      //}

      auto psystem = system();

      //estatus = 

      constructø(m_pwritetext);


   }


   ::pointer<::factory::factory>& draw2d::write_text_factory()
   {

      string strImplementationName;

      if (has_property("write_text"))
      {

         strImplementationName = payload("write_text");

         //strDraw2d.trim();

         //if (strDraw2d.has_character())
         //{

         //   strDraw2d.case_insensitive_begins_eat("draw2d_");

         //   strDraw2d.case_insensitive_begins_eat("draw2d");

         //   strLibrary = "draw2d_" + strDraw2d;

         //}

      }

      ::e_status estatus;

      if (strImplementationName.has_character())
      {

         ::pointer<::aura::system>psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", strImplementationName);

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }

      strImplementationName = write_text_get_default_implementation_name();

      if (strImplementationName.is_empty())
      {

#ifdef WINDOWS

         strImplementationName = system()->implementation_name("write_text", "gdiplus");

#else

         strImplementationName = system()->implementation_name("write_text", "pango");

#endif

      }

      auto psystem = system();

      auto & pfactoryWriteText = psystem->factory("write_text", strImplementationName);

      if (pfactoryWriteText)
      {

         return pfactoryWriteText;

      }


#ifdef WINDOWS_DESKTOP

      if (strImplementationName != system()->implementation_name("write_text", "gdiplus"))
      {

         ::pointer<::aura::system>psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "gdiplus");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


      if (strImplementationName != system()->implementation_name("write_text", "direct2d"))
      {

         ::pointer<::aura::system>psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "direct2d");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }


#endif

      if (strImplementationName != system()->implementation_name("write_text", "pango"))
      {

         auto psystem = system();

         auto & pfactoryWriteText = psystem->factory("write_text", "pango");

         if (pfactoryWriteText)
         {

            return pfactoryWriteText;

         }

      }

      //informationf("No write_text pluging available!!.");
      if (pfactoryWriteText)
      {

         return pfactoryWriteText;

      }

      throw ::exception(error_resource, "No write_text pluging available!!");

      //destroy:

      //   PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("([a-z0-9_]+)_factory");

      //   if (([a-z0-9_]+)_factory == nullptr)
      //   {

      //      return false;

      //   }

      //   ([a-z0-9_]+)_factory(::factory::factory * pfactory);

      //   return true;

   //#endif

   }


   string draw2d::write_text_get_default_implementation_name()
   {
#if defined(WINDOWS_DESKTOP)
      return "win32";
#elif defined(LINUX)

      return "pango";

#elif defined(__ANDROID__)

      return "afont";

#elif defined(__BSD__)


      return "pango";

#else

      return "write_text";

      //return PLATFORM_COMMON_STRING;

#endif

}


   bool draw2d::lock_device()
   {

      return false;

   }


   void draw2d::unlock_device()
   {


   }


   void draw2d::adjust_composited_window_styles(::u32& nExStyle, ::u32& nStyle)
   {

      ////if (!m_papplication->m_bUseSwapChainWindow)
      //{

      //   nExStyle |= WS_EX_LAYERED;

      //}
      //if (m_papplication->m_bUseSwapChainWindow)
      //{

      //   nExStyle |= WS_EX_NOREDIRECTIONBITMAP;
      //   //nExStyle |= WS_EX_TRANSPARENT;
      //}


   }


} // namespace draw2d


