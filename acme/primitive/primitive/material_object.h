#pragma once


class CLASS_DECL_ACME material_object :
   virtual public ::property_object
{
public:


   __pointer(::id_map < ::routine_array >)         m_pmapPropertyRoutine;
   __pointer(::i64_array)                          m_pia;


   material_object() { }
   material_object(const ::atom & atom) : PARTICLE(atom), ::particle(atom), ::property_object(atom) {}
   material_object(const material_object & object);
   material_object(material_object && materialobject) :
      ::PARTICLE(::move(materialobject)),
      ::particle(::move(materialobject)),
      ::element(::move(materialobject)),
      ::matter(::move(materialobject)),
      ::property_object(::move(materialobject)),
      m_pmapPropertyRoutine(::move(materialobject.m_pmapPropertyRoutine)),
      m_pia(::move(materialobject.m_pia))
   {  }
   ~material_object() override;


   virtual ::string get_string() const;

   using ::property_object::cast;

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

   void destroy() override;


   virtual bool is_branch_current() const;


   virtual void post_routine(const ::routine & routine);


   virtual void send_routine(const ::routine & routine);


   template < typename POSTING_OBJECT, typename POSTING_METHOD, typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_REFERENCE >
   bool __send_payload(POSTING_OBJECT pposting, POSTING_METHOD posting_method, OBJECT_POINTER pobject, OBJECT_METHOD objectmethod, PAYLOAD_REFERENCE & payload);

   template < typename POSTING_OBJECT, typename POSTING_METHOD >
   void __send_routine(POSTING_OBJECT pposting, POSTING_METHOD posting_method, const ::routine & routine);



   ::routine_array * routine_array(const ::atom & atom, bool bCreate = false);


   void add_routine(const ::atom & atom, const ::routine & routine);



   inline ::i64_array & idarray() const;





};



template < typename TYPE >
class ___matter :
   virtual public TYPE,
   virtual public ::matter
{
public:


};


#define __matter(TYPE) __new(::___matter < TYPE > )



