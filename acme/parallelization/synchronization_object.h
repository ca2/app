// Created by camilo on 2022-10-28 14:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/particle.h"


//#define MUTEX_DEBUG
#undef MUTEX_DEBUG


//namespace acme_windows_common
//{


   class CLASS_DECL_ACME synchronization_object :
      virtual public ::particle
   {
   public:


#ifdef MUTEX_DEBUG
      string                  m_strThread;
      itask                 m_itask;
#endif



      hsynchronization        m_handle;
      bool                    m_bOwner;


      synchronization_object();
      ~synchronization_object();


      hsynchronization get_synchronization_handle() override;


      bool _wait(const class time & timeWait) override;


   };


//} // namespace acme_windows_common



