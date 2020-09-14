#include "framework.h" 
#include "base/update.h" 



impact_update::impact_update(::layered * pobjectContext) :
   ::context_object(pobject),
   ::update(pobject)
{

   m_eimpact            = ::impact_none;
   m_uId                = id_none;
   m_bOk                = true;
   m_ekey               = ::user::key_none;
   m_bEnterKeyPressed   = false;
   m_iTime              = 0;

}


impact_update::~impact_update()
{

}



