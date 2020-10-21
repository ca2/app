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

      IGUI_MSG_LINK(WM_SETTINGCHANGE, pchannel,this,&system_interaction_impl::_001OnMessage);
      IGUI_MSG_LINK(WM_DISPLAYCHANGE, pchannel,this,&system_interaction_impl::_001OnMessage);
      IGUI_MSG_LINK(WM_FONTCHANGE, pchannel, this, &system_interaction_impl::_001OnMessage);

   }


   bool system_interaction_impl::is_system_message_window()
   {

      return true;

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


            system_update(id_os_font_change);

            //fork([this]()
              // {

                 // Session.call(e_method_font_change);

               //});

         //}
      }
      else if (
         pbase->m_id == WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
      {

         system_update(id_dark_mode);

      }
         else if (pbase->m_id == WM_DISPLAYCHANGE ||
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

            //      pinteraction->post_message(message_display_change);

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



