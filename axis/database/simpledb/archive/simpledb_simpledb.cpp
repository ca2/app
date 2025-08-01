#include "framework.h"


namespace simpledb
{


   simpledb::simpledb(::particle * pparticle) :
      ::object(pparticle),
      ::acme::department(pparticle)
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

      synchronous_lock synchronouslock(this->synchronization());

      if (m_bInitialized)
      {

         return true;

      }

      if (m_pserver != nullptr)
      {

         return true;

      }

      if(get_app()->is_system())
      {
//#ifndef UNIVERSAL_WINDOWS
//         /* initialize client library */
//         if (mysql_library_init (0, nullptr, nullptr))
//         {
//            informationf("mysql_library_init() failed");
//            return false;
//         }
//#endif
      }

      m_pserver = __allocate db_server(get_app());


      m_pserver->add_client(this);

      if (!m_pserver->initialize())
      {
         message_box(nullptr, "Could not initialize simpledb.", e_message_box_ok);
         return false;
      }

      m_bInitialized = true;

      return true;

   }


   void simpledb::on_set_locale(const ::scoped_string & scopedstr, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         datastream()->set({ "locale", true }, lpcsz);

      }

      get_app()->m_psession->on_set_locale(lpcsz, context);

   }


   void simpledb::on_set_schema(const ::scoped_string & scopedstr, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         datastream()->set({ "schema", true }, lpcsz);

      }

      get_app()->m_psession->on_set_schema(lpcsz,context);

   }


   bool simpledb::FinalizeDataCentral()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_bInitialized)
      {

         return true;

      }

      if (m_pserver.is_set())
      {

         try
         {

            m_pserver->destroy();

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

      if(get_app()->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = get_app()->m_varTopicQuery["locale"].stra()[0];
         get_app()->m_psession->set_locale(str,::e_source_database);
      }

      if(get_app()->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = get_app()->m_varTopicQuery["schema"].stra()[0];
         get_app()->m_psession->set_schema(str,::e_source_database);
      }

//      if(&AppUser(this) == nullptr)
      //       return false;

      if(!InitializeDataCentral())
      {
         message_box(nullptr, "Could not initialize data central");
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


   bool simpledb::destroy()
   {

      try
      {
         //  ::database::database::destroy();
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




   void simpledb::on_set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(psession->get_user() != nullptr)
         {

            datastream()->set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



