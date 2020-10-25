#pragma once




namespace sockets
{
   /** Smtp server axis class. */
   class CLASS_DECL_AXIS smtp_socket : public tcp_socket
   {
   public:


      typedef enum 
      {

         SMTP_NO_HELLO,
         SMTP_NAME_TOO_LONG,
         SMTP_DOMAIN_TOO_LONG,
         SMTP_QUIT

      } reason_t;


      enum enum_state
      {
         state_initial,
         state_hello,
         state_auth,
         state_auth_login,
         state_auth_login_username,
         state_auth_login_password,
         state_sender,
         state_recipient,
         state_data,
         state_body,
         state_sent,
         state_quit,
         state_end
      };

      enum_state m_estate;

      __pointer(::net::email)    m_pemail;


   public:
      smtp_socket(base_socket_handler&);


      void OnLine(const string &);

      /** \return 'false' to abort */
      //virtual bool OnHello(const string & domain) = 0;

      /** \return 'false' to abort */
      //virtual bool OnMailFrom(const EmailAddress& addr) = 0;

      /** \return 'false' to abort */
      //virtual bool OnRcptTo(const EmailAddress& addr) = 0;

      //virtual void OnHeader(id idKey, const string & value) = 0;

      //virtual void OnHeaderComplete() = 0;

      //virtual void OnData(const string & line) = 0;

      /** \return 'false' if message write failed (message will probably be resent) */
      //virtual bool OnDataComplete() = 0;

      //virtual void OnRset() = 0;

      //virtual void OnAbort(reason_t) = 0;

      //virtual void OnNotSupported(const string & cmd, const string & arg) = 0;

   };

} // namespace sockets



