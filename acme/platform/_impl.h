#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)

namespace std { enum class align_val_t : std::size_t {}; }

#endif




//inline fork_block::fork_block(const memory_base & memory) :
//   fork_block(memory.get_data(), memory.get_size())
//{
//
//}


#ifndef __cplusplus_winrt


template < typename BLOCK_TYPE >
inline BLOCK_TYPE & memory_template < BLOCK_TYPE > ::operator = (const ::block & block)
{

   if (block.get_size() < get_size())
   {

      throw ::exception(error_bad_argument);

   }

   ::memcpy_dup(get_data(), block.get_data(), (size_t) get_size());

   return *get_data();

}


#endif // __cplusplus_winrt


//struct lparam_debug :
//   virtual matter
//{
//
//};
//
//CLASS_DECL_ACME lparam_debug & lparam_debug();
//

template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
{

   ENSURE((nCount == 0) || (pElements != nullptr));
   ASSERT((nCount == 0) ||
          __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), false));
#ifdef WINDOWS
   &dumpcontext; // not used
   pElements;  // not used
   nCount; // not used
#endif
   // default does nothing

}


template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
{

   ENSURE((nCount == 0) || ((pDest != 0) && (pSrc != 0)));
   ASSERT((nCount == 0) || __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
   ASSERT((nCount == 0) || __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));

   // default is matter-copy using assignment
   while (nCount--)
   {

      *pDest++ = *pSrc++;

   }

}




//namespace acme
//{
//
//
//   template < class APP >
//   ::pointer<::acme::application>single_application_library < APP > ::get_new_application(::matter * pobject, const char * pszAppId)
//   {
//
//      if(!contains_app(pszAppId))
//      {
//
//         return error_not_found;
//
//      }
//
//      auto pappNew = __new(APP);
//
//      if(pappNew == nullptr)
//      {
//
//         return error_no_memory;
//
//      }
//
//      ::pointer<::acme::application>papp;
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
//      auto estatus = papp->initialize(pobject);
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
//      if (m_strFileExt.has_char())
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


inline bool IsDirSep(widechar ch)
{

   return (ch == '\\' || ch == '/');

}


//#define memory_new ACME_NEW


template < typename T >
const char * memory_counter_id(T * pthis)
{

   return typeid(*pthis).name();

}


template < typename T >
void memory_counter_increment(T * pthis)
{

   if (memory_counter_on())
   {

      auto psz = memory_counter_id(pthis);

      _memory_counter_increment(psz);

      //synchronous_lock synchronouslock(g_pmutexMemoryCounters);

      //int i = atoi(m_psystem->m_pacmefile->as_string(path));

      //m_psystem->m_pacmefile->put_contents(path, __string(i + 1));
   }

}


template < typename T >
void memory_counter_decrement(T * pthis)
{

   if (memory_counter_on())
   {

      auto psz = memory_counter_id(pthis);

      _memory_counter_decrement(psz);

      //int i = atoi(m_psystem->m_pacmefile->as_string(path));

      //m_psystem->m_pacmefile->put_contents(path, __string(i - 1));

   }

}


namespace acme
{


   template < typename T >
   inline void delobj(T * & p)
   {

      try
      {

         if (::is_set(p))
         {

            T * pdel = p;

            p = nullptr;

            delete pdel;

         }

      }
      catch (...)
      {

      }

   }


} // namespace acme


//inline stream & operator >> (stream & s, ::earth::time & time);


template < typename BASE >
inline ::pointer<BASE>alloc_object(::matter * pobject)
{

   return BASE::g_pallocfactory->alloc_object(pobject);

}


template < typename BASE >
inline ::pointer<BASE>& alloc_object(::pointer<BASE> p, ::matter * pobject)
{

   return p = ::alloc_object < BASE > (pobject);

}

//
//inline class ::synchronization_object * matter::get_mutex()
//{
//
//   return ::is_null(this) ? nullptr : mutex();
//
//}


template < typename TDST, typename TSRC >
inline ::pointer<TDST>& clone(::pointer<TDST> dst, const ::pointer<TSRC>src)
{

   if (src.is_null())
   {

      dst.release();

      return dst;

   }

   return dst = ::move_transfer(src->clone());

}


//template < typename T >
//inline pointer < T > clone(const pointer < T > & t)
//{
//
//   if (t.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return t->clone();
//
//}




template < typename T >
template < typename T2 >
inline pointer < T > & pointer < T >::clone(T2 * p)
{

   if (::is_null(p))
   {

      release();

      return *this;

   }

   return operator = (p->clone());

}


//#ifndef __DEBUG
//
//#include "acme/primitive/primitive/block.inl"
//
//#endif // !__DEBUG

//
//#ifndef __cplusplus_winrt
//
//
//// namespace str
//// {
//
//
//
////inline ::string __string(const bool & b)
////{
////
////   if(b)
////   {
////
////      str = "{[(true)]}";
////
////   }
////   else
////   {
////
////      str = "{[(false)]}";
////
////   }
////
////}
//
//
//// } // namespace str
//
//
//#endif // __cplusplus_winrt
//


namespace papaya
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value()
      {

         throw ::interface_only("template only exception");

      }


   } // namespace chill


} // namespace papaya


//inline float i32muldiv(float f, i32 iNum, i32 iDen)
//{
//
//   return (float) (f * iNum / iDen);
//
//}
//
//
//inline double i32muldiv(double d, i32 iNum, i32 iDen)
//{
//
//   return (double) (d * iNum / iDen);
//
//}
//
//
//inline i32 i32muldiv(i32 i, i32 iNum, i32 iDen)
//{
//
//   return (i32) ::MulDiv(i, iNum, iDen);
//
//}
//

#ifndef WINDOWS


inline i64 MulDiv(i64 nNumber, i32 iNum, i32 iDen)
{

   return nNumber * iNum / iDen;

}

#endif


#ifndef __cplusplus_winrt


template < primitive_integral MULTIPLICATOR, primitive_integral NUMERATOR, primitive_integral DENOMINATOR, primitive_integral RESULT >
inline RESULT muldiv(MULTIPLICATOR iMultiplicator, NUMERATOR iNumerator, DENOMINATOR iDenominator)
{

   return iMultiplicator * iNumerator / iDenominator;

}


inline string __string(const ::e_display & edisplay) { return __string((::enum_display) edisplay); }


//template < typename TYPE >
//::stream & read_container_as_parent(::stream & stream, pointer_array < TYPE > & a)
//{
//
//   ::count c = 0;
//
//   stream >> c;
//
// /*  if (stream.fail())
//   {
//
//      return stream;
//
//   }*/
//
//   while (c > 0)
//   {
//
//      auto p = __new(TYPE(&a));
//
//      stream >> *p;
//
//      //if (stream.fail())
//      //{
//
//      //   break;
//
//      //}
//
//      a.add(p);
//
//      c--;
//
//   }
//
//   return stream;
//
//}
//
//
//template < typename TYPE >
//::stream & write_container_as_parent(::stream & stream, const pointer_array < TYPE > & a)
//{
//
//   ::count c = a.get_count();
//
//   stream << c;
//
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   for (auto & item : a)
//   {
//
//      stream >> item;
//
//      c--;
//
//   }
//
//   return stream;
//
//}
//

#endif // __cplusplus_winrt


template < class c_derived >
inline i64 increment_reference_count(c_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_null(pca))
   {

      return -1;

   }

   return pca->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


template < class c_derived, typename SOURCE >
inline i64 increment_reference_count(c_derived * & pca, const SOURCE * psource)
{

   c_derived * pderived = dynamic_cast <c_derived *>((SOURCE *)psource);

   if (::is_null(pderived))
   {

      throw ::exception(error_wrong_type);

   }

   pca = pderived;

   return increment_reference_count(pca);

}


template < class c_derived, typename SOURCE >
inline i64 increment_reference_count(c_derived *& pderived, const ::pointer<SOURCE>& psource)
{

   return increment_reference_count(pderived, psource.m_p);

}


template < class c_derived >
inline i64 release(c_derived *& pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   c_derived * ptr = pca;

   if (::is_null(ptr))
   {

      return -1;

   }

#ifdef _DEBUG

//   ::atom atom = p->m_atom;
   //char * pszType = nullptr;
   //
   //try
   //{

   //   pszType = _strdup(typeid(*p).name());

   //}
   //catch (...)
   //{

   //   ::output_debug_string("exception release strdup(typeid(*p).name())\n");

   //}

#endif

   try
   {

      pca = nullptr;

   }
   catch (...)
   {

      //::output_debug_string("exception release pca = nullptr; (" + string(atom) + ")\n");
      ::output_debug_string("exception release pca = nullptr; \n");

   }

   try
   {

      return ptr->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }
   catch (...)
   {

      ::output_debug_string("exception release p->release() \n");

   }

   return -1;

}


//template < class COMPOSITE >
//inline i64 release(::pointer<COMPOSITE>& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   return release(pcomposite.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


template < typename TYPE >
inline i64 release(::pointer<TYPE>& pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
inline i64 __finalize(::pointer<TYPE> pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   if (!pointer) return -1;
   
   pointer->destroy();
   
   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}

//
//template < class REFERENCE >
//inline i64 release(::pointer<REFERENCE>& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   return release(preference.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


template < class c_derived >
inline i64 ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}


//#ifndef __cplusplus_winrt







