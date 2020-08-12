#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {

      //if(get_context_application() != nullptr)
      //{

      //   m_spmemoryfileFallback = __new(::memory_file(get_object()));

      //}

      m_pinstanceMain      = nullptr;
      m_pinstanceParent    = nullptr;
      m_pnetnodesocket     = nullptr;
      m_pmanager           = nullptr;

      m_pscript            = nullptr;

      m_iDebug             = 0;

   }


   script_interface::~script_interface()
   {

   }

   void script_interface::destroy()
   {
   }


   ::estatus     script_interface::run()
   {

      return ::success;

   }


   void script_interface::dinit()
   {
   }

   void script_interface::dprint(const char *)
   {
   }


   property & script_interface::get(const char * pszKey)
   {
      return get_property_set().get(pszKey);
   }


   bool script_interface::main_initialize()
   {

      return true;

   }


   bool script_interface::main_finalize()
   {

      m_pnetnodesocket     = nullptr;
      m_pmanager           = nullptr;

      m_pscript            = nullptr;
      m_pinstanceMain      = nullptr;
      m_pinstanceParent    = nullptr;

      return true;

   }


   ::file::file * script_interface::file()
   {

      if(m_pinstanceMain == this)
      {

         __throw(interface_only_exception());

      }
      else if(m_pinstanceMain != nullptr)
      {

         return m_pinstanceMain->file();

      }
      else if(m_pnetnodesocket != nullptr)
      {

         return m_pnetnodesocket->response().file();

      }
      else
      {

         __throw(interface_only_exception());

      }

   }

//   ::text_stream script_interface::ostream()
//   {
//
//      if (m_pinstanceMain == this)
//      {
//
//         __throw(interface_only_exception());
//
//      }
//      else if (m_pinstanceMain != nullptr)
//      {
//
//         return m_pinstanceMain->ostream();
//
//      }
//      else if (m_pnetnodesocket != nullptr)
//      {
//
//         return m_pnetnodesocket->response().ostream().m_p.m_p;
//
//      }
//      else
//      {
//
//         __throw(interface_only_exception());
//
//      }
//
//   }


//   ::binary_stream script_interface::bstream()
//   {
//
//      if(m_pinstanceMain == this)
//      {
//
//         __throw(interface_only_exception());
//
//      }
//      else if(m_pinstanceMain != nullptr)
//      {
//
//         return m_pinstanceMain->ostream().m_p;
//
//      }
//      else if(m_pnetnodesocket != nullptr)
//      {
//
//         return m_pnetnodesocket->response().ostream().m_p;
//
//      }
//      else
//      {
//
//         __throw(interface_only_exception());
//
//      }
//
//   }


   ::estatus script_interface::on_initialize()
   {
      
      return ::success;

   }


   ::estatus script_interface::initialize_dynamic_source_script_interface(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager)
   {

      auto estatus = initialize(pinterfaceMain);

      if (!estatus)
      {

         return estatus;

      }

      m_pinstanceMain      = pinterfaceMain;
      m_pinstanceParent    = pinterfaceParent;
      m_pnetnodesocket     = pdssocket;
      m_pmanager           = pmanager;

      estatus = on_initialize();
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      return estatus;

   }


   void script_interface::set_session_value(id, var)
   {

   }


   var script_interface::get_session_value(id)
   {

      return var(::type_new);

   }

   string script_interface::session_id(const char *)
   {

      return "";

   }
} // namespace dynamic_source



