#pragma once


namespace promise
{


   class CLASS_DECL_ACME subject :
      virtual public context_object
   {
   public:


      __pointer(::promise::handler)       m_phandler;
      __pointer(::promise::context)       m_pcontext;
      __pointer(::matter)                 m_pmatter;
      __pointer(::layered)                m_pobjectTopic;
      ::action_context                         m_actioncontext;
      __pointer(::layered)                m_psender;
      __pointer(::layered)                m_puserinteraction; // user::interaction
      __pointer(::layered)                m_pcontrolevent; // user::control_event
      __pointer(::file::item)             m_pfileitem;
      ::payload                                m_var;
      bool                                     m_bRet;
      ::user::e_key                            m_ekey;


      subject();
      subject(const ::id &id, ::matter *pmatter = nullptr);
      subject(const ::id &id, const ::action_context &actioncontext);
      subject(::promise::handler * phandler, const ::action_context &actioncontext);
      subject(::promise::handler * phandler, ::matter *pmatter = nullptr);
      subject(::promise::handler * phandler, ::promise::context * pcontext, ::matter *pmatter);
      virtual ~subject();


      void action_common_construct();


      virtual ::estatus start_task();


      void reset_update(const ::id &id);


      virtual ::estatus on_task() override;


      operator subject *() { return this; }


      operator const subject *() const { return this; }


      virtual bool is_up_to_date() const;


      virtual void set_up_to_date();


      inline ::id &id() { return m_id; }


      inline const ::id &id() const { return m_id; }


   };


   inline ::promise::subject_pointer new_action(const ::id &id, ::matter *pmatter = nullptr)
   {

      return __new(subject(id, pmatter));

   }


   inline ::promise::subject_pointer new_action(const ::id &id, const ::action_context &actioncontext)
   {

      return __new(subject(id, actioncontext));

   }


} // namespace promise



