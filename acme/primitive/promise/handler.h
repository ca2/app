#pragma once


namespace promise
{


   class CLASS_DECL_ACME handler :
      virtual public ::context_object
   {
   public:


      __pointer(::id_map<__pointer(::promise::subject)>)    m_pmapSubject;

      static ::critical_section                             g_cs;
      // todo implement keyset
      // a hashmap of just the key (but not a value)
      // like std::set?
      static ::set < handler_pointer >                      g_handlerset;
      static bool                                           g_bDestroyAll;


      handler() { }
      virtual ~handler() {}

#ifdef DEBUG


      i64 add_ref(OBJ_REF_DBG_PARAMS);
      i64 dec_ref(OBJ_REF_DBG_PARAMS);
      i64 release(OBJ_REF_DBG_PARAMS);

#endif

      //virtual ::estatus run() override;


      ::promise::subject_pointer fork_subject(const ::id &id);

      ::promise::subject * subject(const ::id &id);

      virtual ::promise::subject * start_subject_handling(const ::id &id);
      virtual void process_subject(const ::id & id);
      virtual void process_subject(const ::id & id, const ::payload & payload);
      virtual void process_subject(const ::id & id, const ::action_context &actioncontext);
      virtual void process(::promise::subject * psubject);

      using ::context_object::on_subject;
      virtual void on_subject(::promise::subject * psubject);
      //virtual void on_subject(::promise::subject * psubject);

      virtual void deliver(const ::id &id);
      virtual void deliver(const ::id &id, const ::action_context &actioncontext);

      virtual void set_modified(const ::id &id);
      virtual void delivery_for(const ::id &id, ::matter *pmatter, bool bForkWhenNotify = false);
      virtual void remove_subject(const ::id &id, ::matter *pmatter);
      //static handler_pointer fork_handler(const ::id &id, ::matter *pmatter = nullptr);
      //subject_pointer subject(const ::id &id, ::matter *pmatter = nullptr);

      virtual void finalize() override;

      //virtual void source_add(::matter* pmatter);
      //virtual void source_remove(::matter* pmatter);

      //void update_add(const ::id& id, ::matter* pmatter);
      //void update_remove(const ::id& id, ::matter* pmatter);

      void remove(::matter *pmatter);

      static void remove_from_any_source(::matter *pmatter);

      //static void __add(const ::id& id, ::matter* pmatter);

      //static void __remove(const ::id& id, ::matter* pmatter);

      static void __remove(::matter *pmatter);

      static void post_destroy_all();


   };


   /*inline ::promise::subject_pointer new_subject(::promise::subject * pmanager) { return __new(::promise::subject(pmanager)); }


   inline ::promise::subject_pointer new_subject(::promise::subject * phandler, ::matter *pmatter)
   {

      return __new(::promise::subject(phandler, pmatter));

   }*/

   using manager_pointer = __pointer(promise::subject);

} // namespace promise



