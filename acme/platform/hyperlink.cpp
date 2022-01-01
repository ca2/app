#include "framework.h"
#include "acme/id.h"
#include "hyperlink.h"


hyperlink::hyperlink()
{
   
   m_bProfile = false;

}


hyperlink::~hyperlink()
{

}


//bool hyperlink::open_link(string strLink, string strProfile, string strTarget)
//{
//
//   m_psystem->open_profile_link(strLink, strProfile, strTarget);
//
//   return true;
//
//}
//

::e_status hyperlink::run()
{

   if (m_bProfile)
   {

      return get_system()->open_profile_link(m_strLink, m_strProfile, m_strTarget);

   }

   return get_system()->open_link(m_strLink, m_strProfile, m_strTarget);

}



