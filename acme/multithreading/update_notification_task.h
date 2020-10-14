#pragma once


typedef ::i64 UPDATE_SERIAL();
using PFN_UPDATE_SERIAL = UPDATE_SERIAL *;


CLASS_DECL_ACME int os_get_system_update_poll_time(::i64 iUpdate);


struct update_notification_task :
   virtual public ::element
{
protected:


   element_array m_elementa;


   virtual void add(::element * pelement);
   virtual void remove(::element * pelement);


public:


   static ::critical_section * g_pcs;
   static ::i64_map < update_notification_task * > * g_pmap;
   static bool g_bDestroyAll;


   bool                    m_bModified;
   int                     m_iMillisSleep;
   ::i64                   m_iUpdate;


   update_notification_task();
   virtual ~update_notification_task();

   virtual void notify();

   static void add(::i64 iUpdate, ::element * pelement);

   static void remove(::i64 iUpdate, ::element * pelement);

   static void set_modified(::i64 iUpdate);



   virtual ::estatus run() override;

   static update_notification_task * & task(::i64 iUpdate);
   static void post_destroy_all();

   inline bool is_ending() { sync_lock sl(mutex()); return m_elementa.is_empty();};
   inline int poll_millis() { return os_get_system_update_poll_time(m_iUpdate);};

   static inline bool should_poll(int iMillis)
   {

      return iMillis >= 100;

   }


};


//template < typename PAYLOAD >
//class update_notification_task :
//   virtual public ::update_notification_task
//{
//public:
//
//
//   PAYLOAD         m_payload;
//   HAS_CHANGED *   m_pfnHasChanged;
//
//   update_notification_task(::i64 iUpdate, HAS_CHANGED * pfnHasChanged, int iMillisSleep = 300) :
//      update_notification_task(iUpdate, iMillisSleep),
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





