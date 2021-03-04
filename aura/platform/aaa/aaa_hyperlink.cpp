#include "framework.h"


hyperlink::hyperlink(::layered * pobjectContext) :
   ::object(pobject)
{

}


hyperlink::~hyperlink()
{

}


bool hyperlink::open_link(string strLink, string strProfile, string strTarget)
{

   //if (is_system())
   {

      if (strLink.begins_ci("mailto:"))
      {

         return Context.os().file_open(strLink);

      }

      open_profile_link(strLink, strProfile, strTarget);

      return true;

   }
   //else
   //{

   //   return psession->open_link(strLink, strProfile, strTarget);

   //}

   //return false;

}


void hyperlink::open_profile_link(string strUrl, string strProfile, string strTarget)
{


   System->open_profile_link(strUrl, strProfile, strTarget);

}




//void hyperlink::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
//{
//
//   System->browser(strUrl, "", strProfile, strTarget);
//
//}




