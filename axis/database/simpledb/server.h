#pragma once


#include "apex/database/server.h"


namespace simpledb
{


   class CLASS_DECL_AXIS server :
      virtual public ::database::server
   {
   public:


      ::pointer<::database::database>    m_pdatabaseLocal;

      ::pointer<storage>               m_pstorage;

      ::pointer<simpledb>              m_psimpledb;

      bool                                m_bWorking;

      string                              m_strDatabase;

      ::pointer<::database::database>    m_pdatabaseUser;

      string                              m_strUser;


      server();
      virtual ~server();


      ::pointer<::database::database>get_local_database();

      
      virtual bool _data_server_load(::database::client * pclient, const ::database::key & atom, get_memory getmemory, ::topic * ptopic = nullptr) override;
      virtual void _data_server_save(::database::client * pclient, const ::database::key & atom, block block, ::topic * ptopic = nullptr) override;


      virtual void create_server_dataset();


      virtual void initialize_simpledb_server(::particle * pparticle, const ::string & pszDatabase);
      virtual void destroy() override;


      virtual void initialize_user(::database::database * pdatabaseUser, const ::string & pszUser);


   };


} // namespace simpledb



