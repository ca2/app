#pragma once


//#include "acme/prototype/collection/pointer_array.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "apex/parallelization/thread.h"


namespace simpledb
{

   class storage;


   class CLASS_DECL_AXIS thread :
      virtual public ::thread
   {
   public:


      storage *                                 m_pstorage;
      ::pointer<sockets::socket_handler>       m_phandler;
      ::pointer<sockets::http_session>         m_phttpsession;

      pointer_array < queue_item >              m_itema;


      thread()
      {

      }

      virtual ~thread() {}


      virtual void     run() override;

      void queue(const ::scoped_string & scopedstrKey, block block);

   };


} // namespace simpledb



