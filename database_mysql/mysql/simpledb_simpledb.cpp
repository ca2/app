#include "framework.h"

#ifndef UNIVERSAL_WINDOWS
#include "mysql/mysql.h"
#endif


namespace simpledb
{


   simpledb::simpledb(::particle * pparticle) :
      ::object(pparticle),
      ::platform::department(pparticle)
   {

      m_pserver      = nullptr;

   }

   simpledb::~simpledb()
   {

   }

   bool simpledb::InitializeDataCentral()
   {

      if(get_app()->is_system())
      {
      }

      m_pserver = øallocate< db_server(get_app >());


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         Platform.userex()->message_box(nullptr, "Could not initialize simpledb.", ::user::e_message_box_ok);
         return false;
      }

      return true;
   }

   void simpledb::on_set_locale(const ::scoped_string & scopedstr, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         datastream()->set("&data_source=local&locale", lpcsz);
      }
      get_app()->m_psession->on_set_locale(lpcsz, context);
   }

   void simpledb::on_set_schema(const ::scoped_string & scopedstr, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         datastream()->set("&data_source=local&schema", lpcsz);
      }
      get_app()->m_psession->on_set_schema(lpcsz,context);
   }

   bool simpledb::FinalizeDataCentral()
   {

      try
      {
         m_pserver->destroy();
      }
      catch(...)
      {
      }

      try
      {
         delete m_pserver;
      }
      catch(...)
      {
      }

      if(get_app()->is_system())
      {

         m_pserver = nullptr;
      }

      return true;
   }

   bool simpledb::init2()
   {

      if(get_app()->m_pcoreapp->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = get_app()->m_pcoreapp->m_varTopicQuery["locale"].stra()[0];
         get_app()->m_psession->set_locale(str,::e_source_database);
      }

      if(get_app()->m_pcoreapp->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = get_app()->m_pcoreapp->m_varTopicQuery["schema"].stra()[0];
         get_app()->m_psession->set_schema(str,::e_source_database);
      }

//      if(&AppUser(this) == nullptr)
  //       return false;

      if(!InitializeDataCentral())
      {
         get_app()->m_pcoreapp->message_box(nullptr, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);

      if (papp->m_spdataserver.is_null())
      {

         papp->m_spdataserver = m_pserver;

      }


//      ::aura::application_request * prequest = psystem->get_application_request();


      get_app()->m_psession->fill_locale_schema(*get_app()->m_psession->textcontext()->m_plocaleschema);


      //if(!get_app()->m_pcoreapp->is_installing() && !get_app()->m_pcoreapp->is_unstalling() && !get_app()->m_pcoreapp->is_system())
      //{

      //   set_keyboard_layout(nullptr, context + ::e_source_sync + ::e_source_system;

      //}


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


   bool simpledb::set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & context)
   {

      return psession->set_keyboard_layout(scopedstrPath, context);

   }


   void simpledb::on_set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(Sess(get_app()).safe_get_user() != nullptr)
         {

            datastream()->set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



