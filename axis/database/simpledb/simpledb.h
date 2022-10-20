#pragma once


#include "acme/primitive/primitive/get_memory.h"


namespace simpledb
{


   class CLASS_DECL_AXIS simpledb :
      virtual public ::database::client
   {
   public:


      ::pointer<::database::dataset>        m_ppropertyset;
      ::duration                             m_durationRemoteTimeout;


      simpledb();
      ~simpledb() override;

      
      virtual void initialize_simpledb(server * pserver);


      virtual bool load(const ::database::key & key, get_memory getmemory);
      virtual void save(const ::database::key & key, block block);


      virtual bool erase(const ::database::key & key);

      virtual class server * server();


   };


} // namespace simpledb



