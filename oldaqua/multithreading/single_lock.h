#pragma once


class CLASS_DECL_AQUA single_lock :
   virtual public sync
{
public:


   __pointer(sync)         m_psync;
   HANDLE                  m_hobject;
   bool                    m_bAcquired;


   explicit single_lock(sync * pobject, bool bInitialLock = false);
   ~single_lock();

   sync_result wait();
   sync_result wait(const duration & duration);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = nullptr);
   bool IsLocked();


};
