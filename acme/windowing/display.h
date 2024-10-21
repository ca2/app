//
// Created by camilo on 12/04-April/2022. 22:07 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
namespace acme
{

   namespace windowing
   {


      class CLASS_DECL_ACME display :
         virtual public ::object
      {
      public:
         //::array < ::procedure >      m_procedureaPost;
         ::point_i32 m_pointCursor2;

         enum_display_type m_edisplaytype;


         //inline static display * g_p = nullptr;


         display();


         ~display() override;


         virtual void open_display();


         virtual enum_display_type get_display_type();


         virtual void initialize_display_type(enum_display_type edisplaytype);


         void kick_idle() override;


         virtual void display_post(const ::procedure& procedure);


         virtual void display_send(const ::procedure& procedure);


         //virtual bool display_posted_routine_step();


         virtual ::size_i32 get_main_screen_size();


      };


   } // namespace windowing


} // namespace acme
