// Copied by camilo on 2021-07-26 02:20 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/networking/sockets/base/socket_thread.h"
#include "networking_bsd/sockets/_collection.h"
#include "acme/parallelization/task.h"


namespace sockets_bsd
{

   /** Detached base_socket run thread.
   \ingroup internal */
   class CLASS_DECL_NETWORKING_BSD socket_thread :
      virtual public ::sockets::socket_thread
   {
   public:


//      ::pointer<socket_handler>       m_psockethandler;
//      //::pointer<base_socket>          m_psocket;
//
//
      socket_thread();
      ~socket_thread() override;
//
//
      //
      // virtual void transfer(socket_map::node * pnode, socket_map * psocketmap = nullptr);
      void initialize_socket_thread(base_socket* psocket);
//
//      //virtual void init_thread() override;
//
//      //virtual void term_thread() override;
//
      ::sockets::base_socket* get_socket() const override;
//
//      void run() override;
//
//#ifdef _DEBUG
//
//      ::i64 increment_reference_count() override;
//
//      ::i64 decrement_reference_count() override;
//
//#endif
//

   };


} // namespace sockets_bsd



