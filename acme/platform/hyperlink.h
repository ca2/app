#pragma once


#include "acme/primitive/primitive/particle.h"


class CLASS_DECL_ACME hyperlink :
   virtual public ::particle
{
public:

   
   string      m_strLink;
   string      m_strBrowserAccount;
   string      m_strTarget;
   bool        m_bProfile;

   
   hyperlink();
   ~hyperlink() override;


   void run() override;
   //bool open_link(string strLink, string strProfile = "", string strTarget = "");
   //void open_profile_link(string strUrl, string strProfile, string strTarget);
   //virtual void sync_open_profile_link(string strUrl, string strProfile, string strTarget);




};
