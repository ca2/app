#include "framework.h"
#include "message.h"
#include "acme/primitive/primitive/memory.h"


namespace http
{


   message::message() 
   {

      m_pcookies     = nullptr;
      m_estatusRet   = ::success_none;

   }


   void message::want_memory_response(memory_base * pusermessage)
   {

      if (::is_set(pusermessage))
      {

         payload("get_memory") = create_memory();

      }
      else
      {

         payload("get_memory") = pusermessage;

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

      str = pmemory->as_string();

      return str;

   }



} // namespace http




