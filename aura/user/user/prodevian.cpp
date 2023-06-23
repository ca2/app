// From _impl.h by camilo on 2022-08-27 13:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "prodevian.h"
#include "interaction.h"


prodevian::prodevian(::user::interaction * pinteraction) :
   m_pinteraction(pinteraction)
{

   m_pinteraction->add_prodevian(this);

}


prodevian::~prodevian()
{

   m_pinteraction->erase_prodevian(this);

}




