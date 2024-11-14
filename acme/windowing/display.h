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


         ::int_point             m_pointCursor2;

         //enum_display_type       m_edisplaytype;


         display();
         ~display() override;


         virtual void open_display();


         void destroy() override;


         //virtual enum_display_type get_display_type();


         //virtual void initialize_display_type(enum_display_type edisplaytype);


         void kick_idle() override;


         virtual void display_post(const ::procedure& procedure);


         virtual void display_send(const ::procedure& procedure);


         virtual ::int_size get_main_screen_size();

virtual void * raw_x11_display();
      };


   } // namespace windowing


} // namespace acme
