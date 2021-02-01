#pragma once


namespace graphics
{


   class CLASS_DECL_AURA multiple_buffer :
      virtual public graphics
   {
   public:


      index                         m_iBuffer;
      index                         m_iDone;
      index                         m_iScreen;

      //
      // Waste of references
      // (or too much references...)
      //
      // Please, do not create array of reference
      // it is perfectly possible, but...
      // (But behind, there is a parallel context_object array in the composer (the array type)
      // ("mirroring"  the references). So why are you keeping references in the array)
      //
      // Easy-Coding Advantage
      // for ca2 framework coding, if all array of pointers (or most of them are)
      // (array of ::pointer, a smart pointer), you can use the same handling for all
      // array of pointers (or most of them are)(array of ::pointer, a smart pointer),
      // i.e., you don't need to "analyze" which memory management model to use,
      // you use just use a array of pointer like any all-array-of-pointers ...
      // any=all all allsquare2-arrayofpointers.... ca2 framework (RR)
      // you may need to repeat much more times to train a biological neural network though....
      // so they learn what is really, actually and simpley and complexly and all good!!
      __pointer_array(::image)            m_imageaBuffer;
      __pointer_array(::mutex)            m_mutexa;


      multiple_buffer();
      virtual ~multiple_buffer();


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl * pimpl) override;


      virtual bool buffer_lock_round_swap_key_buffers() override;

      index find_best_buffer(const ::size_i32 & size);

      using graphics::update_window;
      virtual bool update_window() override;

      virtual sync * get_draw_lock() override;
      virtual ::draw2d::graphics * on_begin_draw() override;

      // sync_lock screen sync first...
      virtual sync * get_screen_sync() override;
      virtual ::image_pointer & get_screen_image() override;

      //virtual ::image_pointer & get_screen_image_and_sync(sync ** psync, const ::size_i32 & size) override;
      //virtual sync * get_screen_sync() override;

   };


} // namespace graphics



