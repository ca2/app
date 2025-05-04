//
//  property_object.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/06/19.
//
#pragma once


#include "matter.h"
//#include "linked_property.h"
#include "acme/prototype/string/scoped_string_base.h"
#include "payload.h"


class object;


class CLASS_DECL_ACME property_object :
   virtual public ::matter
{
public:


   ::pointer<::property_set>                        m_ppropertyset;


   property_object() { }
   ~property_object() override;


   void destroy() override;


   virtual void notify_on_destroy(::property_object * pcontextobjectFinish) override;


   virtual void ping();
   virtual void on_ping();
   virtual bool is_pinging() const;


   //void call() override;


   //virtual void run() override;


   virtual ::object * source_channel();



   //virtual void exchange(::stream & stream) override;
   //virtual void exchange(::payload_stream& stream) override;


   virtual void handle_exception(const ::exception& e);


   virtual void add_exception(const ::exception & e);
   virtual void on_catch_all_exception();



   //virtual stream & write(::stream & stream) const override;
   //virtual stream & read(::stream & stream) override;








//#ifdef GCC_PORKBARBECUE_AND_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS
//
//   inline GCC_PORKBARBECUE_AND_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & _routine_array(const ::atom& atom);
//
//   inline GGCC_PORKBARBECUE_AND_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & ::procedure_array(const ::atom & atom);
//
//#else

   //inline ::procedure_array * _routine_array(const ::atom& atom);

//#endif

   virtual ::string get_object_file_name();

   virtual ::file::path get_ini_configuration_path();

   virtual bool include_hostname_in_configuration_path();

   virtual void read_ini_configuration();
   virtual void write_ini_configuration();

   virtual void read_configuration_from_ini(const ::payload & payloadFile);
   virtual void write_configuration_to_ini(const ::payload & payloadFile);

   bool has_property(const atom & atom) const;
   ::property * lookup_property(const atom & atom) const;
   bool erase_key(const atom & atom);

   ::property_set & property_set();
   bool has_property_set() const;
   bool contains(const ::property_set & set) const;

   using matter::set_flag;

//   template < typename TYPE >
//   inline void set(const ::atom & atom, const TYPE & t);
//
//   template < typename TYPE >
//   inline void get(const ::atom & atom, TYPE & t);

   //::payload & topic(const ::atom & atom);

   ::collection::index index_of_property(const ::atom & atom) const;

   //::extended::status run_property(const ::atom& atom);

   void defer_run_property(const ::atom& atom);

   ::collection::index index_of_attribute(const ::atom & atom);
   ::property & lookup_attribute(const ::atom& atom);
   ::property& attribute(const ::atom& atom);

   template < typename TYPE >
   inline bool lookup_attribute(const ::atom & atom, TYPE & t);

   template < typename TYPE >
   inline TYPE & get_attribute(const ::atom& atom, TYPE& t);

   //::payload & get_object(const ::atom & atom);

   //::payload operator()(const ::atom & atom) const;
   //::payload operator()(const ::atom & atom, const ::payload & payloadDefault) const;

   //::payload & operator[](const ::atom & atom);

   //::payload operator[](const ::atom & atom) const;

   ::property & property(const ::atom & atom);

   ::property & property(const ::atom & atom) const
   {

      return ((::property_object *)this)->property(atom);

   }


   ::payload get_payload(const ::atom & atom, const ::payload & payloadDefault) const;


   ::payload& payload(const ::atom& atom) { return this->property(atom); }

   ::payload payload(const ::atom & atom) const { return this->property(atom); }
   //::payload payload(const ::atom & atom, const ::payload & payloadDefault) const;

   ::collection::index index_of_payload(const ::atom & atom) const;
   //::payload find_payload(const ::atom & atom, const ::payload & payloadDefault) const;


   string get_string(const ::atom& atom, const ::scoped_string& scopedstrDefault = {}) const;

   int get_int(const ::atom & atom, int iDefault = 0) const;

   unsigned int get_unsigned_int(const ::atom & atom, unsigned int uDefault = 0) const;

   //template < typename TYPE > inline TYPE & get_cast(const ::atom & atom, TYPE * pDefault = nullptr);

   using matter::cast;

   template < ::primitive_subparticle TYPE > 
   inline TYPE * cast(const ::atom & atom) const;

   void defer_propset();

   bool is_true(const ::atom & atom) const;
   bool is_false(const ::atom & atom) const;
   bool is_true_or_empty(const ::atom & atom) const;
   //inline bool is_true(const ::atom & atom, const ::payload & payloadDefault, bool bDefault) const;

   //virtual string get_text(const ::payload & payload, const ::atom & atom);

   //virtual linked_property parent_lookup_property(const atom & atom) const;

   virtual void property_set_replace(string & str) const;
   virtual string property_set_evaluate(const ::string & str) const;
   virtual string property_set_get_evaluation(const ::string & str) const;
   virtual string property_set_get_string(const ::string & str) const;
   virtual bool property_set_get_string(string & strResult, const string& str) const;
   virtual bool property_set_get_evaluation(string & strResult, const string& str) const;

   //virtual atom translate_property_id(const ::atom & atom);

   virtual void notify_property_changed(::property* pproperty, const ::action_context& actioncontext);

   virtual void on_property_changed(::property * pproperty, const ::action_context& actioncontext);

   //virtual ::linked_property fetch_property(const ::atom & atom, bool bCreate = true);

   //virtual ::linked_property on_fetch_property(const ::atom & atom) const;

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



template < primitive_subparticle TYPE >
inline TYPE * property_object::cast(const ::atom & atom) const
{

   auto pproperty = this->lookup_property(atom);

   if (!pproperty)
   {

      return nullptr;

   }

   return pproperty->cast < TYPE >();

}


