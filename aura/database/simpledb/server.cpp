#include "framework.h"
#include "_simpledb.h"
#include "aura/database/sqlitedb/_.h"
#include <sqlite3.h>
#include "storage.h"


::database::database * create_inline_relational_database()
{

   return nullptr;

}


namespace simpledb
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::estatus server::initialize_simpledb_server(::object * pobjectContext, const char * pszDatabase)
   {

      auto estatus = ::database::server::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bRemote = !Application.is_local_data();

      if (m_pdatabaseLocal.is_set())
      {

         finalize();

      }

      ::file::path pathDatabase(pszDatabase);

      if (!Context.dir().mk(pathDatabase.folder()))
      {

         return false;

      }

      //auto pdatabase = __new(::sqlite::database());

      auto pdatabase = move_transfer(create_inline_relational_database());

      if (pdatabase.is_null())
      {

         return false;

      }

      sync_lock sl(pdatabase->mutex());

      estatus = pdatabase->connect(pszDatabase);

      if (!estatus)
      {

         return estatus;

      }

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

         sync_lock sl(pdatabase->mutex());

         var item = pdatabase->query_item("select COUNT(*) from sqlite_master where type like 'table' and name like '" + strTable + "'");

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


   void server::finalize()
   {

      m_bWorking = false;

      if (m_pdatabaseLocal)
      {

         m_pdatabaseLocal->disconnect();

      }

      m_pdatabaseLocal.release();

      ::database::server::finalize();

   }


   __pointer(::database::database) server::get_local_database()
   {

      return m_pdatabaseLocal;

   }


   bool server::_data_server_load(::database::client * pclient, const ::database::key & id, get_memory getmemory, ::update * pupdate)
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


   bool server::_data_server_save(::database::client * pclient, const ::database::key & id, block block, ::update * pupdate)
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



