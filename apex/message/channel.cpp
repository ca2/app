#include "framework.h"
#include "apex/message.h"

//
//namespace message
//{
//
//
//   sender::sender()
//   {
//
//      m_pmutexIdRoute = new ::mutex();
//
//      m_bNew = true;
//
//   }
//
//
//   sender::~sender()
//   {
//
//      remove_all_routes();
//
//      ::acme::del(m_pmutexIdRoute);
//
//   }
//
//
//   void sender::remove_receiver(::object * preceiver)
//   {
//
//      for (auto & id_route_array : m_idroute)
//      {
//
//         if (id_route_array.element2().is_null())
//         {
//
//            continue;
//
//         }
//
//         id_route_array.element2()->pred_remove([=](auto & pitem)
//         {
//
//            return pitem->m_preceiver == preceiver;
//
//         });
//
//      }
//
//      //preceiver->m_sendera.remove(this);
//
//   }
//
//   void sender::transfer_receiver(id_route & router, ::object * preceiver)
//   {
//
//      for (auto & id_route_array : m_idroute)
//      {
//
//         if (id_route_array.element2().is_null())
//         {
//
//            continue;
//
//         }
//
//         id_route_array.element2()->pred_each([&](auto & pitem)
//         {
//
//            if (pitem->m_preceiver == preceiver)
//            {
//
//               auto & routera = router[id_route_array.element1()];
//
//               if (routera.is_null())
//               {
//
//                  routera = __new(route_array);
//
//               }
//
//               routera->add(pitem);
//
//            }
//
//         });
//
//         id_route_array.element2()->pred_remove([&](auto & pitem)
//         {
//
//            return pitem->m_preceiver == preceiver;
//
//         });
//
//      }
//
//
//   }
//
//
//   void sender::route_message(::message::message * pmessage)
//   {
//
//      if (::is_null(pmessage)) { ASSERT(FALSE); return; } { sync_lock sl(m_pmutexIdRoute); pmessage->m_routea = m_idroute[pmessage->m_id]; } if (pmessage->m_routea.is_null()) { return; }
//
//      for(pmessage->m_psender = this, pmessage->m_iRouteIndex = pmessage->m_routea->get_upper_bound(); pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
//      {
//
//         pmessage->m_routea.m_p->m_pData[pmessage->m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(pmessage); if(pmessage->m_bRet) return;
//
//      }
//
//   }
//
//
//   void sender::remove_all_routes()
//   {
//
//      try
//      {
//
//         sync_lock sl(m_pmutexIdRoute);
//
//         if(m_bNew)
//         {
//
//            m_idrouteNew = m_idroute;
//
//            m_bNew = false;
//
//         }
//
//         m_idroute.remove_all();
//
////         for (auto & id_route_array : m_idroute)
////         {
////
////            if (id_route_array.element2().is_null())
////            {
////
////               continue;
////
////            }
////
////            id_route_array.element2()->pred_each([=](auto & route)
////            {
////
////               try
////               {
////
////                  sync_lock sl(route->m_preceiver->mutex());
////
////                  route->m_preceiver->m_sendera.remove(this);
////
////               }
////               catch (...)
////               {
////
////               }
////
////            });
////
////            id_route_array.element2()->remove_all();
////
////         }
////
//
//      }
//      catch (...)
//      {
//
//      }
//
//
//
//   }
//
//
//
//
//} // namespace message

__pointer(::mutex) channel::s_pmutexChannel;


   channel::channel()
   {


      CommonConstruct();


   }


   channel::~channel()
   {

      remove_all_routes();

   }


   ::mutex * channel::defer_mutex_channel()
   {

      return s_pmutexChannel;

   }


   void channel::remove_receiver(::object * preceiver)
   {

      sync_lock sl(defer_mutex_channel());

      for (auto & id_route_array : m_idroute)
      {

         if (id_route_array.element2().is_null())
         {

            continue;

         }

         id_route_array.element2()->pred_remove([=](auto & pitem)
         {

            return pitem->m_preceiver == preceiver;

         });

      }

      //preceiver->m_sendera.remove(this);

   }

   void channel::transfer_receiver(::message::id_route & router, ::object * preceiver)
   {

      sync_lock sl(defer_mutex_channel());

      for (auto & id_route_array : m_idroute)
      {

         if (id_route_array.element2().is_null())
         {

            continue;

         }

         id_route_array.element2()->pred_each([&](auto & pitem)
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

         id_route_array.element2()->pred_remove([&](auto & pitem)
         {

            return pitem->m_preceiver == preceiver;

         });

      }


   }


   void channel::route_message(::message::message * pmessage)
   {

      if (::is_null(pmessage)) { ASSERT(FALSE); return; } { sync_lock sl(defer_mutex_channel()); pmessage->m_proutea = m_idroute[pmessage->m_id]; } if (pmessage->m_proutea.is_null()) { return; }

      for(pmessage->m_pchannel = this, pmessage->m_iRouteIndex = pmessage->m_proutea->get_upper_bound(); pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
      {

         pmessage->m_proutea.m_p->m_pData[pmessage->m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(pmessage); if(pmessage->m_bRet) return;

      }

   }


   __pointer(::message::base) channel::get_message_base(UINT message, WPARAM wparam, lparam lparam)
   {

      MESSAGE msg;

      xxf_zero(msg);

      msg.message = message;
      msg.wParam = wparam;
      msg.lParam = lparam;

      return get_message_base(&msg);

   }





   __pointer(::message::base) channel::get_message_base(LPMESSAGE pmsg)
   {

      //__throw(todo("message"));
      //__throw(todo("interaction"));
      ::user::primitive * pinteraction = nullptr;

      //if (pinteraction == nullptr && pmsg->hwnd != nullptr)
      //{

      //   if (pmsg->message == 126)
      //   {

      //      TRACE("WM_DISPLAYCHANGE");

      //   }

      //   ::user::interaction_impl * pimpl = System.impl_from_handle(pmsg->hwnd);

      //   if (pimpl != nullptr)
      //   {

      //      try
      //      {

      //         pinteraction = pimpl->m_puserinteraction;

      //      }
      //      catch (...)
      //      {

      //         pinteraction = nullptr;

      //      }

      //   }

      //   if (pinteraction == nullptr)
      //   {

      //      pinteraction = pimpl;

      //   }

      //}

      //if (pinteraction != nullptr)
      //{

      //   return pinteraction->get_message_base(pmsg->message, pmsg->wParam, pmsg->lParam);

      //}

      auto pbase = __new(::message::base);

      if (!pbase)
      {

         return nullptr;

      }

      pbase->set(pinteraction, pmsg->message, pmsg->wParam, pmsg->lParam);


      return pbase;



   }


   void channel::remove_all_routes()
   {

      try
      {

         sync_lock sl(defer_mutex_channel());

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
//            id_route_array.element2()->pred_each([=](auto & route)
//            {
//
//               try
//               {
//
//                  sync_lock sl(route->m_preceiver->m_pmutexChannel);
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





   void channel::CommonConstruct()
   {

      //defer_create_mutex();

      m_bNewChannel = true;

   }



   bool channel::handle(::user::command * pcommand)
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


   void channel::default_toggle_check_handling(const ::id & id)
   {

      auto pproperty = fetch_property(id);

      connect_command_pred(id, [this, id, pproperty](::message::message* pmessage)
         {

            SCAST_PTR(::user::command, pcommand, pmessage);

            if (pproperty->get_bool())
            {

               *pproperty = ::check_unchecked;

            }
            else
            {

               *pproperty = ::check_checked;

            }

            call_update(pproperty->m_id, pcommand->m_actioncontext);


      });

   }


   void channel::_001SendCommand(::user::command * pbase)
   {

      pbase->m_pchannel = this;

      {

         __set_restore(pbase->m_id.m_emessagetype, ::message::type_command);

         route_command_message(pbase);

      }

   }


   void channel::_001SendCommandProbe(::user::command * pcommand)
   {

      pcommand->m_pcommandtargetSource = this;

      {

         __set_restore(pcommand->m_id.m_emessagetype, ::message::type_command_probe);

         route_command_message(pcommand);

      }

   }


   void channel::call_update(const ::id & id, const ::action_context & context)
   {

      auto & notifya = m_mapUpdate[id];

      for (auto & pnotify : notifya)
      {

         pnotify->call_update(id, context);

      }
      
      if(context.is_user_source())
      {

         auto& runnablea = m_mapRunnable[id];

         ::call_sync(runnablea);
         
      }

   }



   void channel::route_command_message(::user::command * pcommand)
   {

      on_command_message(pcommand);

   }


   void channel::on_command_message(::user::command* pcommand)
   {

      if (pcommand->m_id.m_emessagetype == ::message::type_command)
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
      else if (pcommand->m_id.m_emessagetype == ::message::type_command_probe)
      {

         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

         on_command_probe(pcommand);

      }
      else if (pcommand->m_id.m_emessagetype == ::message::type_has_command_handler)
      {

         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      }
      else
      {

         __throw(not_implemented());

      }

   }


   void channel::on_command(::user::command * pcommand)
   {

      {

         __set_restore(pcommand->m_id.m_emessagetype, ::message::type_command);

         route_message(pcommand);

      }

   }


   bool channel::has_command_handler(::user::command * pcommand)
   {

      sync_lock sl(defer_mutex_channel());

      __set_restore(pcommand->m_id.m_emessagetype, ::message::type_command);

      if (m_idaHandledCommands.contains(pcommand->m_id))
      {

         return true;

      }

      __pointer(::message::route_array) & proutea = m_idroute[pcommand->m_id];

      if (proutea.is_null())
      {

         return false;

      }

      if (proutea->is_empty())
      {

         return false;

      }

      return true;

   }


   void channel::on_command_probe(::user::command * pcommand)
   {

      {

         __set_restore(pcommand->m_id.m_emessagetype, ::message::type_command_probe);

         route_message(pcommand);

         pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

         pcommand->m_bRet =
            pcommand->m_bEnableChanged
            || pcommand->m_bRadioChanged
            || pcommand->m_echeck != check_undefined;

      }

   }




   void channel::install_message_routing(::channel * pchannel)
   {

      ::object::install_message_routing(pchannel);

   }
