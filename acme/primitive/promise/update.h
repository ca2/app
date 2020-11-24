#pragma once


namespace promise
{


   class CLASS_DECL_ACME update :
           virtual public context_object
   {
   public:


      __pointer(::promise::handler)       m_pmanager;
      __pointer(::promise::context)       m_pcontext;
      __pointer(::matter)                 m_pmatter;
      __pointer(::layered)                m_pobjectTopic;
      ::action_context                          m_actioncontext;
      __pointer(::layered)                m_psender;
      __pointer(::layered)                m_puserinteraction; // user::interaction
      __pointer(::layered)                m_pcontrolevent; // user::control_event
      __pointer(::file::item)             m_pfileitem;
      ::payload                                     m_var;
      bool                                      m_bRet;
      ::user::e_key                             m_ekey;


      update();
      update(const ::id &id, ::matter *pmatter = nullptr);
      update(const ::id &id, const ::action_context &actioncontext);
      update(::promise::handler * phandler, const ::action_context &actioncontext);
      update(::promise::handler * phandler, ::matter *pmatter = nullptr);
      update(::promise::handler * phandler, ::promise::source * psource, ::matter *pmatter);
      virtual ~update();


      void action_common_construct();


      virtual ::estatus start_task();


      void reset_update(const ::id &id);


      virtual ::estatus on_task() override;


      operator update *() { return this; }


      operator const update *() const { return this; }


      virtual bool is_up_to_date() const;


      virtual void set_up_to_date();


      inline ::id &id() { return m_id; }


      inline const ::id &id() const { return m_id; }


   };


   inline ::promise::subject_pointer new_action(const ::id &id, ::matter *pmatter = nullptr)
   {

      return __new(update(id, pmatter));

   }


   inline ::promise::subject_pointer new_action(const ::id &id, const ::action_context &actioncontext)
   {

      return __new(update(id, actioncontext));

   }


} // namespace promise



