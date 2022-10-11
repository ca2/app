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


   void caller::call(const ::string & pszMessage, const duration & durationTimeout)
   {

      if (!is_caller_ok())
      {

         return;

      }

      //return ::success;

   }


   //void caller::send(int message, void * pdata, int len, const duration & durationTimeout)
   //{

   //   if (message == 0x80000000)
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



