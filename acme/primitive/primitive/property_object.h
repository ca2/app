//
//  property_object.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//
#pragma once


class object;
//class runnable_array;


class CLASS_DECL_ACME property_object :
   virtual public ::matter
{
public:


   __pointer(property_set)                         m_ppropertyset;


   property_object() { }
   property_object(const ::atom& atom) : PARTICLE(atom), ::particle(atom) {}
   property_object(const property_object & propertyobject);
   property_object(property_object && propertyobject) :
      ::PARTICLE(::move(propertyobject)),
      ::particle(::move(propertyobject)),
      ::element(::move(propertyobject)),
      ::matter(::move(propertyobject)),
      m_ppropertyset(::move(propertyobject.m_ppropertyset))
      {  }
   ~property_object() override;




   void destroy() override;


   virtual void notify_on_destroy(::property_object * pcontextobjectFinish) override;


   //void destroy() override;


   //virtual void on_finish() override;
   

   template < typename TYPE >
   inline void __construct_new(__pointer(TYPE)& pusermessage);


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual void operator()() override;




   virtual void run() override;


   virtual ::object * source_channel();



   virtual void exchange(::stream & stream) override;
   virtual void exchange(::payload_stream& stream) override;


   virtual void handle_exception(const ::exception& e);


   virtual void add_exception(const ::exception & e);
   virtual void on_catch_all_exception();



   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;




   inline bool is_status_ok() const { return m_estatus; }
   inline bool has_failed_status() const { return !is_status_ok(); }




//#ifdef GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS
//
//   inline GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & _routine_array(const ::atom& atom);
//
//   inline GGCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & routine_array(const ::atom & atom);
//
//#else

   //inline ::routine_array * _routine_array(const ::atom& atom);

//#endif



   inline bool has_property(const atom & atom) const;
   inline property * lookup_property(const atom & atom) const;
   inline bool erase_key(const atom & atom);

   inline property_set & get_property_set();
   inline const property_set & get_property_set() const;
   inline bool contains(const ::property_set & set) const;

   using matter::set;

//   template < typename TYPE >
//   inline void set(const ::atom & atom, const TYPE & t);
//
//   template < typename TYPE >
//   inline void get(const ::atom & atom, TYPE & t);

   inline ::payload & topic(const ::atom & atom);

   inline property * find_property(const ::atom & atom) const;

   //::extended::status run_property(const ::atom& atom);

   void run_property(const ::atom& atom);

   inline ::payload attribute(const ::atom & atom);
   ::property * find_attribute(const ::atom & atom);

   template < typename TYPE >
   inline bool find_attribute(const ::atom & atom, TYPE & t);

   inline ::payload & get_object(const ::atom & atom);

   inline ::payload operator()(const ::atom & atom) const;
   inline ::payload operator()(const ::atom & atom, const ::payload & varDefault) const;

   inline ::payload & operator[](const ::atom & atom);

   inline ::payload operator[](const ::atom & atom) const;

   inline ::payload & payload(const ::atom & atom);

   inline ::payload payload(const ::atom & atom) const;
   inline ::payload payload(const ::atom & atom, const ::payload & varDefault) const;

   inline ::payload find_payload(const ::atom & atom) const;
   inline ::payload find_payload(const ::atom & atom, const ::payload & varDefault) const;

   inline string find_string(const ::atom & atom, const ansichar * pszDefault = nullptr) const;

   inline ::i32 find_i32(const ::atom & atom, ::i32 iDefault = 0) const;

   inline ::u32 find_u32(const ::atom & atom, ::u32 iDefault = 0) const;

   template < typename TYPE > inline TYPE & get_cast(const ::atom & atom, TYPE * pDefault = nullptr);

   //using material_object::cast;

   template < typename TYPE > inline __pointer(TYPE) cast(const ::atom & atom) const;

   inline void defer_propset();

   inline bool is_true(const ::atom & atom) const;
   inline bool is_false(const ::atom & atom) const;
   inline bool is_true(const ::atom & atom, const ::payload & varDefault, bool bDefault) const;

   virtual string get_text(const ::payload & payload, const ::atom & atom);

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


using reference_pointer = __pointer(::property_object);


#define __add_runnable(array, ID) add_predicate(array, [this]() { ID(); } )



template < typename TYPE > inline __pointer(TYPE) __cast(::matter * p) { return dynamic_cast <TYPE *> (p); }

