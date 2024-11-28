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


void channel::install_message_routing(::channel* pchannel)
{

   ::object::install_message_routing(pchannel);

}
void channel::erase_handler(::particle * pparticle)
{
   erase_handler(pparticle, false);
   erase_handler(pparticle, true);
   
}


void channel::erase_handler(::particle * pparticle, bool bProber)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   auto payloads = get_dispatcher_map(bProber)->payloads();

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


void channel::transfer_handler(::message::dispatcher_map & dispatchermap, ::particle * pparticle, bool bProber)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());
   
   auto pdispatchermap = get_dispatcher_map(bProber);

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


::particle* channel::add_message_handler(const ::atom & atom, const ::message::dispatcher & dispatcher, bool bProber)
{

   auto pdispatchermap =
   
       get_dispatcher_map(bProber);
   
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

   return dispatcher.m_pparticleHandlerTarget;

}


void channel::route_message(::message::message * pmessage)
{

   if (::is_null(pmessage)) { ASSERT(false); return; } { critical_section_lock synchronouslock(platform()->channel_critical_section()); pmessage->m_pdispatchera = get_dispatcher_map(pmessage->m_bProbing)->pget(pmessage->m_atom); } if(pmessage->m_pdispatchera == nullptr || pmessage->m_pdispatchera->is_empty()) return;

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

   auto pmessagemessage = __allocate ::message::message();

   pmessagemessage->m_oswindow = pmessage->oswindow;
   pmessagemessage->m_atom = pmessage->m_atom;
   pmessagemessage->m_wparam = pmessage->wParam;
   pmessagemessage->m_lparam = pmessage->lParam;

   return pmessagemessage;

}
#define _NEW_MESSAGE(TYPE) \
   auto pmessage = __allocate TYPE(); \
   pmessageBase = pmessage; \
   pmessage->m_atom = atom; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam;


//::pointer<::message::message>channel::get_message(const ::atom & atom, wparam wparam, lparam lparam, const ::int_point & point)
::pointer<::message::message>channel::get_message(const ::atom& atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype)
{

   ::pointer<::message::message>pmessageBase;

   if (eprototype == ::message::e_prototype_none)
   {

      eprototype = ::message::get_message_prototype(atom.as_emessage(), 0);

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

   //pmessagemessage->m_atom = atom;
   //pmessagemessage->m_wparam = wparam;
   //pmessagemessage->m_lparam = lparam;

   return pmessageBase;

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
      ::pointer_array < ::particle >a;

      {

         critical_section_lock synchronouslock(platform()->channel_critical_section());

         for (auto & i : m_dispatchermapNormal)
         {
            for (auto & j : i.m_element2)
            {
               a.add_item(::transfer(j.m_pparticleHandlerTarget));
            }
         }
         for (auto & i : m_dispatchermapProbe)
         {
            for (auto & j : i.m_element2)
            {
               a.add_item(::transfer(j.m_pparticleHandlerTarget));
            }
         }
         //      m_dispatchermapProbe.erase_all();

               // if(m_bNewChannel)
               // {

               //    m_dispatchermapNew = m_dispatchermap;

               //    m_bNewChannel = false;

               // }

         m_dispatchermapNormal.erase_all();
         m_dispatchermapProbe.erase_all();

      }

      a.clear();

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

   
   ::message::dispatcher_map * channel::get_dispatcher_map(bool bProber)
   {
      
      
    if(bProber)
    {
     
       return &m_dispatchermapProbe;
       
    }
   else
    {
       
         return &m_dispatchermapNormal;
         
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

   m_dispatchermapNormal.erase_all();
   m_dispatchermapProbe.erase_all();

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

//      scoped_restore(pcommand->m_atom.m_etype);
//
//      pcommand->m_atom.set_compounded_type(::atom::e_type_command);

      route_command(pcommand, true);

   }

}


void channel::_001SendCommandProbe(::message::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      scoped_restore(pcommand->m_bProbing);
      pcommand->m_bProbing = true;
//      pcommand->m_atom.set_compounded_type(::atom::e_type_command_probe);

      route_command(pcommand);

   }

}


void channel::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   command_handler(pcommand);

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

         return;

      }

      on_command(pcommand);

   }

}


bool channel::has_command_handler(::message::command * pcommand)
{

   critical_section_lock synchronouslock(platform()->channel_critical_section());

   scoped_restore(pcommand->m_atom.m_etype);

   string strText = pcommand->m_atom.as_string();

   if (strText.has_character())
   {

      if (m_atomaHandledCommands.contains(strText))
      {

         return true;

      }

   }

//   pcommand->m_atom.set_compounded_type(::atom::e_type_command);
//
//   if (m_atomaHandledCommands.contains(pcommand->m_atom))
//   {
//
//      return true;
//
//   }

   auto passociation = m_dispatchermapNormal.plookup(pcommand->m_atom);

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

   //pcommand->m_atom.set_compounded_type(::atom::e_type_command_probe);
   pcommand->m_bProbing = true;
   route_message(pcommand);

   pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   pcommand->m_bRet =
      pcommand->m_bEnableChanged
      || pcommand->m_bRadioChanged
      || pcommand->echeck() != e_check_undefined;

}


void channel::on_command(::message::command * pcommand)
{

//   scoped_restore(pcommand->m_atom.m_etype);
//
//   pcommand->m_atom.set_compounded_type(::atom::e_type_command);

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



