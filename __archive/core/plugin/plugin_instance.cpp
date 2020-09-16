#include "framework.h"



//::hotplugin::plugin * new_hotplugin(::generic * pobject);


namespace plugin
{


   instance::instance()
   {

      m_pfile           = nullptr;

//      m_lpbMemory       = nullptr;

      //    m_iMemory         = -1;

      m_puiHost         = nullptr;

      m_oswindow        = nullptr;

      m_bStream         = false;

   }

   instance::~instance()
   {
      if(m_puiHost != nullptr)
      {
         delete m_puiHost;
      }

   }


   bool instance::initialize()
   {

      m_oswindow = m_phost->get_host_window();

      if(m_oswindow == nullptr)
         return FALSE;

      m_bInitialized = true;

      //NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_oswindow);

      start_ca2_system();

      return TRUE;

   }


   void instance::shut()
   {

      //::KillTimer(nullptr, (uptr) this);

      plugin::finalize();

      m_oswindow = nullptr;

      m_bInitialized = false;

   }


   host_interaction * instance::create_host_interaction()
   {

      host_interaction * pinteraction = new host_interaction(get_context_object());

      pinteraction->create_message_queue("npca2");

      pinteraction->m_bMessageWindow = false;

      pinteraction->install_message_routing(pinteraction->m_pimpl);

      ::user::interaction_impl * pwindow = pinteraction->m_pimpl;

      pwindow->m_bTranslateMouseMessageCursor = false;

      return pinteraction;

   }


} // namespace plugin




//::hotplugin::plugin * new_hotplugin(::generic * pobject)
//{
//
//   return new ::plugin::instance(pobject);
//
//}


