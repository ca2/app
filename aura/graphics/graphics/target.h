// Created by camilo on 2021-01-29 14:13 <3ThomasBS_!!
// From animated_wallpaper to graphics::target by camilo on 2022-05-12 17:40 <3ThomasBorregaardSorensen!! (ThomasLikesNumber5!!)
#pragma once


////#include "acme/primitive/primitive/object.h"


namespace graphics
{


   class CLASS_DECL_AURA target :
      virtual public object
   {
   public:


      //::pointer < ::mutex >     m_pmutex;
      //::image_pointer         m_pimage;
      //int                   o  m_cx;
      //int                     m_cy;
      ::function < void() >                           m_functionFallback;
      ::function < void(target *) >                   m_functionInitializationComplete;


      target();
      ~target() override;


      //virtual void open();
      //virtual void close();


      //virtual void update_wallpaper();

      virtual void render(image* pimage);

      //virtual void on_image_updating();


   };


} // namespace graphics



