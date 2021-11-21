#pragma once


namespace graphics
{


   class CLASS_DECL_AURA bitmap_source_buffer :
      virtual public graphics
   {
   public:


      __pointer(file::memory_map)         m_pmemorymap;
      string                              m_strBitmapSource;
      __pointer(::mutex)                  m_pmutexBitmapSource;


      bitmap_source_buffer();
      ~bitmap_source_buffer() override;


      inline bool is_ipc_copy_enabled() const { return m_pmemorymap && m_pmemorymap->is_mapped(); }

      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl* pimpl) override;

      bool ipc_copy(const pixmap * ppixmap) override;

      ::e_status set_bitmap_source(const string& strBitmapSource) override;

      ::e_status clear_bitmap_source() override;

      string get_bitmap_source() const override;

      virtual bool buffer_lock_round_swap_key_buffers() override;


   };

} // namespace graphics



