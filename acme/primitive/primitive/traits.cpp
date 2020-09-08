//
//  promisse_map.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//

#include "framework.h"

//
//traits::traits()
//{
//
//
//}
//
//
//traits::~traits()
//{
//
//}
//
//mutex * g_pmutexTrait;
//
//bool traits::is_ok() const
//{
//
//   if (!m_pestatusa)
//   {
//
//      return false;
//
//   }
//   //g_mutexTrait
//
//   for (auto & estatus : *m_pestatusa)
//   {
//
//      if (::failed(estatus))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//void traits::add(::i64 iTrait)
//{
//
//   if (!m_piaTraits)
//   {
//
//      m_piaTraits = __new(i64_array);
//
//   }
//
//   m_piaTraits->add(iTrait);
//
//   if (!m_pestatusa)
//   {
//
//      m_pestatusa = __new(array<::estatus>);
//
//   }
//
//   while (m_pestatusa->get_size() & m_piaTraits->get_size())
//   {
//
//      m_pestatusa->add(error_not_ready);
//
//   }
//
//
//}
////void traits::notify(::u64 uId)
////{
////
////   set_result(uId, 0, m_pobjectTrait);
////
////}
//
//
//
////__pointer(trait) traits::get(::u64 uId, ::u64 uTrait)
////{
////
////   auto ptrait = find(uId, uTrait);
////
////   if(ptrait)
////   {
////
////      return ptrait;
////
////   }
////
////   ptrait = __new(trait);
////
////   ptrait->construct(uId, uTrait);
////
////   m_traits.add(ptrait);
////
////   return ptrait;
////
////}
//
//
////__pointer(trait) traits::find(::u64 uId, ::u64 uTrait)
////{
////
////   auto & traits = m_traits;
////
////   for(auto & ptrait : traits.ptra())
////   {
////
////      if(ptrait->m_uId == uId && ptrait->m_uTrait == uTrait)
////      {
////
////         return ptrait;
////
////      }
////
////   }
////
////   return nullptr;
////
////}
//
//
////void traits::set_action(::generic * pobjectFork, const ::trait & traitPayload)
////{
////
////   if(traitPayload.m_uTrait == EVENT_ID)
////   {
////
////      throw(new invalid_argument_exception());
////
////   }
////   else
////   {
////
////      if(traitPayload.m_uTrait == 0)
////      {
////
////         throw(new invalid_argument_exception());
////
////      }
////      else
////      {
////
////         auto ptrait = get(traitPayload);
////
////         ptrait->set_action(traitPayload);
////
////         if(m_pobjectTrait->m_uid & traitPayload.m_uId)
////         {
////
////            if(!ptrait->m_preference)
////            {
////
////               ptrait->m_preference = m_pobjectTrait;
////
////            }
////
////            ptrait->fork(pobjectFork);
////
////         }
////
////      }
////
////   }
////
////}
////
////
////void traits::add_notification(const ::trait & traitPayload)
////{
////
////   if(traitPayload.m_uTrait == EVENT_ID)
////   {
////
////      auto ptrait = get(traitPayload);
////
////      ptrait->set_persistent();
////
////      if (traitPayload.m_pobjectTaskTransport)
////      {
////
////         traitPayload.m_pobjectTaskTransport->set_persistent();
////
////      }
////
////      ptrait->add_notification(traitPayload);
////
////   }
////   else if(m_pobjectTrait->m_uid & traitPayload.m_uId)
////   {
////
////      if(traitPayload.m_uTrait == 0)
////      {
////
////         auto & trait = (::trait &) traitPayload;
////
////         trait.m_preference = m_pobjectTrait;
////
////         trait.m_pobjectTaskaNotify = __new(::runnablea());
////
////         trait.m_pobjectTaskaNotify->add(traitPayload.m_pobjectTaskTransport);
////
////         trait._notify(m_pobjectTrait->get_context_object());
////
////      }
////      else
////      {
////
////         auto ptrait = get(traitPayload);
////
////         if(is_traited(traitPayload))
////         {
////
////            ptrait->add_notification(traitPayload);
////
////            auto & trait = (::trait &) traitPayload;
////
////            trait.m_preference = m_pobjectTrait;
////
////            trait.m_pobjectTaskaNotify = __new(::runnablea());
////
////            trait.m_pobjectTaskaNotify->add(traitPayload.m_pobjectTaskTransport);
////
////            trait._notify(m_pobjectTrait->get_context_object());
////
////         }
////         else
////         {
////
////            ptrait->add_notification(traitPayload);
////
////         }
////
////      }
////
////   }
////   else
////   {
////
////      auto ptrait = get(traitPayload);
////
////      ptrait->add_notification(traitPayload);
////
////   }
////
////}
////
////
////void traits::set_result(::u64 uId, ::u64 uPromisse, ::generic * preference)
////{
////
////   if(uPromisse == 0)
////   {
////
////      auto ptrait = find(uId, EVENT_ID);
////
////      if(ptrait)
////      {
////
////         _notify(ptrait);
////
////      }
////
////   }
////
////   auto ptrait = find(uId, uPromisse);
////
////   if(!ptrait)
////   {
////
////      return;
////
////   }
////
////   ptrait->m_preference = preference;
////
////   _notify(ptrait);
////
////}
//
//
////
////
////         }
////         else
////         {
////
////            if(promisse.m_pobjectTask)
////            {
////
////               promisse.m_pobjectTask->call(promisse);
////
////            }
////
////         }
////
////      }
////
////   }
////
////}
////
////
////
////{
////
////   auto & map = m_map[uId];
////
////   if (map.is_empty())
////   {
////
////      return nullptr;
////
////   }
////
////   return m_pappobject->get_object()->fork([this, uId, prefResult]()
////                                        {
////
////                                           set_result(uId, prefResult);
////
////                                        });
////
////}
////
////
////
////void promisse(const ::promisse & promisse);
////{
////
////   promisse * ppromisse = find(promisse);
////
////   if (m_pappobject->has_id(promisse.m_uId))
////   {
////
////      promiss
////      if (succeeded(promisse.m_pobjectTask->call(promisse.m_uId, m_pappobject)))
////      {
////
////         set_promisse(promisse.m_uId, promisse.m_uPromisse);
////
////      }
////      else
////      {
////
////         clear_promisse(promisse.m_u, promisse.m_uPromisse);
////
////      }
////
////   }
////   else
////   {
////
////      m_pappobject->add_event(promisse.m_u, promisse.m_pobjectTask);
////
////      if (m_pappobject->has_id(promisse.m_u) && promisse.m_pobjectTask->m_cRun == 0)
////      {
////
////         if (succeeded(promisse.m_pobjectTask->call()))
////         {
////
////            set_promisse(promisse.m_u, promisse.m_uPromisse);
////
////         }
////         else
////         {
////
////            clear_promisse(promisse.m_u, promisse.m_uPromisse);
////
////         }
////
////      }
////
////   }
////
////}
//
////void traits::_notify(::trait * ptrait)
////{
////
////   switch(ptrait->m_enotify)
////   {
////      case notify_fork:
////         _fork_notify(ptrait);
////         break;
////      case notify_fork_each:
////         _fork_notify_each(ptrait);
////         break;
////      default:
////         _call_notify(ptrait);
////         break;
////   };
////
////}
////
////
////void traits::_call_notify(::trait * ptrait)
////{
////
////   if(ptrait->m_uId > 0 && ptrait->m_uTrait != EVENT_ID)
////   {
////
////      m_pobjectTrait->m_uid |= ptrait->m_uId;
////
////   }
////
////   auto & notifya = *ptrait->m_pobjectTaskaNotify;
////
////   for(index i = 0; i < notifya.get_count(); )
////   {
////
////      auto & pnotify = notifya[i];
////
////      pnotify->call(*ptrait);
////
////      if(pnotify->is_persistent())
////      {
////
////         i++;
////
////      }
////      else
////      {
////
////         notifya.remove_at(i);
////
////      }
////
////   }
////
////}
////
////
////thread_pointer traits::_fork_notify(__pointer(::trait) ptrait)
////{
////
////   return m_pobjectTrait->get_context_object()->fork([this, ptrait] { _notify(ptrait); });
////
////}
////
////
////thread_spa traits::_fork_notify_each(__pointer(::trait) ptrait)
////{
////
////   thread_spa threada;
////
////   auto & notifya = *ptrait->m_pobjectTaskaNotify;
////
////   for(index i = 0; i < notifya.get_count(); )
////   {
////
////      auto pnotify = notifya[i];
////
////      try
////      {
////
////         threada.add(m_pobjectTrait->get_context_object()->fork([pnotify, ptrait] { pnotify->call(*ptrait); }));
////
////      }
////      catch (...)
////      {
////
////      }
////
////      if(pnotify->is_persistent())
////      {
////
////         i++;
////
////      }
////      else
////      {
////
////         notifya.remove_at(i);
////
////      }
////
////   }
////
////   return threada;
////
////}
////
////
////::runnablea * trait::notifya()
////{
////
////   if(!m_pobjectTaskaNotify)
////   {
////
////      m_pobjectTaskaNotify = __new(runnablea);
////
////   }
////
////   return m_pobjectTaskaNotify;
////
////}
////
////
////void trait::set_action(const ::trait & traitPayload)
////{
////
////   m_preference = traitPayload.m_preference;
////   m_pobjectTask = traitPayload.m_pobjectTaskTransport;
////
////}
////
////
////void trait::add_notification(const ::trait & traitPayload)
////{
////
////   notifya()->add(traitPayload.m_pobjectTaskTransport);
////
////   if(traitPayload.m_enotify != notify_none)
////   {
////
////      m_enotify = traitPayload.m_enotify;
////
////   }
////
////}
////
////
////void trait::_notify(::generic * pobject)
////{
////
////   if(!m_pobjectTaskaNotify || m_pobjectTaskaNotify->is_empty()) return;
////
////   switch(m_enotify)
////   {
////      case notify_fork:
////         _fork_notify(pobject);
////         break;
////      case notify_fork_each:
////         _fork_notify_each(pobject);
////         break;
////      default:
////         _call_notify(pobject);
////         break;
////   };
////
////}
////
////
////void trait::_call_notify(::generic * pobject)
////{
////
////   auto & notifya = *m_pobjectTaskaNotify;
////
////   for(index i = 0; i < notifya.get_count(); )
////   {
////
////      auto & pnotify = notifya[i];
////
////      pnotify->call(*this);
////
////      if(pnotify->m_uid & PERSIST_ID)
////      {
////
////         i++;
////
////      }
////      else
////      {
////
////         notifya.remove_at(i);
////
////      }
////
////   }
////
////}
////
////
////thread_pointer trait::_fork_notify(::generic * pobject)
////{
////
////   if(m_pobjectTaskaNotify) return nullptr;
////
////   __pointer(::generic) p(pobject);
////
////   return pobject->fork([this, p] { _call_notify(p); });
////
////}
////
////
////thread_spa trait::_fork_notify_each(::generic * pobjectFork)
////{
////
////   thread_spa threada;
////
////   if(m_pobjectTaskaNotify) return threada;
////
////   __pointer(::generic) p(pobject);
////
////   auto & notifya = *m_pobjectTaskaNotify;
////
////   for(index i = 0; i < notifya.get_count(); )
////   {
////
////      auto pnotify = notifya[i];
////
////      try
////      {
////
////         threada.add(p->fork([pnotify, this] { pnotify->call(*this); }));
////
////      }
////      catch (...)
////      {
////
////      }
////
////      if(pnotify->m_uid & PERSIST_ID)
////      {
////
////         i++;
////
////      }
////      else
////      {
////
////         notifya.remove_at(i);
////
////      }
////
////   }
////
////   return threada;
////
////}
////
////
////
////
////void trait::fork(::generic * pobject)
////{
////
////   if (is_traited())
////   {
////
////      return;
////
////   }
////
////   __pointer(trait) ptrait = this;
////
////   pobject->fork([ptrait]()
////                 {
////
////                    ptrait->m_pobjectTask->call(*ptrait);
////
////                 });
////
////}
