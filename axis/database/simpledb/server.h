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

      
      virtual bool _data_server_load(::database::client * pclient, const ::database::key & id, get_memory getmemory, ::subject * psubject = nullptr) override;
      virtual bool _data_server_save(::database::client * pclient, const ::database::key & id, block block, ::subject * psubject = nullptr) override;


      virtual bool create_server_dataset();


      virtual ::e_status initialize_simpledb_server(::object * pobject, const ::string & pszDatabase);
      virtual ::e_status destroy() override;


      virtual bool initialize_user(::database::database * pdatabaseUser, const ::string & pszUser);


   };


} // namespace simpledb



