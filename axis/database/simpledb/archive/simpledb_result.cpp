#include "framework.h"


namespace simpledb
{


   result::result(database * pdatabase):
      m_pdatabase(pdatabase)
   {

      //      m_pdatabase->m_resultptra.add(this);
      m_iFieldCount = -1;

   }


   result::~result()
   {

      free_result();

   }


   bool result::free_result()
   {

      return true;

   }



   i32 result::num_fields()
   {
      return -1;
   }

   i64 result::num_rows()
   {
      return -1;
   }


   /* process rows and then free the result dataset */
   //process_result_set (conn, res_set);




} // namespace simpledb


