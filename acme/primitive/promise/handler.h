#pragma once


namespace promise
{


   class company;


   CLASS_DECL_ACME int os_get_system_update_poll_time(const ::id &id);


   using matter_machine = isomap<＿＿pointer(::matter), ＿＿pointer(::promise::machine)>;


   class CLASS_DECL_ACME handler :
      virtual public ::context_object
   {
   public:


      ＿＿pointer(::promise::company)    m_pcompany;
      ::promise::matter_machine              m_mattermachine;
      ::user::e_key                          m_ekey;
      ::var                                  m_var;
      ::i64                                  m_iUpdateSerial;
      bool                                   m_bModified;
      int                                    m_iMillisSleep;


      handler(const ::id &id);
      handler(::promise::company * psource, const ::id & id);
      virtual ~handler();


   #ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);
   #endif


      using context_object::process;

      virtual void perform(const ::var &var);

      virtual void perform(const ::action_context &actioncontext);

      virtual void perform();

      virtual void notify(const ::action_context &actioncontext);

      virtual void notify();

      virtual void add(::matter *pmatter, bool bForkWhenNotify = false);

      virtual void remove(::matter *pmatter);


      void set_modified();


      virtual ::promise::machine * machine(::matter *pmatter);


      virtual ::estatus run() override;


      void post_destroy_all();


      inline bool is_ending()
      {

         sync_lock sl(mutex());

         return m_mattermachine.is_empty();

      }


      inline int poll_millis() { return os_get_system_update_poll_time(m_id); };


      static inline bool should_poll(int iMillis)
      {

         return iMillis >= 100;

      }


      ::promise::handler & operator=(const ::id &id)
      {

         m_id = id;

         return *this;

      }


      inline bool operator==(const ::id &id) const { return m_id == id || m_id == FULL_ID; }


      inline ::id &id();

      inline const ::id &id() const;


   };


   using manager_pointer = ＿＿pointer(promise::handler);


} // namespace promise



