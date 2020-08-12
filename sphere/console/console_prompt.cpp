#include "framework.h"


namespace console
{


   prompt::prompt(::object * pobject) :
      ::object(pobject)
   {


      ::user::single_document_template* pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
      get_context_application(),
      "system/form",
      __type(prompt_document),
      __type(prompt_frame),
      __type(prompt_impact));

      Application.add_document_template(pdoctemplate);

      m_pdocumenttemplate = pdoctemplate;



   }


   prompt_impact & prompt::impact(bool bShow, bool bCreateMini)
   {

      if(m_pdocumenttemplate->get_document() == nullptr)
      {

         Application.send_message(WM_APP + 3243,(bShow ? 1 : 0) | (bCreateMini ? 2 : 0));

      }

      if(bShow && !m_pdocumenttemplate->get_document()->get_typed_view < prompt_impact >()->is_window_visible())
      {
         if(bCreateMini)
         {

            m_pdocumenttemplate->get_document()->get_typed_view < prompt_impact >()->GetTypedParent < prompt_frame > ()->show_mini();
         }
         else
         {
            m_pdocumenttemplate->get_document()->get_typed_view < prompt_impact >()->display(display_normal);

         }

      }

      return *m_pdocumenttemplate->get_document()->get_typed_view < prompt_impact >();

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



















