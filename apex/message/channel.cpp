#include "framework.h"
#include "channel.h"
#include "acme/operating_system/message.h"
#include "acme/platform/message.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/scoped_restore.h"
//#include "apex/message.h"
#include "apex/message/command.h"


//::pointer < ::mutex >channel::s_pmutexChannel;


channel::channel()
{

   channel_common_construct();

}


channel::~channel()
{

   erase_all_routes();

}


void channel::install_message_routing(::channel* pchannel)
{

   ::object::install_message_routing(pchannel);

}


void channel::erase_handler(::particle * pparticle)
{

   critical_section_lock synchronouslock(::acme::acme::g_p->channel_critical_section());

   auto values = m_dispatchermap.values();

   auto begin = values.begin();

   auto end = values.end();

   for (auto & dispatchera : values)
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


void channel::transfer_handler(::message::dispatcher_map & dispatchermap, ::particle * pparticle)
{

   critical_section_lock synchronouslock(::acme::acme::g_p->channel_critical_section());

   for (auto & pair : m_dispatchermap)
   {

      if (pair.element2().is_empty())
      {

         continue;

      }

      pair.element2().predicate_each([&](auto & dispatcher)
      {

         if (dispatcher.m_pparticleHandlerTarget == pparticle)
         {

            auto & dispatcha = dispatchermap[pair.element1()];

            dispatcha.add(dispatcher);

         }

      });

      pair.element2().predicate_erase([&](auto & dispatcher)
      {

         return dispatcher.m_pparticleHandlerTarget == pparticle;

      });

   }

}


::particle* channel::add_message_handler(const ::atom & atom, const ::message::dispatcher & dispatcher)
{

   auto & dispatchera = m_dispatchermap[atom];
   
   // Try to not add already added dispatcher
   for (index i = 0; i < dispatchera.get_count(); i++)
   {

      auto & dispatcherItem = dispatchera[i];

      if (dispatcherItem == dispatcher)
      {

         return nullptr;

      }

   }
   
   dispatchera.add(dispatcher);

   return dispatcher.m_pparticleHandlerTarget;

}


void channel::route_message(::message::message * pmessage)
{

   if (::is_null(pmessage)) { ASSERT(false); return; } { critical_section_lock synchronouslock(::acme::acme::g_p->channel_critical_section()); pmessage->m_pdispatchera = m_dispatchermap.pget(pmessage->m_atom); } if(pmessage->m_pdispatchera == nullptr || pmessage->m_pdispatchera->is_empty()) return;

   for(pmessage->m_pchannel = this, pmessage->m_iRouteIndex = pmessage->m_pdispatchera->get_upper_bound(); pmessage->m_pdispatchera && pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
   {

      auto & dispatcher = pmessage->m_pdispatchera->m_begin[pmessage->m_iRouteIndex];

      if (::is_null(&dispatcher))
      {

         break;

      }

      dispatcher.m_functionHandler(pmessage); if(pmessage->m_bRet) return;

   }

}


::pointer<::message::message>channel::get_message(MESSAGE * pmessage)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      pmessage->oswindow, 
      nullptr,
      pmessage->m_atom, 
      pmessage->wParam, 
      pmessage->lParam);

   return pmessagemessage;

}


//::pointer<::message::message>channel::get_message(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
::pointer<::message::message>channel::get_message(const ::atom& atom, wparam wparam, lparam lparam)
{

   auto pmessagemessage = __new(::message::message);

   pmessagemessage->set(
      nullptr,
      nullptr,
      atom,
      wparam,
      lparam);

   return pmessagemessage;

}


//::pointer<::user::message>channel::get_message_base(::windowing::window * pwindow, const ::atom & atom, wparam wparam, lparam lparam)
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
//   msg.message = (::u32) atom.m_emessage;
//   msg.wParam = wparam;
//   msg.lParam = lparam;
//
//   return get_message_base(&msg);
//
//}


//#ifdef LINUX
//
//
//::pointer<::user::message>channel::get_message_base(void * pevent,::user::interaction * puserinteraction)
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

      critical_section_lock synchronouslock(::acme::acme::g_p->channel_critical_section());

      // if(m_bNewChannel)
      // {

      //    m_dispatchermapNew = m_dispatchermap;

      //    m_bNewChannel = false;

      // }

      m_dispatchermap.erase_all();

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

   m_dispatchermap.erase_all();

///   m_dispatchermapNew.erase_all();

   //for (auto& procedurea : m_proceduremap.values())
   //{

   //   procedurea.destroy();

   //   procedurea.erase_all();

   //}

   //m_proceduremap.erase_all();

   ::object::destroy();

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

      ___scoped_restore(pcommand->m_atom.m_etype);

      pcommand->m_atom.set_compounded_type(::atom::e_type_command);

      route_command(pcommand, true);

   }

}


void channel::_001SendCommandProbe(::message::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      ___scoped_restore(pcommand->m_atom.m_etype);

      pcommand->m_atom.set_compounded_type(::atom::e_type_command_probe);

      route_command(pcommand);

   }

}


void channel::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   command_handler(pcommand);

}


void channel::command_handler(::message::command * pcommand)
{

   if (pcommand->is_command())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

      if (!pcommand->m_bEnableChanged
         && !pcommand->m_bRadioChanged
         && pcommand->m_echeck == e_check_undefined
         && !pcommand->m_bHasCommandHandler)
      {

         return;

      }

      on_command(pcommand);

   }
   else if (pcommand->m_atom.is_command_probe())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

   }
   else if (pcommand->m_atom.is_command())
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   }
   else
   {

      //throw ::not_implemented();

   }

}


bool channel::has_command_handler(::message::command * pcommand)
{

   critical_section_lock synchronouslock(::acme::acme::g_p->channel_critical_section());

   ___scoped_restore(pcommand->m_atom.m_etype);

   string strText = pcommand->m_atom;

   if (strText.has_char())
   {

      if (m_atomaHandledCommands.contains(strText))
      {

         return true;

      }

   }

   pcommand->m_atom.set_compounded_type(::atom::e_type_command);

   if (m_atomaHandledCommands.contains(pcommand->m_atom))
   {

      return true;

   }

   auto passociation = m_dispatchermap.plookup(pcommand->m_atom);

   if (!passociation)
   {

      return false;

   }

   if (passociation->m_element2.is_empty())
   {

      return false;

   }

   if (passociation->element2().is_empty())
   {

      return false;

   }

   return true;

}


void channel::on_command_probe(::message::command * pcommand)
{

   ___scoped_restore(pcommand->m_atom.m_etype);

   pcommand->m_atom.set_compounded_type(::atom::e_type_command_probe);

   route_message(pcommand);

   pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   pcommand->m_bRet =
      pcommand->m_bEnableChanged
      || pcommand->m_bRadioChanged
      || pcommand->m_echeck != e_check_undefined;

}


void channel::on_command(::message::command * pcommand)
{

   ___scoped_restore(pcommand->m_atom.m_etype);

   pcommand->m_atom.set_compounded_type(::atom::e_type_command);

   route_message(pcommand);

}


//bool channel::_add_message_handler(const ::atom & atom, ::object * preceiver, void * phandler, const ::message::handler & handler)
//{
//
//    auto & handlera = m_handlermap[atom];
//
//    if(preceiver != nullptr || phandler != nullptr)
//    {
//
//        for (::index i = 0; i < handlera.get_count(); i++)
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





void channel::default_toggle_check_handling(const ::atom & atom)
{

   auto linkedproperty = fetch_property(atom);

   add_command_handler(atom, [linkedproperty](::message::message * pmessage)
      {

         if (linkedproperty->get_bool())
         {

            *linkedproperty = ::e_check_unchecked;

         }
         else
         {

            *linkedproperty = ::e_check_checked;

         }

         linkedproperty.notify_property_changed(pmessage->m_actioncontext);

         pmessage->m_bRet = true;

      });

}



