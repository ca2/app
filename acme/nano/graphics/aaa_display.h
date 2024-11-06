//
// Created by camilo on 12/04-April/2022. 22:07 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
namespace nano
{

   namespace user
   {
   

   class CLASS_DECL_ACME display :
      virtual public ::object
   {
   public:


      ::array < ::procedure >      m_procedureaPost;
      ::int_point                   m_pointCursor2;


      inline static display * g_p = nullptr;


      display();
      ~display() override;


      void kick_idle() override;
      virtual void display_post(const ::procedure & procedure);
      virtual void display_send(const ::procedure & procedure);
      virtual bool display_posted_routine_step();


      virtual ::int_size get_main_screen_size();


   };


   } // namespace user


} // namespace nano



