#pragma once


class CLASS_DECL_AURA context_object :
   virtual public context_object
{
public:


   __pointer(::traits)                    m_ptraits;


   inline context_object() {}
   context_object(e_default_init);
   //context_object(::object * pobject);
   virtual ~context_object();

   virtual ::aura::application * get_context_application() const;
   virtual ::object * get_object() const;


   void call_update(::u64 uId);
   virtual void call_update(::update * pupdate);
   virtual void update(::update * pupdate);
   virtual bool update((::update * pupdate);


   virtual void notify(::u64 uId) override;

   virtual ::object * source_channel() override;

   virtual ::file_result get_file(const var& varFile, efileopen eopen);
   virtual ::file_result get_reader(const var& varFile, efileopen eopen = ::file::mode_read | ::file::type_binary);
   virtual ::file_result get_writer(const var& varFile, efileopen eopen = ::file::mode_write | ::file::type_binary | ::file::defer_create_directory | ::file::mode_no_truncate | ::file::mode_create);


   inline bool is_ok() const
   {

      return has_id(OK);

   }



   virtual void add_handler(::u64 uId, ::context_object_pointer prunnable);


   template < typename TYPE >
   inline void add_handler(::u64 uId, TYPE * p, void (TYPE::* pprocedure)())
   {

      return add_handler(uId, __runnable_procedure(p, pprocedure));

   }


   template < typename TYPE >
   inline void add_handler(::u64 uId, void (TYPE::* pprocedure)())
   {

      return add_handler(uId, dynamic_cast < TYPE * > (this), pprocedure);

   }


   virtual string get_text(const var & var, id id);

   virtual property * parent_lookup_property(const id & id) const;

   virtual void set_trait_result(::u64 uId, ::u64 uTrait, ::context_object * preference);


   virtual void _notify(::trait * ptrait);


   virtual void _call_notify(::trait * ptrait);
   virtual thread_pointer _fork_notify(__pointer(::trait) ptrait);
   virtual thread_spa _fork_notify_each(__pointer(::trait) ptrait);


   inline void defer_traits();

   inline ::traits * traits() { defer_traits(); return m_ptraits; }

   inline bool is_traited(::u64 u, ::u64 uTrait);

   inline void set_action(const ::trait & traitPayload);

   inline void add_notification(const ::trait & traitPayload);

   context_object & operator =(const ::trait & trait)
   {

      this->set_action(trait);

      return *this;

   }

   context_object & operator +=(const ::trait & trait)
   {

      this->add_notification(trait);

      return *this;

   }


   virtual void property_set_replace(string & str) const;
   virtual string property_set_evaluate(const string & str) const;
   virtual string property_set_get_evaluation(const string & str) const;
   virtual string property_set_get_string(const string & str) const;


   virtual id translate_property_id(const ::id& id);

   virtual void add_property_set(property_set * pset);

   virtual property * fetch_property(const ::id & id, bool bCreate = true);

   virtual property * on_fetch_property(const ::id & id) const;

   virtual ::context_object * parent_property_set_holder() const;

   ::estatus  bind_update(property * pproperty);
   ::estatus  bind_update(const ::id & id, bool bCreate = true);
   ::estatus  bind_update(const ::id & id, ::object * pobject);


   inline ::papaya::topic topic(const ::id & id);


   
   

   __pointer(::papaya::ini) appini();







};





