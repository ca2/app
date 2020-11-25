#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS server :
      virtual public ::database::server
   {
   public:


      __pointer(::database::database)     m_pdatabaseLocal;

      __composite(storage)                m_pstorage;

      __composite(simpledb)               m_psimpledb;

      bool                                m_bWorking;

      string                              m_strDatabase;

      __pointer(::database::database)     m_pdatabaseUser;

      string                              m_strUser;


      server();
      virtual ~server();


      __pointer(::database::database) get_local_database();

      
      virtual bool _data_server_load(::database::client * pclient, const ::database::key & id, get_memory getmemory, ::promise::subject * psubject = nullptr) override;
      virtual bool _data_server_save(::database::client * pclient, const ::database::key & id, block block, ::promise::subject * psubject = nullptr) override;


      virtual bool create_server_dataset();


      virtual ::estatus initialize_simpledb_server(::layered * pobjectContext, const char * pszDatabase);
      virtual void finalize() override;


      virtual bool initialize_user(::database::database * pdatabaseUser, const char * pszUser);


   };


} // namespace simpledb



