// Created by camilo on 2023-11-22 20:35 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "manager.h"
#include "manager_room.h"
#include "apex/platform/system.h"



manager_room::manager_room()
{

   m_bDestroyAll = false;

}


manager_room::~manager_room()
{



}



void manager_room::erase_signal_handler_from_any_source(const ::signal_handler & signalhandler)
{

   erase_signal_handler(signalhandler);

}


void manager_room::erase_signal_handler(const ::signal_handler & signalhandler)
{

   critical_section_lock synchronouslock(&m_criticalsection);

   for (auto & passociation : m_managerset)
   {

      auto & pmanager = passociation.element();

      pmanager->erase_signal_handler(signalhandler);

   }

}


void manager_room::post_destroy_signal_handling()
{

   m_bDestroyAll = true;

}



bool manager_room::may_run_signal_handling()
{

   if (m_bDestroyAll)
   {

      return false;

   }

   if (!::task_get_run())
   {

      return false;

   }

   return true;

}



namespace apex
{


   ::manager_room * system::manager_room()
   {

      if (!m_pmanagerroom)
      {

         øconstruct_new(m_pmanagerroom);

      }

      return m_pmanagerroom;

   }


} // namespace apex



