#pragma once


class CLASS_DECL_APEX retry_single_lock
{
public:


   synchronization *               m_psync;
   hsynchronization                m_hsync;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   int                  m_iRetry;


   retry_single_lock(synchronization * pparticle, duration durationLock, duration durationSleep, int iRetry = -1, bool bInitialLock = true);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
