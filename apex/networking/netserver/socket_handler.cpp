#include "framework.h"
#include "_netserver.h"


namespace netserver
{


   socket_handler::socket_handler()
   {

   }


   socket_handler::~socket_handler()
   {

   }


   void socket_handler::add(const ::sockets::socket_pointer & psocket)
   {

      m_pcomposite->add(psocket);

   }


   //void socket_handler::move2(::sockets::socket_pointer && psocket)
   //{

   //   m_pcomposite->move2(::move(psocket));

   //}

   //void socket_handler::erase(::sockets::base_socket & pbasesocket)
   //{

   //   m_pcomposite->erase(pbasesocket);

   //}

   bool socket_handler::contains(::sockets::base_socket * pbasesocket) 
   {

      return m_pcomposite->contains(pbasesocket);

   }


} // namespace netserver




