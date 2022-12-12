//
//  property_object.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/06/19.
//
#pragma once


#include "matter.h"
#include "linked_property.h"
#include "payload.h"


class object;


class CLASS_DECL_ACME property_object :
   virtual public ::matter
{
public:


   ::pointer<property_set>                        m_ppropertyset;


   property_object() { }
   ~property_object() override;


   void destroy() override;


   virtual void notify_on_destroy(::property_object * pcontextobjectFinish) override;


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


   void call_run() override;


   virtual void run() override;


   virtual ::object * source_channel();



   //virtual void exchange(::stream & stream) override;
   //virtual void exchange(::payload_stream& stream) override;


   virtual void handle_exception(const ::exception& e);


   virtual void add_exception(const ::exception & e);
   virtual void on_catch_all_exception();



   //virtual stream & write(::stream & stream) const override;
   //virtual stream & read(::stream & stream) override;








//#ifdef GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS
//
//   inline GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & _routine_array(const ::atom& atom);
//
//   inline GGCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & ::procedure_array(const ::atom & atom);
//
//#else

   //inline ::procedure_array * _routine_array(const ::atom& atom);

//#endif



   bool has_property(const atom & atom) const;
   property * lookup_property(const atom & atom) const;
   bool erase_key(const atom & atom);

   property_set & get_property_set();
   const property_set & get_property_set() const;
   bool contains(const ::property_set & set) const;

   using matter::set_flag;

//   template < typename TYPE >
//   inline void set(const ::atom & atom, const TYPE & t);
//
//   template < typename TYPE >
//   inline void get(const ::atom & atom, TYPE & t);

   ::payload & topic(const ::atom & atom);

   property * find_property(const ::atom & atom) const;

   //::extended::status run_property(const ::atom& atom);

   void run_property(const ::atom& atom);

   ::payload attribute(const ::atom & atom);
   ::property * find_attribute(const ::atom & atom);

   template < typename TYPE >
   inline bool find_attribute(const ::atom & atom, TYPE & t);

   ::payload & get_object(const ::atom & atom);

   ::payload operator()(const ::atom & atom) const;
   ::payload operator()(const ::atom & atom, const ::payload & varDefault) const;

   ::payload & operator[](const ::atom & atom);

   ::payload operator[](const ::atom & atom) const;

   ::payload & payload(const ::atom & atom);

   ::payload payload(const ::atom & atom) const;
   ::payload payload(const ::atom & atom, const ::payload & varDefault) const;

   ::payload find_payload(const ::atom & atom) const;
   ::payload find_payload(const ::atom & atom, const ::payload & varDefault) const;

   string find_string(const ::atom & atom, const ::ansi_character * pszDefault = nullptr) const;

   ::i32 find_i32(const ::atom & atom, ::i32 iDefault = 0) const;

   ::u32 find_u32(const ::atom & atom, ::u32 iDefault = 0) const;

   template < typename TYPE > inline TYPE & get_cast(const ::atom & atom, TYPE * pDefault = nullptr);

   //using material_object::cast;

   template < typename TYPE > inline ::pointer<TYPE>cast(const ::atom & atom) const;

   void defer_propset();

   bool is_true(const ::atom & atom, bool bDefault = false) const;
   bool is_false(const ::atom & atom) const;
   //inline bool is_true(const ::atom & atom, const ::payload & varDefault, bool bDefault) const;

   //virtual string get_text(const ::payload & payload, const ::atom & atom);

   virtual linked_property parent_lookup_property(const atom & atom) const;

   virtual void property_set_replace(string & str) const;
   virtual string property_set_evaluate(const ::string & str) const;
   virtual string property_set_get_evaluation(const ::string & str) const;
   virtual string property_set_get_string(const ::string & str) const;
   virtual bool property_set_get_string(string & strResult, const string& str) const;
   virtual bool property_set_get_evaluation(string & strResult, const string& str) const;

   virtual atom translate_property_id(const ::atom & atom);

   virtual void notify_property_changed(property* pproperty, const ::action_context& actioncontext);

   virtual void on_property_changed(property * pproperty, const ::action_context& actioncontext);

   virtual ::linked_property fetch_property(const ::atom & atom, bool bCreate = true);

   virtual ::linked_property on_fetch_property(const ::atom & atom) const;

   virtual ::property_object * parent_property_set_holder() const;


};


using reference_pointer = ::pointer<::property_object>;


#define __add_runnable(array, ID) add_predicate(array, [this]() { ID(); } )



//template < typename TYPE > 
//inline ::pointer<TYPE> __cast(::element * p)
//{ 
//   
//   return dynamic_cast <TYPE *> (p); 
//
//}



template < typename TYPE > inline ::pointer<TYPE>property_object::cast(const ::atom & atom) const
{

   auto pproperty = find_property(atom);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


