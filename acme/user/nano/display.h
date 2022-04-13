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


      ::array < ::function < void() > >      m_functionaPost;


      static display *                       g_p;


      display();
      ~display() override;


      virtual void kick_idle();
      virtual void display_post(const ::function < void() > & function);
      virtual void display_send(const ::function < void() > & function);
      virtual bool display_posted_routine_step();


   };



} // namespace nano



