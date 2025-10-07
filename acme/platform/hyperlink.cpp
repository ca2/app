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


//bool hyperlink::open_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
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



