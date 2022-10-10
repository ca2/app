#include "framework.h"
#include "axis/database/simpledb/simpledb_socket_thread.h"

#ifdef WINDOWS
//#include <ShlObj.h>
#endif

namespace simpledb
{


   service::service(::object * pobject) :
      ::object(pobject),
      plain_service(pobject)
   {

   }


   service::~service()
   {

   }


   void service::serve()
   {

      ::pointer<::aura::application>pbaseapp = get_app();

      
      ::set_thread(&Sys(pbaseapp));


      m_pmanager = memory_new ::simpledb::manager(pbaseapp);
      

      /*App(pbaseapp).m_strFontopusServer		= psystem->m_simpledb.db().data_load("account_server");
      App(pbaseapp).m_strDatabaseServerHost	= psystem->m_simpledb.db().data_load("database_server");
      App(pbaseapp).m_iDatabaseServerPort	= psystem->m_simpledb.db().data_load("database_port");
      if(App(pbaseapp).m_strDatabaseServerHost.is_empty())
      {
         App(pbaseapp).m_strDatabaseServerHost = "localhost";
      }
      if(App(pbaseapp).m_iDatabaseServerPort <= 0)
      {
         App(pbaseapp).m_iDatabaseServerPort = 0;
      }*/

      string_array stra;

      stra = psystem->m_psimpledb->db().data_load(nullptr, "simpledb").stra();

      for(i32 i = 0; i < stra.get_size(); i++)
      {

         m_threadptra.add(__begin_thread < socket_thread > (this));

         socket_thread * pthread = m_threadptra.last();
         {

            pthread->m_evInitialized.wait();
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 443;
            pthread->m_pservice = this;
            pthread->post_message(WM_APP);

         }

      }

      while (get_run_service())
      {

         sleep(1_s);

      }

      sleep(10000_ms);

   }


} // namespace simpledb








