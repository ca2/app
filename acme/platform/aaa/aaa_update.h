#pragma once


//CLASS_DECL_ACME int os_get_system_update_poll_time(::i64 iUpdate);

using update_map = map < __pointer(matter), __pointer(::update_item) > ;

class CLASS_DECL_ACME update :
   virtual public ::object
{
protected:

   friend class matter;
   friend class ::acme::acme;

   static __pointer(update)& get(const ::id & id);

   virtual void add(::matter* pmatter);
   virtual void erase(::matter* pmatter);

   static void _add(const :: id & id, ::matter* pmatter);

   static void _erase(const ::id& id, ::matter* pmatter);

   static void _erase(::matter* pmatter);

   static ::critical_section* g_pcs;
   static ::id_map < __pointer(update) >* g_pmap;
   static bool g_bDestroyAll;



public:


   ::id                                            m_id;
   bool                                            m_bRet;
   __pointer(::layered)                            m_psender;
   __pointer(::layered)                            m_pobjectTopic;
   ::action_context                                m_actioncontext;
   ::update_map                                    m_map;
   __pointer(::layered)                            m_puserinteraction; // user::interaction
   __pointer(::layered)                            m_pcontrolevent; // user::control_event
   __pointer(::file::item)                         m_pfileitem;
   //__pointer(::u)                        m_pupdatetask;
   ::i64                                           m_iUpdateSerial;
   ::user::enum_key                                   m_ekey;
   ::payload                                           m_var;
   bool                                            m_bModified;
   int                                             m_iMillisSleep;
   //::i64                                        m_iUpdate;
   //::i64                   m_iSerial;


   update();
   update(const ::id & id);
   virtual ~update();


   virtual void notify();


   static void set_modified(const ::id& id);



   virtual ::e_status run() override;

   static void post_destroy_all();

   inline bool is_ending() { synchronous_lock synchronouslock(mutex()); return m_map.is_empty(); };
   inline int poll_millis() { return os_get_system_update_poll_time(m_iUpdateSerial); };

   static inline bool should_poll(int iMillis)
   {

      return iMillis >= 100;

   }


   //update();
   //virtual ~update();


   ::update& operator =(const ::id& id) { m_id = id; return *this; }
   inline bool operator ==(const ::id& id) const { return m_id == id || m_id == FULL_ID; }

   //void set_handled_by(const ::matter* pobject) { m_handledbya.add((::matter*) pobject); }
   //bool handled_by(const ::matter* pobject) const { return m_handledbya.has((::matter*) pobject); }



};


using manager_pointer = __pointer(::update);


inline auto new_update(const ::id & id) { return __new(::update(id)); }

