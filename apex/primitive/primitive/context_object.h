//
//  context_object.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//
#pragma once


class object;
class runnable_array;


class CLASS_DECL_APEX context_object :
   virtual public layered
{
public:


   ::id                             m_id;
   __pointer(::i64_array)           m_pia;
   ::estatus                        m_estatus;
   __pointer(property_set)          m_pset;



   context_object() { }
   virtual ~context_object();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & action_context) const override;


   virtual ::estatus    initialize(::layered * pobjectContext) override;
   virtual void         finalize() override;


   



   
   template < typename TYPE >
   inline ::estatus __construct_new(__pointer(TYPE)& pbase);


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual ::estatus call() override;


   inline ::i64_array & idarray() const;


   inline bool is_shared() const { return m_countReference > 1; }


   inline bool is_status_ok() const { return (bool)m_estatus; }
   inline bool has_failed_status() const { return !is_status_ok(); }


   virtual ::estatus run() override;


   virtual ::object * source_channel();



   virtual void exchange(::stream & stream) override;


   virtual void add_exception(::exception::exception * pexception);
   virtual void on_catch_all_exception();


   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;

   
   template < typename TYPE >
   inline __pointer(TYPE) cast() {return this;}

   template < typename TYPE >
   inline __pointer(TYPE) cast() const {return (::context_object *) this;}

   template < typename TYPE >
   inline bool is() const {return cast < TYPE > ();}

   template < typename TYPE >
   inline __pointer(TYPE) cast(const ::id & id);


   template < typename PRED >
   void add_pred(runnable_array & array, PRED pred);

   inline bool has_property(const id & id) const;
   inline property * lookup_property(const id & id) const;
   inline bool remove_key(const id & id);

   inline property_set & get_property_set();
   inline const property_set & get_property_set() const;
   inline bool contains(const ::property_set & set) const;

   inline var & value(const ::id & id);

   using elemental::set;

   template < typename TYPE >
   inline void set(const ::id & id, const TYPE & t);

   template < typename TYPE >
   inline void get(const ::id & id, TYPE & t);

   inline var topic(const ::id & id);

   inline property * find_property(const ::id & id) const;

   ::status::result run_property(const ::id& id);

   inline var attribute(const ::id & id);
   ::property * find_attribute(const ::id & id);

   template < typename TYPE >
   inline bool find_attribute(const ::id & id, TYPE & t);

   inline var find_value(const ::id & id) const;
   inline var find_value(const ::id & id, const var & varDefault) const;

   using elemental::get_context_object;
   inline var & get_context_object(const ::id & id);

   inline var operator()(const ::id & id) const;
   inline var operator()(const ::id & id, const var & varDefault) const;

   inline var & operator[](const ::id & id);

   inline var operator[](const ::id & id) const;

   inline var value(const ::id & id) const;
   inline var value(const ::id & id, const var & varDefault) const;

   inline string find_string(const ::id & id, const ansichar * pszDefault = nullptr) const;

   inline ::i32 find_i32(const ::id & id, ::i32 iDefault = 0) const;

   inline ::u32 find_u32(const ::id & id, ::u32 iDefault = 0) const;

   template < typename TYPE > inline TYPE & get_cast(const ::id & id, TYPE * pDefault = nullptr);

   template < typename TYPE > inline __pointer(TYPE) cast(const ::id & id) const;

   inline void defer_propset();

   inline bool is_true(const ::id & id) const;
   inline bool is_false(const ::id & id) const;
   inline bool is_true(const ::id & id, const var & varDefault, bool bDefault) const;

   virtual string get_text(const var & var, const ::id & id);

   virtual property * parent_lookup_property(const id & id) const;

   virtual void property_set_replace(string & str) const;
   virtual string property_set_evaluate(const string & str) const;
   virtual string property_set_get_evaluation(const string & str) const;
   virtual string property_set_get_string(const string & str) const;
   virtual bool property_set_get_string(string & strResult, const string& str) const;
   virtual bool property_set_get_evaluation(string & strResult, const string& str) const;

   virtual id translate_property_id(const ::id & id);

   virtual void add_property_set(property_set * pset);

   virtual property * fetch_property(const ::id & id, bool bCreate = true);

   virtual property * on_fetch_property(const ::id & id) const;

   virtual ::object * parent_property_set_holder() const;

   virtual void to_string(const string_exchange & str) const override;
   virtual strsize sz_len() const override;
   virtual void to_sz(char * sz, strsize len) const override;

   virtual void call_update(const ::__id& id, const ::action_context& context) override;
   virtual void call_update(const ::__id& id) override;
   virtual void call_update(::update* pupdate) override;


};


using reference_pointer = __pointer(::context_object);


#define __add_runnable(array, ID) add_pred(array, [this]() { ID(); } )



template < typename TYPE > inline __pointer(TYPE) __cast(::elemental * p) { return dynamic_cast <TYPE *> (p); }
   
