#include "framework.h"

//
//
//namespace axis
//{
//
//
//   live_signal::live_signal()
//   {
//
//   }
//
//   live_signal::live_signal(const live_signal & signal)
//   {
//
//      operator = (signal);
//
//   }
//
//   void live_signal::keep(object * pliveobject)
//   {
//
//      if(pliveobject != nullptr)
//      {
//
//         m_objectaLive.add(pliveobject);
//
//      }
//
//   }
//
//   void live_signal::unkeep(object * pliveobject)
//   {
//
//      if(pliveobject != nullptr)
//      {
//
//         m_objectaLive.remove(pliveobject);
//
//      }
//
//   }
//
//
//   void live_signal::on_keep_alive()
//   {
//
//      for(i32 i = 0; i < m_objectaLive.get_count(); i++)
//      {
//
//         try
//         {
//
//            m_objectaLive.element_at(i)->keep_alive();
//
//         }
//         catch(...)
//         {
//
//         }
//
//      }
//
//   }
//
//
//   bool live_signal::is_alive()
//   {
//
//      return true;
//
////      for(i32 i = 0; i < m_objectaLive.get_count(); i++)
////      {
////
////         try
////         {
////
////            if(!m_objectaLive.element_at(i)->is_alive())
////               return false;
////
////         }
////         catch(...)
////         {
////
////            return false;
////
////         }
////
////      }
////
////      return true;
//
//   }
//
//   live_signal & live_signal::operator = (const live_signal & signal)
//   {
//
//      if(this != &signal)
//      {
//         m_objectaLive = signal.m_objectaLive;
//      }
//
//      return *this;
//
//   }
//
//
//} // namespace axis
//
//
