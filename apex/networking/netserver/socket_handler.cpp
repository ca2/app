#include "framework.h"
#include "socket_handler.h"
//#include "_netserver.h"


namespace netserver
{


   socket_handler::socket_handler()
   {

   }


   socket_handler::~socket_handler()
   {

   }


   void socket_handler::add(::sockets::base_socket * psocket)
   {

      m_pcomposite->add(psocket);

   }

   void socket_handler::erase(const ::sockets::socket_pointer & psocket)
   {

      m_pcomposite->erase(psocket);

   }


   //void socket_handler::move2(::sockets::socket_pointer && psocket)
   //{

   //   m_pcomposite->move2(::transfer(psocket));

   //}

   //void socket_handler::erase(::sockets::socket_interface & pbasesocket)
   //{

   //   m_pcomposite->erase(pbasesocket);

   //}


   bool socket_handler::contains(::sockets::base_socket * pbasesocket) 
   {

      return m_pcomposite->contains(pbasesocket);

   }


} // namespace netserver




