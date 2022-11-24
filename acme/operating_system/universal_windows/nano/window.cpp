#include "framework.h"
#include "window.h"
#include "acme/operating_system/universal_windows/_winrt_foundation.h"
#include "acme/user/nano/button.h"
#include "acme/user/nano/window.h"


#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Popups.h>
#include <winrt/Windows.Foundation.Collections.h>


namespace universal_windows
{


   nano_window::nano_window()
   {


   }


   nano_window::~nano_window()
   {


   }


   void nano_window::create()
   {

      m_messagedialog = ::winrt::Windows::UI::Popups::MessageDialog(__hstring(m_pinterface->m_strMessage), __hstring(m_pinterface->m_strTitle));

      for (auto & pbutton : m_pinterface->m_buttona)
      {

         auto predicate = [this, pbutton](::winrt::Windows::UI::Popups::IUICommand command)
         {

            on_click(pbutton->m_edialogresult, nullptr);

         };

         ::winrt::Windows::UI::Popups::UICommand command(__hstring(pbutton->m_strText), predicate);

         m_messagedialog.Commands().Append(command);

      }

      //::user::message_box::show(puserinteraction, strMessage, strMessage, emessagebox);

      m_messagedialog.DefaultCommandIndex(0);

      m_messagedialog.CancelCommandIndex(1);



   }

   
   void nano_window::display()
   {

      m_messagedialog.ShowAsync();

   }


} // namespace universal_windows



void operating_system_initialize_nano(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::universal_windows::nano_window, ::nano_window_implementation >();
   //pfactory->add_factory_item < ::windows::nano_brush, ::nano_brush >();
   //pfactory->add_factory_item < ::windows::nano_font, ::nano_font >();
   //pfactory->add_factory_item < ::windows::nano_pen, ::nano_pen >();
   //pfactory->add_factory_item < ::windows::nano_device, ::nano_device >();


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