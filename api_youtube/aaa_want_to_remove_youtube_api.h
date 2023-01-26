#pragma once


namespace youtube
{


   class CLASS_DECL_APP_CORE_YOUTUBE api :
      virtual public object
   {
   public:


      string      m_strApiProfile;
      ::u32       m_dwApiSleep;
      string      m_strScopes;


      api(::particle * pparticle, const ::string & pszApiProfile);
      virtual ~api();


      virtual ::pointer< ::mutex > get_api_mutex() = 0;

      virtual string get_local_path() = 0;

      virtual string youtube_api_authorization(bool bForce);

      virtual void log(string strOutput);

      virtual string randomDataBase64url(u32 uiLength);

      virtual memory sha256(string str);

      virtual string base64urlencodeNoPadding(memory m);

      virtual bool api_get(string strGet, ::payload & payload, property_set * pset);


   };


} // namespace resident_youtube



