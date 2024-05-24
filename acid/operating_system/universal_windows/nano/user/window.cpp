#include "framework.h"
#include "window.h"
#include "acid/operating_system/universal_windows/_winrt_foundation.h"
#include "acid/platform/application.h"
#include "acid/platform/platform.h"
#include "acid/nano/user/button.h"
#include "acid/nano/user/window.h"
#include "acid/nano/user/user.h"


#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Popups.h>
#include <winrt/Windows.Foundation.Collections.h>


namespace universal_windows
{


   namespace nano
   {


      namespace user
      {

         window::window()
         {


         }


         window::~window()
         {


         }


         void window::create()
         {

            if (platform()->m_bConsole)
            {

               _console_create();

            }
            else
            {

               m_messagedialog = ::winrt::Windows::UI::Popups::MessageDialog(as_hstring(m_pinterface->m_strMessage), as_hstring(m_pinterface->m_strTitle));

               for (auto & pnanobutton : m_pinterface->m_nanobuttona)
               {

                  auto predicate = [this, pnanobutton](::winrt::Windows::UI::Popups::IUICommand command)
                     {

                        on_click(pnanobutton->m_edialogresult1, nullptr);

                     };

                  ::winrt::Windows::UI::Popups::UICommand command(as_hstring(pnanobutton->m_strText), predicate);

                  m_messagedialog.Commands().Append(command);

               }

               m_messagedialog.DefaultCommandIndex(0);

               m_messagedialog.CancelCommandIndex(1);

            }

            //::user::message_box::show(puserinteraction, strMessage, strMessage, emessagebox);

         }


         void window::display()
         {

            if (platform()->m_bConsole)
            {

               _display_console();

            }
            else
            {

               m_messagedialog.ShowAsync();

            }

         }

      } // namespace user


   } // namespace nano


} // namespace universal_windows



void operating_system_initialize_nano_user(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::universal_windows::nano::user::window, ::nano::user::window_implementation >();

   pfactory->add_factory_item < ::nano::user::user >();
   //pfactory->add_factory_item < ::windows::nano::user::brush, ::nano::user::brush >();
   //pfactory->add_factory_item < ::windows::nano::user::font, ::nano::user::font >();
   //pfactory->add_factory_item < ::windows::nano::user::pen, ::nano::user::pen >();
   //pfactory->add_factory_item < ::windows::nano::user::device, ::nano::user::device >();


}


bool is_ui_possible()
{

   auto mainview = ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView();

   if (!mainview)
   {

      return false;

   }

   return true;


}