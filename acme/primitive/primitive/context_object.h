//
//  context_object.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//
#pragma once


class object;
//class runnable_array;


class CLASS_DECL_ACME context_object :
   virtual public id_matter
{
public:


   ::e_status                          m_estatus;
   __pointer(::layered)                m_pobjectContext;
   __pointer(::i64_array)              m_pia;
   __pointer(property_set)             m_pset;
   __pointer(matter_array)             m_pnotifya;


   context_object() { }
   context_object(const ::id& id) : id_matter(id) {}
   context_object(const context_object & object);
   context_object(context_object && object) :
      id_matter(::move(object)),
      m_pia(::move(object.m_pia)),
      m_estatus(object.m_estatus),
      m_pset(::move(object.m_pset))
      {  }
   virtual ~context_object();


   inline matter_array * _notify_array() { return m_pnotifya; }


   inline matter_array & notify_array() { ::__defer_construct_new(m_pnotifya); return *m_pnotifya; }


   virtual void assert_valid() const override;
   virtual void dump(dump_context & action_context) const override;


   virtual ::e_status    initialize(::layered * pobjectContext) override;
   virtual void         finalize() override;


   virtual ::context_object * _get_context_object() override;


   virtual void notify_on_finish(::context_object * pcontextobjectFinish) override;


   inline ::object * get_context_object() const { return __object(m_pobjectContext); }
   virtual void set_context_object(::layered * pobjectContext OBJ_REF_DBG_COMMA_PARAMS);



   virtual ::e_status finish(::context_object * pcontextobjectFinish = nullptr) override;



   virtual void on_finish() override;
   


   template < typename TYPE >
   inline ::e_status __construct_new(__pointer(TYPE)& pusermessage);


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual ::e_status operator()() override;


   inline ::i64_array & idarray() const;


   inline bool is_shared() const { return m_countReference > 1; }


   inline bool is_status_ok() const { return (bool)m_estatus; }
   inline bool has_failed_status() const { return !is_status_ok(); }


   virtual ::e_status run() override;


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



   inline bool has_property(const id & id) const;
   inline property * lookup_property(const id & id) const;
   inline bool remove_key(const id & id);

   inline property_set & get_property_set();
   inline const property_set & get_property_set() const;
   inline bool contains(const ::property_set & set) const;

   using matter::set;

   template < typename TYPE >
   inline void set(const ::id & id, const TYPE & t);

   template < typename TYPE >
   inline void get(const ::id & id, TYPE & t);

   inline ::payload topic(const ::id & id);

   inline property * find_property(const ::id & id) const;

   ::status::result run_property(const ::id& id);

   inline ::payload attribute(const ::id & id);
   ::property * find_attribute(const ::id & id);

   template < typename TYPE >
   inline bool find_attribute(const ::id & id, TYPE & t);



   //using matter::get_context_object;
   inline ::payload & get_context_object(const ::id & id);

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

   template < typename TYPE > inline __pointer(TYPE) cast(const ::id & id) const;

   inline void defer_propset();

   inline bool is_true(const ::id & id) const;
   inline bool is_false(const ::id & id) const;
   inline bool is_true(const ::id & id, const ::payload & varDefault, bool bDefault) const;

   virtual string get_text(const ::payload & payload, const ::id & id);

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

   virtual ::context_object * parent_property_set_holder() const;

   virtual void to_string(const string_exchange & str) const override;
   virtual strsize sz_len() const override;
   virtual void to_sz(char * sz, strsize len) const override;

   //virtual void call_update(const ::__id& id, const ::action_context& context) override;
   //virtual void call_update(const ::__id& id) override;
   //virtual void call_update(::machine * pchange) override;


};


using reference_pointer = __pointer(::context_object);


#define __add_runnable(array, ID) add_pred(array, [this]() { ID(); } )



template < typename TYPE > inline __pointer(TYPE) __cast(::matter * p) { return dynamic_cast <TYPE *> (p); }

