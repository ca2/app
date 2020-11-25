#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_windows.h"
#endif
#include "aura/message.h"
#include "aura/procedure.h"
#include "system_interaction_impl.h"


namespace user
{


   system_interaction_impl::system_interaction_impl()
   {

      m_ewindowflag -= window_flag_graphical;
      m_bMessageWindow = true;

   }


   system_interaction_impl::~system_interaction_impl()
   {


   }


   void system_interaction_impl::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &system_interaction_impl::_001OnDestroy);
      MESSAGE_LINK(WM_SETTINGCHANGE, pchannel,this,&system_interaction_impl::_001OnMessage);
      MESSAGE_LINK(e_message_display_change, pchannel,this,&system_interaction_impl::_001OnMessage);
      MESSAGE_LINK(WM_FONTCHANGE, pchannel, this, &system_interaction_impl::_001OnMessage);

   }


   bool system_interaction_impl::is_system_message_window()
   {

      return true;

   }


   bool system_interaction_impl::DestroyWindow()
   {

      return ::user::interaction::DestroyWindow();

   }


   void system_interaction_impl::_001OnDestroy(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      ::output_debug_string("system_interaction_impl::_001OnDestroy");

   }


   void system_interaction_impl::_001OnMessage(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (pbase != nullptr)
      {

         WPARAM wparam = pbase->m_wparam;
         LPARAM lparam = pbase->m_lparam;

         string strLparamString;

         if (pbase->m_id == WM_SETTINGCHANGE && wparam == 0)
         {

            strLparamString = (LPCTSTR(lparam));

         }

         if (pbase->m_id == WM_FONTCHANGE)
         {


            System.process_subject(id_os_font_change);

            //fork([this]()
              // {

                 // psession->call(e_procedure_font_change);

               //});

         //}
      }
      else if (
         pbase->m_id == WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
      {

         System.process_subject(id_dark_mode);

      }
         else if (pbase->m_id == e_message_display_change ||
               (pbase->m_id == WM_SETTINGCHANGE &&
                (pbase->m_wparam == SPI_SETWORKAREA)))
         {

            output_debug_string("test");

            //throw_todo();

            //System.enum_display_monitors();

            //__pointer(::user::interaction) pinteraction;

            //while(System.get_frame(pinteraction))
            //{

            //   try
            //   {

            //      pinteraction->post_message(e_message_display_change);

            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }

      }

   }


} // namespace base


CLASS_DECL_AURA ::user::interaction * create_system_message_window(::layered * pobjectContext)
{

   ::user::system_interaction_impl * pimpl = new ::user::system_interaction_impl;

    pimpl->initialize(pobjectContext);

    ::user::create_struct createstruct;

    if (!pimpl->create_window_ex(createstruct, nullptr, "::user::system_interaction_impl"))
    {

       return false;

    }

    return pimpl;

}



