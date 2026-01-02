#pragma once


//typedef struct st_mysql_res MYSQL_RES;
//typedef char **MYSQL_ROW;		/* return data as array of strings */
//
//#ifndef UNIVERSAL_WINDOWS
//
//
//namespace mysql
//{
//
//
//   class database;
//
//
//   class CLASS_DECL_CA2_DATA dataset :
//      virtual public ::database::dataset
//   {
//   public:
//
//
//      MYSQL_RES *    m_pres;
//
//
//      dataset(database * pdatabase, MYSQL_RES * pres);
//      virtual ~dataset();
//
//
//      MYSQL_ROW fetch_row();
//      unsigned long * fetch_lengths();
//      long long num_rows();
//      int num_fields();
//
//      bool free_result();
//
//
//   };
//
//
//} //   namespace mysql
//
//
//#endif
