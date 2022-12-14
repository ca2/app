#pragma once


#include "acme/primitive/comparison/equals.h"
//#include "particle_factory.h"
#include "acme/exception/no_memory.h"

inline bool __enum_is_failed(const ::e_status & e)
{

   return ::failed(e);

}






//template < >
//inline uptr u32_hash < const type & >(const ::type & type)
//{
//
//   return u32_hash < const ::atom & > (type);
//
//}


//inline stream & operator << (stream & stream, const ::type & type)
//{
//
//   stream << type.m_strName;
//
//   return stream;
//
//}
//
//
//inline stream & operator >> (stream & stream, type & type)
//{
//
//   stream >> type.m_strName;
//
//   return stream;
//
//}


// bool get_memory::get_base64(const ::string & str)


//template < typename PRED >
//inline ::image_pointer matter::get_image(const ::payload & payloadFile, ::u64 uTrait, PRED pred)
//{
//
//   return acmesystem()->get_image(this, payloadFile, uTrait, pred);
//
//}


//#include "acme/primitive/primitive/trait_predicate.h"


//inline property_set ca_property_set()
//{
//
//   return property_set();
//
//}

//template < typename STRINGABLE >
//inline string operator + (const char * psz, const STRINGABLE& stringable)
//{
//
//   string strRight(stringable);
//
//   return as_string(psz) + strRight;
//
//}


/// END property_set

//
//inline ::pointer<::handle::ini>operator ""_pini(const char * psz, size_t s)
//{
//
//   return __new(::handle::ini(string(psz, s)));
//
//}


//inline string CLASS_DECL_ACME operator + (const char * psz, const ::payload & payload)
//{
//
//   return as_string(psz) + payload.get_string();
//
//}
//

//inline class ::payload & payload::operator -= (const class property & property) { operator -=(property);  return *this; }
//inline class ::payload & payload::operator += (const class property & property) { operator +=(property);  return *this; }
//inline class ::payload & payload::operator /= (const class property & property) { operator /=(property);  return *this; }
//inline class ::payload & payload::operator *= (const class property & property) { operator *=(property);  return *this; }



//template < class T >
//template < typename VAR >
//inline pointer < T >  & pointer < T >::operator = (const payload_type < VAR > & payload)
//{
//
//   if (payload.this_var()->m_etype == e_type_element)
//   {
//
//      return operator = (payload.this_var()->m_p);
//
//   }
//   else if (payload.this_var()->m_etype == e_type_memory)
//   {
//
//      auto pfile = create_memory_file();
//
//      ::binary_stream stream(pfile);
//
//      stream << payload.this_var()->memory();
//
//      string strText;
//
//      stream >> strText;
//
//      //if (!stream.fail())
//      {
//
//         if (strText.is_empty() || strText.case_insensitive_begins_eat("factoryless://"))
//         {
//
//            if(is_set() && __type_name(m_p) == strText)
//            {
//
//               ::output_debug_string("POINTER: loading into existing matter of same class type (1)");
//
//            }
//            else
//            {
//
//               this->defer_create_new();
//
//               if(is_null())
//               {
//
//                  ::output_debug_string("POINTER: defer_new failed (1.1)");
//
//                  //stream.set_fail_bit();
//
//                  throw ::exception(error_io);
//
//               }
//               else if(__type_name(m_p) != strText)
//               {
//
//                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (1.2)");
//
//                  //stream.set_fail_bit();
//
//                  throw ::exception(error_io);
//
//               }
//
//            }
//
//         }
//         else
//         {
//
//            ::atom atom = stream.text_to_factory_id(strText);
//
//            if(is_set() && __type_name(m_p) == atom)
//            {
//
//               ::output_debug_string("POINTER: loading into existing matter of same class type (2)");
//
//            }
//            else
//            {
//
//               auto p = stream.create_object_from_text(strText);
//
//               if(!p)
//               {
//
//                  ::output_debug_string("POINTER: stream::alloc_object_from_text failed (2.1)");
//
//               }
//               else if(__type_name(p) != atom)
//               {
//
//                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (2.2)");
//
//                  //stream.set_fail_bit();
//
//                  throw ::exception(error_io);
//
//               }
//               else
//               {
//
//                  operator =(p);
//
//               }
//
//            }
//
//         }
//
//         //if (!stream.fail())
//         {
//
//            m_p->read(stream);
//
//         }
//
//      }
//
//      return *this;
//
//   }
//   else
//   {
//
//      return operator =(nullptr);
//
//   }
//
//}



inline bool succeeded(const ::property & property)
{

   return ::succeeded((const ::payload &) property);

}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE>particle::__create(::factory::factory* pfactory)
{

   auto p = pfactory->__create<BASE_TYPE>();

   p->initialize(this);

   return p;

}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE>particle::__id_create(const ::atom & atom, ::factory::factory* pfactory)
{

   auto p = pfactory->__id_create<BASE_TYPE>(atom);

   p->initialize(this);

   return p;

}


template < typename TYPE >
inline ::pointer<TYPE>particle::__create_new()
{

   //ASSERT(::is_set(this));

   return ::__create_new<TYPE>(this);

   //return p;

}


//template < class T >
//template < typename TEMPLATER >
//inline pointer < T > & pointer < T >::create(TEMPLATER)
//{
//
//   __construct(*this);
//
//   return *this;
//
//}



template < typename BASE_TYPE >
inline void particle::__construct(::pointer<BASE_TYPE>& p, ::factory::factory * pfactory)
{

   auto & pfactoryitem = pfactory->get_factory_item < BASE_TYPE >();

   if (!pfactory)
   {

      throw ::exception(::error_no_factory);

   }

   auto ptypeNew = pfactoryitem->__create();

   p = ptypeNew;

   if (!p)
   {

      throw ::exception(error_wrong_type);

   }

   p->initialize(this);


}


//
//
//template < typename BASE_TYPE >
//inline void matter::__raw_construct(::pointer<BASE_TYPE>& p)
//{
//
//   if (!p)
//   {
//
//      auto & pfactory = factory_item < BASE_TYPE >();
//
//      if (!pfactory)
//      {
//
//         return ::error_no_factory;
//
//      }
//
//      auto ptypeNew = pfactory->call_new();
//
//      if (!ptypeNew)
//      {
//
//         return ::error_no_memory;
//
//      }
//
//      p = ptypeNew;
//
//      if (!p)
//      {
//
//         return error_wrong_type;
//
//      }
//
//      auto estatus = add_composite(p);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//   }
//
//   return ::success;
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__construct(::pointer<BASE_TYPE>& p, const SOURCE * psource)
//{
//
//   p = psource;
//
//   if (!p)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   auto estatus = p->initialize(this);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_estatus = add_composite(p);
//
//   return m_estatus;
//
//}
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__raw_construct(::pointer<BASE_TYPE>& p, const SOURCE * psource)
//{
//
//   p = psource;
//
//   if (!p)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   m_estatus = add_composite(p);
//
//   return m_estatus;
//
//}
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__construct(::pointer<BASE_TYPE>& p, const ::pointer<SOURCE> psource)
//{
//
//   return __construct(p, psource.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__raw_construct(::pointer<BASE_TYPE>& p, const ::pointer<SOURCE> psource)
//{
//
//   return __raw_construct(p, psource.get());
//
//}
//
//
//
//template < typename BASE_TYPE >
//inline void matter::__id_construct(::pointer<BASE_TYPE>& p, const ::atom & atom)
//{
//
//   auto & pfactory = factory_item(atom);
//
//   if (!pfactory)
//   {
//
//      return ::error_no_factory;
//
//   }
//
//   auto ptypeNew = pfactory->call_new();
//
//   if (!ptypeNew)
//   {
//
//      return ::error_no_memory;
//
//   }
//
//   p = ptypeNew;
//
//   if (!p)
//   {
//
//      return ::error_wrong_type;
//
//   }
//
//   auto estatus = p->initialize(this);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = add_composite(p);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}
//
//
//template < typename TYPE >
//inline void matter::__raw_construct_new(::pointer<TYPE>& p)
//{
//
//   auto ptypeNew = __new(TYPE);
//
//   if (!ptypeNew)
//   {
//
//      return ::error_no_memory;
//
//   }
//
//   p = ptypeNew;
//
//   auto estatus = add_composite(p);
//
//   if (!estatus)
//   {
//
//      p.clear_member();
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


template < typename TYPE >
inline void particle::__construct_new(::pointer<TYPE>& p)
{

   auto ptypeNew = __new(TYPE);

   if (!ptypeNew)
   {

      throw ::no_memory();

   }

   ptypeNew->initialize(this);

   p = ptypeNew;


}


//
//template < typename TYPE >
//inline void matter::__construct(::pointer<TYPE>& p)
//{
//
//   auto estatus = ::__construct(p);
//
//   if (estatus && p)
//   {
//
//      estatus = p->initialize(this);
//
//   }
//
//   return estatus;
//
//}
//
//
//template < typename TYPE >
//inline void matter::__id_construct(::pointer<TYPE>& p, const ::atom & atom)
//{
//
//   auto estatus = ::__id_construct(p, atom);
//
//   if (estatus && p)
//   {
//
//      estatus = p->initialize(this);
//
//   }
//
//   return estatus;
//
//}
//
//
//template < typename TYPE >
//inline void matter::__construct_new(::pointer<TYPE>& p)
//{
//
//   auto estatus = ::__construct_new(p);
//
//   if(estatus.succeeded())
//   {
//
//      estatus = p->initialize(this);
//
//   }
//
//   return estatus;
//
//}
//
//
//template < typename BASE_TYPE >
//inline void matter::__release(::pointer<BASE_TYPE>& pcomposite)
//{
//
//   if (pcomposite)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_pcompositea)
//      {
//
//         if (m_pcompositea->erase(pcomposite) >= 0)
//         {
//
//            pcomposite->release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//            pcomposite.clear_member();
//
//         }
//
//      }
//
//   }
//
//   return ::success;
//
//}
//
//
//template < typename BASE_TYPE >
//inline void matter::__release(::pointer<BASE_TYPE>& preference)
//{
//
//   if (preference)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_preferencea)
//      {
//
//         if (m_preferencea->erase(preference.get()) >= 0)
//         {
//
//            preference->release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);
//
//            preference.clear_member();
//
//         }
//         else
//         {
//
//            return ::error_failed;
//
//         }
//
//      }
//
//   }
//
//   return ::success;
//
//}
//
//
//template < typename SOURCE >
//inline void matter::release_reference(::pointer<SOURCE>& psource)
//{
//
//   return release_reference(psource.m_p);
//
//}
//
//
//CLASS_DECL_ACME void object_on_add_composite(const matter * p);
//
//
//template < typename BASE_TYPE >
//inline void matter::add_composite(::pointer<BASE_TYPE>& pcomposite)
//{
//
//   return add_composite(pcomposite.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, psource.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const ::primitive::member < SOURCE > & pmember, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, pmember.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const SOURCE * psource, const char* pszObjRefDbg)
//{
//
//   preference = psource;
//
//   if (!preference)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   return add_reference(preference);
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(::pointer<SOURCE>& psource)
//{
//
//   return add_reference(psource.get());
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(::pointer<SOURCE>& preference)
//{
//
//   return add_reference(preference.get());
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(SOURCE * psource)
//{
//
//   ::pointer<::matter>pparticle;
//
//   pparticle = (SOURCE *) psource;
//
//   if (!pparticle)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   return add_reference((::matter *) pparticle.m_p);
//
//}
//
//
template < typename T >
inline ::pointer < T > move_transfer(T* p) { return { e_move_transfer, p }; }


//template < typename TYPE >
//TYPE & operator |=(TYPE & o,  eobject)
//{
//
//   o.set(eobject);
//
//   return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator +=(TYPE & o,  eobject)
//{
//
//   o.set(eobject);
//
//   return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator -=(TYPE & o,  eobject)
//{
//
//   o.clear(eobject);
//
//   return o;
//
//}


//template < typename T >
//template < typename TEMPLATER >
//inline pointer < T > & pointer<T> ::defer_create(TEMPLATER)
//{
//
//   if (is_null())
//   {
//
//      operator=(__create < TYPE >());
//
//   }
//
//   return *this;
//
//}
//



//template < class T >
//inline stream & operator << (stream & os, const pointer < T > & sp)
//{
//
//   os << *sp.m_p;
//
//   return os;
//
//}
//
//
//template < class T >
//inline stream & operator >> (stream & is, pointer < T > & sp)
//{
//
//   is >> *sp.m_p;
//
//   return is;
//
//}
//

//inline void context::load_from_file(::particle * pparticle, const ::payload& payloadFile, const ::payload* pvarOptions)
//{
//
//   if (pvarOptions)
//   {
//
//      return _load_from_file(pparticle, payloadFile, *pvarOptions);
//
//   }
//   else
//   {
//
//      return _load_from_file(pparticle, payloadFile, e_type_empty_argument);
//
//   }
//
//}
//
//
//inline void context::load_from_file(::particle * pparticle, const ::payload& payloadFile)
//{
//
//   return _load_from_file(pparticle, payloadFile, e_type_empty_argument);
//
//}
//
//
//inline void context::save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::particle * pparticle)
//{
//
//   if (pvarOptions)
//   {
//
//      return _save_to_file(payloadFile, *pvarOptions, pparticle);
//
//   }
//   else
//   {
//
//      return _save_to_file(payloadFile, e_type_empty_argument, pparticle);
//
//   }
//
//}
//
//
//inline void context::save_to_file(const ::payload& payloadFile, const ::particle * pparticle)
//{
//
//   return _save_to_file(payloadFile, e_type_empty_argument, pparticle);
//
//}
//
//

//
//inline ::file_pointer matter::get_reader(const ::payload & payloadFile, const ::file::e_open & eopen)
//{
//
//   return get_file(payloadFile, eopen | ::file::e_open_read) ;
//
//}
//
//
//inline ::file_pointer matter::get_writer(const ::payload & payloadFile, const ::file::e_open & eopen)
//{
//
//   return get_file(payloadFile, eopen | ::file::e_open_write);
//
//}






//
//template < typename TYPE >
//inline void matter::set(const ::atom & atom, const TYPE & t)
//{
//
//   ::assign(value(atom), t);
//
//   set(e_object_property_set_modified);
//
//}
//
//
//template < typename TYPE >
//inline void matter::get(const ::atom & atom, TYPE & t)
//{
//
//   ::assign(t, value(atom));
//
//}
//

//inline string &  payload::as_string ()
//{
//
//   if (m_etype == ::e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_string();
//
//   }
//   else if (m_etype == ::e_type_property)
//   {
//
//      return m_pproperty->as_string();
//
//   }
//   else if (m_etype == ::e_type_pstring)
//   {
//
//      return *m_pstr;
//
//   }
//   else if (m_etype != ::e_type_string)
//   {
//
//      m_str = this->string();
//
//      set_type(e_type_string, false);
//
//   }
//
//   return m_str;
//
//}


//inline payload::operator string() const
//{
//
//    return get_string();
//
//}

#define IMPL_VAR_REF(TYPE, VAR, NAME)        \
   inline TYPE & payload::as_ ## NAME()      \
   {                                         \
                                             \
      if(m_etype == ::e_type_payload_pointer)        \
      {                                      \
                                             \
         return m_ppayload->as_ ## NAME();   \
                                             \
      }                                      \
      else if(m_etype == ::e_type_property)        \
      {                                      \
                                             \
         return m_pproperty->as_ ## NAME();   \
                                             \
      }                                      \
      else if(m_etype == ::e_type_p ## NAME)        \
      {                                      \
                                             \
         return *m_p ## VAR;                 \
                                             \
      }                                      \
      else if(m_etype == ::e_type_ ## NAME)    \
      {                                      \
                                             \
         return m_ ## VAR;                   \
                                             \
      }                                      \
      else                                   \
      {                                      \
                                             \
         set_type(::e_type_ ## NAME, true);   \
                                             \
         return m_ ## VAR;                   \
                                             \
      }                                      \
                                             \
   }

//
////#define IMPL_VAR_REF1(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF(bool, b, bool);
////#undef IMPL_VAR_REF1
////
//
//#define IMPL_VAR_REF2(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, VAR)
//IMPL_VAR_REF2(::i8, i8);
//IMPL_VAR_REF2(::u8, u8);
//IMPL_VAR_REF2(::i16, i16);
//IMPL_VAR_REF2(::u16, u16);
//IMPL_VAR_REF2(::i32, i32);
//IMPL_VAR_REF2(::u32, u32);
//IMPL_VAR_REF2(::i64, i64);
//IMPL_VAR_REF2(::u64, u64);
//#undef IMPL_VAR_REF2


//#define IMPL_VAR_REF3(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF3(::f32, f32);
//IMPL_VAR_REF3(::f64, f64);
//#undef IMPL_VAR_REF3


#undef IMPL_VAR_REF

//
//inline ::memory & payload::as_memory()
//{
//
//   return this->mem();
//
//}
//

//inline payload::memory() const
//{
//
//   return this->memory();
//
//}


//inline void & payload::as_estatus()
//{
//
//   if(m_etype == ::e_type_payload_pointer)
//   {
//
//      return m_ppayload->as_estatus();
//
//   }
//   else if(m_etype == ::e_type_property)
//   {
//
//      return m_pproperty->as_estatus();
//
//   }
//   else if(m_etype == ::e_type_enum_status)
//   {
//
//      return m_estatus;
//
//   }
//   else
//   {
//
//      set_type(::e_type_enum_status, true);
//
//      return m_estatus;
//
//   }
//
//}


//inline bool type::operator == (const ::atom& atom) const
//{
//
//   return ::atom::operator ==(atom);
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const ::payload & payload) :
//   string_base(payload.to_string())
//{
//
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(const property& property) :
//   string_base(property.to_string())
//{
//
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(const atom& atom) :
//   string_base(atom.to_string())
//{
//
//
//}


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(::payload & payload) :
//   string_base(payload.to_string())
//{
//
//
//}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(property & property) :
//   string_base(property.to_string())
//{
//
//
//}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(atom & atom) :
//   string_base(atom.to_string())
//{
//
//
//}




//template < typename PRED >
//void method::pred(PRED pred)
//{
//
//   m_pparticle = method(pred);
//
//}
//

//template < typename PRED >
//inline void future::pred(PRED pred)
//{
//
//   m_pparticle = __new(predicate_future < PRED > (pred));
//
//}
//
//
//

//template < typename TYPE >
//inline ::pointer<TYPE>element::cast(const ::atom & atom)
//{
//
//   return value(atom).cast < TYPE>();
//
//}









//
//template < typename PRED >
//inline ::count fork_count_end(::particle * pparticle, ::count iCount, PRED pred, index iStart, ::enum_priority epriority)
//{
//
//   if (iCount <= 0)
//   {
//
//      return -1;
//
//   }
//
//   auto pgroup = acmesystem()->task_group(epriority);
//
//   synchronous_lock slGroup(pgroup->synchronization());
//
//   ///   auto ptool = acmesystem()->task_tool(op_fork_count);
//
//   if (pgroup == nullptr || pgroup->get_count() <= 1)
//   {
//
//      for (index i = iStart; i < iCount; i++)
//      {
//
//         pred(i);
//
//      }
//
//      return 1;
//
//   }
//
//   if (!pgroup->prepare(::e_thread_op_fork_count, iCount - iStart))
//   {
//
//      return -1;
//
//   }
//
//   synchronization_array ptra;
//
//   ::count iScan = maximum(1, minimum(iCount - iStart, pgroup->thread_count()));
//
//   for (index iOrder = 0; iOrder < iScan; iOrder++)
//   {
//
//      ::pointer<predicate_holder_base>p = __new(forking_count_predicate < PRED > (iOrder, iOrder + iStart, iScan, iCount, pred));
//
//      if (!pgroup->add_predicate(p))
//      {
//
//         return -1;
//
//      }
//
//   }
//
//   if (!(*pgroup)())
//   {
//
//      return -1;
//
//   }
//
//   return iScan;
//
//}
//

//inline void future::operator()(const ::payload & payload) const
//{
//
//   if (!m_pparticle)
//   {
//
//      return;
//
//   }
//
//   return m_pparticle->receive_response(payload);
//
//}
//


//template < typename PRED >
//method::method(PRED pred) : function(__new(predicate_method < PRED >(pred))) { }
//
//
//template < typename PRED >
//future::future(PRED pred) : function(__new(predicate_future < PRED >(pred))) { }




//inline void method::operator()() const
//{ 
//   
//   return ::is_set(m_pparticle) ? m_pparticle->call() : (void) ::success_none;
//
//}



#if OBJECT_REFERENCE_COUNT_DEBUG


template < typename TYPE, typename T >
void object_reference_count_debug_assign(::pointer<TYPE>& ptr, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   auto pold = ptr.m_p;

   ptr.m_p = p;

   p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   object_reference_count_debug_release(pold OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void object_reference_count_debug_release(::pointer<TYPE>& ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   object_reference_count_debug_release(ptr.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void object_reference_count_debug_release(TYPE * & p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   release(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


#endif


//inline bool class ::time::done(const class time & time) const { return elapsed(class ::time).m_i >= 0; }
//inline bool class ::time::done() const { return elapsed().m_i >= 0; }






//template < typename BASE_TYPE >
//inline void object::__construct(::pointer<BASE_TYPE> pcomposite)
//{
//
//   if (!pcomposite)
//   {
//
//      auto& pfactory = factory_item < BASE_TYPE >();
//
//      if (!pfactory)
//      {
//
//         throw ::exception(error_no_factory);
//
//      }
//
//      auto pelement = ::move(pfactory->create_element());
//
//      if (!pelement)
//      {
//
//         throw ::exception(error_no_memory);
//
//      }
//
//      pcomposite = pelement;
//
//      if (!pcomposite)
//      {
//
//         throw ::exception(error_wrong_type);
//
//      }
//
//      /*auto estatus = */ pcomposite->initialize(this);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      /*estatus = */ add_composite(pcomposite);
//
//      //if (!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//   }
//
//   //return ::success;
//
//}
//

//
//template < typename BASE_TYPE, typename SOURCE >
//inline void object::__construct(::pointer<BASE_TYPE> pcomposite, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   pcomposite = psource;
//
//   if (!pcomposite)
//   {
//
//      throw ::exception(error_wrong_type);
//
//   }
//
//   //auto estatus = pcomposite->initialize(this);
//    pcomposite->initialize(this);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//    add_composite(pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//   //return m_estatus;
//
//}
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void object::__raw_construct(::pointer<BASE_TYPE> p, const SOURCE* psource)
//{
//
//   p = psource;
//
//   if (!p)
//   {
//
//      throw ::exception(error_wrong_type);
//
//   }
//
//   /*m_estatus = */ add_composite(p);
//
//   //return m_estatus;
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void object::__construct(::pointer<BASE_TYPE> p, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   /* return */ __construct(p, psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void object::__construct(::pointer<BASE_TYPE> p, const ptr < SOURCE > & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   /* return */ __construct(p, psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void object::__raw_construct(::pointer<BASE_TYPE> p, const ::pointer<SOURCE>psource)
//{
//
//   /*return*/ __raw_construct(p, psource.get());
//
//}
//
//
//template < typename BASE_TYPE >
//inline void object::__id_construct(::pointer<BASE_TYPE> p, const ::atom& atom)
//{
//
//   auto& pfactory = factory_item(atom);
//
//   if (!pfactory)
//   {
//
//      throw ::exception(::error_no_factory);
//
//   }
//
//   auto ptypeNew = pfactory->create_element();
//
//   if (!ptypeNew)
//   {
//
//      throw ::exception(::error_no_memory);
//
//   }
//
//   p = ptypeNew;
//
//   if (!p)
//   {
//
//      throw ::exception(::error_wrong_type);
//
//   }
//
//   /*auto estatus =*/ p->initialize(this);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   /* estatus = */ add_composite(p);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //return estatus;
//
//}
//
//
//template < typename TYPE >
//inline void object::__raw_construct_new(::pointer<TYPE> p)
//{
//
//   auto ptypeNew = __new(TYPE);
//
//   if (!ptypeNew)
//   {
//
//      throw ::exception(::error_no_memory);
//
//   }
//
//   p = ptypeNew;
//
//   /*auto estatus = */ add_composite(p);
//
//   //if (!estatus)
//   //{
//
//   //   p.clear_member();
//
//   //   return estatus;
//
//   //}
//
//   //return estatus;
//
//}
//
//
//template < typename TYPE >
//inline void object::__construct_new(::pointer<TYPE> p)
//{
//
//   auto ptypeNew = __new(TYPE);
//
//   if (!ptypeNew)
//   {
//
//      throw ::exception(::error_no_memory);
//
//   }
//
//   /*auto estatus = */ ptypeNew->initialize(this);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   p = ptypeNew;
//
//   /*estatus = */ add_composite(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(this));
//
//   //if (!estatus)
//   //{
//
//      //p.clear_member();
//
////      return estatus;
//
////   }
//
////   return estatus;
//
//}
//
//


#define IMPL_VAR_REF(TYPE, VAR, ENUM)        \
  inline payload::operator TYPE &()                  \
  {                                         \
                                            \
     if(m_etype == ::type_pvar)        \
     {                                      \
                                            \
        return m_ppayload->operator TYPE &();   \
                                            \
     }                                      \
     else if(m_etype == ::type_prop)        \
     {                                      \
                                            \
        return m_pproperty->operator TYPE &();   \
                                            \
     }                                      \
     else if(m_etype == ::type_p ## ENUM)        \
     {                                      \
                                            \
        return *m_p ## VAR;                 \
                                            \
     }                                      \
     else if(m_etype == ::type_ ## ENUM)    \
     {                                      \
                                            \
        return m_ ## VAR;                   \
                                            \
     }                                      \
     else                                   \
     {                                      \
                                            \
        set_type(::type_ ## ENUM, true);   \
                                            \
        return m_ ## VAR;                   \
                                            \
     }                                      \
                                            \
  }


//template < typename TYPE >
//inline void object::__construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority)
//{
//
//   p = fork(pfn, epriority);
//
//   if (!p)
//   {
//
//      throw ::exception(error_failed);
//
//   }
//
//}


//template < typename TYPE >
//inline void object::__construct_below_normal(::task_pointer& p, void (TYPE::* pfn)())
//{
//
//   return __construct(p, pfn, e_priority_below_normal);
//
//}
//

//template < typename TYPE >
//inline ::task_pointer object::defer_branch(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority)
//{
//
//   auto pfork = fork(pfn, epriority);
//
//   get_property_set()["thread"][atom] = pfork;
//
//   return pfork;
//
//}


//template < typename PRED >
//inline void add_procedure(::procedure_array& routinea, PRED pred)
//{
//
//   routinea.add(__routine(pred));
//
//}



//template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
//bool material_object::__get_posted_payload_synchronously(POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER preturning, OBJECT_METHOD returning_method, ::payload & payload, const class time & timeWait)
//{
//
//   if(pposting->is_branch_current())
//   {
//
//      payload = (preturning->*returning_method)();
//
//      return true;
//
//   }
//
//   auto posting = [pposting, posting_method](const ::procedure & procedure)
//   {
//
//      (pposting->*posting_method)(procedure);
//
//   };
//
//   ::function < void(const ::procedure &) > functionPost(posting);
//
//   ::function < ::payload() > functionReturn([preturning, returning_method]()
//   {
//
//      return (preturning->*returning_method)();
//
//   });
//
//   functionReturn.m_timeTimeout = wait;
//
//   return __get_posted_payload_synchronously(functionPost, functionReturn, payload);
//
//}
//
//
//template < typename POSTING_OBJECT, typename POSTING_METHOD >
//void material_object::__send_procedure(POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::procedure & procedure)
//{
//
//   if(pposting->is_branch_current())
//   {
//
//      return procedure();
//
//   }
//
//   auto posting = [pposting, posting_method](const ::procedure & procedure)
//   {
//
//      (pposting->*posting_method)(procedure);
//
//   };
//
//   __send_procedure(posting, procedure);
//
//}
//






//template < class T >
//inline pointer < T > & __move(pointer < T > & p, lparam & lparam)
//{
//
//   pointer < T > pelement(lparam);
//
//   if (::is_null(pelement))
//   {
//
//      ::release(pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(nullptr, "pointer::pointer(LPARAM)"));
//
//   }
//
//   return pelement;
//
//}


//template < class T >
//template < typename PARTICLE >
//inline pointer < T > ::pointer(enum_create, PARTICLE * p) :
//   m_p(nullptr),
//   m_pparticle(nullptr)
//{
//
//   operator=(p->__create < T >());
//
//}



inline e_check::e_check(const ::tristate & triestate)
{

   if (triestate == e_boolean_undefined)
   {

      m_echeck = e_check_undefined;

   }
   else if (triestate == e_boolean_yes)
   {

      m_echeck = e_check_checked;

   }
   else if (triestate == e_boolean_no)
   {

      m_echeck = e_check_unchecked;

   }
   else
   {

      m_echeck = e_check_tristate;

   }

}


template < typename TYPE >
inline void particle::__defer_construct(::pointer<TYPE> & p, ::factory::factory * pfactory)
{

   if (::is_null(p))
   {

      __construct(p, pfactory);

   }

}


template < typename TYPE >
inline void particle::__defer_construct_new(::pointer<TYPE> & p)
{

   if (::is_null(p))
   {

      __construct_new(p);

   }

}


