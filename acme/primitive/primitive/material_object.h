#pragma once


class CLASS_DECL_ACME material_object :
   virtual public ::property_object
{
public:


   pointer< ::id_map < ::procedure_array > >       m_pmapPropertyProcedure;
   ::pointer<::i64_array>                          m_pia;


   material_object() { }
   //material_object(const ::atom & atom) : PARTICLE(atom), ::particle(atom), ::property_object(atom) {}
   material_object(const material_object & object);
   //material_object(material_object && materialobject) :
   //   ::PARTICLE(::move(materialobject)),
   //   ::particle(::move(materialobject)),
   //   ::element(::move(materialobject)),
   //   ::matter(::move(materialobject)),
   //   ::property_object(::move(materialobject)),
   //   m_pmapPropertyProcedure(::move(materialobject.m_pmapPropertyProcedure)),
   //   m_pia(::move(materialobject.m_pia))
   //{  }
   ~material_object() override;


   virtual ::string as_string() const;

   using ::property_object::cast;

   template < typename TYPE >
   inline ::pointer<TYPE>cast() { return this; }

   template < typename TYPE >
   inline ::pointer<TYPE>cast() const { return (::property_object*)this; }

   template < typename TYPE >
   inline bool is_a() const { return cast < TYPE >(); }

   
   
   //// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
   virtual void handle_command(const ::atom & atom);



//   ::pointer<task>branch(
//      ::matter* pmatter,
//      ::enum_priority epriority = e_priority_normal,
//      u32 nStackSize = 0,
//      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   void destroy() override;


   virtual bool is_branch_current() const;


   virtual void post_procedure(const ::procedure & procedure);


   virtual void send_procedure(const ::procedure & procedure);

   //virtual bool __get_posted_payload_synchronously(::matter * pposting, POSTING_PROCEDURE * posting_method, ::matter * preturning, RETURNING_PROCEDURE * returning_method, ::payload & payload, const class ::wait & wait);

   //virtual void __send_procedure(::matter * pposting, POSTING_PROCEDURE * posting_method, const ::procedure & procedure);

   virtual bool __get_posted_payload_synchronously(const ::function < void(const ::procedure &) > & functionPost, const ::function < ::payload(void) > & functionReturn, ::payload & payload);

   virtual void __send_procedure(const ::function < void(const ::procedure &) > & functionPost, const ::procedure & procedure);



   ::procedure_array * procedure_array(const ::atom & atom, bool bCreate = false);


   void add_procedure(const ::atom & atom, const ::procedure & procedure);


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



