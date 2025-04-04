#include "framework.h"
#include "window.h"
#include "acme/operating_system/universal_windows/_winrt_foundation.h"
#include "acme/platform/application.h"
#include "acme/platform/platform.h"
#include "acme/user/micro/button.h"
#include "acme/user/micro/window.h"
#include "acme/user/micro/user.h"


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

            if (::system()->m_bConsole)
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

            if (::system()->m_bConsole)
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


   pfactory->add_factory_item < ::universal_windows::micro::elemental, ::micro::window_implementation >();

   pfactory->add_factory_item < ::micro::user >();
   //pfactory->add_factory_item < ::windows::nano::graphics::brush, ::nano::graphics::brush >();
   //pfactory->add_factory_item < ::windows::nano::graphics::font, ::nano::graphics::font >();
   //pfactory->add_factory_item < ::windows::nano::graphics::pen, ::nano::graphics::pen >();
   //pfactory->add_factory_item < ::windows::nano::graphics::device, ::nano::graphics::device >();


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