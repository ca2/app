// Copied by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/parallelization/task.h"


namespace sockets
{

   /** Detached base_socket run thread.
   \ingroup internal */
   class CLASS_DECL_APEX socket_thread :
      virtual public ::task
   {
   public:


      ::i64                            m_iAllocatedCount;
      ::pointer<socket_handler>        m_psockethandler;
      //::pointer<base_socket>         m_psocket;


      socket_thread();
      ~socket_thread() override;


      void on_initialize_particle() override;


      //virtual void transfer(socket_map::association * passociation, socket_map * psocketmap = nullptr);

      //virtual void init_thread() override;

      //virtual void term_thread() override;

      virtual base_socket* get_socket() const;

      void run() override;

#ifdef _DEBUG

      ::i64 increment_reference_count() override;

      ::i64 decrement_reference_count() override;

#endif


   };


} // namespace sockets



