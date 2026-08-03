// Created by camilo on 2026-07-31 16:36 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA window_attachment : 
      virtual public ::particle
   {
   public:


      ::pointer<::windowing::window> m_pwindow;


      window_attachment();
      ~window_attachment() override;

      
      virtual void initialize_window_attachment(::windowing::window * pwindow);


   };


} // namespace draw2d_direct2d
