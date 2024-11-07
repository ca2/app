// Created by camilo on 2024-11-06 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "frame_interaction.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"


namespace acme
{


   namespace user
   {



      frame_interaction::frame_interaction() :
         m_uAcmeUserFrameInteractionFlags(0)
      {

      }


      frame_interaction::~frame_interaction()
      {

      }


      ::pointer<::operating_system::a_system_menu> frame_interaction::create_system_menu(bool bContextual)
      {

         auto psystemmenu = __allocate ::operating_system::a_system_menu();

         if (m_bMinimizeBox)
         {

            psystemmenu->add_item("Minimize", "minimize");

         }

         if (!bContextual || is_window_zoomed())
         {

            psystemmenu->add_item("Restore", "restore");

         }

         if (m_bMaximizeBox)
         {

            if (!bContextual || !is_window_zoomed())
            {

               psystemmenu->add_item("Maximize", "maximize");

            }

         }

         if (::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk4 ||
            ::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk3)
         {
            psystemmenu->add_item("Drag to Move", "***move");
         }
         else
         {
            psystemmenu->add_item("Move", "***move");

         }

         if (m_bResizeable)
         {

            if (::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk4 ||
               ::windowing::get_etoolkit() == ::windowing::e_toolkit_gtk3)
            {
               psystemmenu->add_item("Drag to Size", "***size");
            }
            else
            {
               psystemmenu->add_item("Size", "***size");

            }

         }

         psystemmenu->add_separator();

         if (application()->fill_system_menu(psystemmenu))
         {

            psystemmenu->add_separator();

         }

         psystemmenu->add_item("Close", "close");

         return psystemmenu;

      }



   } // namespace user


} // namespace acme



