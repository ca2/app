#include "framework.h"


namespace console
{


   prompt::prompt(::particle * pparticle) :
      ::object(pparticle)
   {


      ::user::single_document_template* pdoctemplate;

      pdoctemplate = memory_new ::user::single_document_template(
      get_app(),
      "system/form",
      __type(prompt_document),
      __type(prompt_frame),
      __type(prompt_impact));

      papp->add_document_template(pdoctemplate);

      m_pimpactsystem = pdoctemplate;



   }


   prompt_impact & prompt::impact(bool bShow, bool bCreateMini)
   {

      if(m_pimpactsystem->get_document() == nullptr)
      {

         papp->send_message(WM_APP + 3243,(bShow ? 1 : 0) | (bCreateMini ? 2 : 0));

      }

      if(bShow && !m_pimpactsystem->get_document()->get_typed_impact < prompt_impact >()->is_window_visible())
      {
         if(bCreateMini)
         {

            m_pimpactsystem->get_document()->get_typed_impact < prompt_impact >()->get_typed_parent < prompt_frame > ()->show_mini();
         }
         else
         {
            m_pimpactsystem->get_document()->get_typed_impact < prompt_impact >()->display(e_display_restored);

         }

      }

      return *m_pimpactsystem->get_document()->get_typed_impact < prompt_impact >();

   }


   int prompt::getch()
   {

      return impact().getch();

   }

   void prompt::ungetch(int c)
   {

      impact().ungetch(c);

   }

} // namespace console



















