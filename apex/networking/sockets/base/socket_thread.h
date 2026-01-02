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



      ::pointer < ::factory::factory >             m_pfactorySocketHandler;
      ::platform::type                             m_typeSocketHandler;
      ::pointer < ::sockets::socket_handler >      m_psockethandler;
      long long                                        m_iAllocatedCount;
      //::platform::type                           m_typeListenSocket;
      //::pointer < ::factory::factory >    m_pfactory;


      socket_thread();
      ~socket_thread() override;


      virtual void initialize_socket_thread(::sockets::base_socket* psocket);


      void on_initialize_particle() override;


      virtual base_socket* get_socket() const;

      virtual void on_socket_thread_start();

      void run() override;

#ifdef _DEBUG

      long long increment_reference_count() override;

      long long decrement_reference_count() override;

#endif


      virtual ::pointer < ::sockets::socket_handler > create_socket_handler();


      void destroy() override;



   };


} // namespace sockets



