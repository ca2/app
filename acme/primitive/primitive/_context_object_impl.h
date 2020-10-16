#pragma once


inline context_object::context_object(const context_object & object) :
      element(object),
      m_id(object.m_id),
      m_pia(__new(::i64_array(*object.m_pia))),
      m_estatus(object.m_estatus),
      m_pset(__new(::property_set(*object.m_pset)))
{

}


inline bool context_object::has_property(const id & id) const { return m_pset && m_pset->has_property(id); }
inline property * context_object::lookup_property(const id& id) const { return m_pset ? m_pset->find(id) : nullptr; }
inline bool context_object::remove_key(const id & id) { return m_pset && m_pset->remove_by_name(id); }
inline property_set & context_object::get_property_set() { defer_propset(); return *m_pset; }
inline const property_set & context_object::get_property_set() const { ((context_object *)this)->defer_propset(); return *m_pset; }


inline ::i64_array& context_object::idarray() const { if (!m_pia) ((context_object*)this)->m_pia.create_new(); return *m_pia; }

inline bool context_object::contains(const property_set & set) const
{

  if (set.isEmpty())
  {

     return true;

  }

  if (m_pset.is_null())
  {

     return false;

  }

  return m_pset->contains(set);

}

inline void context_object::defer_propset() { if (!m_pset) ::__construct_new(m_pset); }



inline property * context_object::find_property(const id & id) const
{

   if (!m_pset)
   {

      return nullptr;

   }

   return m_pset->find(id);

}


inline string context_object::find_string(const ::id & id, const ansichar * pszDefault) const
{

   if (!m_pset)
   {

      return pszDefault;

   }

   auto pproperty = m_pset->find(id);

   if (!pproperty)
   {

      return pszDefault;

   }

   return pproperty->get_string(pszDefault);

}


inline ::i32 context_object::find_i32(const ::id & id, ::i32 iDefault) const
{

   if (!m_pset)
   {

      return iDefault;

   }

   auto pproperty = m_pset->find(id);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->i32(iDefault);

}


inline ::u32 context_object::find_u32(const ::id & id, ::u32 iDefault) const
{

   if (!m_pset)
   {

      return iDefault;

   }

   auto pproperty = m_pset->find(id);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->u32(iDefault);

}


template < typename TYPE > inline TYPE & context_object::get_cast(const ::id & id, TYPE * pDefault)
{

   return value(id).get_cast <TYPE>(pDefault);

}


template < typename TYPE > inline __pointer(TYPE) context_object::cast(const ::id & id) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


inline var & context_object::value(const id & id)
{

   auto & set = get_property_set();

   return set.get(id);

}


inline bool context_object::is_true(const ::id & id) const
{

   return m_pset && value(id).is_true();

}


inline bool context_object::is_false(const ::id& id) const
{

   return !is_true(id);

}


inline bool context_object::is_true(const ::id & id, const var & varDefault, bool bDefault = false) const
{

   return value(id).is_true(varDefault, bDefault);

}


inline var & context_object::operator[](const ::id & id) { return value(id); }

inline var context_object::operator[](const ::id & id) const { return find_property(id); }

inline var context_object::value(const ::id & id) const { return find_property(id); }

inline var context_object::value(const ::id & id, const var & varDefault) const { return operator()(id, varDefault); }

inline var context_object::operator()(const ::id & id) const { return find_value(id, ::error_not_found); }

inline var context_object::operator()(const ::id & id, const var & varDefault) const { return find_value(id, varDefault); }

inline var context_object::find_value(const ::id & id) const { return find_value(id, ::error_not_found); }

inline var context_object::find_value(const ::id & id, const var & varDefault) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}

inline var context_object::attribute(const ::id & id) { return value(id); }

inline ::property * context_object::find_attribute(const ::id & id) { return find_property(id); }

template < typename TYPE >
inline bool context_object::find_attribute(const ::id & id, TYPE & t)
{

   auto p = find_property(id);

   if (!p)
   {

      return false;

   }

   t = *p;

   return true;

}


inline var & context_object::get_context_object(const ::id & id)
{

   auto pproperty = &value(id);

   if (!pproperty)
   {

      __throw(resource_exception());

   }

   return *pproperty;

}




inline var context_object::topic(const ::id& id)
{

   auto pproperty = fetch_property(id);

   if (!pproperty)
   {

      __throw(resource_exception());

   }

   return pproperty;

}

