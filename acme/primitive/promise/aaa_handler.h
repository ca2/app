#pragma once


namespace promise
{


   CLASS_DECL_ACME int os_get_system_update_poll_time(const ::id &id);


   using matter_context = map<__pointer(::matter), __pointer(::promise::context)>;


   class CLASS_DECL_ACME handler :
      virtual public ::context_object
   {
   public:


      __pointer(::promise::handler)          m_pbacking;
      ::promise::matter_context              m_mattercontext;
      ::user::e_key                          m_ekey;
      ::payload                              m_var;
      ::i64                                  m_iUpdateSerial;
      bool                                   m_bModified;
      int                                    m_iMillisSleep;


      //handler(const ::id &id);
      handler(::promise::handler * pbacking, const ::id & id);
      virtual ~handler();


   #ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);
   #endif

      virtual void process(const ::payload & payload);

      virtual void process(const ::action_context &actioncontext);

      virtual void process();

      virtual void deliver(const ::action_context &actioncontext);

      virtual void deliver();

      virtual void add(::matter *pmatter, bool bForkWhenNotify = false);

      virtual void remove(::matter *pmatter);

      void set_modified();

      virtual ::promise::context * context(::matter *pmatter);

      virtual ::e_status run() override;

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

      ::promise::subject & operator=(const ::id &id)
      {

         m_id = id;

         return *this;

      }

      inline bool operator==(const ::id &id) const { return m_id == id || m_id == FULL_ID; }

      inline ::id &id();

      inline const ::id &id() const;


   };


   using manager_pointer = __pointer(promise::subject);


} // namespace promise



