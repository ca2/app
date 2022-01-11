#pragma once


class CLASS_DECL_ACME hyperlink :
   virtual public ::matter
{
public:

   string      m_strLink;
   string      m_strProfile;
   string      m_strTarget;
   bool        m_bProfile;
   
   hyperlink();
   virtual ~hyperlink();


   virtual void run() override;
   //bool open_link(string strLink, string strProfile = "", string strTarget = "");
   //void open_profile_link(string strUrl, string strProfile, string strTarget);
   //virtual void sync_open_profile_link(string strUrl, string strProfile, string strTarget);




};
