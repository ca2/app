#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


update::update()
{

   m_bRet = false;
   m_psender = nullptr;
   m_pobjectTopic = nullptr;
   m_puserinteraction = nullptr;
   m_pcontrolevent = nullptr;

}


update::~update()
{

}

