#include "framework.h"
#include "base/net/net_sockets.h"
#include "aura/database/simpledb/simpledb_socket_thread.h"

#ifdef WINDOWS
#include <ShlObj.h>
#endif

namespace simpledb
{


   service::service(::layered * pobjectContext) :
      ::object(pobject),
      plain_service(pobject)
   {
   }

   service::~service()
   {
   }

   void service::serve()
   {

      __pointer(::aura::application) pbaseapp = get_context_application();

      ::set_thread(&Sys(pbaseapp));


      m_pmanager = new ::simpledb::manager(pbaseapp);


      /*App(pbaseapp).m_strFontopusServer		= System.m_simpledb.db().data_load("account_server");
      App(pbaseapp).m_strDatabaseServerHost	= System.m_simpledb.db().data_load("database_server");
      App(pbaseapp).m_iDatabaseServerPort	= System.m_simpledb.db().data_load("database_port");
      if(App(pbaseapp).m_strDatabaseServerHost.is_empty())
      {
         App(pbaseapp).m_strDatabaseServerHost = "localhost";
      }
      if(App(pbaseapp).m_iDatabaseServerPort <= 0)
      {
	      App(pbaseapp).m_iDatabaseServerPort = 0;
      }*/


      string_array stra;
      stra = System.m_simpledb.db().data_load(nullptr, "simpledb");
      for(i32 i = 0; i < stra.get_size(); i++)
      {
         m_threadptra.add(__begin_thread < socket_thread > (get_object()));
         socket_thread * pthread = m_threadptra.last();
         {
            pthread->m_evInitialized.wait();
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 443;
            pthread->m_pservice = this;
            pthread->post_thread_message(WM_APP);
         }
      }

      while (thread_get_run())
      {
         sleep(1_s);
      }
      sleep(10000);

   }


} // namespace simpledb

