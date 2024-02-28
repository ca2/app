#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_client :
      virtual public ::object
   {
   public:

      sip_base_client_socket *   m_psocket;

      void invite(const ::string & pszTo, const ::string & pszFrom);

   };


} // namespace sockets



