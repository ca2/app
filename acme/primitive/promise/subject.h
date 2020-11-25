#pragma once


enum enum_subject
{

   e_subject_prepare,
   e_subject_process,
   e_subject_deliver,

};

namespace promise
{
   using matter_context = isomap<__pointer(::matter), __pointer(::promise::context)>;

   CLASS_DECL_ACME int os_get_system_update_poll_time(const ::id & id);

   class CLASS_DECL_ACME subject :
      virtual public context_object
   {
   public:


      __pointer(::promise::handler)       m_phandler;
      ::promise::matter_context           m_mattercontext;
      ::user::e_key                       m_ekey;
      ::payload                           m_payload;
      ::i64                               m_iUpdateSerial;
      bool                                m_bModified;
      int                                 m_iMillisSleep;



      enum_subject                        m_esubject;
      __pointer(::matter)                 m_pmatter;
      __pointer(::layered)                m_pobjectTopic;
      ::action_context                    m_actioncontext;
      __pointer(::layered)                m_psender;
      __pointer(::layered)                m_puserinteraction; // user::interaction
      __pointer(::layered)                m_pcontrolevent; // user::control_event
      __pointer(::file::item)             m_pfileitem;
      bool                                m_bRet;


      subject(::promise::handler * phandler, const ::id & id);
      virtual ~subject();


      //handler(const ::id &id);
      //handler(::promise::handler * pbacking, const ::id & id);
      //virtual ~handler();


#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);
#endif

      virtual ::estatus run() override;

      //virtual void process(const ::payload & payload);

      //virtual void process(const ::action_context & actioncontext);

      //virtual void process();

      virtual void deliver(const ::action_context & actioncontext);

      virtual void deliver();

      virtual void add(::matter * pmatter, bool bForkWhenNotify = false);

      virtual void remove(::matter * pmatter);

      void set_modified();

      virtual ::promise::context * context(::matter * pmatter);

      //virtual ::estatus run() override;

      void post_destroy_all();

      inline bool is_ending()
      {

         sync_lock sl(mutex());

         return m_mattercontext.is_empty();

      }

      inline int poll_millis() { return os_get_system_update_poll_time(m_id); };

      static inline bool should_poll(int iMillis)
      {

         return iMillis >= 100;

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


      virtual ::estatus start_task();


      void reset_update(const ::id &id);


      virtual ::estatus on_task() override;


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



