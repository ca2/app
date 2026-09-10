#pragma once


#include "graphics.h"
#include "acme/filesystem/file/memory_map.h"


namespace graphics
{


   constexpr ::i64 BITMAP_SOURCE_BUFFER_MAGIC = 0x324D5042324143LL;
   constexpr ::i64 BITMAP_SOURCE_BUFFER_VERSION = 2;


   struct bitmap_source_buffer_header
   {

      ::i64 m_iMagic;
      ::i64 m_iVersion;
      ::i64 m_xWindow;
      ::i64 m_yWindow;
      ::i64 m_cxWindow;
      ::i64 m_cyWindow;
      ::i64 m_xMonitor;
      ::i64 m_yMonitor;
      ::i64 m_cxMonitor;
      ::i64 m_cyMonitor;
      ::i64 m_cxBitmap;
      ::i64 m_cyBitmap;
      ::i64 m_iScan;
      ::i64 m_bTopLeft;

   };


   class CLASS_DECL_AURA bitmap_source_buffer_graphics :
      virtual public graphics
   {
   public:


      ::pointer<file::memory_map>        m_pmemorymap;
      string                              m_strBitmapSource;
      ::pointer < ::mutex >                 m_pmutexBitmapSource;


      bitmap_source_buffer_graphics();
      ~bitmap_source_buffer_graphics() override;


      inline bool is_ipc_copy_enabled() const { return m_pmemorymap && m_pmemorymap->is_mapped(); }

      void initialize_graphics_graphics(::windowing::window * pwindow) override;

      bool ipc_copy(const pixmap * ppixmap) override;

      void set_bitmap_source(const ::scoped_string & scopedstrBitmapSource, bool bCreate = true) override;

      void clear_bitmap_source() override;

      string get_bitmap_source() const override;

      bool buffer_lock_round_swap_key_buffers() override;


   };

} // namespace graphics



