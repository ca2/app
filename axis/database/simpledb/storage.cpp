#include "framework.h"
#include "storage.h"
#include "server.h"


namespace simpledb
{


   storage::storage()
   {

      //m_pstmtSelect = nullptr;

      //m_pstmtReplace = nullptr;

      m_iSelectId = -1;

      m_iReplaceId = -1;

      m_iReplaceValue = -1;

      defer_create_synchronization();

   }


   storage::~storage()
   {


   }


   void storage::initialize_simpledb_storage(server * pserver)
   {

      //auto estatus = 
      
      ::matter::initialize(pserver);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pserver = pserver;

      m_strUser = pserver->m_strUser;

      //return estatus;

   }


} // namespace simpledb



