// From _impl.h by camilo on 2022-08-27 13:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "auto_refresh.h"
#include "interaction.h"


auto_refresh::auto_refresh(::user::interaction * pinteraction) :
   m_pinteraction(pinteraction)
{

   m_pinteraction->add_auto_refresh(this);

}


auto_refresh::~auto_refresh()
{

   m_pinteraction->erase_auto_refresh(this);

}




