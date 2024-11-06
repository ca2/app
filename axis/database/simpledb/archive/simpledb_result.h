#pragma once




namespace simpledb
{


   class database;


   class CLASS_DECL_CORE result :
      virtual public ::object
   {
   public:


      database *     m_pdatabase;
//      MYSQL_RES *    m_pres;
      int        m_iFieldCount;
      u64       m_uiAffectedRows;


      result(database * pdatabase);
      virtual ~result();


//      MYSQL_ROW fetch_row();
  //    unsigned long * fetch_lengths();
      virtual i64 num_rows();
      virtual int num_fields();

      virtual bool free_result();


   };


} //   namespace simpledb


