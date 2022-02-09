#pragma once


inline property_object::property_object(const property_object & propertyobject) :
   ::PARTICLE(propertyobject),
   ::particle(propertyobject),
   ::element(propertyobject),
   ::matter(propertyobject),
   m_ppropertyset(propertyobject.m_ppropertyset)
{

}




inline bool property_object::has_property(const atom & atom) const { return m_ppropertyset && m_ppropertyset->has_property(atom); }
inline property * property_object::lookup_property(const atom& atom) const { return m_ppropertyset ? m_ppropertyset->find(atom) : nullptr; }
inline bool property_object::erase_key(const atom & atom) { return m_ppropertyset && m_ppropertyset->erase_by_name(atom); }
inline property_set & property_object::get_property_set() { defer_propset(); return *m_ppropertyset; }
inline const property_set & property_object::get_property_set() const { ((property_object *)this)->defer_propset(); return *m_ppropertyset; }


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



inline property * property_object::find_property(const atom & atom) const
{

   if (!m_ppropertyset)
   {

      return nullptr;

   }

   return m_ppropertyset->find(atom);

}


inline string property_object::find_string(const ::atom & atom, const ansichar * pszDefault) const
{

   if (!m_ppropertyset)
   {

      return pszDefault;

   }

   auto pproperty = m_ppropertyset->find(atom);

   if (!pproperty)
   {

      return pszDefault;

   }

   return pproperty->string(pszDefault);

}


inline ::i32 property_object::find_i32(const ::atom & atom, ::i32 iDefault) const
{

   if (!m_ppropertyset)
   {

      return iDefault;

   }

   auto pproperty = m_ppropertyset->find(atom);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->i32(iDefault);

}


inline ::u32 property_object::find_u32(const ::atom & atom, ::u32 iDefault) const
{

   if (!m_ppropertyset)
   {

      return iDefault;

   }

   auto pproperty = m_ppropertyset->find(atom);

   if (!pproperty)
   {

      return iDefault;

   }

   return pproperty->u32(iDefault);

}


template < typename TYPE > inline TYPE & property_object::get_cast(const ::atom & atom, TYPE * pDefault)
{

   return payload(atom).get_cast <TYPE>(pDefault);

}


template < typename TYPE > inline __pointer(TYPE) property_object::cast(const ::atom & atom) const
{

   auto pproperty = find_property(atom);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


inline ::payload & property_object::payload(const atom & atom)
{

   auto & set = get_property_set();

   return set.get(atom);

}


inline bool property_object::is_true(const ::atom & atom) const
{

   return m_ppropertyset && payload(atom).is_true();

}


inline bool property_object::is_false(const ::atom& atom) const
{

   return !is_true(atom);

}


inline bool property_object::is_true(const ::atom & atom, const ::payload & varDefault, bool bDefault = false) const
{

   return payload(atom).is_true(varDefault, bDefault);

}


inline ::payload & property_object::operator[](const ::atom & atom) { return payload(atom); }

inline ::payload property_object::operator[](const ::atom & atom) const { return find_property(atom); }

inline ::payload property_object::payload(const ::atom & atom) const { return find_property(atom); }

inline ::payload property_object::payload(const ::atom & atom, const ::payload & varDefault) const { return operator()(atom, varDefault); }

inline ::payload property_object::operator()(const ::atom & atom) const { return find_payload(atom, ::error_not_found); }

inline ::payload property_object::operator()(const ::atom & atom, const ::payload & varDefault) const { return find_payload(atom, varDefault); }

inline ::payload property_object::find_payload(const ::atom & atom) const { return find_payload(atom, ::error_not_found); }

inline ::payload property_object::find_payload(const ::atom & atom, const ::payload & varDefault) const
{

   auto pproperty = find_property(atom);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}

inline ::payload property_object::attribute(const ::atom & atom) { return payload(atom); }

inline ::property * property_object::find_attribute(const ::atom & atom) { return find_property(atom); }

template < typename TYPE >
inline bool property_object::find_attribute(const ::atom & atom, TYPE & t)
{

   auto p = find_property(atom);

   if (!p)
   {

      return false;

   }

   t = *p;

   return true;

}


inline ::payload & property_object::get_object(const ::atom & atom)
{

   auto pproperty = &payload(atom);

   if (!pproperty)
   {

      throw ::exception(error_resource);

   }

   return *pproperty;

}




inline ::payload & property_object::topic(const ::atom& atom)
{

   auto property = fetch_property(atom);

   if (!property)
   {

      throw ::exception(error_resource);

   }

   return *property.m_pproperty;

}



inline material_object::material_object(const material_object & materialobject) :
   ::PARTICLE(materialobject),
   ::particle(materialobject),
   ::element(materialobject),
   ::matter(materialobject),
   ::property_object(materialobject),
   m_pmapPropertyRoutine(materialobject.m_pmapPropertyRoutine),
   m_pia(materialobject.m_pia)
{

}


inline ::i64_array & material_object::idarray() const { m_psystem->__defer_construct_new(((material_object *)this)->m_pia); return *m_pia; }



