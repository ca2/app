#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE frame : 
      public simple_frame_window
   {
   public: 


      
      
      ::image::image_list_pointer               m_pimagelist;
      bool                       m_bTimerOn;


      frame(::particle * pparticle);
      virtual ~frame();

      virtual bool pre_create_window(::user::system * pusersystem);

      void ShowControlBars(bool bShow);
      
      
   
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
   

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void OnTimer(unsigned int uEvent);

   };

} // namespace calculator




