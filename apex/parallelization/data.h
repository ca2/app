#pragma once


//class CLASS_DECL_APEX __thread_data
//{
//public:
//
//
//#if defined(_POSIX_THREADS) || defined(LINUX)
//
//   pthread_key_t        m_key;
//
//#else
//
//   ::u32                m_dwIndex;
//
//#endif
//
//
//   __thread_data();
//   ~__thread_data();
//
//
//   void * get();
//   void set(void * p);
//
//
//};
//
//
//template < class T >
//class __thread_pointer :
//   public __thread_data
//{
//public:
//
//
//   static __thread_pointer < __pointer_array(::object) > t_preferencea;
//
//   inline operator T *() { return (T *)get(); }
//   inline T * operator ->() { return operator T *(); }
//   inline __thread_pointer & operator = (const __pointer < T > & p)
//   {
//
//      auto pPrevious = operator T * ();
//
//      if (p != pPrevious)
//      {
//
//         if (t_preferencea.operator pointer_array<object> * () == nullptr)
//         {
//
//            t_preferencea = __new(__pointer_array(::object));
//
//         }
//
//         if (::is_set(p))
//         {
//
//            t_preferencea->erase_first(pPrevious);
//
//         }
//
//         t_preferencea->erase_first(pPrevious);
//
//         set(p);
//
//      }
//
//      return *this;
//
//   }
//
//};
//
//
//template < class T >
//class __thread_iptr :
//   public __thread_data
//{
//public:
//
//   operator T () { return (T)(iptr)get(); }
//   thread_int_ptr & operator = (T t) { set((void *)(iptr)t); return *this; }
//
//   bool operator == (iptr i)
//   {
//      return ((iptr)get()) == i;
//   }
//
//};
//
////template < class T >
////class thread_object :
////   public thread_data
////{
////public:
////
////   inline operator T *() { if (get() == nullptr) { set(new T()); } return (T *)get(); }
////   inline T * operator ->() { return operator T *(); }
////
////};
//
//
//


//extern thread_local tristate t_booleana[e_thread_boolean_count];
//
//
//inline ::tristate& task_boolean(enum_thread_boolean ethreadboolean)
//{
//
//   //return ::get_task()->payload(atom);
//   return t_booleana[ethreadboolean];
//
//}
//
//
//extern thread_local payload t_payloada[e_thread_payload_count];
//
//
//inline ::payload & thread_payload(enum_thread_payload ethreadpayload)
//{
//
//   //return ::get_task()->payload(atom);
//   return t_payloada[ethreadpayload];
//
//}


//inline bool task_flag().is_set(enum_task_flag ethreadboolean)
//{
//
//   return task_flag(ethreadboolean);
//
//}



