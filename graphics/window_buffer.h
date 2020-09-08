#pragma once


namespace graphics
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      ::image_pointer                       m_pimageBuffer;

      bool                          m_bDibIsHostingBuffer;
      file::memory_map              m_memorymap;


      window_buffer();
      virtual ~window_buffer();


      //virtual void initialize(::user::interaction_impl* pimpl) override;
      ::draw2d::graphics * on_begin_draw(sync ** ppsync) override;
      virtual bool update_window() override;
      virtual bool round_swap_key_buffers() override;


      virtual bool create_buffer(const ::size & size, int iStride = -1);
      virtual void destroy_buffer();
      inline ::size buffer_size() { return m_pimageBuffer->size(); }


      virtual void defer_initialize_ipc_copy();

/*      virtual bool update_window(::image * pimage);
      virtual bool is_buffer_ok();
      ::image_pointer & get_buffer();

      virtual bool ipc_copy(const pixmap * ppixmap);


   };


} // namespace graphics



