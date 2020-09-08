#pragma once


inline property * generic::find_property(const id & id) const
{

   if (!m_pset)
   {

      return nullptr;

   }

   return m_pset->find(id);

}


inline string generic::find_string(const ::id & id, const ansichar * pszDefault) const
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


inline ::i32 generic::find_i32(const ::id & id, ::i32 iDefault) const
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


inline ::u32 generic::find_u32(const ::id & id, ::u32 iDefault) const
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


template < typename TYPE > inline TYPE & generic::get_cast(const ::id & id, TYPE * pDefault)
{

   return value(id).get_cast <TYPE>(pDefault);

}


template < typename TYPE > inline __pointer(TYPE) generic::cast(const ::id & id) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


inline var & generic::value(const id & id)
{

   auto & set = get_property_set();

   return set.get(id);

}


inline bool generic::is_true(const ::id & id) const
{

   return m_pset && value(id).is_true();

}


inline bool generic::is_false(const ::id& id) const
{

   return !is_true(id);

}


inline bool generic::is_true(const ::id & id, const var & varDefault, bool bDefault = false) const
{

   return value(id).is_true(varDefault, bDefault);

}


inline var & generic::operator[](const ::id & id) { return value(id); }

inline var generic::operator[](const ::id & id) const { return find_property(id); }

inline var generic::value(const ::id & id) const { return find_property(id); }

inline var generic::value(const ::id & id, const var & varDefault) const { return operator()(id, varDefault); }

inline var generic::operator()(const ::id & id) const { return find_value(id, ::error_not_found); }

inline var generic::operator()(const ::id & id, const var & varDefault) const { return find_value(id, varDefault); }

inline var generic::find_value(const ::id & id) const { return find_value(id, ::error_not_found); }

inline var generic::find_value(const ::id & id, const var & varDefault) const
{

   auto pproperty = find_property(id);

   if (!pproperty)
   {

      return varDefault;

   }

   return pproperty;

}

inline var generic::attribute(const ::id & id) { return value(id); }

inline ::property * generic::find_attribute(const ::id & id) { return find_property(id); }

template < typename TYPE >
inline bool generic::find_attribute(const ::id & id, TYPE & t)
{

   auto p = find_property(id);

   if (!p)
   {

      return false;

   }

   t = *p;

   return true;

}


inline var & generic::get_context_object(const ::id & id)
{

   auto pproperty = &value(id);

   if (!pproperty)
   {

      __throw(resource_exception());

   }

   return *pproperty;

}

