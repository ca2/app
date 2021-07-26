// Copied by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace sockets
{

   /** Detached base_socket run thread.
   \ingroup internal */
   class CLASS_DECL_APEX socket_thread :
      virtual public ::task
   {
   public:


      __composite(socket_handler)    m_phandler;
      __reference(base_socket)       m_psocket;


      socket_thread();
      ~socket_thread() override;


      virtual ::e_status start_socket_thread(base_socket* psocket);

      //virtual ::e_status init_thread() override;

      //virtual void term_thread() override;

      base_socket* get_socket() const { return m_psocket; }

      ::e_status run() override;

#ifdef DEBUG

      ::i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

      ::i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   };


} // namespace sockets



