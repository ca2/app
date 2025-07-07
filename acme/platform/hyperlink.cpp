#include "framework.h"
#include "hyperlink.h"
#include "acme/constant/id.h"
#include "acme/platform/system.h"


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
//   system()->open_profile_link(strLink, strProfile, strTarget);
//
//   return true;
//
//}
//

void hyperlink::run()
{

   // if (m_bProfile)
   // {
   //
   //    return system()->open_internet_link(m_strLink, m_strBrowserAccount, m_strTarget);
   //
   // }

   return system()->open_internet_link(m_strLink, m_strBrowserAccount, m_strTarget);

}



