#pragma once


class CLASS_DECL_AURA hyperlink :
   virtual public ::object
{
public:


   hyperlink(::context_object * pcontextobject);
   virtual ~hyperlink();

   virtual bool open_link(string strLink, string strProfile = "", string strTarget = "");
   virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
   //virtual void sync_open_profile_link(string strUrl, string strProfile, string strTarget);




};