#pragma once


namespace subject
{


   class CLASS_DECL_APEX subject :
      virtual public object
   {
   public:


      __pointer(::subject::manager)       m_pmanager;
      ::subject::matter_context           m_mattercontext;
      ::user::enum_key                    m_ekey;
      ::payload                           m_payload;
      ::i64                               m_iUpdateSerial;
      bool                                m_bModified;
      ::millis                            m_millisSleep;

      enum_subject                        m_esubject;
      __pointer(::matter)                 m_pmatter;
      __pointer(::property_object)        m_pobjectTopic;
      ::action_context                    m_actioncontext;
      __pointer(::property_object)        m_psender;
      __pointer(::user::primitive)        m_puserprimitive; // user::interaction
      __pointer(::property_object)        m_pcontrolevent; // user::control_event
      __pointer(::file::item)             m_pfileitem;
      bool                                m_bRet;


      subject(::subject::manager * phandler, const ::id & id);
      virtual ~subject();


      //handler(const ::id &id);
      //handler(::subject::manager * pbacking, const ::id & id);
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

      virtual void erase(::matter * pmatter);

      void set_modified();

      virtual ::subject::context * context(::matter * pmatter);

      //virtual ::e_status run() override;

      void post_destroy_all();

      inline bool is_ending()
      {

         return false;

//         synchronous_lock synchronouslock(mutex());
//
//         return m_mattercontext.is_empty();

      }

      inline ::millis poll_time() { return os_get_system_update_poll_time(m_id); };

      static inline bool should_poll(::millis millis)
      {

         return millis >= 100_ms;

      }


      ::subject::subject & operator=(const ::id & id)
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


      //virtual ::e_status run() override;


      operator subject *() { return this; }


      operator const subject *() const { return this; }


      virtual bool is_up_to_date(const ::subject::context * pcontext) const;


      virtual void set_up_to_date(::subject::context * pcontext);


      inline ::id &id() { return m_id; }


      inline const ::id &id() const { return m_id; }


   };


   //inline ::subject::subject_pointer new_action(const ::id &id, ::matter *pmatter = nullptr)
   //{

   //   return __new(subject(id, pmatter));

   //}


   //inline ::subject::subject_pointer new_action(const ::id &id, const ::action_context &actioncontext)
   //{

   //   return __new(subject(id, actioncontext));

   //}
//
//
} // namespace promise



