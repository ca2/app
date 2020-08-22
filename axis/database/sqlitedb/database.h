#pragma once


namespace sqlite
{


   class CLASS_DECL_AXIS database :
      public ::database::database
   {
   public:


      void *      m_psqlite;


      database();
      virtual ~database();


   protected:

      virtual void start_transaction() override;
      virtual void commit_transaction() override;
      virtual void rollback_transaction() override;

   public:


      virtual __pointer(::database::result_set) query_result(const char * pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;

      //virtual __pointer(::database::dataset) dataset() override;
      virtual ::database::e_connection connection_status() override;

      virtual ::estatus     set_error_code(i32 iErrorCode) override;

      virtual void * get_handle() override;
      virtual string get_error_message() override;

      virtual ::estatus     _connect() override;
      virtual void disconnect() override;
      virtual ::estatus     create() override;
      virtual ::estatus     drop() override;



      virtual bool exec(const char * pszQuery) override;

      string escape(const char * psz) override;



   };

} // namespace sqlite

