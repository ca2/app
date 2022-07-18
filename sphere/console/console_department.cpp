#include "framework.h"


namespace console
{


   department::department(::object * pobject) :
      ::acme::department(pobject)
   {

   }


   department::~department()
   {

   }


   bool department::init_instance()
   {


      add_factory_item <console::prompt_document >();
      add_factory_item <console::prompt_frame >();
      add_factory_item <console::prompt_impact >();

      if(!::acme::department::init_instance())
         return false;


      m_spprompt = __new(prompt(this));

      console_prompt().impact(false);



      return true;

   }


   void department::pre_translate_message(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      if(pusermessage != nullptr)
      {
         if(pusermessage->m_atom == e_message_key_down)
         {

            auto pkey = pmessage->m_union.m_pkey;

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

      __pointer(::user::message) pusermessage(pmessage);


      bool bShow = pmessage->m_wparam & 1;

      bool bCreateMini = (pmessage->m_wparam & 2) != 0;

      bool bCreate = false;

      if(m_spprompt->m_pdocumenttemplate->get_document() == nullptr)
      {

         bCreate = true;

         m_spprompt->m_pdocumenttemplate->open_document_file(get_app(), nullptr,false);

      }

      prompt_impact & i = *m_spprompt->m_pdocumenttemplate->get_document()->get_type_impact < prompt_impact >();

      if(bShow)
      {

         if(bCreate && bCreateMini)
         {

            i.GetTypedParent < prompt_frame >()->show_mini();
         }
         else
         {
            i.get_top_level()->display(e_display_restored);

         }

      }

      pusermessage->m_bRet = true;

   }


} // namespace userstack






















