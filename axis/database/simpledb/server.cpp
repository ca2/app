#include "platform.h"
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
      information() << "startup: simpledb::server::initialize_simpledb_server: enter";


      //auto estatus =
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before ::database::server::initialize(pparticle)";
      ::database::server::initialize(pparticle);
      information() << "startup: simpledb::server::initialize_simpledb_server: after ::database::server::initialize(pparticle)";

      //if (!estatus)
      //{

      //   return estatus;

      //}

      information() << "startup: simpledb::server::initialize_simpledb_server: before m_bRemote = !m_papplication->is_local_data()";
      m_bRemote = !m_papplication->is_local_data();
      information() << "startup: simpledb::server::initialize_simpledb_server: after m_bRemote = !m_papplication->is_local_data()";

      if (m_pdatabaseLocal.is_set())
      {

         information() << "startup: simpledb::server::initialize_simpledb_server: before destroy()";
         destroy();
         information() << "startup: simpledb::server::initialize_simpledb_server: after destroy()";

      }

      information() << "startup: simpledb::server::initialize_simpledb_server: before ::file::path pathDatabase(scopedstrDatabase)";
      ::file::path pathDatabase(scopedstrDatabase);
      information() << "startup: simpledb::server::initialize_simpledb_server: after ::file::path pathDatabase(scopedstrDatabase)";

      //if (!
      information() << "startup: simpledb::server::initialize_simpledb_server: before directory()->create(pathDatabase.folder())";
      directory()->create(pathDatabase.folder());
      information() << "startup: simpledb::server::initialize_simpledb_server: after directory()->create(pathDatabase.folder())";

      //{

      //   //return false;

      //   throw ::exception(error_failed);

      //}

      information() << "startup: simpledb::server::initialize_simpledb_server: before auto & pfactoryDatabase = system()->factory(\"database\", \"sqlite3\")";
      auto & pfactoryDatabase = system()->factory("database", "sqlite3");
      information() << "startup: simpledb::server::initialize_simpledb_server: after auto & pfactoryDatabase = system()->factory(\"database\", \"sqlite3\")";

      //if(!pfactoryDatabase)
      //{
      //   
      //   warning() <<"Failed to load database_sqlite3";

      //   return pfactoryDatabase;

      //}

      information() << "startup: simpledb::server::initialize_simpledb_server: before pfactoryDatabase->constructø(this, m_pdatabaseLocal)";
      pfactoryDatabase->constructø(this, m_pdatabaseLocal);
      information() << "startup: simpledb::server::initialize_simpledb_server: after pfactoryDatabase->constructø(this, m_pdatabaseLocal)";

      //if (!estatus)
      //{

      //   return false;

      //}

      information() << "startup: simpledb::server::initialize_simpledb_server: before _synchronous_lock synchronouslock(m_pdatabaseLocal->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX)";
      _synchronous_lock synchronouslock(m_pdatabaseLocal->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      information() << "startup: simpledb::server::initialize_simpledb_server: after _synchronous_lock synchronouslock(m_pdatabaseLocal->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX)";

      //estatus = pdatabase->set_finish(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pdatabaseLocal = pdatabase;

      information() << "startup: simpledb::server::initialize_simpledb_server: before m_pdatabaseLocal->initialize(this)";
      m_pdatabaseLocal->initialize(this);
      information() << "startup: simpledb::server::initialize_simpledb_server: after m_pdatabaseLocal->initialize(this)";

 /*     if (!estatus)
      {

         return ::error_failed;

      }*/

      //estatus = 
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before m_pdatabaseLocal->connect(scopedstrDatabase)";
      m_pdatabaseLocal->connect(scopedstrDatabase);
      information() << "startup: simpledb::server::initialize_simpledb_server: after m_pdatabaseLocal->connect(scopedstrDatabase)";

 /*     if (!estatus)
      {

         return ::error_failed;

      }*/

      //estatus =
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before construct_newø(m_psimpledb)";
      construct_newø(m_psimpledb);
      information() << "startup: simpledb::server::initialize_simpledb_server: after construct_newø(m_psimpledb)";

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before m_psimpledb->initialize_simpledb(this)";
      m_psimpledb->initialize_simpledb(this);
      information() << "startup: simpledb::server::initialize_simpledb_server: after m_psimpledb->initialize_simpledb(this)";

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before create_server_dataset()";
      create_server_dataset();
      information() << "startup: simpledb::server::initialize_simpledb_server: after create_server_dataset()";
      //if (!)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before construct_newø(m_pstorage)";
      construct_newø(m_pstorage);
      information() << "startup: simpledb::server::initialize_simpledb_server: after construct_newø(m_pstorage)";

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //estatus = 
      
      information() << "startup: simpledb::server::initialize_simpledb_server: before m_pstorage->initialize_simpledb_storage(this)";
      m_pstorage->initialize_simpledb_storage(this);
      information() << "startup: simpledb::server::initialize_simpledb_server: after m_pstorage->initialize_simpledb_storage(this)";

      //if (!estatus)
      //{

      //   return ::error_failed;

      //}

      //m_pstorage = allocateø storage(this);

      m_bWorking = true;

      m_strDatabase = scopedstrDatabase;

      // return ::success;

      information() << "startup: simpledb::server::initialize_simpledb_server: leave";

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
      
      construct_newø(m_psimpledb);

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

         _synchronous_lock synchronouslock(pdatabase->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         ::payload item = pdatabase->query_item("select COUNT(*) from sqlite_master where type like 'table' and name like '" + strTable + "'");

         if (item.as_i32() <= 0)
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

      m_pdatabaseLocal.defer_destroy_and_release();

      m_pstorage.defer_destroy_and_release();

      m_pdatabaseUser.defer_destroy_and_release();

      m_psimpledb.defer_destroy_and_release();

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

      informationf("data_server_load key : %s", pszDataKey);

      string strType = ::platform::type(pclient).name();

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

      informationf("data_server_save key : %s", pszDataKey);

      string strType = ::platform::type(pclient).name();

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



