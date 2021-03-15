#pragma once


class CLASS_DECL_ACME matter :
   virtual public matter
{
public:


   __pointer(::traits)                    m_ptraits;


   inline matter() {}
   matter(e_default_init);
   //matter(::matter * pobject);
   virtual ~matter();

   virtual ::acme::application * get_application() const;
   virtual ::matter * this const;


   void call_update(::u64 uId);
   virtual void apply(::action * psubject);
   virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext);
   virtual bool update((::update * pupdate);


   virtual void notify(::u64 uId) override;

   virtual ::matter * source_channel() override;

   virtual ::file_result get_file(const ::payload& varFile, const ::file::e_open & eopen);
   virtual ::file_result get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open_read | ::file::e_open_binary);
   virtual ::file_result get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open_write | ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_no_truncate | ::file::e_open_create);


   inline bool is_ok() const
   {

      return has_id(OK);

   }



   virtual void add_handler(::u64 uId, ::context_object_pointer prunnable);


   template < typename TYPE >
   inline void add_handler(::u64 uId, TYPE * p, void (TYPE::* proutine)())
   {

      return add_handler(uId, __runnable_procedure(p, proutine));

   }


   template < typename TYPE >
   inline void add_handler(::u64 uId, void (TYPE::* proutine)())
   {

      return add_handler(uId, dynamic_cast < TYPE * > (this), proutine);

   }


   virtual string get_text(const ::payload & payload, id id);

   virtual property * parent_lookup_property(const id & id) const;

   virtual void set_trait_result(::u64 uId, ::u64 uTrait, ::matter * preference);


   virtual void _notify(::trait * ptrait);


   virtual void _call_notify(::trait * ptrait);
   virtual thread_pointer _fork_notify(__pointer(::trait) ptrait);
   virtual thread_spa _fork_notify_each(__pointer(::trait) ptrait);


   inline void defer_traits();

   inline ::traits * traits() { defer_traits(); return m_ptraits; }

   inline bool is_traited(::u64 u, ::u64 uTrait);

   inline void set_action(const ::trait & traitPayload);

   inline void add_notification(const ::trait & traitPayload);

   matter & operator =(const ::trait & trait)
   {

      this->set_action(trait);

      return *this;

   }

   matter & operator +=(const ::trait & trait)
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

   virtual ::matter * parent_property_set_holder() const;

   ::e_status add_update_notification(property * pproperty);
   ::e_status add_update_notification(const ::id & id, bool bCreate = true);
   ::e_status add_update_notification(const ::id & id, ::matter * pobject);


   inline ::papaya::topic topic(const ::id & id);


   
   

   __pointer(::papaya::ini) appini();







};





