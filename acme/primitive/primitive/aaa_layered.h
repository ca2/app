#pragma once

//
//template < typename TYPE >
//class CLASS_DECL_ACME layered :
//   virtual public matter
//{
//public:
//
//   
//   tiny_array < void * >   m_layers;
//
//
//   void set_layer(::i32 iIndex, void* p)
//   {
//
//      m_layers.set_at_grow(iIndex, p);
//
//   }
//
//
//   inline void * layer(::i32 iIndex)
//   {
//      
//      return m_layers.element_at_grow(iIndex);
//   
//   }
//
//
//   inline void clear_layers() { m_layers.zero(); }
//
//
//};
//
//
//
//
//
//#define LAYERED_ACME 0
//#define LAYERED_APEX 1
//#define LAYERED_AQUA 2
//#define LAYERED_AURA 3
//#define LAYERED_AXIS 4
//#define LAYERED_BASE 5
//#define LAYERED_BRED 6
//#define LAYERED_CORE 7
//
//#define LAYERED_OBJECT 0
//#define LAYERED_DRAW2D_GRAPHICS 1
//#define LAYERED_USER_CREATE 1
//#define LAYERED_CHANNEL 1
//#define LAYERED_USER_PRIMITIVE 2
//#define LAYERED_THREAD 2
//#define LAYERED_USER_INTERACTION 3
//#define LAYERED_USER_FRAME 4
//#define LAYERED_USER_CONTROL_EVENT 7
//#define LAYERED_TASK_POOL 5
//#define LAYERED_OS_USER_INTERACTION_IMPL 6
//#define LAYERED_IMPL 7
//#define LAYERED_X11 6
//
//
//class object;
//
//
//class channel;
//
//
//class thread;
//
//
//template < typename TYPE >
//inline ::object* __object(::layered < TYPE > * playered)
//{
//
//   return (::object *) playered->layer(LAYERED_OBJECT);
//
//}
//
//
//template < typename TYPE >
//inline ::channel* __channel(::layered < TYPE > * playered)
//{
//
//   return (::channel *) playered->layer(LAYERED_OBJECT);
//
//}
//
//
//template < typename TYPE >
//inline ::thread* ___thread(::layered < TYPE > * playered)
//{
//
//   return (::thread *) playered->layer(LAYERED_THREAD);
//
//}
//
//
//
//namespace user
//{
//
//   class system;
//   class interaction;
//   class frame;
//   class primitive;
//   class control_event;
//
//} // namespace user
//
//
//template < typename FROM, typename TO_POINTER >
//concept layered_pointer_of =
//::std::is_convertible < FROM, layered < TO_POINTER > * >::value ||
//::std::is_convertible < FROM, const layered < TO_POINTER > * >::value ||
//::std::is_convertible < FROM, __pointer(layered < TO_POINTER > ) >::value;
//
//
//template < layered_pointer_of < ::user::system > LAYERED_POINTER >
//inline ::user::system * __user_system(const LAYERED_POINTER & playered)
//{
//
//   return (::user::system *)playered->layer(LAYERED_USER_CREATE);
//
//}
//
//
//template < layered_pointer_of < ::user::frame > LAYERED_POINTER >
//inline ::user::frame * __user_frame(const LAYERED_POINTER & playered)
//{
//
//   return (::user::frame *) playered->layer(LAYERED_USER_FRAME);
//
//}
//
//
//template < layered_pointer_of < ::user::interaction > LAYERED_POINTER >
//inline ::user::interaction* __user_interaction(const LAYERED_POINTER& playered)
//{
//
//   return (::user::interaction *) playered->layer(LAYERED_USER_INTERACTION);
//
//}
//
//
//template < layered_pointer_of < ::user::interaction > LAYERED_POINTER >
//inline ::user::primitive * __user_primitive(::layered < TYPE > * playered)
//{
//
//   return (::user::primitive *) playered->layer(LAYERED_USER_PRIMITIVE);
//
//}
//
//
//template < typename TYPE >
//inline ::user::control_event * __user_control_event(::layered < TYPE > * playered)
//{
//
//   return (::user::control_event*) playered->layer(LAYERED_USER_CONTROL_EVENT);
//
//}
//
//
//
////inline ::task_pool* __task_pool(::layered * playered)
////{
////
////   return (::task_pool*) playered->layer(LAYERED_TASK_POOL);
////
////}
//
//
//
