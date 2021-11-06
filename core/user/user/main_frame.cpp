// Created by camilo on 2021-10-09 18:43 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "main_frame.h"


namespace user
{


   main_frame::main_frame()
   {


   }


   main_frame::~main_frame()
   {


   }


   void main_frame::install_message_routing(::channel * pchannel)
   {

      simple_main_frame::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &main_frame::on_message_create);

   }


   void main_frame::assert_valid() const
   {

      simple_main_frame::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_main_frame::dump(dumpcontext);

   }

   
   void main_frame::on_message_create(::message::message * pmessage)
   {



   }



   ::user::tool_window * main_frame::tool_window(enum_tool etool, bool bCreate)
   {

      if (etool == e_tool_font)
      {

         if (!m_prichtextformattool)
         {

            if (bCreate)
            {

               __construct_new(m_prichtextformattool);

               m_prichtextformattool->create_host();

               m_prichtextformattool->set_owner(this);

            }

         }

         return m_prichtextformattool;

      }

      return nullptr;

   }



} // namespace user
