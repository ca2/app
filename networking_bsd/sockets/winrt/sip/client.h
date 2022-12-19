#pragma once


namespace sockets
{


   class CLASS_DECL_APEX sip_client :
      virtual public ::object
   {
   public:

      sip_base_client_socket *   m_psocket;

      void invite(const scoped_string & strTo, const scoped_string & strFrom);

   };


} // namespace sockets



