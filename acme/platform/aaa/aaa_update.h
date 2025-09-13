#pragma once


//CLASS_DECL_ACME int os_get_system_update_poll_time(long long iUpdate);

using update_map = map < ::pointer<matter> ::pointer<::update_item>>

class CLASS_DECL_ACME update :
   virtual public ::object
{
protected:

   friend class matter;
   friend class ::acme::acme;

   static ::pointer<update> get(const ::atom & atom);

   virtual void add(::matter* pmatter);
   virtual void erase(::matter* pmatter);

   static void _add(const :: atom & atom, ::matter* pmatter);

   static void _erase(const ::atom& atom, ::matter* pmatter);

   static void _erase(::matter* pmatter);

   static ::critical_section* g_pcs;
   static ::atom_map < ::pointer<update >> g_pmap;
   static bool g_bDestroyAll;



public:


   ::atom                                            id();
   bool                                            m_bRet;
   ::pointer<::layered>                           m_psender;
   ::pointer<::layered>                           m_pobjectTopic;
   ::action_context                                m_actioncontext;
   ::update_map                                    m_map;
   ::pointer<::layered>                           m_puserinteraction; // user::interaction
   ::pointer<::layered>                           m_pcontrolevent; // user::control_event
   ::pointer<::file::item>                        m_pfileitem;
   //::pointer<::u>                       m_pupdatetask;
   long long                                           m_iUpdateSerial;
   ::user::enum_key                                   m_ekey;
   ::payload                                           m_var;
   bool                                            m_bModified;
   int                                             m_iMillisSleep;
   //long long                                        m_iUpdate;
   //long long                   m_iSerial;


   update();
   update(const ::atom & atom);
   virtual ~update();


   virtual void notify();


   static void set_modified(const ::atom& atom);



   virtual void run() override;

   static void post_destroy_all();

   inline bool is_ending() { synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX); return m_map.is_empty(); };
   inline int poll_millis() { return os_get_system_update_poll_time(m_iUpdateSerial); };

   static inline bool should_poll(int iMillis)
   {

      return iMillis >= 100;

   }


   //update();
   //virtual ~update();


   ::update& operator =(const ::atom& atom) { id() = atom; return *this; }
   inline bool operator ==(const ::atom& atom) const { return id() == atom || id() == FULL_ID; }

   //void set_handled_by(const ::particle * pparticle) { m_handledbya.add((::matter*) pparticle); }
   //bool handled_by(const ::particle * pparticle) const { return m_handledbya.has((::matter*) pparticle); }



};


using manager_pointer = ::pointer<::update>


inline auto new_update(const ::atom & atom) { return øallocate ::update(atom); }

