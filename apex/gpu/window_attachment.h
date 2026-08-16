// Created by camilo on 2026-08-07 10:58 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


namespace apex
{


   namespace gpu
   {


      class CLASS_DECL_APEX window_attachment :
         virtual public ::particle
      {
      public:


         ::collection::index                                m_iCurrentFrame3;
         ::collection::index                                m_iCurrentImage;
         ::collection::index                                m_iFrameSerial2;
         ::collection::count                                m_iFrameCount;

         ::pointer < ::acme::windowing::window >            m_pacmewindowingwindow;


         window_attachment();
         ~window_attachment() override;


         virtual void initialize_gpu_window_attachment(::acme::windowing::window * pwindow);


         virtual ::i32 get_frame_index3();
         virtual ::i32 get_image_index();
         virtual ::i32 get_frame_count();
         virtual void restart_frame_counter();
         virtual bool is_starting_frame()const;



      };





   }


} // namespace apex


