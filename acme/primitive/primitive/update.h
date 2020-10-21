#pragma once


class source;


CLASS_DECL_ACME int os_get_system_update_poll_time(const ::id & id);


using matter_change = isomap < __pointer(::matter), __pointer(::change) >;


class CLASS_DECL_ACME update :
   virtual public ::context_object
{
public:


   __pointer(::source)                             m_psource;
   ::matter_change                                 m_matterchange;
   ::user::e_key                                   m_ekey;
   ::var                                           m_var;
   ::i64                                           m_iUpdateSerial;
   bool                                            m_bModified;
   int                                             m_iMillisSleep;


   update(const ::id& id);
   update(::source * psource, const :: id & id);
   virtual ~update();


#ifdef DEBUG
   virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 release(OBJ_REF_DBG_PARAMS);
#endif


   using context_object::apply;
   virtual void apply(const ::var& var);
   virtual void apply(const ::action_context& actioncontext);
   virtual void apply();

   virtual void notify(const ::action_context& actioncontext);
   virtual void notify();

   virtual void add(::matter* pmatter, bool bForkWhenNotify = false);
   virtual void remove(::matter* pmatter);


   void set_modified();


   virtual ::change* change(::matter * pmatter);


   virtual ::estatus run() override;


   void post_destroy_all();


   inline bool is_ending() { sync_lock sl(mutex()); return m_matterchange.is_empty(); };
   inline int poll_millis() { return os_get_system_update_poll_time(m_id); };


   static inline bool should_poll(int iMillis)
   {

      return iMillis >= 100;

   }


   ::update& operator =(const ::id& id) { m_id = id; return *this; }
   inline bool operator ==(const ::id& id) const { return m_id == id || m_id == FULL_ID; }


   inline ::id& id();
   inline const ::id& id() const;


};


using update_pointer = __pointer(::update);



