#include "framework.h"

#include "base/net/net_sockets.h"
#include "simpledb_socket.h"


namespace simpledb
{


   manager::manager(::particle * pparticle) :
      ::object(pparticle),
      thread(pparticle),
      
      
      
      m_spqueue(e_create)
   {
      m_dwBuildTimeWindow = 84;
      m_dwBuildTimeRandomWindow = 77 * 5;

      m_iDatabaseWaitTimeOut = 1000 * 1000 * 60;

      begin();

   }

   manager::~manager()
   {
   }



   bool manager::init_instance()
   {

      m_spqueue->create_message_queue("::aura::netnode::ca2");

      return true;

   }


   bool manager::handle(socket * psocket)
   {
      memory memory;
      if(!get_output_internal(psocket->inattr("request_uri"), memory))
      {
         string strError;
         strError = "Error processing command";
         psocket->response().file()->write(strError, strError.length());
         return false;
      }
      psocket->response().file()->write(memory.get_data(), memory.get_size());
      psocket->outheader("content-type") = "application/x-aura-::payload";
      return true;
   }

   bool manager::get_output_internal(const ::scoped_string & scopedstrCommand, memory & memory)
   {
      __UNREFERENCED_PARAMETER(scopedstrCommand);
      __UNREFERENCED_PARAMETER(memory);
      return true;
   }



   void manager::message_queue_message_handler(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);
      if(pusermessage->id() == WM_APP + 13)
      {
         //if(wparam == 0)
           // ((script *) lparam)->Load(false);
         //else if(wparam == 13)
           // ((script *) lparam)->Unload(false);
         pusermessage->m_bRet = true;
      }
      else if(pusermessage->id() == WM_APP + 14)
      {
      }
   }





   session * & manager::get_session(const ::scoped_string & scopedstrId)
   {
      single_lock synchronouslock(m_pmutexSession, true);
      ::simpledb::session * & psession = m_mapSession[pszId];
      return psession;
   }



} // namespace simpledb



