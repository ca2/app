#pragma once


namespace promise
{


   class CLASS_DECL_ACME company :
           virtual public ::context_object
   {
   public:


      ＿＿pointer(::id_map<＿＿pointer(::promise::handler)>)    m_pmap;

      static ::critical_section                                         g_cs;
      // todo implement keyset
      // a hashmap of just the key (but not a value)
      // like std::set?
      static isomap < company_pointer, company_pointer >                g_sourcekeyset;
      static bool                                                       g_bDestroyAll;


      company();
      virtual ~company();


      static ::promise::company_pointer fork_manager(const ::id &id);

      ::promise::handler * manager(const ::id &id);

      virtual void deliver_subject(const ::id &id);

      virtual void deliver_subject(const ::id &id, const ::action_context &actioncontext);

      virtual void perform_subject(const ::id &id);

      virtual void perform_subject(const ::id &id, const ::action_context &actioncontext);

      virtual void perform_subject(const ::id &id, const ::var &var);

      virtual void set_modified(const ::id &id);

      virtual void add_update(const ::id &id, ::matter *pmatter, bool bForkWhenNotify = false);

      virtual void remove_update(const ::id &id, ::matter *pmatter);

      static company_pointer fork_action(const ::id &id, ::matter *pmatter = nullptr);

      company_pointer action(const ::id &id, ::matter *pmatter = nullptr);


      virtual void finalize() override;

      //virtual void source_add(::matter* pmatter);
      //virtual void source_remove(::matter* pmatter);

      //void update_add(const ::id& id, ::matter* pmatter);
      //void update_remove(const ::id& id, ::matter* pmatter);


      void remove(::matter *pmatter);

      static void remove_from_any_source(::matter *pmatter);


      //static void ＿＿add(const ::id& id, ::matter* pmatter);

      //static void ＿＿remove(const ::id& id, ::matter* pmatter);

      static void ＿＿remove(::matter *pmatter);

      static void post_destroy_all();


   };


   inline ::promise::subject_pointer new_subject(::promise::manager * pmanager) { return ＿＿new(::promise::subject(pmanager)); }


   inline ::promise::subject_pointer new_subject(::promise::manager * pmanager, ::matter *pmatter)
   {

      return ＿＿new(::promise::subject(pmanager, pmatter));

   }


} // namespace promise



