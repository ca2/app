// Working on it on 2023-11-27 03:34 <3ThomasBorregaardSorensen!!
#pragma once

/*
#if !defined(WINDOWS) \
 && !defined(LINUX) \
 && !defined(__APPLE__) \
 && !defined(__ANDROID__) \
 && !defined(FREEBSD) \
 && !defined(OPENBSD)

namespace std { enum class align_val_t : std::size_t {}; }

#endif
*/



//inline fork_block::fork_block(const memory_base & memory) :
//   fork_block(memory.get_data(), memory.get_size())
//{
//
//}


#ifndef __cplusplus_winrt




#endif // __cplusplus_winrt


//struct lparam_debug :
//   virtual matter
//{
//
//};
//
//CLASS_DECL_ACME lparam_debug & lparam_debug();
//

//template<class TYPE>
//inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::collection::count nCount)
//{
//
//   ENSURE((nCount == 0) || (pElements != nullptr));
//   ASSERT((nCount == 0) ||
//          is_memory_segment_ok(pElements, (size_t)nCount * sizeof(TYPE), false));
//#ifdef WINDOWS
//   &dumpcontext; // not used
//   pElements;  // not used
//   nCount; // not used
//#endif
//   // default does nothing
//
//}




//namespace acme
//{
//
//
//   template < class APP >
//   ::pointer<::platform::application>single_application_library < APP > ::get_new_application(::particle * pparticle, const ::scoped_string & scopedstrAppId)
//   {
//
//      if(!contains_app(scopedstrAppId))
//      {
//
//         return error_not_found;
//
//      }
//
//      auto pappNew = __allocate APP();
//
//      if(pappNew == nullptr)
//      {
//
//         return error_no_memory;
//
//      }
//
//      ::pointer<::platform::application>papp;
//
//      papp = pappNew;
//
//      if (!papp)
//      {
//
//         return error_wrong_type;
//
//      }
//
//      auto estatus = papp->initialize(pparticle);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return papp;
//
//   }
//
//
//   template < class APP >
//   void single_application_library < APP > ::get_extension_list(string_array & stra)
//   {
//
//      if (m_strFileExt.has_character())
//      {
//
//         stra.add(m_strFileExt);
//
//      }
//
//   }
//
//
//} // namespace acme







template < typename T >
const_char_pointer memory_counter_id(T * pthis)
{

   return typeid(*pthis).name();

}


//template < typename T >
//void memory_counter_increment(T * pthis)
//{
//
//   if (memory_counter_on())
//   {
//
//      auto psz = memory_counter_id(pthis);
//
//      _memory_counter_increment(scopedstr);
//
//      //synchronous_lock synchronouslock(g_pmutexMemoryCounters);
//
//      //int i = atoi(file_system()->as_string(path));
//
//      //file_system()->put_contents(path, as_string(i + 1));
//   }
//
//}
//
//
//template < typename T >
//void memory_counter_decrement(T * pthis)
//{
//
//   if (memory_counter_on())
//   {
//
//      auto psz = memory_counter_id(pthis);
//
//      _memory_counter_decrement(scopedstr);
//
//      //int i = atoi(file_system()->as_string(path));
//
//      //file_system()->put_contents(path, as_string(i - 1));
//
//   }
//
//}

//
//namespace acme
//{
//
//
//   template < typename T >
//   inline void delobj(T * & p)
//   {
//
//      try
//      {
//
//         if (::is_set(p))
//         {
//
//            T * pdel = p;
//
//            p = nullptr;
//
//            delete pdel;
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//} // namespace acme
//
//
////inline stream & operator >> (stream & s, ::earth::time & time);
//
//
//template < typename BASE >
//inline ::pointer<BASE>alloc_object(::particle * pparticle)
//{
//
//   return BASE::g_pallocfactory->alloc_object(pparticle);
//
//}
//
//
//template < typename BASE >
//inline ::pointer<BASE>& alloc_object(::pointer<BASE> p, ::particle * pparticle)
//{
//
//   return p = ::alloc_object < BASE > (pparticle);
//
//}
//
////
////inline class ::synchronization * matter::get_mutex()
////{
////
////   return ::is_null(this) ? nullptr : mutex();
////
////}
//
//
//template < typename TDST, typename TSRC >
//inline ::pointer<TDST>& clone(::pointer<TDST> dst, const ::pointer<TSRC>src)
//{
//
//   if (src.is_null())
//   {
//
//      dst.release();
//
//      return dst;
//
//   }
//
//   return dst = ::pointer_transfer(src->clone());
//
//}
//
//
////template < typename T >
////inline pointer < T > clone(const pointer < T > & t)
////{
////
////   if (t.is_null())
////   {
////
////      return nullptr;
////
////   }
////
////   return t->clone();
////
////}
//
//
//
//
//template < typename T >
//template < typename T2 >
//inline pointer < T > & pointer < T >::clone(T2 * p)
//{
//
//   if (::is_null(p))
//   {
//
//      release();
//
//      return *this;
//
//   }
//
//   return operator = (p->clone());
//
//}
//
//
////#ifndef _DEBUG
////
////#include "acme/prototype/prototype/block.inl"
////
////#endif // !__DEBUG
//
////
////#ifndef __cplusplus_winrt
////
////
////// namespace str
////// {
////
////
////
//////inline ::string as_string(const bool & b)
//////{
//////
//////   if(b)
//////   {
//////
//////      str = "{[(true)]}";
//////
//////   }
//////   else
//////   {
//////
//////      str = "{[(false)]}";
//////
//////   }
//////
//////}
////
////
////// } // namespace str
////
////
////#endif // __cplusplus_winrt
////
//
//
//namespace acme
//{
//
//
//   namespace chill
//   {
//
//
//      template < typename TYPE >
//      inline TYPE default_payload()
//      {
//
//         throw ::interface_only("template only exception");
//
//      }
//
//
//   } // namespace chill
//
//
//} // namespace acme
//
//
////inline float i32muldiv(float f, int iNum, int iDen)
////{
////
////   return (float) (f * iNum / iDen);
////
////}
////
////
////inline double i32muldiv(double d, int iNum, int iDen)
////{
////
////   return (double) (d * iNum / iDen);
////
////}
////
////
////inline int i32muldiv(int i, int iNum, int iDen)
////{
////
////   return (int) ::MulDiv(i, iNum, iDen);
////
////}
////
//
//#ifndef WINDOWS
//
//
//inline long long MulDiv(long long nNumber, int iNum, int iDen)
//{
//
//   return nNumber * iNum / iDen;
//
//}
//
//#endif
//
//
//#ifndef __cplusplus_winrt
//
//
//template < primitive_integral MULTIPLICATOR, primitive_integral NUMERATOR, primitive_integral DENOMINATOR, primitive_integral RESULT >
//inline RESULT muldiv(MULTIPLICATOR iMultiplicator, NUMERATOR iNumerator, DENOMINATOR iDenominator)
//{
//
//   return iMultiplicator * iNumerator / iDenominator;
//
//}
//
//
//
//
////template < typename TYPE >
////::stream & read_container_as_parent(::stream & stream, pointer_array < TYPE > & a)
////{
////
////   ::collection::count c = 0;
////
////   stream >> c;
////
//// /*  if (stream.fail())
////   {
////
////      return stream;
////
////   }*/
////
////   while (c > 0)
////   {
////
////      auto p = __allocate TYPE(&a);
////
////      stream >> *p;
////
////      //if (stream.fail())
////      //{
////
////      //   break;
////
////      //}
////
////      a.add(p);
////
////      c--;
////
////   }
////
////   return stream;
////
////}
////
////
////template < typename TYPE >
////::stream & write_container_as_parent(::stream & stream, const pointer_array < TYPE > & a)
////{
////
////   ::collection::count c = a.get_count();
////
////   stream << c;
////
////   //if (stream.fail())
////   //{
////
////   //   return stream;
////
////   //}
////
////   for (auto & item : a)
////   {
////
////      stream >> item;
////
////      c--;
////
////   }
////
////   return stream;
////
////}
////
//
//#endif // __cplusplus_winrt
//
//
//
//
////#ifndef __cplusplus_winrt
//
//
//
//
//
//


#include "allocator.h"


//template < typename T, typename ...Args >
//inline T * __call__allocate(Args &&... args)
//{
//
//   auto p = ::platform::allocator::__callnew T (::std::forward < Args >(args)...);
//
//   return p;
//
//}

//
//template < typename T >
//inline void __call__delete(T * p)
//{
//
//   ::platform::allocator::__call__delete < T >(p);
//
//}

//
//template < typename T >
//inline T * __allocate_array(::collection::count c)
//{
//
//   auto p = ::platform::allocator::new  T[c];
//
//   return p;
//
//}


//template < typename T >
//inline void __delete(T * p)
//{
//
//   ::platform::allocator::__delete < T >(p);
//
//}

//template < typename T >
//inline void __delete(T* p, void * pAllocation)
//{
//
//   ::platform::allocator::__delete < T >(p, pAllocation);
//
//}

