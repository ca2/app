#include "framework.h"
#include "acme/id.h"


hyperlink::hyperlink()
{
   m_bProfile = false;
}


hyperlink::~hyperlink()
{

}


bool hyperlink::open_link(string strLink, string strProfile, string strTarget)
{

   auto plink = __new(hyperlink);
   plink->m_strLink = strLink;
   plink->m_strProfile = strProfile;
   plink->m_strTarget = strTarget;

   system_call_update(id_open_hyperlink, plink);
   //if (is_system())
   {

      //if (strLink.begins_ci("mailto:"))
      //{

      //   return Context.os().file_open(strLink);

      //}

      //open_profile_link(strLink, strProfile, strTarget);

      return true;

   }
   //else
   //{

   //   return Session.open_link(strLink, strProfile, strTarget);

   //}

   //return false;

}


void hyperlink::open_profile_link(string strUrl, string strProfile, string strTarget)
{

   auto plink = __new(hyperlink);
   plink->m_strLink = strUrl;
   plink->m_strProfile = strProfile;
   plink->m_strTarget = strTarget;
   plink->m_bProfile = true;

   system_call_update(id_open_hyperlink, plink);


   //__throw(todo("hyperlink"));
   //System.open_profile_link(strUrl, strProfile, strTarget);

   //system

}




//void hyperlink::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
//{
//
//   System.browser(strUrl, "", strProfile, strTarget);
//
//}




