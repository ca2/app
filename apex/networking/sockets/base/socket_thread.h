// Copied by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardS�rensen!!
#pragma once


namespace sockets
{

   /** Detached base_socket run thread.
   \ingroup internal */
   class CLASS_DECL_APEX socket_thread :
      virtual public ::task
   {
   public:


      __pointer(socket_handler)        m_psockethandler;
      //__pointer(base_socket)           m_psocket;


      socket_thread();
      ~socket_thread() override;


      virtual ::e_status move(socket_map::association * passociation, socket_map * psocketmap = nullptr);

      //virtual ::e_status init_thread() override;

      //virtual void term_thread() override;

      base_socket* get_socket() const;

      ::e_status run() override;

#ifdef _DEBUG

      ::i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

      ::i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   };


} // namespace sockets



