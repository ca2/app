// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "caller.h"


namespace interprocess
{


   caller::caller()
   {

   }


   caller::~caller()
   {


   }


   void caller::open(const ::string & strChannel, launcher * plauncher)
   {

      //return true;

   }


   void caller::close()
   {

      //if (get_hwnd() == nullptr)
      //{

      //   return true;

      //}

      //set_hwnd(nullptr);

      m_strBaseChannel = "";

      //return true;

   }


   void caller::call(const ::string & pszMessage, const class time & timeTimeout)
   {

      if (!is_caller_ok())
      {

         return;

      }

      //return ::success;

   }


   //void caller::send(int message, void * pdata, int len, const class time & timeTimeout)
   //{

   //   if (message == I32_MINIMUM)
   //   {

   //      //return false;

   //      return;

   //   }

   //   if (!is_tx_ok())
   //   {

   //      //return false;

   //      return;

   //   }


   //   //return true;

   //}


   bool caller::is_caller_ok()
   {

      return false;

   }


} // namespace interprocess



