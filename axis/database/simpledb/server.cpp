#include "framework.h"
#include "server.h"
#include "storage.h"
#include "simpledb.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/context.h"
#include "acme/platform/system.h"
#include "apex/filesystem/filesystem/dir_context.h"
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


   void server::initialize_simpledb_server(::particle * pparticle, const ::string & pszDatabase)
   {

      //auto estatus =
      
      ::database::server::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bRemote = !m_pcontext->m_papexcontext->is_local_data();

      if (m_pdatabaseLocal.is_set())
      {

         destroy();

      }

      ::file::path pathDatabase(pszDatabase);

      //if (!
      dir()->create(pathDatabase.folder());

      //{

      //   //return false;

      //   throw ::exception(error_failed);

      //}

      auto & pfactoryDatabase = acmesystem()->factory("database", "sqlite3");

      //if(!pfactoryDatabase)
      //{
      //   
      //   WARNING("Failed to load database_sqlite3");

      //   return pfactoryDatabase;

      //}

      pfactoryDatabase->__construct(this, m_pdatabaseLocal);

      //if (!estatus)
      //{

      //   return false;

      //}

      synchronous_lock synchronouslock(m_pdatabaseLocal->synchronization());

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
      
      m_pdatabaseLocal->connect(pszDatabase);

 /*     if (!estatus)
      {

         return ::error_failed;

      }*/

      //estatus =
      
      __construct_new(m_psimpledb);

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
      
      __construct_new(m_pstorage);

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

      //m_pstorage = __new(storage(this));

      m_bWorking = true;

      m_strDatabase = pszDatabase;

      // return ::success;

   }


   void server::initialize_user(::database::database * pdatabaseUser, const ::string & pszUser)
   {

      if (::is_null(pdatabaseUser))
      {

         throw ::exception(error_null_pointer);

      }

      m_bRemote = false;

      m_pdatabaseUser = pdatabaseUser;

      m_strUser = pszUser;

      //auto estatus = 
      
      __construct_new(m_psimpledb);

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

         synchronous_lock synchronouslock(pdatabase->synchronization());

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

      //return true;

   }


   void server::destroy()
   {

      m_bWorking = false;

      if (m_pdatabaseLocal)
      {

         m_pdatabaseLocal->disconnect();

      }

      m_pdatabaseLocal.release();

      //auto estatus = 
      
      ::database::server::destroy();

      //return estatus;

   }


   ::pointer<::database::database>server::get_local_database()
   {

      return m_pdatabaseLocal;

   }


   bool server::_data_server_load(::database::client * pclient, const ::database::key & atom, get_memory getmemory, ::topic * ptopic)
   {

      ::database::key key;

      key = pclient->calc_data_key(atom);

      string strType = __type_name(pclient);

      if(strType.contains("filemanager::frame"))
      {

         INFORMATION("filemanager");

      }

      if (!m_psimpledb->load(key, getmemory))
      {

         return false;

      }

      return true;

   }


   void server::_data_server_save(::database::client * pclient, const ::database::key & atom, block block, ::topic * ptopic)
   {

      ::database::key key;

      key = pclient->calc_data_key(atom);

      string strType = __type_name(pclient);

      if(strType.contains("filemanager::frame"))
      {

         //INFORMATION("filemanager");

      }

      m_psimpledb->save(key, block);
      //{

      //   return false;

      //}

      //return true;

   }


} // namespace simpledb



