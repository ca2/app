#include "framework.h"
#include "channel.h"
#include "acme/operating_system/message.h"
#include "acme/platform/message.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/scoped_restore.h"
#include "apex/message/command.h"
#include "apex/message/simple_command.h"


//::pointer < ::mutex >channel::s_pmutexChannel;


channel::channel()
{

   channel_common_construct();

}


channel::~channel()
{

   erase_all_routes();

}


void channel::install_message_routing(::channel * pchannel)
{


}


void channel::erase_handler(::particle * pparticle)
{

   erase_message_handler(pparticle);
   erase_command_handler(pparticle);
   erase_command_probe_handler(pparticle);

}


void channel::erase_message_handler(::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   auto payloads = get_message_map()->payloads();

   for (auto & dispatchera : payloads)
   {

      if (dispatchera.is_empty())
      {

         continue;

      }

      dispatchera.predicate_erase([=](auto & dispatcher)
      {

         return dispatcher.m_pparticleHandlerTarget == pparticle;

      });

   }

}


void channel::erase_command_handler(::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   auto payloads = get_command_map()->payloads();

   for (auto & dispatchera : payloads)
   {

      if (dispatchera.is_empty())
      {

         continue;

      }

      dispatchera.predicate_erase([=](auto & dispatcher)
      {

         return dispatcher.m_pparticleHandlerTarget == pparticle;

      });

   }

}


void channel::erase_command_probe_handler(::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   auto payloads = get_command_probe_map()->payloads();

   for (auto & dispatchera : payloads)
   {

      if (dispatchera.is_empty())
      {

         continue;

      }

      dispatchera.predicate_erase([=](auto & dispatcher)
      {

         return dispatcher.m_pparticleHandlerTarget == pparticle;

      });

   }

}


void channel::transfer_handler(::channel * pchannelReceiver, ::particle * pparticle)
{

   transfer_message_handler(pchannelReceiver, pparticle);
   transfer_command_handler(pchannelReceiver, pparticle);
   transfer_command_probe_handler(pchannelReceiver, pparticle);

}


void channel::transfer_message_handler(::channel * pchannelReceiver, ::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   {

      auto pdispatchermap = get_message_map();

      for (auto & pair : *pdispatchermap)
      {

         if (pair.element2().is_empty())
         {

            continue;

         }

         pair.element2().predicate_each([&](auto & dispatcher)
         {

            if (dispatcher.m_pparticleHandlerTarget == pparticle)
            {

               auto & dispatcha = pchannelReceiver->m_messagemap[pair.element1()];

               dispatcha.add(dispatcher);

            }

         });

         pair.element2().predicate_erase([&](auto & dispatcher)
         {

            return dispatcher.m_pparticleHandlerTarget == pparticle;

         });

      }

   }


}


void channel::transfer_command_handler(::channel * pchannelReceiver, ::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   {

      auto pdispatchermap = get_command_map();

      for (auto & pair : *pdispatchermap)
      {

         if (pair.element2().is_empty())
         {

            continue;

         }

         pair.element2().predicate_each([&](auto & dispatcher)
         {

            if (dispatcher.m_pparticleHandlerTarget == pparticle)
            {

               auto & dispatcha = pchannelReceiver->m_commandmap[pair.element1()];

               dispatcha.add(dispatcher);

            }

         });

         pair.element2().predicate_erase([&](auto & dispatcher)
         {

            return dispatcher.m_pparticleHandlerTarget == pparticle;

         });

      }

   }


}


void channel::transfer_command_probe_handler(::channel * pchannelReceiver, ::particle * pparticle)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   {

      auto pcommandmapProbe = get_command_probe_map();

      for (auto & pair : *pcommandmapProbe)
      {

         if (pair.element2().is_empty())
         {

            continue;

         }

         pair.element2().predicate_each([&](auto & dispatcher)
         {

            if (dispatcher.m_pparticleHandlerTarget == pparticle)
            {

               auto & dispatcha = pchannelReceiver->m_commandmapProbe[pair.element1()];

               dispatcha.add(dispatcher);

            }

         });

         pair.element2().predicate_erase([&](auto & dispatcher)
         {

            return dispatcher.m_pparticleHandlerTarget == pparticle;

         });

      }

   }

}




::particle * channel::add_message_handler(::enum_message emessage, const ::message::dispatcher & dispatcher)
{

   auto pdispatchermap = get_message_map();

   auto & dispatchera = (*pdispatchermap)[emessage];

   // Try to not add already added dispatcher
   for (::collection::index i = 0; i < dispatchera.get_count(); i++)
   {

      auto & dispatcherItem = dispatchera[i];

      if (dispatcherItem == dispatcher)
      {

         return nullptr;

      }

   }

   dispatchera.add(dispatcher);

   return dispatcher.m_pparticleHandlerTarget.m_p;

}


::particle * channel::add_command_handler(const ::atom & atom, const ::message::dispatcher & dispatcher)
{

   auto pdispatchermap = get_command_map();

   auto & dispatchera = (*pdispatchermap)[atom];

   // Try to not add already added dispatcher
   for (::collection::index i = 0; i < dispatchera.get_count(); i++)
   {

      auto & dispatcherItem = dispatchera[i];

      if (dispatcherItem == dispatcher)
      {

         return nullptr;

      }

   }

   dispatchera.add(dispatcher);

   return dispatcher.m_pparticleHandlerTarget.m_p;

}



::particle * channel::add_command_prober(const ::atom & atom, const ::message::dispatcher & dispatcher)
{

   auto pdispatchermap = get_command_probe_map();

   auto & dispatchera = (*pdispatchermap)[atom];

   // Try to not add already added dispatcher
   for (::collection::index i = 0; i < dispatchera.get_count(); i++)
   {

      auto & dispatcherItem = dispatchera[i];

      if (dispatcherItem == dispatcher)
      {

         return nullptr;

      }

   }

   dispatchera.add(dispatcher);

   return dispatcher.m_pparticleHandlerTarget.m_p;

}



void channel::route_message(::message::message * pmessage)
{

   if (::is_null(pmessage)) { ASSERT(false); return; } { critical_section_lock synchronouslock(platform()->channel_critical_section()); pmessage->m_pdispatchera = get_message_map()->pget(pmessage->m_emessage); } if (pmessage->m_pdispatchera == nullptr || pmessage->m_pdispatchera->is_empty()) return;

   for (pmessage->m_pchannel = this, pmessage->m_iRouteIndex = pmessage->m_pdispatchera->get_upper_bound(); pmessage->m_pdispatchera && pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
   {

      auto & dispatcher = pmessage->m_pdispatchera->m_begin[pmessage->m_iRouteIndex];

      if (::is_null(&dispatcher))
      {

         break;

      }

      dispatcher.m_functionHandler(pmessage); if (pmessage->m_bRet) return;

   }

}


void channel::_route_command(::message::command * pcommand)
{

   ASSERT(!pcommand->m_bProbing);

   if (::is_null(pcommand)) { ASSERT(false); return; } { critical_section_lock synchronouslock(platform()->channel_critical_section()); pcommand->m_pdispatchera = get_command_map()->pget(pcommand->m_atomCommand); } if (pcommand->m_pdispatchera == nullptr || pcommand->m_pdispatchera->is_empty()) return;

   for (pcommand->m_pchannel = this, pcommand->m_iRouteIndex = pcommand->m_pdispatchera->get_upper_bound(); pcommand->m_pdispatchera && pcommand->m_iRouteIndex >= 0; pcommand->m_iRouteIndex--)
   {

      auto & dispatcher = pcommand->m_pdispatchera->m_begin[pcommand->m_iRouteIndex];

      if (::is_null(&dispatcher))
      {

         break;

      }

      dispatcher.m_functionHandler(pcommand); if (pcommand->m_bRet) return;

   }

}


void channel::_route_command_probe(::message::command * pcommand)
{

   ASSERT(pcommand->m_bProbing);

   if (::is_null(pcommand)) { ASSERT(false); return; } { critical_section_lock synchronouslock(platform()->channel_critical_section()); pcommand->m_pdispatchera = get_command_probe_map()->pget(pcommand->m_atomCommand); } if (pcommand->m_pdispatchera == nullptr || pcommand->m_pdispatchera->is_empty()) return;

   for (pcommand->m_pchannel = this, pcommand->m_iRouteIndex = pcommand->m_pdispatchera->get_upper_bound(); pcommand->m_pdispatchera && pcommand->m_iRouteIndex >= 0; pcommand->m_iRouteIndex--)
   {

      auto & dispatcher = pcommand->m_pdispatchera->m_begin[pcommand->m_iRouteIndex];

      if (::is_null(&dispatcher))
      {

         break;

      }

      dispatcher.m_functionHandler(pcommand); if (pcommand->m_bRet) return;

   }

}


::pointer<::message::message>channel::get_message(MESSAGE * pmessage)
{

   auto pmessagemessage = __allocate::message::message();

   pmessagemessage->m_oswindow = pmessage->m_oswindow;
   pmessagemessage->m_emessage = pmessage->m_emessage;
   pmessagemessage->m_wparam = pmessage->m_wparam;
   pmessagemessage->m_lparam = pmessage->m_lparam;

   return pmessagemessage;

}
#define _NEW_MESSAGE(TYPE) \
   auto pmessage = __allocate TYPE(); \
   pmessageBase = pmessage; \
   pmessage->m_emessage = emessage; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam;


//::pointer<::message::message>channel::get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, const ::int_point & point)
::pointer<::message::message>channel::get_message(::enum_message emessage, ::wparam wparam, ::lparam lparam, ::message::enum_prototype eprototype)
{

   ::pointer<::message::message>pmessageBase;

   if (eprototype == ::message::e_prototype_none)
   {

      eprototype = ::message::get_message_prototype(emessage, 0);

   }

   switch (eprototype)
   {
   case ::message::e_prototype_simple_command:
   {
      _NEW_MESSAGE(::message::simple_command);
   }
   break;
   //case ::message::e_prototype_object:
   //{
   //   _NEW_MESSAGE(::message::particle);
   //}
   //break;
   default:
   {
      _NEW_MESSAGE(::message::message);
   }
   break;
   }


   //auto pmessagemessage = __allocate ::message::message();

   //pmessagemessage->id() = atom;
   //pmessagemessage->m_wparam = wparam;
   //pmessagemessage->m_lparam = lparam;

   return pmessageBase;

}


//::pointer<::user::message>channel::get_message_base(::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
//{
//
//   if (atom.m_etype != ::atom::e_type_message)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   MESSAGE msg;
//
//   zero(msg);
//
//   msg.message = (unsigned int) atom.m_emessage;
//   msg.wParam = wparam;
//   msg.lParam = lparam;
//
//   return get_message_base(&msg);
//
//}


//#ifdef LINUX
//
//
//::pointer<::user::message>channel::get_message_base(void * phappening,::user::interaction * puserinteraction)
//{
//
//   throw ::exception(todo);
//
//   return nullptr;
//
//}
//
//
//#endif




void channel::erase_all_routes()
{

   try
   {

      ///::pointer_array < ::particle >a;

      {

         critical_section_lock synchronouslock(platform()->channel_critical_section());

         //for (auto & i : m_dispatchermapNormal)
         //{
         //   for (auto & j : i.m_element2)
         //   {
         //      a.add_item(j.m_pparticleHandlerTarget.m_p);
         //   }
         //}
         //for (auto & i : m_dispatchermapProbe)
         //{
         //   for (auto & j : i.m_element2)
         //   {
         //      a.add_item(j.m_pparticleHandlerTarget.m_p);
         //   }
         //}
         //      m_dispatchermapProbe.erase_all();

               // if(m_bNewChannel)
               // {

               //    m_dispatchermapNew = m_dispatchermap;

               //    m_bNewChannel = false;

               // }

         m_messagemap.erase_all();
         m_commandmap.erase_all();
         m_commandmapProbe.erase_all();

      }

      //a.clear();

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
//                  synchronous_lock synchronouslock(route->m_preceiver->m_pmutexChannel);
//
//                  route->m_preceiver->m_sendera.erase(this);
//
//               }
//               catch (...)
//               {
//
//               }
//
//            });
//
//            id_route_array.element2()->erase_all();
//
//         }
//

   }
   catch (...)
   {

   }

}


::message::message_map * channel::get_message_map()
{

   return &m_messagemap;

}

::message::command_map * channel::get_command_map()
{

   return &m_commandmap;

}

::message::command_map * channel::get_command_probe_map()
{

   return &m_commandmapProbe;

}
//
//   }
//   else
//   {
//
//      return &m_dispatchermapNormal;
//
//   }
//}

void channel::channel_common_construct()
{

   //m_bNewChannel = true;

}


void channel::destroy()
{

   if (m_pchannel && m_pchannel != this)
   {

      m_pchannel->destroy();

   }

   m_pchannel.release();

   m_atomaHandledCommands.erase_all();

   m_messagemap.erase_all();
   m_commandmap.erase_all();
   m_commandmapProbe.erase_all();

   ///   m_dispatchermapNew.erase_all();

      //for (auto& procedurea : m_proceduremap.values())
      //{

      //   procedurea.destroy();

      //   procedurea.erase_all();

      //}

      //m_proceduremap.erase_all();

   ::particle::destroy();

   //return ::success;

}


//void channel::command_handler(::message::command * pcommand)
//{
//
//   pcommand->handle(this);
//
//}


void channel::message_handler(::message::message * pmessage)
{

   //return false;

}


void channel::_001SendCommand(::message::command * pcommand)
{

   pcommand->m_pchannel = this;

   {

      //      scoped_restore(pcommand->m_atomCommand.m_etype);
      //
      //      pcommand->m_atomCommand.set_compounded_type(::atom::e_type_command);

      route_command(pcommand, true);

   }

}


void channel::_001SendCommandProbe(::message::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      scoped_restore(pcommand->m_bProbing);
      pcommand->m_bProbing = true;
      //      pcommand->m_atomCommand.set_compounded_type(::atom::e_type_command_probe);

      route_command(pcommand);

   }

}


void channel::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   if (pcommand->m_bProbing)
   {

      _route_command_probe(pcommand);

   }
   else
   {

      _route_command(pcommand);

   }

}


void channel::command_handler(::message::command * pcommand)
{

   if (pcommand->m_bProbing)
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

   }
   else
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

      if (!pcommand->m_bEnableChanged
         && !pcommand->m_bRadioChanged
         && pcommand->echeck() == e_check_undefined
         && !pcommand->m_bHasCommandHandler)
      {

         if (on_command_final(pcommand->m_emessage, pcommand->user_activation_token()))
         {

            pcommand->m_bRet = true;

         }

         return;

      }

      on_command(pcommand);

   }

}


bool channel::has_command_handler(::message::command * pcommand)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   if (m_atomaHandledCommands.contains(pcommand->m_atomCommand))
   {

      return true;

   }

   //   pcommand->m_atomCommand.set_compounded_type(::atom::e_type_command);
   //
   //   if (m_atomaHandledCommands.contains(pcommand->m_atomCommand))
   //   {
   //
   //      return true;
   //
   //   }

   auto passociation = m_commandmap.plookup(pcommand->m_atomCommand);

   if (passociation.is_null())
   {

      return false;

   }

   if (passociation->m_element2.is_empty())
   {

      return false;

   }

   return true;

}


void channel::on_command_probe(::message::command * pcommand)
{

   scoped_restore(pcommand->m_bProbing);

   //pcommand->m_atomCommand.set_compounded_type(::atom::e_type_command_probe);
   pcommand->m_bProbing = true;
   route_message(pcommand);

   pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   pcommand->m_bRet =
      pcommand->m_bEnableChanged
      || pcommand->m_bRadioChanged
      || pcommand->echeck() != e_check_undefined;

}


bool channel::on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken)
{

   return false;

}


void channel::on_command(::message::command * pcommand)
{

   //   scoped_restore(pcommand->m_atomCommand.m_etype);
   //
   //   pcommand->m_atomCommand.set_compounded_type(::atom::e_type_command);

   //if (pcommand->m_bProbing)
   //{

   //   route_command_probe(pcommand);

   //}
   //else
   {

      route_command(pcommand);

   }

}


//bool channel::_add_message_handler(const ::atom & atom, ::object * preceiver, void * phandler, const ::message::handler & handler)
//{
//
//    auto & handlera = m_handlermap[atom];
//
//    if(preceiver != nullptr || phandler != nullptr)
//    {
//
//        for (::collection::index i = 0; i < handlera.get_count(); i++)
//        {
//
//            if (handlera.element_at(i).m_preceiver == preceiver
//                && handlera.element_at(i).m_pHandler == (void *) phandler)
//            {
//
//                return false;
//
//            }
//
//        }
//
//    }
//
//    ::message::handler_item handleritem(preceiver, phandler);
//
//    handleritem.m_handler = handler;
//
//    handlera.add(handleritem);
//
//    return true;
//
//}


//void channel::id_notify(const ::atom & atom, const ::matter * pmatter)
//{
//
//   auto & procedurea = m_proceduremap[atom];
//
//   procedurea.add(procedure); // pmatter is notified with atom
//
//}





// void channel::default_toggle_check_handling(const ::atom & atom)
// {
//
//    auto linkedproperty = fetch_property(atom);
//
//    add_command_handler(atom, [linkedproperty](::message::message * pmessage)
//       {
//
//          if (linkedproperty->get_bool())
//          {
//
//             *linkedproperty = ::e_check_unchecked;
//
//          }
//          else
//          {
//
//             *linkedproperty = ::e_check_checked;
//
//          }
//
//          linkedproperty.notify_property_changed(pmessage->m_actioncontext);
//
//          pmessage->m_bRet = true;
//
//       });
//
// }



