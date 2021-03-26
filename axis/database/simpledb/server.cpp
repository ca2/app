#include "framework.h"
#include "aura/operating_system.h"
#include "_simpledb.h"
#include "axis/database/sqlitedb/_.h"
#include <sqlite3.h>
#include "storage.h"


namespace simpledb
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::e_status server::initialize_simpledb_server(::object * pobject, const char * pszDatabase)
   {

      auto estatus = ::database::server::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_bRemote = !m_pcontext->m_pcontext->is_local_data();

      if (m_pdatabaseLocal.is_set())
      {

         finalize();

      }

      ::file::path pathDatabase(pszDatabase);

      if (!m_pcontext->m_pcontext->dir().mk(pathDatabase.folder()))
      {

         return false;

      }

      auto pdatabase = (*m_psystem->m_pfactorymapsquare)["simpledb"]->new_object<::database::database>();

      if (pdatabase.is_null())
      {

         return false;

      }

      synchronization_lock synchronizationlock(pdatabase->mutex());

      //estatus = pdatabase->set_finish(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pdatabaseLocal = pdatabase;

      estatus = __compose_new(m_psimpledb);

      if (!estatus)
      {

         return ::error_failed;

      }

      estatus = m_psimpledb->initialize_simpledb(this);

      if (!estatus)
      {

         return ::error_failed;

      }

      if (!create_server_dataset())
      {

         return ::error_failed;

      }

      estatus = __compose_new(m_pstorage);

      if (!estatus)
      {

         return ::error_failed;

      }

      estatus = m_pstorage->initialize_simpledb_storage(this);

      if (!estatus)
      {

         return ::error_failed;

      }

      //m_pstorage = __new(storage(this));

      m_bWorking = true;

      m_strDatabase = pszDatabase;

      return ::success;

   }


   bool server::initialize_user(::database::database * pdatabaseUser, const char * pszUser)
   {

      if (::is_null(pdatabaseUser))
      {

         return false;

      }

      m_bRemote = false;

      m_pdatabaseUser = pdatabaseUser;

      m_strUser = pszUser;

      auto estatus = __compose_new(m_psimpledb);

      if (!estatus)
      {

         return false;

      }

      estatus = m_psimpledb->initialize_simpledb(this);

      if (!estatus)
      {

         return false;

      }

      m_bWorking = true;

      return true;

   }



   bool server::create_server_dataset()
   {

      auto pdatabase = m_pdatabaseLocal;

      string strTable("blobtable");

      try
      {

         synchronization_lock synchronizationlock(pdatabase->mutex());

         ::payload item = pdatabase->query_item("select COUNT(*) from sqlite_master where type like 'table' and name like '" + strTable + "'");

         if (item.i32() <= 0)
         {

            pdatabase->exec("create table '" + strTable + "' (id TEXT primary key, value BLOB)");

            pdatabase->exec("create index primary_unique ON " + strTable + "(id)");

         }

      }
      catch (...)
      {

      }

      return true;

   }


   ::e_status server::finalize()
   {

      m_bWorking = false;

      if (m_pdatabaseLocal)
      {

         m_pdatabaseLocal->disconnect();

      }

      m_pdatabaseLocal.release();

      auto estatus = ::database::server::finalize();

      return estatus;

   }


   __pointer(::database::database) server::get_local_database()
   {

      return m_pdatabaseLocal;

   }


   bool server::_data_server_load(::database::client * pclient, const ::database::key & id, get_memory getmemory, ::subject::subject * psubject)
   {

      ::database::key key;

      key = pclient->calc_data_key(id);

      string strType = ::str::demangle(pclient->type_name());

      if(strType.contains("filemanager::frame"))
      {

         INFO("filemanager");

      }

      if (!m_psimpledb->load(key, getmemory))
      {

         return false;

      }

      return true;

   }


   bool server::_data_server_save(::database::client * pclient, const ::database::key & id, block block, ::subject::subject * psubject)
   {

      ::database::key key;

      key = pclient->calc_data_key(id);

      string strType = ::str::demangle(pclient->type_name());

      if(strType.contains("filemanager::frame"))
      {

         //INFO("filemanager");

      }

      if (!m_psimpledb->save(key, block))
      {

         return false;

      }

      return true;

   }


} // namespace simpledb



