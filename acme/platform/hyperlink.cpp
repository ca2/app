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

   ::acme::get_system()->open_profile_link(strLink, strProfile, strTarget);

   return true;

}


void hyperlink::open_profile_link(string strUrl, string strProfile, string strTarget)
{

   ::acme::get_system()->open_profile_link(strUrl, strProfile, strTarget);

}



