#include "framework.h"


namespace simpledb
{


   simpledb::simpledb(::object * pobject) :
      ::object(pobject),
      ::aura::department(pobject)
   {

      m_pserver         = nullptr;
      m_bInitialized    = false;

   }


   simpledb::~simpledb()
   {

      FinalizeDataCentral();

   }


   bool simpledb::InitializeDataCentral()
   {

      sync_lock sl(mutex());

      if (m_bInitialized)
      {

         return true;

      }

      if (m_pserver != nullptr)
      {

         return true;

      }

      if(get_context_application()->is_system())
      {
//#ifndef _UWP
//         /* initialize client library */
//         if (mysql_library_init (0, nullptr, nullptr))
//         {
//            TRACE("mysql_library_init() failed\n");
//            return false;
//         }
//#endif
      }

      m_pserver = __new(db_server(get_context_application()));


      m_pserver->add_client(this);

      if (!m_pserver->initialize())
      {
         Application.message_box(nullptr, "Could not initialize simpledb.", MB_OK);
         return false;
      }

      m_bInitialized = true;

      return true;

   }


   void simpledb::on_set_locale(const char * lpcsz, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         data_set({ "locale", true }, lpcsz);

      }

      get_context_application()->m_psession->on_set_locale(lpcsz, context);

   }


   void simpledb::on_set_schema(const char * lpcsz, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         data_set({ "schema", true }, lpcsz);

      }

      get_context_application()->m_psession->on_set_schema(lpcsz,context);

   }


   bool simpledb::FinalizeDataCentral()
   {

      sync_lock sl(mutex());

      if (!m_bInitialized)
      {

         return true;

      }

      if (m_pserver.is_set())
      {

         try
         {

            m_pserver->finalize();

         }
         catch (...)
         {

         }

         m_pserver.release();

      }

      m_pserver = nullptr;

      m_bInitialized = false;

      return true;

   }

   bool simpledb::init2()
   {

      if(get_context_application()->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = get_context_application()->m_varTopicQuery["locale"].stra()[0];
         get_context_application()->m_psession->set_locale(str,::source_database);
      }

      if(get_context_application()->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = get_context_application()->m_varTopicQuery["schema"].stra()[0];
         get_context_application()->m_psession->set_schema(str,::source_database);
      }

//      if(&AppUser(this) == nullptr)
      //       return false;

      if(!InitializeDataCentral())
      {
         Application.message_box(nullptr, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);


      return true;

   }




   bool simpledb::initialize()
   {



      if(!::database::database::initialize())
         return false;



      return true;


   }


   bool simpledb::finalize()
   {

      try
      {
         //  ::database::database::finalize();
      }
      catch(...)
      {
      }

      try
      {
         FinalizeDataCentral();
      }
      catch(...)
      {
      }


      return true;


   }


   ::database::server * simpledb::get_data_server()
   {

      return m_pserver;

   }


   db_server & simpledb::db()
   {

      return *m_pserver;

   }




   void simpledb::on_set_keyboard_layout(const char * pszPath, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(Session.get_user() != nullptr)
         {

            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



