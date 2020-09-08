#pragma once


class CLASS_DECL_ACME hyperlink :
   virtual public ::generic
{
public:


   hyperlink(::generic * pobject);
   virtual ~hyperlink();

   virtual bool open_link(string strLink, string strProfile = "", string strTarget = "");
   virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
   //virtual void sync_open_profile_link(string strUrl, string strProfile, string strTarget);




};