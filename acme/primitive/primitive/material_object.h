#pragma once


class CLASS_DECL_ACME material_object :
   virtual public matter
{
public:


   ::id                                m_id;
   ::e_status                          m_estatus;


   material_object() { }
   material_object(const ::id & id) : m_id(id) {}
   material_object(const material_object & object);
   material_object(material_object && object) :
      matter(::move(object)),
      m_id(::move(object.m_id))
   {  }
   ~material_object() override;


   virtual ::string get_string() const;

   template < typename TYPE >
   inline __pointer(TYPE) cast() { return this; }

   template < typename TYPE >
   inline __pointer(TYPE) cast() const { return (::property_object*)this; }

   template < typename TYPE >
   inline bool is_a() const { return cast < TYPE >(); }

   
   
   //// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
   virtual ::e_status handle_command(const ::id & id);



//   __transport(task) branch(
//      ::matter* pmatter,
//      ::enum_priority epriority = e_priority_normal,
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);



   template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_REFERENCE >
   auto  __sync_status_payload(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD objectmethod, PAYLOAD_REFERENCE & payload);

   //template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename MEMBER_POINTER >
   //::e_status  __sync_member(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD objectmethod, MEMBER_POINTER ppayload);

   //template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD >
   //::e_status  __sync_member(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, OBJECT_POINTER pobject, OBJECT_METHOD objectmethod);

   template < typename BRANCHING_OBJECT, typename BRANCHING_METHOD >
   ::e_status __sync_routine(const ::duration & duration, BRANCHING_OBJECT pbranching, BRANCHING_METHOD branching_method, ::routine routine);


};



template < typename TYPE >
class ___matter :
   virtual public TYPE,
   virtual public ::matter
{
public:


};


#define __matter(TYPE) __new(::___matter < TYPE > )



