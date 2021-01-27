#include "framework.h"


namespace http
{


   message::message() 
   {

      m_pcookies     = nullptr;
      m_estatusRet   = ::success_none;

   }


   void message::want_memory_response(memory_base * pbase)
   {

      if (::is_set(pbase))
      {

         payload("get_memory") = create_memory();

      }
      else
      {

         payload("get_memory") = pbase;

      }

   }


   void message::want_string_response()
   {

      want_memory_response();

   }


   memory_pointer message::get_memory_response()
   {

      return payload("get_memory").cast < memory>();

   }


   string message::get_string_response()
   {

      auto pmemory = get_memory_response();

      if (::is_null(pmemory))
      {

         return "";

      }

      string str;

      pmemory->to_string(str);

      return str;

   }



} // namespace http




