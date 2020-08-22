#pragma once


class CLASS_DECL_AURA critical_section
{
public:


#ifdef WINDOWS
   CRITICAL_SECTION        m_sect;
#else
   pthread_mutex_t         m_mutex;
#endif

   critical_section();
   ~critical_section();


#ifdef WINDOWS
   operator CRITICAL_SECTION * ();
#else
   operator pthread_mutex_t ();
#endif

   inline void lock();

   inline void unlock();


private:

   bool Init();

};


#ifdef WINDOWS

inline void critical_section::lock()
{

   ::EnterCriticalSection(&m_sect);

}


inline void critical_section::unlock()
{

   ::LeaveCriticalSection(&m_sect);

}

#else

inline void critical_section::lock()
{

   pthread_mutex_lock (&m_mutex);

}

inline void critical_section::unlock()
{

   pthread_mutex_unlock (&m_mutex);

}

#endif


class CLASS_DECL_AURA cslock
{
public:

   critical_section * m_pcs;


   inline cslock(critical_section * pcs): m_pcs(pcs) { if(m_pcs != nullptr) m_pcs->lock(); }
   inline ~cslock() { if(m_pcs != nullptr) m_pcs->unlock(); }


};





