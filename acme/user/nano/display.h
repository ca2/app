//
// Created by camilo on 12/04-April/2022. 22:07 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace nano
{


   class CLASS_DECL_ACME display :
      virtual public ::object
   {
   public:


      ::array < ::procedure >      m_procedureaPost;


      static display *                       g_p;


      display();
      ~display() override;


      virtual void kick_idle();
      virtual void display_post(const ::procedure & procedure);
      virtual void display_send(const ::procedure & procedure);
      virtual bool display_posted_routine_step();


   };



} // namespace nano



