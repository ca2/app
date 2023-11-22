#pragma once


#include "acme/primitive/comparison/equals.h"
//#include "particle_factory.h"
#include "acme/exception/no_memory.h"


#include "_impl_pointer.h"



//inline bool __enum_is_failed(const ::e_status & e)
//{
//
//   return ::failed(e);
//
//}


#include "_impl_atom.h"
#include "_impl_primitive.h"


//inline bool succeeded(const ::property & property)
//{
//
//   return ::succeeded((const ::payload &) property);
//
//}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE>particle::__create(::factory::factory* pfactory)
{

   auto pfactoryitem = pfactory->get_factory_item<BASE_TYPE>();

   if (!pfactoryitem)
   {

      throw ::exception(error_no_factory);

   }

   auto p = pfactoryitem->create_particle();

   if (!p)
   {

      throw ::exception(error_wrong_type);

   }

   p->initialize(this);

   return p;

}


//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>particle::__id_create(const ::atom & atom, ::factory::factory* pfactory)
//{
//
//   auto pfactoryitem = pfactory->get_factory_item(atom);
//
//   if (!pfactoryitem)
//   {
//
//      throw ::exception(error_no_factory);
//
//   }
//
//   auto p = pfactoryitem->create_particle();
//
//   if (!p)
//   {
//
//      throw ::no_memory();
//
//   }
//
//   p->initialize(this);
//
//   return p;
//
//}


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

   auto ptypeNew = pfactoryitem->create_particle();

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

   p = ptypeNew;

   p->initialize(this);

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
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource, const ::scoped_string & scopedstrObjRefDbg)
//{
//
//   return __refer(preference, psource.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const ::primitive::member < SOURCE > & pmember, const ::scoped_string & scopedstrObjRefDbg)
//{
//
//   return __refer(preference, pmember.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE>& preference, const SOURCE * psource, const ::scoped_string & scopedstrObjRefDbg)
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
inline ::pointer < T > pointer_transfer(T* p) { return { e_pointer_transfer, p }; }


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
//inline ::file_pointer matter::get_reader(const ::payload & payloadFile, ::file::e_open eopen)
//{
//
//   return get_file(payloadFile, eopen | ::file::e_open_read) ;
//
//}
//
//
//inline ::file_pointer matter::get_writer(const ::payload & payloadFile, ::file::e_open eopen)
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
//   auto pgroup = system()->task_group(epriority);
//
//   synchronous_lock slGroup(pgroup->synchronization());
//
//   ///   auto ptool = system()->task_tool(op_fork_count);
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
//      auto pelement = ::transfer(pfactory->create_element());
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



//inline e_check::e_check(const ::boolean & triestate)
//{
//
//   if (triestate == e_boolean_undefined)
//   {
//
//      m_echeck = e_check_undefined;
//
//   }
//   else if (triestate == e_boolean_yes)
//   {
//
//      m_echeck = e_check_checked;
//
//   }
//   else if (triestate == e_boolean_no)
//   {
//
//      m_echeck = e_check_unchecked;
//
//   }
//   else
//   {
//
//      m_echeck = e_check_tristate;
//
//   }
//
//}
//

template < typename TYPE >
inline bool particle::__defer_construct(::pointer<TYPE> & p, ::factory::factory * pfactory)
{

   if (::is_set(p))
   {

      return false;

   }

   __construct(p, pfactory);

   return true;

}


template < typename TYPE >
inline bool particle::__defer_construct_new(::pointer<TYPE> & p)
{

   if (::is_set(p))
   {

      return false;

   }

   __construct_new(p);

   return true;

}


constexpr ::e_status e_status::worst(const ::e_status & e) const
{

   return (::e_status)(::enum_status)minimum((::i64)m_eenum, (::i64)e.m_eenum);

}


constexpr ::i64 posix_time::minutes() const { return m_iSecond / 60; }
constexpr ::i64 posix_time::hours() const { return m_iSecond / (60 * 60); }
constexpr ::i64 posix_time::days() const { return m_iSecond / (24 * 60 * 60); }



