#pragma once


class CLASS_DECL_APEX retry_single_lock
{
public:


   synchronization_object *               m_psync;
   hsync                m_hsync;
   bool                 m_bAcquired;
   duration             m_durationLock;
   duration             m_durationSleep;
   i32                  m_iRetry;


   retry_single_lock(synchronization_object * pobject, duration durationLock, duration durationSleep, i32 iRetry = -1, bool bInitialLock = true);
   ~retry_single_lock();

   bool lock();
   bool unlock();
   bool IsLocked();


};
