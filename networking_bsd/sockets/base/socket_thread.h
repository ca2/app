// Copied by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace sockets_bsd
{

   /** Detached base_socket run thread.
   \ingroup internal */
   class CLASS_DECL_NETWORKING_BSD socket_thread :
      virtual public ::task
   {
   public:


      ::pointer<socket_handler>       m_psockethandler;
      //::pointer<base_socket>          m_psocket;


      socket_thread();
      ~socket_thread() override;


      virtual void move(socket_map::association * passociation, socket_map * psocketmap = nullptr);

      //virtual void init_thread() override;

      //virtual void term_thread() override;

      base_socket* get_socket() const;

      void run() override;

#ifdef _DEBUG

      ::i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

      ::i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   };


} // namespace sockets_bsd



