#pragma once


class CLASS_DECL_ACME material_object :
   virtual public matter
{
public:


   ::atom                                m_id;
   ::e_status                         m_estatus;


   material_object() { }
   material_object(const ::atom & atom) : m_id(atom) {}
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
   virtual void handle_command(const ::atom & atom);



//   __pointer(task) branch(
//      ::matter* pmatter,
//      ::enum_priority epriority = e_priority_normal,
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);


   virtual bool is_branch_current() const;


   virtual void post_routine(const ::routine & routine);


   virtual void send_routine(const ::routine & routine);


   template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_REFERENCE >
   bool __send_payload(POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER pobject, OBJECT_METHOD objectmethod, PAYLOAD_REFERENCE & payload);

   template < typename POSTING_OBJECT, typename POSTING_METHOD >
   void __send_routine(POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::routine & routine);


};



template < typename TYPE >
class ___matter :
   virtual public TYPE,
   virtual public ::matter
{
public:


};


#define __matter(TYPE) __new(::___matter < TYPE > )



