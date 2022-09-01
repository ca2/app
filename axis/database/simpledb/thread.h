#pragma once


#include "apex/networking/sockets/basic/socket_handler.h"


namespace simpledb
{

   class storage;


   class CLASS_DECL_AXIS thread :
      virtual public ::thread
   {
   public:


      storage *                                 m_pstorage;
      sockets::socket_handler                   m_handler;
      __pointer(sockets::http_session)          m_phttpsession;

      pointer_array < queue_item >              m_itema;


      thread()
      {

      }

      virtual ~thread() {}


      virtual void     run() override;

      void queue(const ::string & pszKey, block block);

   };


} // namespace simpledb



