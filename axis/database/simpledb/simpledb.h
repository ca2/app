#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS simpledb :
      virtual public ::database::client
   {
   public:


      __pointer(::database::dataset)         m_ppropertyset;
      ::duration                             m_durationRemoteTimeout;


      simpledb();
      virtual ~simpledb();

      
      virtual ::e_status initialize_simpledb(server * pserver);


      bool load(const ::database::key & key, get_memory getmemory);
      bool save(const ::database::key & key, block block);


      bool erase(const ::database::key & key);

      virtual class server * server();


   };


} // namespace simpledb



