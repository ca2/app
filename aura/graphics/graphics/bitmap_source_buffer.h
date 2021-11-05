#pragma once


namespace graphics
{


   class CLASS_DECL_AURA bitmap_source_buffer :
      virtual public graphics
   {
   public:


      __pointer(file::memory_map)   m_pmemorymap;
      string                              m_strBitmapSource;


      bitmap_source_buffer();
      virtual ~bitmap_source_buffer();


      inline bool is_ipc_copy_enabled() const { return m_pmemorymap && m_pmemorymap->is_mapped(); }


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl* pimpl) override;

      virtual ::e_status enable_ipc_copy(const ::string & strBitmapSource);

      virtual bool ipc_copy(const pixmap * ppixmap);

      virtual bool buffer_lock_round_swap_key_buffers() override;


   };

} // namespace graphics



