#pragma once





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
   //bool open_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrProfile = "", const ::scoped_string & scopedstrTarget = "");
   //void open_profile_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget);
   //virtual void sync_open_profile_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget);




};
