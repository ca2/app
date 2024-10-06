#pragma once


#include "acme/parallelization/manual_reset_event.h"
#include "acme/prototype/geometry2d/point.h"
#include "acme/prototype/geometry2d/size.h"


namespace graphics
{


   class CLASS_DECL_AURA buffer_item :
      virtual public ::particle
   {
   public:

      
      ::e_graphics                  m_egraphics;
      ::image::image_pointer               m_pimage2;
      ::mutex_pointer               m_pmutex;
      ::draw2d::graphics_pointer    m_pgraphics;
      ::point_i32                   m_point;
      ::size_i32                    m_size;
      ::pointer < ::particle >      m_pparticleData;
      manual_reset_event            m_manualresetevent;
      ::size_i32                    m_sizeInternal;
      ::i32                         m_iScan;


      ::draw2d::graphics_pointer g();


      void destroy() override;


   };


   class CLASS_DECL_AURA graphics :
      virtual public ::object
   {
   public:


      //::pointer<::windowing::window>          m_pimpl;
      ::pointer<::windowing::window>               m_pwindow;
      bool                                         m_bNewBuffer;

      union
      {

         ::uptr                                    m_uptrBuffer;
         ::OPERATING_SYSTEM_NAMESPACE::buffer *    m_pPlatformBuffer;
         ::windowing_universal_windows::buffer *   m_pWindowingUniversalWindowsBuffer;
         ::windowing_win32::buffer *               m_pWindowingWin32Buffer;

      };


      ::pointer_array<buffer_item >                m_bufferitema;


      graphics();
      ~graphics() override;


      
      virtual void initialize_graphics_graphics(::windowing::window * pwindow);


      void destroy() override;

      virtual void destroy_buffer();

      virtual bool is_single_buffer_mode() const;

      //virtual bool presentation_complete();
      virtual void on_after_graphical_update();

      virtual bool buffer_lock_round_swap_key_buffers();

      virtual bool update_screen();

      virtual bool on_update_screen(buffer_item * pitem);

      virtual void buffer_size_and_position(buffer_item * pitem);

      virtual i64 _001GetTopLeftWeightedOpaqueArea(const ::rectangle_i32 &rect);

      //virtual ::particle * get_draw_lock();
      virtual buffer_item * on_begin_draw(::e_graphics egraphics);

      virtual bool _on_begin_draw(buffer_item * pbufferitem);

      virtual void on_end_draw();

      //virtual bool update_buffer(const ::size_i32 & size, int iStrideParam = -1);

      virtual bool update_buffer(buffer_item * pitem);

      virtual bool ipc_copy(const pixmap* ppixmap);

      virtual void set_bitmap_source(const string& strBitmapSource);

      virtual void clear_bitmap_source();

      virtual string get_bitmap_source() const;

      virtual buffer_item * get_buffer_item();
      //virtual ::image::image_pointer & get_buffer_image();
      //virtual ::particle * get_buffer_sync();
      virtual buffer_item * get_screen_item();
      //virtual ::image::image_pointer & get_screen_image();
      //virtual ::particle * get_screen_sync();

      ::trace_statement & trace_statement_prefix(::trace_statement & statement) const override;


   };


} // namespace graphics



