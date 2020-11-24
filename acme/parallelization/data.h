#pragma once


//class CLASS_DECL_ACME ＿＿thread_data
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
//   ＿＿thread_data();
//   ~＿＿thread_data();
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
//class ＿＿thread_pointer :
//   public ＿＿thread_data
//{
//public:
//
//
//   static ＿＿thread_pointer < ＿＿pointer_array(::matter) > t_preferencea;
//
//   inline operator T *() { return (T *)get(); }
//   inline T * operator ->() { return operator T *(); }
//   inline ＿＿thread_pointer & operator = (const ＿＿pointer < T > & p)
//   {
//
//      auto pPrevious = operator T * ();
//
//      if (p != pPrevious)
//      {
//
//         if (t_preferencea.operator pointer_array<matter> * () == nullptr)
//         {
//
//            t_preferencea = ＿＿new(＿＿pointer_array(::matter));
//
//         }
//
//         if (::is_set(p))
//         {
//
//            t_preferencea->remove_first(pPrevious);
//
//         }
//
//         t_preferencea->remove_first(pPrevious);
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
//class ＿＿thread_iptr :
//   public ＿＿thread_data
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

//inline payload & thread_value(const ::id & id) { return ::get_task()->value(id); }
//
//inline bool thread_is_set(const ::id & id)
//{
//   if (!::get_task())
//   {
//
//      return false;
//
//   }
//
//   if (is_null(::get_task()->m_pset))
//   {
//
//      return false;
//
//   }
//
//   if (!::get_task()->has_property(id))
//   {
//
//      return false;
//
//   }
//
//   return ::get_task()->value(id);
//
//}



