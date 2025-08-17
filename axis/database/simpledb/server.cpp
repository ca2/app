#include "framework.h"
#include "server.h"
#include "storage.h"
#include "simpledb.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/context.h"
#include "axis/database/database/database.h"


namespace simpledb
{


   server::server()
   {

   }


   server::~server()
   {

   }



   void server::initialize_simpledb_server(::particle * pparticle, const ::scoped_string & scopedstrDatabase)
   {

      //auto estatus =
      
      ::database::server::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bRemote = !m_papplication->is_local_data();

      if (m_pdatabaseLocal.is_set())
      {

         destroy();

      }

      ::file::path pathDatabase(scopedstrDatabase);

      //if (!
      directory()->create(pathDatabase.folder());

      //{

      //   //return false;

      //   throw ::exception(error_failed);

      //}

      auto & pfactoryDatabase = system()->factory("database", "sqlite3");

      //if(!pfactoryDatabase)
      //{
      //   
      //   warning() <<"Failed to load database_sqlite3";

      //   return pfactoryDatabase;

      //}

      pfactoryDatabase->øconstruct(this, m_pdatabaseLocal);

      //if (!estatus)
      //{

      //   return false;

      //}

      _synchronous_lock synchronouslock(m_pdatabaseLocal->synchronization());

      //estatus = pdatabase->set_finish(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pdatabaseLocal = pdatabase;

      m_pdatabaseLocal->initialize(this);

 /*     if (!estatus)
      {

         return ::error_failed;

      }*/

      //estatus = 
      
      m_pdatabaseLocal->connect(scopedstrDatabase);

 /*     if (!estatus)
      {

         return ::error_failed;

      }*/

      //estatus =
      
      øconstruct_new(m_psimpledb);

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      m_psimpledb->initialize_simpledb(this);

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}
      
      create_server_dataset();
      //if (!)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      øconstruct_new(m_pstorage);

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      m_pstorage->initialize_simpledb_storage(this);

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //m_pstorage = __allocate storage(this);

      m_bWorking = true;

      m_strDatabase = scopedstrDatabase;

      // return ::success;

   }


   void server::initialize_user(::database::database * pdatabaseUser, const ::scoped_string & scopedstrUser)
   {

      if (::is_null(pdatabaseUser))
      {

         throw ::exception(error_null_pointer);

      }

      m_bRemote = false;

      m_pdatabaseUser = pdatabaseUser;

      m_strUser = scopedstrUser;

      //auto estatus = 
      
      øconstruct_new(m_psimpledb);

      //if (!estatus)
      //{

      //   return false;

      //}

      //estatus = 
      
      m_psimpledb->initialize_simpledb(this);

      //if (!estatus)
      //{

      //   return false;

      //}

      m_bWorking = true;

      //return true;

   }



   void server::create_server_dataset()
   {

      auto pdatabase = m_pdatabaseLocal;

      string strTable("blobtable");

      try
      {

         _synchronous_lock synchronouslock(pdatabase->synchronization());

         ::payload item = pdatabase->query_item("select COUNT(*) from sqlite_master where type like 'table' and name like '" + strTable + "'");

         if (item.as_int() <= 0)
         {

            pdatabase->exec("create table '" + strTable + "' (id TEXT primary key, value BLOB)");

            pdatabase->exec("create index primary_unique ON " + strTable + "(id)");

         }

      }
      catch (...)
      {

      }

      //return true;

   }


   void server::destroy()
   {

      m_bWorking = false;

      if (m_pdatabaseLocal)
      {

         m_pdatabaseLocal->disconnect();

      }

      m_pdatabaseLocal.defer_destroy();

      m_pstorage.defer_destroy();

      m_pdatabaseUser.defer_destroy();

      m_psimpledb.defer_destroy();

      //auto estatus = 
      
      ::database::server::destroy();

      //return estatus;

   }


   ::pointer<::database::database>server::get_local_database()
   {

      return m_pdatabaseLocal;

   }


   bool server::_data_server_load(::database::client * pclient, const ::scoped_string & scopedstrDataKey, get_memory getmemory, ::topic * ptopic)
   {

      string strDataKey = pclient->calculate_data_key(scopedstrDataKey);

      auto pszDataKey = strDataKey.c_str();

      printf_line("data_server_load key : %s", pszDataKey);

      string strType = ::type(pclient).name();

      if(strType.contains("filemanager::frame"))
      {

         information() << "filemanager";

      }

      if (!m_psimpledb->load(strDataKey, getmemory))
      {

         return false;

      }

      return true;

   }


   void server::_data_server_save(::database::client * pclient, const ::scoped_string & scopedstrDataKey, block block, ::topic * ptopic)
   {

      auto strDataKey = pclient->calculate_data_key(scopedstrDataKey);

      auto pszDataKey = strDataKey.c_str();

      printf_line("data_server_save key : %s", pszDataKey);

      string strType = ::type(pclient).name();

      if(strType.contains("filemanager::frame"))
      {

         //information() << "filemanager";

      }

      m_psimpledb->save(strDataKey, block);
      //{

      //   return false;

      //}

      //return true;

   }


} // namespace simpledb



