#include "framework.h" // from "aura/net/net_sockets.h"
#include "aura/net/net_sockets.h"
#include "simple_pop3.h"


namespace mail
{


   simple_pop3::simple_pop3(::context_object * pcontextobject) :
      ::object(pobject),
      pop3(pobject)
   {

   }


   string simple_pop3::get_user()
   {

      return m_strUser;

   }


   string simple_pop3::get_pass()
   {
      return m_strPass;
   }

   string simple_pop3::get_host()
   {
      return m_strHost;
   }

   string simple_pop3::get_transaction()
   {
      return m_strTransaction;
   }

   void simple_pop3::set_stat_count(i32 iCount)
   {
      m_iStatCount = iCount;
   }

   void simple_pop3::set_stat_size(i32 iSize)
   {
      m_iStatSize = iSize;
   }

   void simple_pop3::set_list_size(i32 iSize)
   {
      m_iListSize = iSize;
   }

   void simple_pop3::store()
   {
   }

} // namespace mail
