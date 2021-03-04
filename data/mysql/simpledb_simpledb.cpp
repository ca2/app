#include "framework.h"
#ifndef _UWP
#include "mysql/mysql.h"
#endif


namespace simpledb
{


   simpledb::simpledb(::layered * pobjectContext) :
      ::object(pobject),
      ::apex::department(pobject)
   {

      m_pserver      = nullptr;

   }

   simpledb::~simpledb()
   {

   }

   bool simpledb::InitializeDataCentral()
   {

      if(get_context_application()->is_system())
      {
      }

      m_pserver = new db_server(get_context_application());


      m_pserver->add_client(this);

      if(!m_pserver->initialize())
      {
         Platform.userex()->message_box(nullptr, "Could not initialize simpledb.", e_message_box_ok);
         return false;
      }

      return true;
   }

   void simpledb::on_set_locale(const char * lpcsz, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         data_set("&data_source=local&locale", lpcsz);
      }
      get_context_application()->m_psession->on_set_locale(lpcsz, context);
   }

   void simpledb::on_set_schema(const char * lpcsz, const ::action_context & context)
   {
      if(context.is_user_source())
      {
         data_set("&data_source=local&schema", lpcsz);
      }
      get_context_application()->m_psession->on_set_schema(lpcsz,context);
   }

   bool simpledb::FinalizeDataCentral()
   {

      try
      {
         m_pserver->finalize();
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

      if(get_context_application()->is_system())
      {

         m_pserver = nullptr;
      }

      return true;
   }

   bool simpledb::init2()
   {

      if(get_context_application()->m_pcoreapp->m_varTopicQuery["locale"].get_count() > 0)
      {
         string str = get_context_application()->m_pcoreapp->m_varTopicQuery["locale"].stra()[0];
         get_context_application()->m_psession->set_locale(str,::e_source_database);
      }

      if(get_context_application()->m_pcoreapp->m_varTopicQuery["schema"].get_count() > 0)
      {
         string str = get_context_application()->m_pcoreapp->m_varTopicQuery["schema"].stra()[0];
         get_context_application()->m_psession->set_schema(str,::e_source_database);
      }

//      if(&AppUser(this) == nullptr)
  //       return false;

      if(!InitializeDataCentral())
      {
         get_context_application()->m_pcoreapp->message_box(nullptr, "Could not initialize data central");
         return false;
      }

      ::database::client::initialize_data_client(m_pserver);

      if (Application.m_spdataserver.is_null())
      {

         Application.m_spdataserver = m_pserver;

      }


//      ::aura::application_request * prequest = System->get_application_request();


      get_context_application()->m_psession->fill_locale_schema(*get_context_application()->m_psession->str_context()->m_plocaleschema);


      //if(!get_context_application()->m_pcoreapp->is_installing() && !get_context_application()->m_pcoreapp->is_unstalling() && !get_context_application()->m_pcoreapp->is_system())
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


   bool simpledb::set_keyboard_layout(const char * pszPath, const ::action_context & context)
   {

      return psession->set_keyboard_layout(pszPath, context);

   }


   void simpledb::on_set_keyboard_layout(const char * pszPath, const ::action_context & context)
   {

      if(context.is_user_source())
      {

         if(Sess(get_context_application()).safe_get_user() != nullptr)
         {

            data_set("keyboard_layout", pszPath);

         }

      }

   }


} // namespace simpledb



