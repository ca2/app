#pragma once


#include "item.h"
#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/prototype/property_object.h"


namespace simpledb
{


   class server;


   class CLASS_DECL_AXIS storage :
      virtual public ::property_object
   {
   public:


      ::pointer<sockets::socket_handler>                m_phandler;
      ::pointer<sockets::http_session>                  m_phttpsession;
      string_map_base < item >                                m_map;
      bool                                               m_bIndexed;
      ::pointer<server>                                 m_pserver;
      string                                             m_strUser;
      ::i32                                                m_iSelectId;
      ::i32                                                m_iReplaceId;
      ::i32                                                m_iReplaceValue;
      ::pointer<class thread>                            m_pthread;
      ::pointer<class thread_localdatabase>              m_pthreadlocal;


      storage();
      ~storage() override;


      void destroy() override;


      virtual void initialize_simpledb_storage(server * pserver);


   };


} // namespace simpledb



