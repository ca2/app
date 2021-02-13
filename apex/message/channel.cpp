#include "framework.h"
#include "apex/message.h"


__pointer(::mutex) channel::s_pmutexChannel;


channel::channel()
{

   channel_common_construct();

}


channel::~channel()
{

   remove_all_routes();

}


void channel::install_message_routing(::channel* pchannel)
{

   ::object::install_message_routing(pchannel);

}




void channel::remove_receiver(::object * preceiver)
{

   synchronization_lock synchronizationlock(channel_mutex());

   for (auto & id_route_array : m_idroute)
   {

      if (id_route_array.element2().is_null())
      {

         continue;

      }

      id_route_array.element2()->predicate_remove([=](auto & pitem)
      {

         return pitem->m_preceiver == preceiver;

      });

   }


}


void channel::transfer_receiver(::message::id_route & router, ::object * preceiver)
{

   synchronization_lock synchronizationlock(channel_mutex());

   for (auto & id_route_array : m_idroute)
   {

      if (id_route_array.element2().is_null())
      {

         continue;

      }

      id_route_array.element2()->predicate_each([&](auto & pitem)
      {

         if (pitem->m_preceiver == preceiver)
         {

            auto & routera = router[id_route_array.element1()];

            if (routera.is_null())
            {

               routera = __new(::message::route_array);

            }

            routera->add(pitem);

         }

      });

      id_route_array.element2()->predicate_remove([&](auto & pitem)
      {

         return pitem->m_preceiver == preceiver;

      });

   }


}


void channel::route_message(::message::message * pmessage)
{

   if (::is_null(pmessage)) { ASSERT(false); return; } { synchronization_lock synchronizationlock(channel_mutex()); pmessage->m_proutea = m_idroute[pmessage->m_id]; } if (pmessage->m_proutea.is_null()) { return; }

   for(pmessage->m_pchannel = this, pmessage->m_iRouteIndex = pmessage->m_proutea->get_upper_bound(); pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
   {

      pmessage->m_proutea.m_p->m_pData[pmessage->m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(pmessage); if(pmessage->m_bRet) return;

   }

}

__pointer(::message::message) channel::get_message(MESSAGE * pmessage)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      pmessage->oswindow, 
      nullptr,
      pmessage->m_id, 
      pmessage->wParam, 
      pmessage->lParam);

   return pmessagemessage;

}


__pointer(::message::message) channel::get_message(const ::id & id, wparam wparam, lparam lparam)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      nullptr,
      nullptr,
      id,
      wparam,
      lparam);

   return pmessagemessage;

}


//__pointer(::user::message) channel::get_message_base(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam)
//{
//
//   if (id.m_etype != ::id::e_type_message)
//   {
//
//      __throw(invalid_argument_exception());
//
//   }
//
//   MESSAGE msg;
//
//   __zero(msg);
//
//   msg.message = (::u32) id.m_emessage;
//   msg.wParam = wparam;
//   msg.lParam = lparam;
//
//   return get_message_base(&msg);
//
//}


#ifdef LINUX


__pointer(::user::message) channel::get_message_base(void * pevent,::user::interaction * pwnd)
{

   __throw(todo());

   return nullptr;

}


#endif




void channel::remove_all_routes()
{

   try
   {

      synchronization_lock synchronizationlock(channel_mutex());

      if(m_bNewChannel)
      {

         m_idrouteNew = m_idroute;

         m_bNewChannel = false;

      }

      m_idroute.remove_all();

//         for (auto & id_route_array : m_idroute)
//         {
//
//            if (id_route_array.element2().is_null())
//            {
//
//               continue;
//
//            }
//
//            id_route_array.element2()->predicate_each([=](auto & route)
//            {
//
//               try
//               {
//
//                  synchronization_lock synchronizationlock(route->m_preceiver->m_pmutexChannel);
//
//                  route->m_preceiver->m_sendera.remove(this);
//
//               }
//               catch (...)
//               {
//
//               }
//
//            });
//
//            id_route_array.element2()->remove_all();
//
//         }
//

   }
   catch (...)
   {

   }

}


void channel::channel_common_construct()
{

   m_bNewChannel = true;

}


void channel::finalize()
{

   if (m_pchannel && m_pchannel != this)
   {

      m_pchannel->finalize();

   }

   m_pchannel.release();

   m_idaHandledCommands.remove_all();

   m_idroute.remove_all();

   m_idrouteNew.remove_all();

   for (auto& procedurea : m_mapRoutine.values())
   {

      procedurea.finalize();

      procedurea.remove_all();

   }

   m_mapRoutine.remove_all();

   ::object::finalize();

}


::e_status channel::handle(::message::command * pcommand)
{

   return pcommand->handle(this);

}


void channel::BeginWaitCursor()
{

}


void channel::EndWaitCursor()
{

}


void channel::RestoreWaitCursor()
{

}





void channel::_001SendCommand(::message::command * pcommand)
{

   pcommand->m_pchannel = this;

   {

      __restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command);

      route_command_message(pcommand);

   }

}


void channel::_001SendCommandProbe(::message::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      __restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command_probe);

      route_command_message(pcommand);

   }

}


void channel::route_command_message(::message::command * pcommand)
{

   on_command_message(pcommand);

}


void channel::on_command_message(::message::command * pcommand)
{

   if (pcommand->is_command())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

      if (!pcommand->m_bEnableChanged
         && !pcommand->m_bRadioChanged
         && pcommand->m_echeck == check_undefined
         && !pcommand->m_bHasCommandHandler)
      {

         return;

      }

      on_command(pcommand);

   }
   else if (pcommand->m_id.is_compounded(::id::e_type_command_probe))
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

   }
   else if (pcommand->m_id.is_compounded(::id::e_type_command))
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   }
   else
   {

      __throw(not_implemented());

   }

}


void channel::on_command(::message::command * pcommand)
{

   {

      __restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command);

      route_message(pcommand);

   }

}


bool channel::has_command_handler(::message::command * pcommand)
{

   synchronization_lock synchronizationlock(channel_mutex());

   __restore(pcommand->m_id.m_etype);

   pcommand->m_id.set_compounded_type(::id::e_type_command);

   if (m_idaHandledCommands.contains(pcommand->m_id))
   {

      return true;

   }

   auto passoc = m_idroute.plookup(pcommand->m_id);

   if (::is_null(passoc))
   {

      return false;

   }

   if (passoc->m_element2.is_null())
   {

      return false;

   }

   if (passoc->element2()->is_empty())
   {

      return false;

   }

   return true;

}


void channel::on_command_probe(::message::command * pcommand)
{

   {

      __restore(pcommand->m_id.m_etype);

      pcommand->m_id.set_compounded_type(::id::e_type_command_probe);

      route_message(pcommand);

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      pcommand->m_bRet =
         pcommand->m_bEnableChanged
         || pcommand->m_bRadioChanged
         || pcommand->m_echeck != check_undefined;

   }

}



void channel::default_toggle_check_handling(const ::id & id)
{

   auto pproperty = fetch_property(id);

   connect_command_predicate(id, [this, id, pproperty](::message::message * pmessage)
      {

         __pointer(::message::message) pcommand(pmessage);

         if (pproperty->get_bool())
         {

            *pproperty = ::check_unchecked;

         }
         else
         {

            *pproperty = ::check_checked;

         }

         process_subject(pproperty->m_id, pcommand->m_actioncontext);

      });

}










