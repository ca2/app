#include "framework.h"


CLASS_DECL_BASE int_bool ui_get_cursor_pos(POINT * ppt)
{

   if (ppt == nullptr)
      return FALSE;

   int_bool iRet = FALSE;

   ::point pointCursor;

   ::wait(Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([=, &pointCursor, &iRet]()
   {

      try
      {

         iRet = ::GetCursorPos(&pointCursor);

      }
      catch (...)
      {

      }

   })));

   if (iRet != FALSE)
   {

      *ppt = pointCursor;

   }

   return iRet;

}



