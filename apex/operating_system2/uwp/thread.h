#pragma once


template < typename PRED >
void defer_main_thread(PRED pred)
{

   if (::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->HasThreadAccess)
   {

      pred();

   }
   else
   {

      ::wait(
      ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
      ::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
      ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler([&pred]()
      {

         pred();

      })));

   }

}
