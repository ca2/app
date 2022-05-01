#pragma once


typedef ::i64 UPDATE_SERIAL();
using PFN_UPDATE_SERIAL = UPDATE_SERIAL *;



struct CLASS_DECL_ACME update_task :
   virtual public ::matter
{
protected:

   
   friend class matter;

   
   element_array m_elementa;


   static __pointer(update_task) & task(::i64 iUpdate);

   virtual void add(::matter * pmatter);
   virtual void erase(::matter * pmatter);

   static void _add(::i64 iUpdate, ::matter* pmatter);

   static void _erase(::i64 iUpdate, ::matter* pmatter);

   static void _erase(::matter* pmatter);

public:


   static critical_section * g_pcs;
   static ::i64_map < __pointer(update_task) > * g_pmap;
   static bool g_bDestroyAll;


   bool                    m_bModified;
   int                     m_iMillisSleep;
   ::i64                   m_iUpdate;
   ::i64                   m_iSerial;


   update_task();
   virtual ~update_task();

   virtual void notify();


   static void set_modified(::i64 iUpdate);



   virtual void run() override;

   static void post_destroy_all();

   inline bool is_ending() { synchronous_lock synchronouslock(mutex()); return m_elementa.is_empty();};
   inline int poll_millis() { return os_get_system_update_poll_time(m_iUpdate);};

   static inline bool should_poll(int iMillis)
   {

      return iMillis >= 100;

   }


};


//template < typename PAYLOAD >
//class update_task :
//   virtual public ::update_task
//{
//public:
//
//
//   PAYLOAD         m_payload;
//   HAS_CHANGED *   m_pfnHasChanged;
//
//   update_task(::i64 iUpdate, HAS_CHANGED * pfnHasChanged, int iMillisSleep = 300) :
//      update_task(iUpdate, iMillisSleep),
//      m_pfnHasChanged(pfnHasChanged)
//   {
//
//   }
//
//
//
//
//
//};





