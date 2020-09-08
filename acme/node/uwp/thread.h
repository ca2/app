#pragma once


template < typename PRED >
void defer_main_thread(PRED pred)
{

   if (::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->HasThreadAccess)
   {

      pred();

   }
   else
   {

      ::wait(
      Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
      ::Windows::UI::Core::CoreDispatcherPriority::Normal,
      ref new Windows::UI::Core::DispatchedHandler([&pred]()
      {

         pred();

      })));

   }

}
