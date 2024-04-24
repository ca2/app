#pragma once


#include "acme/primitive/primitive/get_memory.h"
#include "apex/database/client.h"


namespace simpledb
{


   class CLASS_DECL_AXIS simpledb :
      virtual public ::database::client
   {
   public:


      ::pointer<::database::dataset>        m_ppropertyset;
      class ::time                             m_timeRemoteTimeout;


      simpledb();
      ~simpledb() override;

      
      virtual void initialize_simpledb(server * pserver);


      virtual bool load(const ::scoped_string & strDataKey, get_memory getmemory);
      virtual void save(const ::scoped_string & strDataKey, block block);


      virtual bool erase(const ::scoped_string & strDataKey);

      virtual class server * server();


   };


} // namespace simpledb



