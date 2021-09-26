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
   virtual public material_object
{
public:


   ::e_status                                      m_estatus;
   __pointer(::id_map < ::routine_array >)         m_pmapPropertyRoutine;
   __pointer(::i64_array)                          m_pia;
   __pointer(property_set)                         m_ppropertyset;


   property_object() { }
   property_object(const ::id& id) : material_object(id) {}
   property_object(const property_object & object);
   property_object(property_object && object) :
      material_object(::move(object)),
      m_pia(::move(object.m_pia)),
      m_estatus(object.m_estatus),
      m_ppropertyset(::move(object.m_ppropertyset))
      {  }
   ~property_object() override;




   ::e_status destroy() override;


   virtual void notify_on_destroy(::property_object * pcontextobjectFinish) override;


   //::e_status destroy() override;


   //virtual ::e_status on_finish() override;
   

   template < typename TYPE >
   inline ::e_status __construct_new(__pointer(TYPE)& pusermessage);


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual ::e_status operator()() override;




   virtual ::e_status run() override;


   virtual ::object * source_channel();



   virtual void exchange(::stream & stream) override;


   virtual ::e_status handle_exception(const ::exception& e);


   virtual void add_exception(const ::exception & e);
   virtual void on_catch_all_exception();



   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;




   inline bool is_status_ok() const { return m_estatus; }
   inline bool has_failed_status() const { return !is_status_ok(); }




//#ifdef GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS
//
//   inline GCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & _routine_array(const ::id& id);
//
//   inline GGCC_PORKBARBECUE_AND_🐷PIGŽ_CPP_ALMOST_STILL_C_BECAUSE_OF_LINUX_TORRVARUDUS_routine_array & routine_array(const ::id & id);
//
//#else

   inline ::routine_array & _routine_array(const ::id& id);

   inline ::routine_array & routine_array(const ::id& id);

//#endif


   inline void add_routine(const ::id& id, const ::routine& routine);



   inline ::i64_array& idarray() const;





   inline bool has_property(const id & id) const;
   inline property * lookup_property(const id & id) const;
   inline bool erase_key(const id & id);

   inline property_set & get_property_set();
   inline const property_set & get_property_set() const;
   inline bool contains(const ::property_set & set) const;

   using matter::set;

//   template < typename TYPE >
//   inline void set(const ::id & id, const TYPE & t);
//
//   template < typename TYPE >
//   inline void get(const ::id & id, TYPE & t);

   inline ::payload & topic(const ::id & id);

   inline property * find_property(const ::id & id) const;

   ::extended::status run_property(const ::id& id);

   inline ::payload attribute(const ::id & id);
   ::property * find_attribute(const ::id & id);

   template < typename TYPE >
   inline bool find_attribute(const ::id & id, TYPE & t);

   inline ::payload & get_object(const ::id & id);

   inline ::payload operator()(const ::id & id) const;
   inline ::payload operator()(const ::id & id, const ::payload & varDefault) const;

   inline ::payload & operator[](const ::id & id);

   inline ::payload operator[](const ::id & id) const;

   inline ::payload & payload(const ::id & id);

   inline ::payload payload(const ::id & id) const;
   inline ::payload payload(const ::id & id, const ::payload & varDefault) const;

   inline ::payload find_payload(const ::id & id) const;
   inline ::payload find_payload(const ::id & id, const ::payload & varDefault) const;

   inline string find_string(const ::id & id, const ansichar * pszDefault = nullptr) const;

   inline ::i32 find_i32(const ::id & id, ::i32 iDefault = 0) const;

   inline ::u32 find_u32(const ::id & id, ::u32 iDefault = 0) const;

   template < typename TYPE > inline TYPE & get_cast(const ::id & id, TYPE * pDefault = nullptr);

   using material_object::cast;

   template < typename TYPE > inline __pointer(TYPE) cast(const ::id & id) const;

   inline void defer_propset();

   inline bool is_true(const ::id & id) const;
   inline bool is_false(const ::id & id) const;
   inline bool is_true(const ::id & id, const ::payload & varDefault, bool bDefault) const;

   virtual string get_text(const ::payload & payload, const ::id & id);

   virtual linked_property parent_lookup_property(const id & id) const;

   virtual void property_set_replace(string & str) const;
   virtual string property_set_evaluate(const ::string & str) const;
   virtual string property_set_get_evaluation(const ::string & str) const;
   virtual string property_set_get_string(const ::string & str) const;
   virtual bool property_set_get_string(string & strResult, const string& str) const;
   virtual bool property_set_get_evaluation(string & strResult, const string& str) const;

   virtual id translate_property_id(const ::id & id);

   virtual void notify_property_changed(property* pproperty, const ::action_context& actioncontext);

   virtual void on_property_changed(property * pproperty, const ::action_context& actioncontext);

   virtual ::linked_property fetch_property(const ::id & id, bool bCreate = true);

   virtual ::linked_property on_fetch_property(const ::id & id) const;

   virtual ::property_object * parent_property_set_holder() const;


};


using reference_pointer = __pointer(::property_object);


#define __add_runnable(array, ID) add_predicate(array, [this]() { ID(); } )



template < typename TYPE > inline __pointer(TYPE) __cast(::matter * p) { return dynamic_cast <TYPE *> (p); }

