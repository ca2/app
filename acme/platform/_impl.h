#pragma once


#if !defined(WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)

namespace std { enum class align_val_t : std::size_t {}; }

#endif


#ifndef __cplusplus_winrt


inline block::block(const memory_base & memory) :
   block(memory.get_data(), memory.get_size())
{

}


inline block::block(const memory_base * pmemory) :
   block(pmemory->get_data(), pmemory->get_size())
{

}


#endif // __cplusplus_winrt


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

      __throw(error_bad_argument);

   }

   ::memcpy_dup(get_data(), block.get_data(), (size_t) get_size());

   return *get_data();

}


#endif // __cplusplus_winrt


struct lparam_debug :
   virtual matter
{

};

CLASS_DECL_ACME lparam_debug & lparam_debug();


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
//   __pointer(::acme::application) single_application_library < APP > ::get_new_application(::matter * pobject, const char * pszAppId)
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
//      __pointer(::acme::application) papp;
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


#define new ACME_NEW


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


inline stream & operator >> (stream & s, ::datetime::time & time);


template < typename BASE >
inline __pointer(BASE) alloc_object(::matter * pobject)
{

   return BASE::g_pallocfactory->alloc_object(pobject);

}


template < typename BASE >
inline __pointer(BASE) & alloc_object(__pointer(BASE) & p, ::matter * pobject)
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
inline __pointer(TDST) & clone(__pointer(TDST) & dst, const __pointer(TSRC) & src)
{

   if (src.is_null())
   {

      dst.release();

      return dst;

   }

   return dst = src->clone();

}


template < typename T >
inline __pointer(T) clone(const __pointer(T) & t)
{

   if (t.is_null())
   {

      return nullptr;

   }

   return t->clone();

}




template < typename T >
template < typename T2 >
inline __pointer(T) & ___pointer < T >::clone(T2 * p)
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


#ifndef __cplusplus_winrt


// namespace str
// {



inline void to_string(string & str, const bool & b)
{

   if(b)
   {

      str = "{[(true)]}";

   }
   else
   {

      str = "{[(false)]}";

   }

}


// } // namespace str


#endif // __cplusplus_winrt


inline void copy(void *, const void *) /* = 0 */ { throw_exception(error_interface_only); }


namespace papaya
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value()
      {

         throw interface_only_exception("template only exception");

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


template < typename TYPE >
::stream & read_container_as_parent(::stream & stream, __pointer_array(TYPE) & a)
{

   ::count c = 0;

   stream >> c;

 /*  if (stream.fail())
   {

      return stream;

   }*/

   while (c > 0)
   {

      auto p = __new(TYPE(&a));

      stream >> *p;

      //if (stream.fail())
      //{

      //   break;

      //}

      a.add(p);

      c--;

   }

   return stream;

}


template < typename TYPE >
::stream & write_container_as_parent(::stream & stream, const __pointer_array(TYPE) & a)
{

   ::count c = a.get_count();

   stream << c;

   //if (stream.fail())
   //{

   //   return stream;

   //}

   for (auto & item : a)
   {

      stream >> item;

      c--;

   }

   return stream;

}


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

      __throw(error_wrong_type);

   }

   pca = pderived;

   return increment_reference_count(pca);

}


template < class c_derived, typename SOURCE >
inline i64 increment_reference_count(c_derived *& pderived, const __pointer(SOURCE) & psource)
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

//   ::atom atom = p->m_id;
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


template < class COMPOSITE >
inline i64 release(__composite(COMPOSITE) & pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return release(pcomposite.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
inline i64 release(__pointer(TYPE) & pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
inline i64 __finalize(__pointer(TYPE)& pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   if (!pointer) return -1;
   
   pointer->destroy();
   
   return release(pointer.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < class REFERENCE >
inline i64 release(__reference(REFERENCE) & preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return release(preference.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < class c_derived >
inline i64 ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}


#ifndef __cplusplus_winrt


template < typename TYPE >
sequence < TYPE > ::sequence()
{

   //m_ptask = ::get_task();

   m_pevent = nullptr;

}


//template < typename TYPE >
//void future < RESULT > ::set_object(const RESULT& result, const ::e_status & estatus)
//{
//
//   critical_section_lock lock(get_sequence_critical_section());
//
//   if (m_p.m_estatus == error_not_initialized)
//   {
//
//      m_p.m_estatus = estatus;
//
//      m_p.m_result = result;
//
//      if (m_pevent)
//      {
//
//         m_pevent->SetEvent();
//
//      }
//
//      if (m_preceptor)
//      {
//
//         m_preceptor->get(this);
//
//      }
//
//   }
//
//}


template < typename TYPE >
void sequence < TYPE > ::fork()
{

   m_psystem->fork(__routine([this]()
   {

      on_sequence();

   }));

}


template < typename TYPE >
void sequence < TYPE > ::on_sequence()
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_pevent)
   {

      m_pevent->SetEvent();

   }
   
   while(m_stepa.has_element())
   {

      auto pfunction = m_stepa.pop_first();

      lock.unlock();

      pfunction->process(*this);

      lock.lock();

   }

}


//template < typename TYPE >
//void sequence < TYPE > ::set_status(const ::e_status & estatus)
//{
//
//   critical_section_lock lock(get_sequence_critical_section());
//
//   m_p.m_estatus = estatus;
//
//   if (m_pevent)
//   {
//
//      m_pevent->SetEvent();
//
//   }
//
//   increment_reference_count();
//
//   m_psystem->fork(__routine([this]()
//      {
//
//         auto pHold = ::move_transfer(this);
//
//         critical_section_lock lock(get_sequence_critical_section());
//
//         while (m_stepa.has_element())
//         {
//
//            auto pfunction = m_stepa.pop_first();
//
//            lock.unlock();
//
//            pfunction->process(*this);
//
//            lock.lock();
//
//         }
//
//      }));
//
//}

template < typename TYPE >
TYPE & sequence < TYPE > ::topic(const ::duration& duration)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_p.m_estatus == error_not_initialized)
   {

      m_pevent = new manual_reset_event();

      if (!m_pevent->wait(duration))
      {

         lock.lock();

         if (m_p.m_estatus == error_not_initialized)
         {

            m_p.m_estatus = error_timeout;

         }

         lock.unlock();

      }

   }

   return m_p;

}


template < typename TYPE >
bool sequence < TYPE > ::wait(const ::duration& duration)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_p.m_estatus == error_not_initialized)
   {

      m_pevent = __new(manual_reset_event);

      lock.unlock();

      if (!m_pevent->wait(duration))
      {

         lock.lock();

         if (m_p.m_estatus == error_not_initialized)
         {

            m_p.m_estatus = error_timeout;

         }

         lock.unlock();

      }

   }

   return m_p.m_estatus;

}


template < typename TYPE >
template < typename OPERATION >
sequence < TYPE > & sequence < TYPE > ::then(OPERATION operation)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_p)
   {

      m_stepa.add(__new(step_operation < OPERATION >(operation)));

   }
   else
   {

      lock.unlock();

      operation(*this);

   }
   
   return *this;

}


template < typename TYPE >
template < typename OPERATION >
sequence < TYPE > & sequence < TYPE > ::then(const ::duration& duration, OPERATION operation)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_p.m_estatus == error_not_initialized)
   {

      m_stepa.add(__new(step_operation < OPERATION >(operation)));

      m_pevent = new manual_reset_event();

      lock.unlock();

      if (!m_pevent->wait(duration))
      {

         lock.lock();

         if (m_p.m_estatus == error_not_initialized)
         {

            m_p.m_estatus = error_timeout;

         }

         lock.unlock();

         if (m_p.m_estatus == error_timeout)
         {

            operation(*this);

         }

      }

   }
   else
   {

      lock.unlock();

      operation(*this);

   }

   return *this;

}



//template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
//SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
//{
//
//   if (!m_pfuture)
//   {
//
//      m_psystem->__construct_new(m_pfuture);
//       
//      m_pfuture->m_psystem = m_psystem;
//
//      m_pfuture->m_p = this;
//
//   }
//
//   return m_pfuture;
//
//}




//template < typename TYPE >
//inline __pointer(TYPE) property_object::__create_new()
//{
//
//   auto p = __new(TYPE);
//
//   p->initialize_matter(this);
//
//   return p;
//
//}


#endif // __cplusplus_winrt


inline tracer trace_log_information() { return ::get_task()->trace_log_information(); }
inline tracer trace_log_warning() { return ::get_task()->trace_log_warning(); }
inline tracer trace_log_error() { return ::get_task()->trace_log_error(); }
inline tracer trace_log_fatal() { return ::get_task()->trace_log_fatal(); }



