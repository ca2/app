#pragma once


namespace graphics
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      ::image::image_pointer               m_pimageBuffer;

      bool                          m_bDibIsHostingBuffer;
      file::memory_map              m_memorymap;


      window_buffer();
      virtual ~window_buffer();


      //virtual void initialize(::windowing::window* pimpl) override;
      ::draw2d::graphics * on_begin_draw(synchronization ** ppsync) override;
      virtual bool update_window() override;
      virtual bool round_swap_key_buffers() override;


      bool update_buffer(const ::int_size & size, int iStride = -1) override;
      void destroy_buffer();
      inline ::int_size buffer_size() { return m_pimageBuffer->size(); }


      virtual void defer_initialize_ipc_copy();

/*      virtual bool update_window(::image::image *pimage);
      virtual bool is_buffer_ok();
      ::image::image_pointer & get_buffer();

      virtual bool ipc_copy(const pixmap * ppixmap);


   };


} // namespace graphics



