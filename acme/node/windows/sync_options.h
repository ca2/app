#pragma once


namespace windows
{


   class CLASS_DECL_AURA sync_options :
      virtual ::sync_options
   {
   public:


      sync_options(LPSECURITY_ATTRIBUTES * lpsa) :
         m_lpsa(lpsa)
      {


      }

      virtual ~sync_options();

      LPSECURITY_ATTRIBUTES   m_lpsa;


   };


   class null_dacl_sync_options :
      virtual public sync_options
   {
   public:

      SECURITY_ATTRIBUTES m_securityattributes;

      SECURITY_DESCRIPTOR m_securitydescriptor;

      null_dacl_security_attributes();

   };

} // namespace windows