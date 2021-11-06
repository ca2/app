#pragma once


inline material_object::material_object(const material_object & idmatter) :
   matter(idmatter),
   m_id(idmatter.m_id)
{

}

inline property_object::property_object(const property_object & object) :
      material_object(object),
      m_pia(__new(::i64_array(*object.m_pia))),
      m_estatus(object.m_estatus),
      m_ppropertyset(__new(::property_set(*object.m_ppropertyset)))
{

}


inline bool property_object::has_property(const id & id) const { return m_ppropertyset && m_ppropertyset->has_property(id); }
inline property * property_object::lookup_property(const id& id) const { return m_ppropertyset ? m_ppropertyset->find(id) : nullptr; }
inline bool property_object::erase_key(const id & id) { return m_ppropertyset && m_ppropertyset->erase_by_name(id); }
inline property_set & property_object::get_property_set() { defer_propset(); return *m_ppropertyset; }
inline const property_set & property_object::get_property_set() const { ((property_object *)this)->defer_propset(); return *m_ppropertyset; }


inline ::i64_array& property_object::idarray() const { m_psystem->__defer_construct_new(((property_object*)this)->m_pia); return *m_pia; }

inline bool property_object::contains(const property_set & set) const
{

  if (set.is_empty())
  {

     return true;

  }

  if (m_ppropertyset.is_null())
  {

     return false;

  }

  return m_ppropertyset->contains(set);

}

inline void property_object::defer_propset() { m_psystem->__defer_construct_new(m_ppropertyset); }



inline property * property_object::find_property(const id & id) const
{

   if (!m_ppropertyset)
   {

      return nullptr;

   }

   return m_ppropertyset->find(id);

}


inline string property_object::find_string(const ::id & id, const ansichar * pszDefault) const
{

   if (!m_ppropertyset)
   {

      return pszDefault;

   }

   auto pproperty = m_ppropertyset->find(id);

   if (!pproperty)
   {

      return pszDefault;

   }

   return pproperty->string(pszDefault);

}


inline ::i32 property_object::find_i32(const ::id & id, ::i32 iDefault) const
{

   if (!m_ppropertyset)
   {

      return iDefault;

   }

   auto pproperty = m_ppropertyset->find(id);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->i32(iDefault);

}


inline ::u32 property_object::find_u32(const ::id & id, ::u32 iDefault) const
{

   if (!m_ppropertyset)
   {

      return iDefault;

   }

   auto pproperty = m_ppropertyset->find(id);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->u32(iDefault);

}


template < typename TYPE > inline TYPE & property_object::get_cast(const ::id & id, TYPE * pDefault)
{

   return payload(id).get_cast <TYPE>(pDefault);

}


template < typename TYPE > inline __pointer(TYPE) property_object::cast(const ::id & id) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


inline ::payload & property_object::payload(const id & id)
{

   auto & set = get_property_set();

   return set.get(id);

}


inline bool property_object::is_true(const ::id & id) const
{

   return m_ppropertyset && payload(id).is_true();

}


inline bool property_object::is_false(const ::id& id) const
{

   return !is_true(id);

}


inline bool property_object::is_true(const ::id & id, const ::payload & varDefault, bool bDefault = false) const
{

   return payload(id).is_true(varDefault, bDefault);

}


inline ::payload & property_object::operator[](const ::id & id) { return payload(id); }

inline ::payload property_object::operator[](const ::id & id) const { return find_property(id); }

inline ::payload property_object::payload(const ::id & id) const { return find_property(id); }

inline ::payload property_object::payload(const ::id & id, const ::payload & varDefault) const { return operator()(id, varDefault); }

inline ::payload property_object::operator()(const ::id & id) const { return find_payload(id, ::error_not_found); }

inline ::payload property_object::operator()(const ::id & id, const ::payload & varDefault) const { return find_payload(id, varDefault); }

inline ::payload property_object::find_payload(const ::id & id) const { return find_payload(id, ::error_not_found); }

inline ::payload property_object::find_payload(const ::id & id, const ::payload & varDefault) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}

inline ::payload property_object::attribute(const ::id & id) { return payload(id); }

inline ::property * property_object::find_attribute(const ::id & id) { return find_property(id); }

template < typename TYPE >
inline bool property_object::find_attribute(const ::id & id, TYPE & t)
{

   auto p = find_property(id);

   if (!p)
   {

      return false;

   }

   t = *p;

   return true;

}


inline ::payload & property_object::get_object(const ::id & id)
{

   auto pproperty = &payload(id);

   if (!pproperty)
   {

      __throw(error_resource);

   }

   return *pproperty;

}




inline ::payload & property_object::topic(const ::id& id)
{

   auto property = fetch_property(id);

   if (!property)
   {

      __throw(error_resource);

   }

   return *property.m_pproperty;

}

