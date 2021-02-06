#include "framework.h"


namespace console
{


   department::department(::layered * pobjectContext) :
      ::apex::department(pobject)
   {

   }


   department::~department()
   {

   }


   bool department::init_instance()
   {


      create_factory <console::prompt_document >();
      create_factory <console::prompt_frame >();
      create_factory <console::prompt_impact >();

      if(!::apex::department::init_instance())
         return false;


      m_spprompt = __new(prompt(this));

      console_prompt().impact(false);



      return true;

   }


   void department::pre_translate_message(::message::message * pmessage)
   {

      __pointer(::message::base) pbase(pmessage);

      if(pbase != nullptr)
      {
         if(pbase->m_id == e_message_key_down)
         {

            __pointer(::message::key) pkey(pmessage);

            if(pkey->m_ekey == ::user::e_key_semicolon2 && psession->is_key_pressed(::user::e_key_shift))
            {

               if (m_spprompt.is_set())
               {

                  console_prompt().impact().keyboard_set_focus();

               }

            }
         }

      }

      //return ::userstack::department::pre_translate_message(pmessage);
      //return false;

   }


   void department::_001OnImpact(::message::message * pmessage)
   {

      __pointer(::message::base) pbase(pmessage);


      bool bShow = pmessage->m_wparam & 1;

      bool bCreateMini = (pmessage->m_wparam & 2) != 0;

      bool bCreate = false;

      if(m_spprompt->m_pdocumenttemplate->get_document() == nullptr)
      {

         bCreate = true;

         m_spprompt->m_pdocumenttemplate->open_document_file(get_context_application(), nullptr,false);

      }

      prompt_impact & i = *m_spprompt->m_pdocumenttemplate->get_document()->get_typed_view < prompt_impact >();

      if(bShow)
      {

         if(bCreate && bCreateMini)
         {

            i.GetTypedParent < prompt_frame >()->show_mini();
         }
         else
         {
            i.get_top_level()->display(e_display_normal);

         }

      }

      pbase->m_bRet = true;

   }


} // namespace userstack






















