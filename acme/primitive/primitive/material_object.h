#pragma once


class CLASS_DECL_ACME material_object :
   virtual public matter
{
public:


   ::id                                m_id;


   material_object() { }
   material_object(const ::id & id) : m_id(id) {}
   material_object(const material_object & object);
   material_object(material_object && object) :
      matter(::move(object)),
      m_id(::move(object.m_id))
   {  }
   virtual ~material_object();




   template < typename TYPE >
   inline __pointer(TYPE) cast() { return this; }

   template < typename TYPE >
   inline __pointer(TYPE) cast() const { return (::property_object*)this; }

   template < typename TYPE >
   inline bool is() const { return cast < TYPE >(); }

   template < typename TYPE >
   inline __pointer(TYPE) cast(const ::id& id);


//   __transport(task) branch(
//      ::matter* pmatter,
//      ::e_priority epriority = priority_normal,
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);


};



