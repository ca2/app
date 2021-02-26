#pragma once


namespace promise
{


   class CLASS_DECL_ACME subject :
      virtual public context_object
   {
   public:


      __pointer(::promise::manager)       m_pmanager;
      ::promise::matter_context           m_mattercontext;
      ::user::enum_key                       m_ekey;
      ::payload                           m_payload;
      ::i64                               m_iUpdateSerial;
      bool                                m_bModified;
      ::millis                            m_millisSleep;



      enum_subject                        m_esubject;
      __pointer(::matter)            m_pmatter;
      __pointer(::layered)           m_pobjectTopic;
      ::action_context                    m_actioncontext;
      __pointer(::layered)           m_psender;
      __pointer(::layered)           m_puserinteraction; // user::interaction
      __pointer(::layered)           m_pcontrolevent; // user::control_event
      __pointer(::file::item)        m_pfileitem;
      bool                                m_bRet;


      subject(::promise::manager * phandler, const ::id & id);
      virtual ~subject();


      //handler(const ::id &id);
      //handler(::promise::manager * pbacking, const ::id & id);
      //virtual ~handler();


#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
      virtual i64 release(OBJ_REF_DBG_PARAMS) override;
#endif

      virtual ::e_status step() override;
      virtual ::e_status run() override;

      //virtual void process(const ::payload & payload);

      //virtual void process(const ::action_context & actioncontext);

      //virtual void process();

      virtual void deliver(const ::action_context & actioncontext);

      virtual void deliver();

      virtual void add(::matter * pmatter, bool bForkWhenNotify = false);

      virtual void remove(::matter * pmatter);

      void set_modified();

      virtual ::promise::context * context(::matter * pmatter);

      //virtual ::e_status run() override;

      void post_destroy_all();

      inline bool is_ending()
      {

         return false;

//         synchronization_lock synchronizationlock(mutex());
//
//         return m_mattercontext.is_empty();

      }

      inline ::millis poll_time() { return os_get_system_update_poll_time(m_id); };

      static inline bool should_poll(::millis millis)
      {

         return millis >= 100_ms;

      }

      ::promise::subject & operator=(const ::id & id)
      {

         m_id = id;

         return *this;

      }

      inline bool operator==(const ::id & id) const { return m_id == id || m_id == FULL_ID; }

      //inline ::id & id();

//      inline const ::id & id() const;


      void subject_common_construct();


      virtual ::e_status start_task();


      void reset_update(const ::id &id);


      virtual ::e_status on_task() override;


      operator subject *() { return this; }


      operator const subject *() const { return this; }


      virtual bool is_up_to_date(const ::promise::context * pcontext) const;


      virtual void set_up_to_date(::promise::context * pcontext);


      inline ::id &id() { return m_id; }


      inline const ::id &id() const { return m_id; }


   };


   //inline ::promise::subject_pointer new_action(const ::id &id, ::matter *pmatter = nullptr)
   //{

   //   return __new(subject(id, pmatter));

   //}


   //inline ::promise::subject_pointer new_action(const ::id &id, const ::action_context &actioncontext)
   //{

   //   return __new(subject(id, actioncontext));

   //}


} // namespace promise



