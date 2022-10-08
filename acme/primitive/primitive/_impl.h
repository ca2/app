#pragma once


#include "acme/primitive/comparison/equals.h"


inline bool __enum_is_failed(const ::e_status & e)
{

   return ::failed(e);

}



template < class T >
template < typename T2 >
inline ___pointer < T > ::___pointer(const ptr < T2 > & t) :
   m_p(t.m_p),
   m_pelement(t.m_p)
{

   if (::is_set(m_p))
   {

      m_pelement->increment_reference_count();

   }

}


template < class T >
template < typename T2 >
inline ___pointer < T > ::___pointer(ptr < T2 > && t) :
   m_p(t.m_p),
   m_pelement(t.m_p)
{

   if (::is_set(m_p))
   {

      m_pelement->increment_reference_count();

   }

}


template < class T >
template < typename T2 >
inline ___pointer < T > & ___pointer < T > ::operator = (const ptr < T2 >  & t)
{

   auto pold = m_pelement;

   m_p = t.m_p;

   m_pelement = t.m_p;

   if (::is_set(m_p))
   {

      m_pelement->increment_reference_count();

   }

   ::release(pold REF_DBG_COMMA_POINTER);

   return *this;

}


template < class T >
template < typename T2 >
inline ___pointer < T > & ___pointer < T > ::operator = (ptr < T2 > && t)
{

   auto pOld         = m_pelement;

   m_p           = t.m_p;

   m_pelement        = t.m_p;

   t.m_p         = nullptr;

   ::release(pOld REF_DBG_COMMA_POINTER);

   return *this;

}


inline type::type(const ::element * pelement)
{

   m_strName = typeid(*(element *)pelement).name();

   m_strName = demangle(m_strName);

}


template < typename BASE >
inline type::type(const __pointer(BASE) & point)
{

   m_strName = typeid(*((BASE *)point.m_p)).name();

   m_strName = demangle(m_strName);

}


template < >
inline uptr uptr_hash < const type & >(const ::type & type)
{

   return uptr_hash < const string & > (type.m_strName);

}


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
//   return get_system()->get_image(this, payloadFile, uTrait, pred);
//
//}


#include "acme/primitive/primitive/trait_predicate.h"


//inline ::payload matter::topic(const ::atom & atom)
//{
//
//   auto pproperty = fetch_property(atom);
//
//   if (!pproperty)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   return pproperty;
//
//}


inline ::index property_set::find_index(const ::atom & atom, ::index i) const
{

   for(; i < m_nSize; i++)
   {

      if (m_pData[i]->m_atom == atom)
      {

         return i;

      }

   }

   return -1;

}



inline property & property_set::get(const ::atom & atom)
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      pproperty = memory_new property(atom);

      add_item(pproperty);

   }

   return *pproperty;

}

//#define memory_new ACME_NEW

inline ::property * property_set::find(const ::atom & atom) const
{

   auto iFind = find_index(atom);

   if(__not_found(iFind))
   {

      return nullptr;

   }

   return (const_cast < property_set * > (this))->m_pData[iFind];

}


inline ::payload property_set::operator()(const ::atom & atom, const ::payload & varDefault) const
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}


inline ::payload & property_set::topic(const atom & atom)
{

   return set(atom);

}





inline ::payload & property_set::set(const ::atom & atom)
{

   auto pproperty = find(atom);

   if (!pproperty)
   {

      pproperty = memory_new property(atom);

      add_item(pproperty);

   }

   return *pproperty;

}


//#define memory_new ACME_NEW

//inline property * payload::find_property(const ::atom & atom) const
//{
//
//   if (!casts_to(e_type_property_set))
//   {
//
//      return nullptr;
//
//   }
//
//   return propset().find(atom);
//
//}


//inline property & payload::get_property(const ::atom & atom)
//{
//
//   return propset().get(atom);
//
//}



//inline CLASS_DECL_ACME string atom::operator + (const atom & atom) const
//{
//
//   if (is_integer())
//   {
//
//      if (atom.is_integer())
//      {
//
//         return (iptr)(m_i + atom.m_i);
//
//      }
//      else if (atom.is_text())
//      {
//
//         return __string(m_i) + "." + string(atom.m_psz);
//
//      }
//      else
//      {
//
//         return *this;
//
//      }
//
//   }
//   else if (atom.is_integer())
//   {
//
//      if (is_text())
//      {
//
//         return string(m_psz) + "." + __string(atom.m_i);
//
//      }
//      else
//      {
//
//         return atom;
//
//      }
//
//   }
//   else if (is_text())
//   {
//
//      if (atom.is_text())
//      {
//
//         return string(m_psz) + string(atom.m_psz);
//
//      }
//      else
//      {
//
//         return *this;
//
//      }
//
//   }
//   else if (atom.is_text())
//   {
//
//      return atom;
//
//   }
//   else
//   {
//
//      return ::atom();
//
//   }
//
//}


inline bool property_set::has_property(atom idName) const
{

   if (::is_null(this))
   {

      return false;

   }

   const property * pproperty = find(idName);

   return pproperty != nullptr && pproperty->m_etype != ::e_type_new;

}


inline bool property_set::is_true(atom idName, bool bDefault) const
{

   const property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return bDefault;

   }

   return pproperty->is_true(bDefault);

}


inline ::payload property_set::value(atom idName) const
{

   property * pproperty = find(idName);

   if (pproperty == nullptr)
   {

      return ::error_not_found;

   }

   return *pproperty;

}


inline ::payload property_set::value(atom idName, ::payload varDefault) const
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

//template < typename STRINGABLE >
//inline string operator + (const char * psz, const STRINGABLE& stringable)
//{
//
//   string strRight(stringable);
//
//   return __string(psz) + strRight;
//
//}


/// END property_set


inline __pointer(::handle::ini) operator ""_pini(const char * psz, size_t s)
{

   return __new(::handle::ini(string(psz, s)));

}


//inline string CLASS_DECL_ACME operator + (const char * psz, const ::payload & payload)
//{
//
//   return __string(psz) + payload.get_string();
//
//}
//

//inline class ::payload & payload::operator -= (const class property & property) { operator -=(property);  return *this; }
//inline class ::payload & payload::operator += (const class property & property) { operator +=(property);  return *this; }
//inline class ::payload & payload::operator /= (const class property & property) { operator /=(property);  return *this; }
//inline class ::payload & payload::operator *= (const class property & property) { operator *=(property);  return *this; }



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

      //if (!stream.fail())
      {

         if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
         {

            if(is_set() && __type_name(m_p) == strText)
            {

               ::output_debug_string("POINTER: loading into existing matter of same class type (1)");

            }
            else
            {

               this->defer_create_new();

               if(is_null())
               {

                  ::output_debug_string("POINTER: defer_new failed (1.1)");

                  //stream.set_fail_bit();

                  throw ::exception(error_io);

               }
               else if(__type_name(m_p) != strText)
               {

                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (1.2)");

                  //stream.set_fail_bit();

                  throw ::exception(error_io);

               }

            }

         }
         else
         {

            ::atom atom = stream.text_to_factory_id(strText);

            if(is_set() && __type_name(m_p) == atom)
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
               else if(__type_name(p) != atom.as_string())
               {

                  ::output_debug_string("POINTER: allocated matter type is different from streamed matter type (2.2)");

                  //stream.set_fail_bit();

                  throw ::exception(error_io);

               }
               else
               {

                  operator =(p);

               }

            }

         }

         //if (!stream.fail())
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

      throw ::exception(error_unexpected_situation);

   }

}


inline bool succeeded(const ::property & property)
{

   return ::succeeded((const ::payload &) property);

}




//
//template < typename BASE_TYPE >
//inline __pointer(BASE_TYPE) matter::__create()
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
//inline __pointer(BASE_TYPE) matter::__id_create(const ::atom & atom)
//{
//
//   auto p = ::__id_create<BASE_TYPE>(atom);
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
//inline __pointer(TYPE) matter::__create_new()
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
//template < class T >
//template < typename TEMPLATER >
//inline __pointer(T) & ___pointer < T >::create(TEMPLATER)
//{
//
//   __construct(*this);
//
//   return *this;
//
//}


template < class T >
template < typename OBJECT >
inline __pointer(T) & ___pointer < T >::create(OBJECT * pobject)
{

  auto p = pobject->template __create < T >();

  return operator =(p);

}


template < class T >
template < typename OBJECT >
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
//inline void matter::__compose(__composite(BASE_TYPE) & pusermessage)
//{
//
//   if (!pusermessage)
//   {
//
//      auto & pfactory = ::factory::get_factory_item < BASE_TYPE >();
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
//inline void matter::__raw_compose(__composite(BASE_TYPE) & pusermessage)
//{
//
//   if (!pusermessage)
//   {
//
//      auto & pfactory = ::factory::get_factory_item < BASE_TYPE >();
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
//inline void matter::__compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource)
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
//inline void matter::__raw_compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource)
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
//inline void matter::__compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource)
//{
//
//   return __compose(pusermessage, psource.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__raw_compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource)
//{
//
//   return __raw_compose(pusermessage, psource.get());
//
//}
//
//
//
//template < typename BASE_TYPE >
//inline void matter::__id_compose(__composite(BASE_TYPE) & pusermessage, const ::atom & atom)
//{
//
//   auto & pfactory = ::factory::get_factory_item(atom);
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
//inline void matter::__raw_compose_new(__composite(TYPE) & p)
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
//inline void matter::__compose_new(__composite(TYPE) & p)
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
//inline void matter::__construct(__pointer(TYPE) & p)
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
//inline void matter::__id_construct(__pointer(TYPE) & p, const ::atom & atom)
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
//inline void matter::__construct_new(__pointer(TYPE) & p)
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
//inline void matter::__release(__composite(BASE_TYPE) & pcomposite)
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
//inline void matter::__release(__reference(BASE_TYPE) & preference)
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
//inline void matter::release_reference(__pointer(SOURCE) & psource)
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
//inline void matter::add_composite(__composite(BASE_TYPE) & pcomposite)
//{
//
//   return add_composite(pcomposite.get());
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(__reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, psource.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(__reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & pmember, const char* pszObjRefDbg)
//{
//
//   return __refer(preference, pmember.get(), pszObjRefDbg);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(__reference(BASE_TYPE) & preference, const SOURCE * psource, const char* pszObjRefDbg)
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
//inline void matter::add_reference(__pointer(SOURCE) & psource)
//{
//
//   return add_reference(psource.get());
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(__reference(SOURCE) & preference)
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
inline ptr < T > move_transfer(T* p) { return { e_move_transfer, p }; }


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


//template < typename T >
//template < typename TEMPLATER >
//inline __pointer(T) & ___pointer<T> ::defer_create(TEMPLATER)
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

template < typename T >
template < typename OBJECT >
inline __pointer(T) & ___pointer<T> ::defer_create(OBJECT * pobject)
{

   if (is_null())
   {

      operator=(pobject->template __create < T >());

   }

   return *this;

}


//template < class T >
//inline stream & operator << (stream & os, const ___pointer < T > & sp)
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
//inline stream & operator >> (stream & is, ___pointer < T > & sp)
//{
//
//   is >> *sp.m_p;
//
//   return is;
//
//}
//

//inline void context::load_from_file(::matter* pobject, const ::payload& payloadFile, const ::payload* pvarOptions)
//{
//
//   if (pvarOptions)
//   {
//
//      return _load_from_file(pobject, payloadFile, *pvarOptions);
//
//   }
//   else
//   {
//
//      return _load_from_file(pobject, payloadFile, e_type_empty_argument);
//
//   }
//
//}
//
//
//inline void context::load_from_file(::matter* pobject, const ::payload& payloadFile)
//{
//
//   return _load_from_file(pobject, payloadFile, e_type_empty_argument);
//
//}
//
//
//inline void context::save_to_file(const ::payload& payloadFile, const ::payload* pvarOptions, const ::matter * pobject)
//{
//
//   if (pvarOptions)
//   {
//
//      return _save_to_file(payloadFile, *pvarOptions, pobject);
//
//   }
//   else
//   {
//
//      return _save_to_file(payloadFile, e_type_empty_argument, pobject);
//
//   }
//
//}
//
//
//inline void context::save_to_file(const ::payload& payloadFile, const ::matter* pobject)
//{
//
//   return _save_to_file(payloadFile, e_type_empty_argument, pobject);
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

inline payload::operator ::memory() const
{

   return this->memory();

}


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


inline bool type::operator == (const ::atom& atom) const
{

   return m_strName == atom.as_string();

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
//inline string_base < TYPE_CHAR >::string_base(const atom& atom) :
//   string_base(atom.to_string())
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
//inline string_base < TYPE_CHAR >::string_base(atom & atom) :
//   string_base(atom.to_string())
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
      else if (m_etype == e_type_property && m_pproperty != nullptr)
      {

         return m_pproperty->cast < T >(pDefault);

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

      if (m_etype == e_type_property && m_pproperty != nullptr)
      {

         return m_pproperty->get_cast <T>(pDefault);

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

      if (m_etype == e_type_property && m_pproperty != nullptr)
      {

         return m_pproperty->cast < T >();

      }

      switch (m_etype)
      {
      case e_type_element:
         return m_p;
      case e_type_string_array:
         return m_pstra;
      case e_type_i32_array:
         return m_pia;
      case e_type_payload_array:
         return m_ppayloada;
      case e_type_property_set:
         return m_ppropertyset;
      case e_type_i64_array:
         return m_pi64a;
      case e_type_memory:
         return m_pmemory;
      case e_type_path:
         return m_ppath;
      default:
         break;
      }

      return nullptr;

   }



//template < typename PRED >
//void method::pred(PRED pred)
//{
//
//   m_pelement = method(pred);
//
//}
//

//template < typename PRED >
//inline void future::pred(PRED pred)
//{
//
//   m_pelement = __new(predicate_future < PRED > (pred));
//
//}
//
//
//

//template < typename TYPE >
//inline __pointer(TYPE) element::cast(const ::atom & atom)
//{
//
//   return value(atom).cast < TYPE>();
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
//inline ::count fork_count_end(::element* pobject, ::count iCount, PRED pred, index iStart, ::enum_priority epriority)
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
//   if (!m_pelement)
//   {
//
//      return;
//
//   }
//
//   return m_pelement->receive_response(payload);
//
//}
//


//template < typename PRED >
//method::method(PRED pred) : function(__new(predicate_method < PRED >(pred))) { }
//
//
//template < typename PRED >
//future::future(PRED pred) : function(__new(predicate_future < PRED >(pred))) { }




inline bool property_set::get_string(string& strResult, const atom& idKey) const
{

   auto pproperty = find_property(idKey);

   if (::is_null(pproperty))
   {

      return false;

   }

   strResult = *pproperty;

   return true;

}




//inline void method::operator()() const
//{ 
//   
//   return ::is_set(m_pelement) ? m_pelement->call() : (void) ::success_none;
//
//}


inline ::payload operator + (::payload payload, const ::procedure & procedure)
{

   if (payload.get_type() != e_type_property_set)
   {

      payload["message"] = payload;

   }

   payload["routine"] = procedure.m_p;

   return payload;

}



#if OBJECT_REFERENCE_COUNT_DEBUG


template < typename TYPE, typename T >
void object_reference_count_debug_assign(__pointer(TYPE) & ptr, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   auto pold = ptr.m_p;

   ptr.m_p = p;

   p->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   object_reference_count_debug_release(pold OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void object_reference_count_debug_release(__pointer(TYPE) & ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{
   
   object_reference_count_debug_release(ptr.m_p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename TYPE >
void object_reference_count_debug_release(TYPE * & p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   release(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


#endif


//inline bool ::duration::done(const ::duration & duration) const { return elapsed(::duration).m_i >= 0; }
//inline bool ::duration::done() const { return elapsed().m_i >= 0; }


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






template < typename TYPE >
inline __pointer(TYPE) object::__create()
{

   auto & pfactory = ::factory::get_factory_item < TYPE >();

   if (!pfactory)
   {

      throw ::exception(::error_not_implemented);

   }

   auto ptypeNew = pfactory->create_element();

   if (!ptypeNew)
   {

      throw ::exception(::error_no_memory);

   }

   TYPE * p;

   __dynamic_cast(p, ptypeNew.m_p);

   if (!p)
   {

      throw ::exception(::error_wrong_type);

   }

   p->initialize(this);


   return p;

}



template < typename TYPE >
inline __pointer(TYPE) object::__id_create(const ::atom& atom)
{

   auto pfactory = ::factory::get_factory_item(atom);
   
   if (!pfactory)
   {
   
      throw ::exception(error_no_factory);
   
   }
   
   auto ptypeNew = pfactory->create_element();
   
   if (!ptypeNew)
   {
   
      throw ::exception(error_no_memory);
   
   }
   
   __pointer(TYPE) p;
   
   p = ptypeNew;
   
   if (!p)
   {
   
      throw ::exception(error_wrong_type);
   
   }
   
   p->set(e_flag_factory);
   
   //auto estatus = p->initialize(this);

   p->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   return ::move(p);

}


template < typename TYPE >
inline __pointer(TYPE) object::__create_new()
{

   ASSERT(::is_set(this));

   auto p = __new(TYPE());

   if (p)
   {

      p->initialize(this);
      
   }

   return ::move(p);

}


template < typename BASE_TYPE >
inline void object::__compose(__composite(BASE_TYPE)& pcomposite)
{

   if (!pcomposite)
   {

      auto& pfactory = ::factory::get_factory_item < BASE_TYPE >();

      if (!pfactory)
      {

         throw ::exception(error_no_factory);

      }

      auto pelement = ::move(pfactory->create_element());

      if (!pelement)
      {

         throw ::exception(error_no_memory);

      }

      pcomposite = pelement;

      if (!pcomposite)
      {

         throw ::exception(error_wrong_type);

      }

      /*auto estatus = */ pcomposite->initialize(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus = */ add_composite(pcomposite);

      //if (!estatus)
      //{

      //   return estatus;

      //}

   }

   //return ::success;

}


template < typename BASE_TYPE >
inline void object::__raw_compose(__composite(BASE_TYPE)& pusermessage)
{

   if (!pusermessage)
   {

      auto& pfactory = ::factory::get_factory_item < BASE_TYPE >();

      if (!pfactory)
      {

         throw ::exception(::error_no_factory);

      }

      auto pelement = pfactory->create_element();

      if (!pelement)
      {

         throw ::exception(::error_no_memory);

      }

      pusermessage = pelement;

      if (!pusermessage)
      {

         throw ::exception(error_wrong_type);

      }

      /*auto estatus = */ add_composite(pusermessage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

   }

   //return ::success;

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__compose(__composite(BASE_TYPE)& pcomposite, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   pcomposite = psource;

   if (!pcomposite)
   {

      throw ::exception(error_wrong_type);

   }

   //auto estatus = pcomposite->initialize(this);
    pcomposite->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

    add_composite(pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

   //return m_estatus;

}

template < typename BASE_TYPE, typename SOURCE >
inline void object::__raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource)
{

   pusermessage = psource;

   if (!pusermessage)
   {

      throw ::exception(error_wrong_type);

   }

   /*m_estatus = */ add_composite(pusermessage);

   //return m_estatus;

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   /* return */ __compose(pusermessage, psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__compose(__composite(BASE_TYPE)& pusermessage, const ptr < SOURCE > & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   /* return */ __compose(pusermessage, psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource)
{

   /*return*/ __raw_compose(pusermessage, psource.get());

}


template < typename BASE_TYPE >
inline void object::__id_compose(__composite(BASE_TYPE)& pusermessage, const ::atom& atom)
{

   auto& pfactory = ::factory::get_factory_item(atom);

   if (!pfactory)
   {

      throw ::exception(::error_no_factory);

   }

   auto ptypeNew = pfactory->create_element();

   if (!ptypeNew)
   {

      throw ::exception(::error_no_memory);

   }

   pusermessage = ptypeNew;

   if (!pusermessage)
   {

      throw ::exception(::error_wrong_type);

   }

   /*auto estatus =*/ pusermessage->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   /* estatus = */ add_composite(pusermessage);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


template < typename TYPE >
inline void object::__raw_compose_new(__composite(TYPE)& p)
{

   auto ptypeNew = __new(TYPE);

   if (!ptypeNew)
   {

      throw ::exception(::error_no_memory);

   }

   p = ptypeNew;

   /*auto estatus = */ add_composite(p);

   //if (!estatus)
   //{

   //   p.clear_member();

   //   return estatus;

   //}

   //return estatus;

}


template < typename TYPE >
inline void object::__compose_new(__composite(TYPE)& p)
{

   auto ptypeNew = __new(TYPE);

   if (!ptypeNew)
   {

      throw ::exception(::error_no_memory);

   }

   /*auto estatus = */ ptypeNew->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   p = ptypeNew;

   /*estatus = */ add_composite(p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(this));

   //if (!estatus)
   //{

      //p.clear_member();

//      return estatus;

//   }

//   return estatus;

}


template < typename TYPE >
inline void object::__defer_construct(__pointer(TYPE)& p)
{

   if (::is_null(p))
   {

      __construct(p);

   }

}


template < typename TYPE >
inline void object::__defer_construct_new(__pointer(TYPE)& p)
{

   if(::is_null(p))
   {

      __construct_new(p);

   }

}


template < typename TYPE >
inline void object::__construct(__pointer(TYPE) & p)
{

   auto & pfactory = ::factory::get_factory_item < TYPE >();
   
   if (!pfactory)
   {

      ERROR("object::__construct has failed to find factory_item for type \"" <<  __type_name < TYPE >() << "\"");

      throw ::exception(::error_not_implemented);

   }
   
   auto ptypeNew = pfactory->create_element();
   
   if (!ptypeNew)
   {

      ERROR("object::__construct no memory to allocate implementation of type \"" + __type_name < TYPE >() + "\"");

      throw ::exception(::error_no_memory);
   
   }

   p.release();
   
   p = ptypeNew;
   
   if (!p)
   {

      ERROR("object::__construct object("<< __type_name(ptypeNew) << ") is not of type \"" << __type_name < TYPE >() << "\"");

      throw ::exception(::error_wrong_type);
   
   }
   
   p->initialize(this);

}


template < typename TYPE >
inline void object::__id_construct(__pointer(TYPE)& p, const ::atom& atom)
{

   auto & pfactory = ::factory::get_existing_factory_item(atom);

   auto ptypeNew = pfactory->create_element();

   //if (!ptypeNew)
   //{

   //   return error_no_memory;

   //}

   p = ptypeNew;

   if (!p)
   {

      throw ::exception(error_wrong_type);

   }

   p->set(e_flag_factory);

   //auto estatus = 
   
   p->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


template < typename TYPE >
inline void object::__construct_new(__pointer(TYPE)& p)
{

   p = __new(TYPE);

   if (!p)
   {

      throw ::exception(error_no_memory);

   }

   p->initialize(this);


}


template < typename BASE_TYPE >
inline void object::__release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_set(pcomposite))
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

   //return ::success;

}


template < typename BASE_TYPE >
inline void object::__release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (::is_set(preference))
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

   //return ::success;

}


template < typename SOURCE >
inline void object::__release(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   release_reference(psource.m_p);

}


CLASS_DECL_ACME void object_on_add_composite(const element* pusermessage);


template < typename BASE_TYPE, typename SOURCE >
inline void object::__refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   __refer(preference, psource.get()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& pmember OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   __refer(preference, pmember.get()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   preference = psource;

   if (!preference)
   {

      throw ::exception(error_wrong_type);

   }

   add_reference(preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__defer_refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   __defer_refer(preference, psource.get()  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline void object::__defer_refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   if (preference.get() != psource)
   {

      __release(preference);

      preference = psource;

      if (preference)
      {

         add_reference(preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

      }

   }

}


template < typename SOURCE >
inline void object::add_reference(__pointer(SOURCE)& psource  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   add_reference(psource.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename SOURCE >
inline void object::add_reference(__reference(SOURCE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   add_reference(preference.get() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


template < typename SOURCE >
inline void object::add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   ::element* pelement = psource;

   if (::is_null(pelement))
   {

      throw ::exception(error_wrong_type);

   }

   add_reference(pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


inline ::file_pointer object::get_reader(const ::payload& payloadFile, const ::file::e_open& eopen)
{

   return get_file(payloadFile, eopen | ::file::e_open_read);

}


inline ::file_pointer object::get_writer(const ::payload& payloadFile, const ::file::e_open& eopen)
{

   return get_file(payloadFile, eopen | ::file::e_open_write);

}


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


template < typename TYPE >
inline void object::__construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority)
{

   p = fork(pfn, epriority);

   if (!p)
   {

      throw ::exception(error_failed);

   }

}


template < typename TYPE >
inline void object::__construct_below_normal(::task_pointer& p, void (TYPE::* pfn)())
{

   return __construct(p, pfn, e_priority_below_normal);

}


template < typename TYPE >
inline ::task_pointer object::defer_branch(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority)
{

   auto pfork = fork(pfn, epriority);

   get_property_set()[__id(thread)][atom] = pfork;

   return pfork;

}


template < typename PRED >
inline void add_procedure(::procedure_array& routinea, PRED pred)
{

   routinea.add(__routine(pred));

}


inline void object::defer_branch(::task_pointer& ptask, const ::procedure & procedure)
{

   __defer_construct(ptask);

   ptask->m_procedure = procedure;

   ptask->branch();

}


inline __pointer(task) object::fork(const ::procedure & procedure, const ::element_array & elementaHold, ::enum_priority epriority, ::u32 nStackSize, ::u32 dwCreateFlags ARG_SEC_ATTRS)
{

   auto ptask = this->branch_procedure(procedure, epriority, nStackSize, dwCreateFlags ADD_PASS_SEC_ATTRS);

   if (!ptask)
   {

      return ptask;

   }

   if (elementaHold.has_element())
   {

      ptask->m_elementaHold.add(elementaHold);

   }

   return ptask;

}


template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
bool material_object::__get_posted_payload_synchronously(POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER preturning, OBJECT_METHOD returning_method, ::payload & payload, const class ::wait & wait)
{

   if(pposting->is_branch_current())
   {

      payload = (preturning->*returning_method)();

      return true;

   }

   auto posting = [pposting, posting_method](const ::procedure & procedure)
   {

      (pposting->*posting_method)(procedure);

   };

   ::function < void(const ::procedure &) > functionPost(posting);

   ::function < ::payload() > functionReturn([preturning, returning_method]()
   {

      return (preturning->*returning_method)();

   });

   functionReturn.m_waitTimeout = wait;

   return __get_posted_payload_synchronously(functionPost, functionReturn, payload);

}


template < typename POSTING_OBJECT, typename POSTING_METHOD >
void material_object::__send_procedure(POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::procedure & procedure)
{

   if(pposting->is_branch_current())
   {

      return procedure();

   }

   auto posting = [pposting, posting_method](const ::procedure & procedure)
   {

      (pposting->*posting_method)(procedure);

   };

   __send_procedure(posting, procedure);

}


inline void assign(bool & b, const payload & payload)
{ 
   
   b = payload.get_bool(); 

}


inline void assign(::block & block, const ::payload & r)
{

   block.operator=(r.block());

}


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)


inline void assign(long & l, const payload & payload)
{

   l = payload.get_long();

}


inline void assign(unsigned long & ul, const payload & payload)
{

   ul = payload.get_unsigned_long();

}


#endif // defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)


inline void assign(::i8 & i, const payload & payload)
{

   i = payload.i8();

}


inline void assign(::u8 & u, const payload & payload)
{

   u = payload.u8();

}


inline void assign(::i16 & i, const payload & payload)
{

   i = payload.i16();

}


inline void assign(::u16 & u, const payload & payload)
{

   u = payload.u16();

}


inline void assign(::i32 & i, const payload & payload)
{

   i = payload.i32();

}


inline void assign(::u32 & u, const payload & payload)
{

   u = payload.u32();

}


inline void assign(::i64 & i, const payload & payload)
{

   i = payload.i64();

}


inline void assign(::u64 & u, const payload & payload)
{

   u = payload.u64();

}


inline void assign(::f32 & f, const payload & payload)
{

   f = payload.f32();

}


inline void assign(::f64 & f, const payload & payload)
{

   f = payload.f64();

}


inline payload_cast::operator payload_array () const
{
   
   return m_payload.payloada(); 

}


inline payload_cast::operator property_set () const
{

   return m_payload.propset(); 

}


inline atom::atom(const ::lparam & lparam)
{

   m_etype = e_type_integer;

   m_u = lparam.m_lparam;

}


//template < class T >
//inline ___pointer < T > & __move(___pointer < T > & p, lparam & lparam)
//{
//
//   ___pointer < T > pelement(lparam);
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
//template < typename OBJECT >
//inline ___pointer < T > ::___pointer(enum_create, OBJECT * p) :
//   m_p(nullptr),
//   m_pelement(nullptr)
//{
//
//   operator=(p->__create < T >());
//
//}


template < class T >
template < typename OBJECT >
::count pointer_array < T > ::set_size_create(OBJECT * pobject, ::count nNewSize, ::count nGrowBy)
{

   ::index i = this->get_size();

   comparable_array < ___pointer < T > > ::set_size(nNewSize);

   ::count c = this->get_size();

   for (; i < c; i++)
   {

      pobject->__construct(this->element_at(i));

   }

   return c;

}



inline ::topic_pointer matter::create_topic(const ::atom & atom)
{

   auto ptopic = __new(::topic(atom));

   ptopic->m_psystem = m_psystem;

   return ::move(ptopic);

}





