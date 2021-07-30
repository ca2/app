#pragma once


#include "acme/primitive/comparison/equals.h"


inline bool __enum_is_failed(const ::e_status & e)
{

   return ::failed(e);

}


inline duration & duration::operator = (const ::datetime::time_span & span)
{

   raw_set(span.GetTotalSeconds());

   return *this;

}


inline duration & duration::operator += (const ::datetime::time_span & span)
{

   set(m_secs.m_i + span.GetTotalSeconds(), m_nanos.m_i);

   return *this;

}


inline duration & duration::operator -= (const ::datetime::time_span & span)
{

   set(m_secs.m_i - span.GetTotalSeconds(), m_nanos.m_i);

   return *this;

}


template < class T >
inline string ___pointer < T >::type_str()
{

   return __type_str(T);

}


//namespace promise
//{


   inline ::e_status routine::operator()() const { return (*m_p)(); }


   inline bool routine::should_run_async() const { return m_p->should_run_async(); }



   //inline void process::operator()(const ::payload & payload) const { if (m_p) (*m_p)(payload); }


   //inline bool process::should_run_async() const { return m_p->should_run_async(); }


//} // namespace promise


inline type::type(const ::matter * pobject)
{

   m_strName = typeid(*(matter *)pobject).name();

   demangle(m_strName);

}


template < typename BASE >
inline type::type(const __pointer(BASE) & point)
{

   m_strName = typeid(*((BASE *)point.m_p)).name();

   demangle(m_strName);

}


template < >
inline uptr uptr_hash < const type & >(const ::type & type)
{

   return uptr_hash < const string & > (type.m_strName);

}


inline stream & operator << (stream & stream, const ::type & type)
{

   stream << type.m_strName;

   return stream;

}


inline stream & operator >> (stream & stream, type & type)
{

   stream >> type.m_strName;

   return stream;

}


inline bool get_memory::get_base64(const string & str)
{

   if (::is_set(m_pmemory))
   {

      m_pmemory->from_base64(str);

      return true;

   }
   else
   {

      ::str::base64 base64;

      return base64.decode(m_block, str);

   }

}


//template < typename PRED >
//inline ::image_result matter::get_image(const ::payload & varFile, ::u64 uTrait, PRED pred)
//{
//
//   return get_system()->get_image(this, varFile, uTrait, pred);
//
//}


#include "acme/primitive/primitive/trait_predicate.h"


//inline ::payload matter::topic(const ::id & id)
//{
//
//   auto pproperty = fetch_property(id);
//
//   if (!pproperty)
//   {
//
//      __throw(error_resource);
//
//   }
//
//   return pproperty;
//
//}


inline ::index property_set::find_index(const ::id & id, ::index i) const
{

   for(; i < m_nSize; i++)
   {

      if (m_pData[i]->m_id == id)
      {

         return i;

      }

   }

   return -1;

}

#undef new

inline property & property_set::get(const ::id & id)
{

   auto pproperty = find(id);

   if (!pproperty)
   {

      pproperty = new property(id);

      add_item(pproperty);

   }

   return *pproperty;

}

#define new ACME_NEW

inline ::property * property_set::find(const ::id & id) const
{

   auto iFind = find_index(id);

   if(__not_found(iFind))
   {

      return nullptr;

   }

   return (const_cast < property_set * > (this))->m_pData[iFind];

}


inline ::payload property_set::operator()(const ::id & id, const ::payload & varDefault) const
{

   auto pproperty = find(id);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}


inline ::payload property_set::topic(const id & id)
{

   return &set(id);

}


#undef new


inline ::payload & property_set::set(const ::id & id)
{

   auto pproperty = find(id);

   if (!pproperty)
   {

      pproperty = new property(id);

      add_item(pproperty);

   }

   return *pproperty;

}


#define new ACME_NEW

//inline property * payload::find_property(const ::id & id) const
//{
//
//   if (!casts_to(e_type_property_set))
//   {
//
//      return nullptr;
//
//   }
//
//   return propset().find(id);
//
//}


//inline property & payload::get_property(const ::id & id)
//{
//
//   return propset().get(id);
//
//}


inline string  id::operator +(const char * psz) const
{

   return to_string() + psz;

}


inline string  id::operator +(const string & str) const
{

   return to_string() +str;

}


inline CLASS_DECL_ACME id id::operator + (const id & id) const
{

   if (is_integer())
   {

      if (id.is_integer())
      {

         return (iptr)(m_i + id.m_i);

      }
      else if (id.is_text())
      {

         return __str(m_i) + "." + string(id.m_psz);

      }
      else
      {

         return *this;

      }

   }
   else if (id.is_integer())
   {

      if (is_text())
      {

         return string(m_psz) + "." + __str(id.m_i);

      }
      else
      {

         return id;

      }

   }
   else if (is_text())
   {

      if (id.is_text())
      {

         return string(m_psz) + string(id.m_psz);

      }
      else
      {

         return *this;

      }

   }
   else if (id.is_text())
   {

      return id;

   }
   else
   {

      return ::id();

   }

}


inline bool property_set::has_property(id idName) const
{

   if (::is_null(this))
   {

      return false;

   }

   const property * pproperty = find(idName);

   return pproperty != nullptr && pproperty->m_etype != ::e_type_new;

}


inline bool property_set::is_true(id idName, bool bDefault) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return bDefault;

   }

   return pproperty->is_true(bDefault);

}


inline ::payload property_set::value(id idName) const
{

   property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return ::error_not_found;

   }

   return *pproperty;

}


inline ::payload property_set::value(id idName, ::payload varDefault) const
{

   property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return varDefault;

   }

   return *pproperty;

}


inline ::payload payload::first() const
{

   return at(0);

}


inline ::payload payload::last() const
{

   if (array_get_count() == 0)
   {

      return first();

   }
   else
   {

      return at(array_get_upper_bound());

   }

}


inline ::payload payload::first()
{

   return at(0);

}


inline ::payload payload::last()
{

   if (array_get_count() == 0)
   {

      return first();

   }
   else
   {

      return at(array_get_upper_bound());

   }

}


inline property_set ca_property_set()
{

   return property_set();

}


inline string CLASS_DECL_ACME operator + (const char * psz, const ::id & id)
{

   return __str(psz) + id.to_string();

}


/// END property_set


inline __pointer(::handle::ini) operator ""_pini(const char * psz, size_t s)
{

   return __new(::handle::ini(string(psz, s)));

}


inline string CLASS_DECL_ACME operator + (const char * psz, const ::payload & payload)
{

   return __str(psz) + payload.get_string();

}


//inline class ::payload & payload::operator -= (const class property & property) { operator -=(property);  return *this; }
//inline class ::payload & payload::operator += (const class property & property) { operator +=(property);  return *this; }
//inline class ::payload & payload::operator /= (const class property & property) { operator /=(property);  return *this; }
//inline class ::payload & payload::operator *= (const class property & property) { operator *=(property);  return *this; }


inline ::property * payload::find_property(const ::id & id) const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->find_property(id);

   }
   else if (m_etype == e_type_prop)
   {

      return m_pprop->find_property(id);

   }
   else if (m_etype == e_type_property_set)
   {

      return m_pset->find_property(id);

   }

   return nullptr;

}


inline ::index payload::property_index(const ::id & id) const
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->property_index(id);

   }
   else if (m_etype == e_type_prop)
   {

      return m_pprop->property_index(id);

   }
   else if (m_etype == e_type_property_set)
   {

      return m_pset->find_index(id);

   }

   return -1;

}


inline property & payload::get_property(const ::id & id)
{

   if (m_etype == e_type_payload_pointer)
   {

      return m_ppayload->get_property(id);

   }
   else if (m_etype == e_type_prop)
   {

      return m_pprop->get_property(id);

   }
   else if (m_etype == e_type_property_set)
   {

      return m_pset->get(id);

   }

   return propset().get(id);

}


inline bool id::begins(const string & strPrefix) const
{

   if (strPrefix.is_empty())
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_integer())
   {

      char sz[64];

      ansi_from_i64(sz, m_i);

      return ::str::begins(sz, strPrefix);

   }
   else if (is_text())
   {

      return ::str::begins(m_psz, strPrefix);

   }
   else
   {

      __throw(::exception::exception("Unexpected ::id m_etype"));

   }

}


inline bool id::begins_ci(const string & strPrefix) const
{

   if (strPrefix.is_empty())
   {

      return true;

   }

   if (is_empty())
   {

      return false;

   }
   else if (is_integer())
   {

      char sz[64];

      ansi_from_i64(sz, m_i);

      return ::str::begins(sz, strPrefix);

   }
   else if (is_text())
   {

      return ::str::begins_ci(m_psz, strPrefix);

   }
   else
   {

      __throw(::exception::exception("Unexpected ::id m_etype"));

   }

}


template < class T >
template < typename VAR >
inline ___pointer < T >  & ___pointer < T >::operator = (const payload_type < VAR > & payload)
{

   if (payload.this_var()->m_etype == e_type_element)
   {

      return operator = (payload.this_var()->m_p);

   }
   else if (payload.this_var()->m_etype == e_type_memory)
   {

      auto pfile = create_memory_file();

      ::binary_stream stream(pfile);

      stream << payload.this_var()->memory();

      string strText;

      stream >> strText;

      if (!stream.fail())
      {

         if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
         {

            if(is_set() && m_p->type_name() == strText)
            {

               ::output_debug_string("POINTER: loading into existing matter of same class type (1)");

            }
            else
            {

               this->defer_create_new();

               if(is_null())
               {

                  ::output_debug_string("POINTER: defer_new failed (1.1)");

                  stream.set_fail_bit();

               }
               else if(m_p->type_name() != strText)
               {

                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (1.2)");

                  stream.set_fail_bit();

               }

            }

         }
         else
         {

            ::id id = stream.text_to_factory_id(strText);

            if(is_set() && m_p->type_name() == id)
            {

               ::output_debug_string("POINTER: loading into existing matter of same class type (2)");

            }
            else
            {

               auto p = stream.create_object_from_text(strText);

               if(!p)
               {

                  ::output_debug_string("POINTER: stream::alloc_object_from_text failed (2.1)");

               }
               else if(::str::demangle(p->type_name()) != id.to_string())
               {

                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (2.2)");

                  stream.set_fail_bit();

               }
               else
               {

                  operator =(p);

               }

            }

         }

         if (!stream.fail())
         {

            m_p->read(stream);

         }

      }

      return *this;

   }
   else
   {

      return operator =(nullptr);

   }

}


inline bool succeeded(const ::payload & payload)
{

   if (payload.m_etype == e_type_enum_status)
   {

      return ::succeeded(payload.m_estatus);

   }
   else if (payload.is_integer())
   {

      return ::succeeded(payload.i64());

   }
   else
   {

      __throw(error_unexpected_situation);

   }

}


inline bool succeeded(const ::property & property)
{

   return ::succeeded((const ::payload &) property);

}




//
//template < typename BASE_TYPE >
//inline __transport(BASE_TYPE) matter::__create()
//{
//
//   auto p = ::__create<BASE_TYPE>();
//
//   if (p)
//   {
//
//      auto estatus = p->initialize(this);
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
//   return p;
//
//}
//
//
//template < typename BASE_TYPE >
//inline __transport(BASE_TYPE) matter::__id_create(const ::id & id)
//{
//
//   auto p = ::__id_create<BASE_TYPE>(id);
//
//   if (p)
//   {
//
//      auto estatus = p->initialize(this);
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
//   return p;
//
//}
//
//
//template < typename TYPE >
//inline __transport(TYPE) matter::__create_new()
//{
//
//   ASSERT(::is_set(this));
//
//   auto p = ::__create_new<TYPE>();
//
//   if (p)
//   {
//
//      p->initialize(this);
//
//   }
//
//   return p;
//
//}
//
//
template < class T >
template < typename TEMPLATER >
inline __pointer(T) & ___pointer < T >::create(TEMPLATER)
{

   __construct(*this);

   return *this;

}


template < class T >
template < typename TYPE, typename OBJECT >
inline __pointer(T) & ___pointer < T >::create(OBJECT * pobject)
{

  auto p = __create < TYPE >();

  if (p)
  {

     p->initialize(pobject);

  }

  return operator =(p);

}


template < class T >
template < typename TYPE, typename OBJECT >
inline __pointer(T) & ___pointer < T >::create(OBJECT * pobject, bool bCreate)
{

  if (bCreate)
  {

     defer_create(pobject);

  }
  else
  {

     release();

  }

  return *this;

}


//template < typename BASE_TYPE >
//inline ::e_status matter::__compose(__composite(BASE_TYPE) & pusermessage)
//{
//
//   if (!pusermessage)
//   {
//
//      auto & pfactory = ::factory::get_factory < BASE_TYPE >();
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
//      pusermessage = ptypeNew;
//
//      if (!pusermessage)
//      {
//
//         return error_wrong_type;
//
//      }
//
//      auto estatus = pusermessage->initialize(this);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = add_composite(pusermessage);
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
//template < typename BASE_TYPE >
//inline ::e_status matter::__raw_compose(__composite(BASE_TYPE) & pusermessage)
//{
//
//   if (!pusermessage)
//   {
//
//      auto & pfactory = ::factory::get_factory < BASE_TYPE >();
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
//      pusermessage = ptypeNew;
//
//      if (!pusermessage)
//      {
//
//         return error_wrong_type;
//
//      }
//
//      auto estatus = add_composite(pusermessage);
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
//inline ::e_status matter::__compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource)
//{
//
//   pusermessage = psource;
//
//   if (!pusermessage)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   auto estatus = pusermessage->initialize(this);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_estatus = add_composite(pusermessage);
//
//   return m_estatus;
//
//}
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__raw_compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource)
//{
//
//   pusermessage = psource;
//
//   if (!pusermessage)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   m_estatus = add_composite(pusermessage);
//
//   return m_estatus;
//
//}
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource)
//{
//
//   return __compose(pusermessage, psource.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__raw_compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource)
//{
//
//   return __raw_compose(pusermessage, psource.get());
//
//}
//
//
//
//template < typename BASE_TYPE >
//inline ::e_status matter::__id_compose(__composite(BASE_TYPE) & pusermessage, const ::id & id)
//{
//
//   auto & pfactory = ::factory::get_factory(id);
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
//   pusermessage = ptypeNew;
//
//   if (!pusermessage)
//   {
//
//      return ::error_wrong_type;
//
//   }
//
//   auto estatus = pusermessage->initialize(this);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   estatus = add_composite(pusermessage);
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
//inline ::e_status matter::__raw_compose_new(__composite(TYPE) & p)
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
//
//
//template < typename TYPE >
//inline ::e_status matter::__compose_new(__composite(TYPE) & p)
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
//   auto estatus = ptypeNew->initialize(this);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   p = ptypeNew;
//
//   estatus = add_composite(p);
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
//
//
//template < typename TYPE >
//inline ::e_status matter::__construct(__pointer(TYPE) & p)
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
//inline ::e_status matter::__id_construct(__pointer(TYPE) & p, const ::id & id)
//{
//
//   auto estatus = ::__id_construct(p, id);
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
//inline ::e_status matter::__construct_new(__pointer(TYPE) & p)
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
//inline ::e_status matter::__release(__composite(BASE_TYPE) & pcomposite)
//{
//
//   if (pcomposite)
//   {
//
//      synchronous_lock synchronouslock(mutex());
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
//inline ::e_status matter::__release(__reference(BASE_TYPE) & preference)
//{
//
//   if (preference)
//   {
//
//      synchronous_lock synchronouslock(mutex());
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
//inline ::e_status matter::release_reference(__pointer(SOURCE) & psource)
//{
//
//   return release_reference(psource.m_p);
//
//}
//
//
//CLASS_DECL_ACME void object_on_add_composite(const matter * pusermessage);
//
//
//template < typename BASE_TYPE >
//inline ::e_status matter::add_composite(__composite(BASE_TYPE) & pcomposite)
//{
//
//   return add_composite(pcomposite.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__refer(__reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, psource.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__refer(__reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & pmember, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, pmember.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline ::e_status matter::__refer(__reference(BASE_TYPE) & preference, const SOURCE * psource, const char* pszObjRefDbg)
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
//inline ::e_status matter::add_reference(__pointer(SOURCE) & psource)
//{
//
//   return add_reference(psource.get());
//
//}
//
//
//template < typename SOURCE >
//inline ::e_status matter::add_reference(__reference(SOURCE) & preference)
//{
//
//   return add_reference(preference.get());
//
//}
//
//
//template < typename SOURCE >
//inline ::e_status matter::add_reference(SOURCE * psource)
//{
//
//   __pointer(::matter) pobject;
//
//   pobject = (SOURCE *) psource;
//
//   if (!pobject)
//   {
//
//      return error_wrong_type;
//
//   }
//
//   return add_reference((::matter *) pobject.m_p);
//
//}
//
//
template < typename T >
inline __pointer(T) move_transfer(T * p) { return ::___pointer < T >(e_move_transfer, p); }


template < typename TYPE >
TYPE & operator |=(TYPE & o, enum_object eobject)
{

   o.set(eobject);

   return o;

}


template < typename TYPE >
TYPE & operator +=(TYPE & o, enum_object eobject)
{

   o.set(eobject);

   return o;

}


template < typename TYPE >
TYPE & operator -=(TYPE & o, enum_object eobject)
{

   o.clear(eobject);

   return o;

}


template < typename T >
template < typename TEMPLATER >
inline __pointer(T) & ___pointer<T> ::defer_create(TEMPLATER)
{

   if (is_null())
   {

      operator=(__create < TYPE >());

   }

   return *this;

}


template < typename T >
template < typename TYPE, typename OBJECT  >
inline __pointer(T) & ___pointer<T> ::defer_create(OBJECT * pobject)
{

   if (is_null())
   {

      operator=(__create < TYPE >(pobject));

   }

   return *this;

}


template < class T >
inline stream & operator << (stream & os, const ___pointer < T > & sp)
{

   os << *sp.m_p;

   return os;

}


template < class T >
inline stream & operator >> (stream & is, ___pointer < T > & sp)
{

   is >> *sp.m_p;

   return is;

}


//inline ::e_status context::load_from_file(::matter* pobject, const ::payload& varFile, const ::payload* pvarOptions)
//{
//
//   if (pvarOptions)
//   {
//
//      return _load_from_file(pobject, varFile, *pvarOptions);
//
//   }
//   else
//   {
//
//      return _load_from_file(pobject, varFile, e_type_empty_argument);
//
//   }
//
//}
//
//
//inline ::e_status context::load_from_file(::matter* pobject, const ::payload& varFile)
//{
//
//   return _load_from_file(pobject, varFile, e_type_empty_argument);
//
//}
//
//
//inline ::e_status context::save_to_file(const ::payload& varFile, const ::payload* pvarOptions, const ::matter * pobject)
//{
//
//   if (pvarOptions)
//   {
//
//      return _save_to_file(varFile, *pvarOptions, pobject);
//
//   }
//   else
//   {
//
//      return _save_to_file(varFile, e_type_empty_argument, pobject);
//
//   }
//
//}
//
//
//inline ::e_status context::save_to_file(const ::payload& varFile, const ::matter* pobject)
//{
//
//   return _save_to_file(varFile, e_type_empty_argument, pobject);
//
//}
//
//

//
//inline ::file_result matter::get_reader(const ::payload & varFile, const ::file::e_open & eopen)
//{
//
//   return get_file(varFile, eopen | ::file::e_open_read) ;
//
//}
//
//
//inline ::file_result matter::get_writer(const ::payload & varFile, const ::file::e_open & eopen)
//{
//
//   return get_file(varFile, eopen | ::file::e_open_write);
//
//}


#ifndef DEBUG


inline i64 matter::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return m_countReference++;

}


inline i64 matter::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return --m_countReference;

}


inline i64 matter::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}

#endif




//
//template < typename TYPE >
//inline void matter::set(const ::id & id, const TYPE & t)
//{
//
//   ::assign(value(id), t);
//
//   set(e_object_property_set_modified);
//
//}
//
//
//template < typename TYPE >
//inline void matter::get(const ::id & id, TYPE & t)
//{
//
//   ::assign(t, value(id));
//
//}
//

inline payload::operator string & ()
{

   if (m_etype == ::e_type_payload_pointer)
   {

      return m_ppayload->operator string & ();

   }
   else if (m_etype == ::e_type_prop)
   {

      return m_pprop->operator string & ();

   }
   else if (m_etype == ::e_type_pstring)
   {

      return *m_pstr;

   }
   else if (m_etype != ::e_type_string)
   {

      m_str = get_string();

      set_type(e_type_string, false);

   }

   return m_str;

}


//inline payload::operator string() const
//{
//
//    return get_string();
//
//}

#define IMPL_VAR_REF(TYPE, VAR, ENUM)        \
   inline payload::operator TYPE &()                  \
   {                                         \
                                             \
      if(m_etype == ::e_type_payload_pointer)        \
      {                                      \
                                             \
         return m_ppayload->operator TYPE &();   \
                                             \
      }                                      \
      else if(m_etype == ::e_type_prop)        \
      {                                      \
                                             \
         return m_pprop->operator TYPE &();   \
                                             \
      }                                      \
      else if(m_etype == ::e_type_p ## ENUM)        \
      {                                      \
                                             \
         return *m_p ## VAR;                 \
                                             \
      }                                      \
      else if(m_etype == ::e_type_ ## ENUM)    \
      {                                      \
                                             \
         return m_ ## VAR;                   \
                                             \
      }                                      \
      else                                   \
      {                                      \
                                             \
         set_type(::e_type_ ## ENUM, true);   \
                                             \
         return m_ ## VAR;                   \
                                             \
      }                                      \
                                             \
   }


#define IMPL_VAR_REF1(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
IMPL_VAR_REF1(bool, b);
#undef IMPL_VAR_REF1


#define IMPL_VAR_REF2(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, VAR)
IMPL_VAR_REF2(::i8, i8);
IMPL_VAR_REF2(::u8, u8);
IMPL_VAR_REF2(::i16, i16);
IMPL_VAR_REF2(::u16, u16);
IMPL_VAR_REF2(::i32, i32);
IMPL_VAR_REF2(::u32, u32);
IMPL_VAR_REF2(::i64, i64);
IMPL_VAR_REF2(::u64, u64);
#undef IMPL_VAR_REF2


#define IMPL_VAR_REF3(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
IMPL_VAR_REF3(float, f);
IMPL_VAR_REF3(double, d);
#undef IMPL_VAR_REF3


#undef IMPL_VAR_REF


inline payload::operator ::memory & ()
{

   return this->memory();

}


inline payload::operator ::memory() const
{

   return this->memory();

}





inline payload::operator ::e_status &()
{

   if(m_etype == ::e_type_payload_pointer)
   {

      return m_ppayload->operator ::e_status &();

   }
   else if(m_etype == ::e_type_prop)
   {

      return m_pprop->operator ::e_status &();

   }
   else if(m_etype == ::e_type_enum_status)
   {

      return m_estatus;

   }
   else
   {

      set_type(::e_type_enum_status, true);

      return m_estatus;

   }

}



inline bool type::operator == (const ::id& id) const
{

   return m_strName == id.to_string();

}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const ::payload & payload) :
//   string_base(payload.to_string())
//{
//
//
//}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const property& property) :
//   string_base(property.to_string())
//{
//
//
//}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const id& id) :
//   string_base(id.to_string())
//{
//
//
//}

//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(::payload & payload) :
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
//inline string_base < TYPE_CHAR >::string_base(id & id) :
//   string_base(id.to_string())
//{
//
//
//}



   template < class T >
   inline __pointer(T) payload::cast(T * pDefault)
   {

      if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
      {

         return m_ppayload->cast < T >(pDefault);

      }
      else if (m_etype == e_type_prop && m_pprop != nullptr)
      {

         return m_pprop->cast < T >(pDefault);

      }

      auto p = cast < T >();

      if (!p)
      {

         return pDefault;

      }

      return p;

   }





      template < class T >
   inline T & payload::get_cast(T * pDefault)
   {

      if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
      {

         return m_ppayload->get_cast < T >(pDefault);

      }

      if (m_etype == e_type_prop && m_pprop != nullptr)
      {

         return m_pprop->get_cast <T>(pDefault);

      }

      if (m_etype != e_type_element)
      {

         return defer_create_type < T >(pDefault);

      }

      auto p = cast < T >();

      if (!p)
      {

         return defer_create_type < T >(pDefault);

      }

      return *p;

   }


   template < class T >
   inline __pointer(T) payload::cast()
   {

      if (m_etype == e_type_payload_pointer && m_ppayload != nullptr)
      {

         return m_ppayload->cast < T >();

      }

      if (m_etype == e_type_prop && m_pprop != nullptr)
      {

         return m_pprop->cast < T >();

      }

#define CAST_ELEMENT(P, ENUM_TYPE) \
      if(m_etype == ENUM_TYPE) { return dynamic_cast < T * >(P); }
      CAST_ELEMENT(m_p, e_type_element);
      CAST_ELEMENT(m_pstra, e_type_string_array);
      CAST_ELEMENT(m_pia, e_type_i32_array);
      CAST_ELEMENT(m_pvara, e_type_payload_array);
      CAST_ELEMENT(m_pset, e_type_property_set);
      CAST_ELEMENT(m_pi64a, e_type_i64_array);
      CAST_ELEMENT(m_pmemory, e_type_memory);
      CAST_ELEMENT(m_ppath, e_type_path);
      //CAST_ELEMENT(m_pimage, type_image);
      return nullptr;
#undef CAST_ELEMENT

   }



//template < typename PRED >
//void method::pred(PRED pred)
//{
//
//   m_pmatter = method(pred);
//
//}
//

//template < typename PRED >
//inline void future::pred(PRED pred)
//{
//
//   m_pmatter = __new(predicate_future < PRED > (pred));
//
//}
//
//
//

//template < typename TYPE >
//inline __pointer(TYPE) matter::cast(const ::id & id)
//{
//
//   return value(id).cast < TYPE>();
//
//}








template < typename T >
inline __pointer(T) payload::pointer() const
{

   auto pproperty = find_pointer < T >();

   if(!pproperty)
   {

      return nullptr;

   }

   return pproperty->template cast < T > ();

}


inline ::payload __visible(::payload varOptions, bool bVisible)
{

   varOptions["visible"] = bVisible;

   return varOptions;

}


//
//template < typename PRED >
//inline ::count fork_count_end(::matter* pobject, ::count iCount, PRED pred, index iStart, ::e_priority epriority)
//{
//
//   if (iCount <= 0)
//   {
//
//      return -1;
//
//   }
//
//   auto pgroup = get_system()->task_group(epriority);
//
//   synchronous_lock slGroup(pgroup->mutex());
//
//   ///   auto ptool = get_system()->task_tool(op_fork_count);
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
//      __pointer(predicate_holder_base) pusermessage = __new(forking_count_predicate < PRED > (iOrder, iOrder + iStart, iScan, iCount, pred));
//
//      if (!pgroup->add_predicate(pusermessage))
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
//   if (!m_pmatter)
//   {
//
//      return;
//
//   }
//
//   return m_pmatter->receive_response(payload);
//
//}
//


//template < typename PRED >
//method::method(PRED pred) : function(__new(predicate_method < PRED >(pred))) { }
//
//
//template < typename PRED >
//future::future(PRED pred) : function(__new(predicate_future < PRED >(pred))) { }




inline bool property_set::get_string(string& strResult, const id& idKey) const
{

   auto pproperty = find_property(idKey);

   if (::is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->get_string();

   return true;

}




//inline ::e_status method::operator()() const
//{ 
//   
//   return ::is_set(m_pmatter) ? m_pmatter->call() : (::e_status) ::success_none; 
//
//}


inline ::payload operator + (::payload payload, const ::routine & routine)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload.get_string();

   }

   payload["routine"] = routine;

   return payload;

}



//inline ::payload operator + (::payload payload, const ::future & process)
//{
//
//   if (payload.get_type() != e_type_property_set)
//   {
//
//      payload["message"] = payload.get_string();
//
//   }
//
//   payload["process"] = process;
//
//   return payload;
//
//}



#if OBJECT_REFERENCE_COUNT_DEBUG


template < typename TYPE, typename T >
void ___assign(__pointer(TYPE) & ptr, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   auto pold = ptr.m_p;

   ptr.m_p = p;

   p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   ___release(pold OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void ___release(__pointer(TYPE) & ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   ___release(ptr.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void ___release(TYPE * & p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   release(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


#endif


inline bool millis::done(const ::millis & millis) const { return elapsed(millis) >= 0; }
inline bool millis::done() const { return elapsed() >= 0; }





template < >
inline uptr uptr_hash < block >(block b)
{

   if (::is_null(b.get_data()) || b.is_empty())
   {

      return 0;

   }

   auto psz = (const char *)b.get_data();

   u32 uHash = 0;

   strsize i = 1;

   for (; i < b.get_size(); i++)
   {

      if (i % 4 == 3)
      {

         uHash = (uHash << 5) + ((u32 *)psz)[i >> 2];

      }

   }

   psz += i;

   i %= 4;

   if (i > 0)
   {

      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);

   }

   return uHash;

}


inline ::application* object::get_application() const 
{ 
   
   return m_pcontext && m_pcontext->m_papexapplication ? m_pcontext->m_papexapplication : (m_psystem ? m_psystem->m_papplicationMain.get() : nullptr);

}


inline ::apex::session * object::get_session() const
{ 
   
   return m_pcontext ? m_pcontext->m_papexsession : nullptr; 

}







//inline ::task_pointer object::opt_fork(const ::routine& routine)
//{
//
//   auto ptask = ::get_task();
//
//   synchronous_lock synchronouslock(ptask->mutex());
//
//   if (ptask && ptask->m_bIsPredicate)
//   {
//
//      routine();
//
//      return ptask;
//
//   }
//
//   return launch(routine);
//
//}
//
//
//



template < typename BASE_TYPE >
inline __transport(BASE_TYPE) object::__create()
{

   auto p = ::__create<BASE_TYPE>();

   if (p)
   {

      auto estatus = p->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

   }

   return p;

}


template < typename BASE_TYPE >
inline __transport(BASE_TYPE) object::__id_create(const ::id& id)
{

   auto p = ::__id_create<BASE_TYPE>(id);

   if (p)
   {

      auto estatus = p->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

   }

   return p;

}


template < typename TYPE >
inline __transport(TYPE) object::__create_new()
{

   ASSERT(::is_set(this));

   auto p = ::__create_new<TYPE>();

   if (p)
   {

      auto estatus = p->initialize(this);
      
      if(!estatus)
      {
         
         return estatus;
         
      }

   }

   return p;

}


template < typename BASE_TYPE >
inline ::e_status object::__compose(__composite(BASE_TYPE)& pcomposite)
{

   if (!pcomposite)
   {

      auto& pfactory = ::factory::get_factory < BASE_TYPE >();

      if (!pfactory)
      {

         return ::error_no_factory;

      }

      auto ptypeNew = pfactory->call_new();

      if (!ptypeNew)
      {

         return ::error_no_memory;

      }

      pcomposite = ptypeNew;

      if (!pcomposite)
      {

         return error_wrong_type;

      }

      auto estatus = pcomposite->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      estatus = add_composite(pcomposite);

      if (!estatus)
      {

         return estatus;

      }

   }

   return ::success;

}


template < typename BASE_TYPE >
inline ::e_status object::__raw_compose(__composite(BASE_TYPE)& pusermessage)
{

   if (!pusermessage)
   {

      auto& pfactory = ::factory::get_factory < BASE_TYPE >();

      if (!pfactory)
      {

         return ::error_no_factory;

      }

      auto ptypeNew = pfactory->call_new();

      if (!ptypeNew)
      {

         return ::error_no_memory;

      }

      pusermessage = ptypeNew;

      if (!pusermessage)
      {

         return error_wrong_type;

      }

      auto estatus = add_composite(pusermessage);

      if (!estatus)
      {

         return estatus;

      }

   }

   return ::success;

}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__compose(__composite(BASE_TYPE)& pcomposite, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   pcomposite = psource;

   if (!pcomposite)
   {

      return error_wrong_type;

   }

   auto estatus = pcomposite->initialize(this);

   if (!estatus)
   {

      return estatus;

   }

   m_estatus = add_composite(pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   return m_estatus;

}

template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource)
{

   pusermessage = psource;

   if (!pusermessage)
   {

      return error_wrong_type;

   }

   m_estatus = add_composite(pusermessage);

   return m_estatus;

}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return __compose(pusermessage, psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource)
{

   return __raw_compose(pusermessage, psource.get());

}


template < typename BASE_TYPE >
inline ::e_status object::__id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id)
{

   auto& pfactory = ::factory::get_factory(id);

   if (!pfactory)
   {

      return ::error_no_factory;

   }

   auto ptypeNew = pfactory->call_new();

   if (!ptypeNew)
   {

      return ::error_no_memory;

   }

   pusermessage = ptypeNew;

   if (!pusermessage)
   {

      return ::error_wrong_type;

   }

   auto estatus = pusermessage->initialize(this);

   if (!estatus)
   {

      return estatus;

   }

   estatus = add_composite(pusermessage);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__raw_compose_new(__composite(TYPE)& p)
{

   auto ptypeNew = __new(TYPE);

   if (!ptypeNew)
   {

      return ::error_no_memory;

   }

   p = ptypeNew;

   auto estatus = add_composite(p);

   if (!estatus)
   {

      p.clear_member();

      return estatus;

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__compose_new(__composite(TYPE)& p)
{

   auto ptypeNew = __new(TYPE);

   if (!ptypeNew)
   {

      return ::error_no_memory;

   }

   auto estatus = ptypeNew->initialize(this);

   if (!estatus)
   {

      return estatus;

   }

   p = ptypeNew;

   estatus = add_composite(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(this));

   if (!estatus)
   {

      p.clear_member();

      return estatus;

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__defer_construct(__pointer(TYPE)& p)
{

   ::e_status estatus = ::success_none;

   if(::is_null(p))
   {

      estatus = __construct(p);

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__defer_construct_new(__pointer(TYPE)& p)
{

   ::e_status estatus = ::success_none;

   if(::is_null(p))
   {

      estatus = __construct_new(p);

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__construct(__pointer(TYPE)& p)
{

   auto estatus = ::__construct(p);

   if (estatus && p)
   {

      estatus = p->initialize(this);

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__id_construct(__pointer(TYPE)& p, const ::id& id)
{

   auto estatus = ::__id_construct(p, id);

   if (estatus && p)
   {

      estatus = p->initialize(this);

   }

   return estatus;

}


template < typename TYPE >
inline ::e_status object::__construct_new(__pointer(TYPE)& p)
{

   auto estatus = ::__construct_new(p);

   if(estatus.succeeded())
   {

      estatus = p->initialize(this);

   }

   return estatus;

}


template < typename BASE_TYPE >
inline ::e_status object::__release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (pcomposite)
   {

      //synchronous_lock synchronouslock(mutex());

      //if (m_pcompositea)
      //{

      //   if (m_pcompositea->erase(pcomposite.get()) >= 0)
      //   {

            pcomposite.clear_member();

      //   }

      //}

   }

   return ::success;

}


template < typename BASE_TYPE >
inline ::e_status object::__release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (preference)
   {

      //synchronous_lock synchronouslock(mutex());

      //if (m_preferencea)
      //{

      //   if (m_preferencea->erase(preference.get()) >= 0)
      //   {

            //preference->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

            preference.clear_member();

   //      }
   //      else
   //      {

   //         return ::error_failed;

   //      }

   //   }

   }

   return ::success;

}


template < typename SOURCE >
inline ::e_status object::__release(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return release_reference(psource.m_p);

}


CLASS_DECL_ACME void object_on_add_composite(const matter* pusermessage);


//template < typename BASE_TYPE >
//inline ::e_status object::add_composite(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
//{
//
//   return add_composite(pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);
//
//}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return __refer(preference, psource.get()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& pmember OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return __refer(preference, pmember.get()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::e_status object::__refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   preference = psource;

   if (!preference)
   {

      return error_wrong_type;

   }

   return add_reference(preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::e_status object::add_reference(__pointer(SOURCE)& psource  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return add_reference(psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::e_status object::add_reference(__reference(SOURCE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return add_reference(preference.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::e_status object::add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   ::matter* pmatter = psource;

   if (::is_null(pmatter))
   {

      return error_wrong_type;

   }

   //return add_reference(pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   return ::success;

}


//template < typename T >
//inline __pointer(T) move_transfer(T * p) { return ::pointer < T >(e_move_transfer, p); }


//inline const char* object::topic_text() { return ::is_null(m_pmeta) ? nullptr : m_pmeta->m_strTopicText; }


//inline ::payload object::context_value(const ::payload& payload)
//{
//
//   ::payload varContextValue;
//
//   varContextValue["context"] = get_context();
//
//   varContextValue["value"] = payload;
//
//   return varContextValue;
//
//}


//inline void object::defer_set_object(::object * pobject)
//{
//
//  if (::is_null(this) && ::is_set(pobject))
//  {
//
//     set_object(pobject);
//
//  }
//
//}


//#include "_property_set_composite_impl.h"


//template < typename TYPE >
//TYPE & operator |=(TYPE & o, enum_object eobject)
//{
//
//  o.set(eobject);
//
//  return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator +=(TYPE & o, enum_object eobject)
//{
//
//  o.set(eobject);
//
//  return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator -=(TYPE & o, enum_object eobject)
//{
//
//  o.clear(eobject);
//
//  return o;
//
//}


//template < typename T >
//template < typename TEMPLATER >
//inline __pointer(T) & pointer<T> ::defer_create(TEMPLATER)
//{
//
//  if (is_null())
//  {
//
//     operator=(__create < TYPE >());
//
//  }
//
//  return *this;
//
//}
//
//
//template < typename T >
//template < typename TYPE, typename OBJECT  >
//inline __pointer(T) & pointer<T> ::defer_create(OBJECT * pobject)
//{
//
//  if (is_null())
//  {
//
//     operator=(__create < TYPE >(pobject));
//
//  }
//
//  return *this;
//
//}
//
//
//template < class T >
//inline stream & operator << (stream & os, const pointer < T > & sp)
//{
//
//  os << *sp.m_p;
//
//  return os;
//
//}
//
//
//template < class T >
//inline stream & operator >> (stream & is, pointer < T > & sp)
//{
//
//  is >> *sp.m_p;
//
//  return is;
//
//}
//

//inline ::e_status context::load_from_file(::matter* pobject, const ::payload& varFile, const ::payload* pvarOptions)
//{
//
//   if (pvarOptions)
//   {
//
//      return _load_from_file(pobject, varFile, *pvarOptions);
//
//   }
//   else
//   {
//
//      return _load_from_file(pobject, varFile, e_type_empty_argument);
//
//   }
//
//}
//
//
//inline ::e_status context::load_from_file(::matter* pobject, const ::payload& varFile)
//{
//
//   return _load_from_file(pobject, varFile, e_type_empty_argument);
//
//}
//
//
//inline ::e_status context::save_to_file(const ::payload& varFile, const ::payload* pvarOptions, const ::matter* pobject)
//{
//
//   if (pvarOptions)
//   {
//
//      return _save_to_file(varFile, *pvarOptions, pobject);
//
//   }
//   else
//   {
//
//      return _save_to_file(varFile, e_type_empty_argument, pobject);
//
//   }
//
//}
//

//inline ::e_status context::save_to_file(const ::payload& varFile, const ::matter* pobject)
//{
//
//   return _save_to_file(varFile, e_type_empty_argument, pobject);
//
//}


inline ::file_result object::get_reader(const ::payload& varFile, const ::file::e_open& eopen)
{

   return get_file(varFile, eopen | ::file::e_open_read);

}


inline ::file_result object::get_writer(const ::payload& varFile, const ::file::e_open& eopen)
{

   return get_file(varFile, eopen | ::file::e_open_write);

}


//template < typename TYPE >
//inline void object::set(const ::id& id, const TYPE& t)
//{
//
//   ::assign(payload(id), t);
//
//   set(e_object_property_set_modified);
//
//}


//template < typename TYPE >
//inline void object::get(const ::id& id, TYPE& t)
//{
//
//   ::assign(t, payload(id));
//
//}


//inline payload::operator string & ()
//{
//
//  if (m_etype == ::type_pvar)
//  {
//
//     return m_ppayload->operator string & ();
//
//  }
//  else if (m_etype == ::type_prop)
//  {
//
//     return m_pprop->operator string & ();
//
//  }
//  else if (m_etype == ::e_type_pstring)
//  {
//
//     return *m_pstr;
//
//  }
//  else if (m_etype != ::e_type_string)
//  {
//
//     m_str = get_string();
//
//     set_type(e_type_string, false);
//
//  }
//
//  return m_str;
//
//}
//

//inline payload::operator string() const
//{
//
//    return get_string();
//
//}

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
        return m_pprop->operator TYPE &();   \
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


//#define IMPL_VAR_REF1(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF1(bool, b);
//#undef IMPL_VAR_REF1
//
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
//
//
//#define IMPL_VAR_REF3(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF3(float, f);
//IMPL_VAR_REF3(double, d);
//#undef IMPL_VAR_REF3
//
//
//#undef IMPL_VAR_REF


template < typename TYPE >
inline ::e_status object::__construct(::task_pointer& p, void (TYPE::* pfn)(), e_priority epriority)
{

   p = fork(pfn, epriority);

   if (!p)
   {

      return error_failed;

   }

   return p->m_estatus;

}


template < typename TYPE >
inline ::e_status object::__construct_below_normal(::task_pointer& p, void (TYPE::* pfn)())
{

   return __construct(p, pfn, priority_below_normal);

}


template < typename TYPE >
inline ::task_pointer object::defer_branch(const ::id& id, void(TYPE::* pfn)(), e_priority epriority)
{

   auto pfork = fork(pfn, epriority);

   get_property_set()[__id(thread)][id] = pfork;

   return pfork;

}


template < typename PRED >
inline void add_routine(::routine_array& routinea, PRED pred)
{

   routinea.add(__routine(pred));

}



inline ::e_status object::defer_branch(::task_pointer& pthread, const ::routine& routine)
{

   auto estatus = __defer_construct(pthread);

   if (!estatus)
   {

      return estatus;

   }

   pthread->m_pmatter = routine;

   return pthread->branch();

}




template < typename PRED >
inline ::task_pointer object::predicate_run(bool bSync, PRED pred)
{

   return ::predicate_run(this, bSync, pred);

}




template < typename PREDICATE >
inline __transport(task) object::fork(PREDICATE predicate, ::e_priority epriority, ::u32 nStackSize, ::u32 dwCreateFlags ARG_SEC_ATTRS)
{

   auto proutine = __routine(predicate);

   if(!proutine)
   {

      return error_failed;

   }

   auto ptask = this->branch(proutine, epriority, nStackSize, dwCreateFlags ADD_PASS_SEC_ATTRS);

   if(!ptask)
   {

      return ptask;

   }

   return ptask;

}


inline routine_array& property_object::_routine_array(const ::id& id)
{
   
   return m_pmapPropertyRoutine->operator[](id);

}


inline routine_array& property_object::routine_array(const ::id& id)
{ 
   
   ::__defer_construct_new(m_pmapPropertyRoutine);
   
   return m_pmapPropertyRoutine->operator[](id);

}


inline void property_object::add_routine(const ::id& id, const ::routine& routine)
{

   routine_array(id).add(routine);

}


template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_REFERENCE >
auto material_object::__sync_status_payload(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD method, PAYLOAD_REFERENCE & payload)
{

   auto psynchronization = __new(::promise::synchronization);

   auto proutine = __routine([pobject, method, &payload, psynchronization]()
                             {

                                auto statuspayload = (pobject->*method)();

                                synchronous_lock synchronizationlock(psynchronization->mutex());

                                psynchronization->m_evGoingToWrite.SetEvent();

                                psynchronization->m_evResponse.wait();

                                if(!psynchronization->m_bTimeout)
                                {

                                   payload = statuspayload;

                                   psynchronization->m_estatus = statuspayload;

                                }

                                psynchronization->m_evReady.SetEvent();

                                ::release((::matter * &)psynchronization.m_p);

                             });

   (pbranching->*branching_method)(proutine);

   if (psynchronization->m_evGoingToWrite.wait(duration).failed())
   {

      psynchronization->m_bTimeout = true;

      psynchronization->m_evResponse.SetEvent();

      return error_timeout;

   }

   psynchronization->m_evResponse.SetEvent();

   psynchronization->m_evReady.wait();

   if(!psynchronization->m_estatus)
   {

      return psynchronization->m_estatus;

   }

   return psynchronization->m_estatus;

}


//template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename MEMBER_POINTER >
//::e_status material_object::__sync_member(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD method, MEMBER_POINTER ppayload)
//{
//
//   auto proutine = __routine([pobject, method, &ppayload]()
//                             {
//
//                                auto statuspayload = (pobject->*method)();
//
//                                if(statuspayload)
//                                {
//
//                                   *ppayload = statuspayload;
//
//                                }
//
//                             });
//
//   auto estatus = __sync_routine(duration, pbranching, branching_method, proutine);
//
//   if(!estatus)
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
//template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
//::e_status material_object::__sync_member(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD method)
//{
//
//   auto proutine = __routine([pobject, method]()
//                             {
//
//                                (pobject->*method)();
//
//                             });
//
//   auto estatus = __sync_routine(duration, pbranching, branching_method, proutine);
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}



template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD >
::e_status material_object::__sync_routine(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, ::routine routine)
{

   if(pbranching->is_branch_current())
   {

      return routine();

   }

   auto psignalization = __new(::promise::signalization);

   auto proutine = __routine([routine, psignalization]()
                             {

                                try
                                {

                                   psignalization->m_estatus = routine();

                                }
                                catch(...)
                                {

                                   psignalization->m_estatus = ::error_exception;

                                }

                                psignalization->m_evReady.SetEvent();

                                psignalization->m_pmatterHold.release();

                                //::release((::matter * &)psignalization.m_p);

                             });

   psignalization->m_pmatterHold = proutine;

   (pbranching->*branching_method)(proutine);

   if (psignalization->m_evReady.wait(duration).failed())
   {

      return error_timeout;

   }

   return psignalization->m_estatus;

}



inline byte* memory_base::find(const ::block& block, ::index iStart) const
{

   return (byte*)memmem(get_data() + iStart, get_size() - iStart, (byte*)block.get_data(), block.get_size());

}


inline ::index memory_base::find_index(const ::block& block, ::index iStart) const
{

   auto p = find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte*)p) - get_data();

}


inline byte* memory_base::reverse_find(const ::block& block, ::index iStart) const
{

   return (byte*)reverse_memmem(get_data() + iStart, get_size() - iStart, (byte*)block.get_data(), block.get_size());

}


inline ::index memory_base::reverse_find_index(const ::block& block, ::index iStart) const
{

   auto p = reverse_find(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte*)p) - get_data();

}


inline byte* memory_base::reverse_find_byte_not_in_block(const ::block& block, ::index iStart) const
{

   return (byte*)reverse_byte_not_in_block(get_data() + iStart, get_size() - iStart, (byte*)block.get_data(), block.get_size());

}


inline ::index memory_base::reverse_find_index_of_byte_not_in_block(const ::block& block, ::index iStart) const
{

   auto p = reverse_find_byte_not_in_block(block, iStart);

   if (!p)
   {

      return -1;

   }

   return ((byte*)p) - get_data();

}



