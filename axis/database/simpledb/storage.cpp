#include "framework.h"
#include "_simpledb.h"
#include <sqlite3.h>
#include "storage.h"


namespace simpledb
{


   storage::storage()
   {

      m_pstmtSelect = nullptr;

      m_pstmtReplace = nullptr;

      m_iSelectId = -1;

      m_iReplaceId = -1;

      m_iReplaceValue = -1;

      defer_create_mutex();

   }


   storage::~storage()
   {

      sync_lock sl(m_pserver.is_set() && m_pserver->m_pdatabaseLocal.is_set() ?
         m_pserver->m_pdatabaseLocal->mutex() : nullptr);

      if (m_pstmtSelect != nullptr)
      {

         sqlite3_finalize(m_pstmtSelect);

         m_pstmtSelect = nullptr;

      }

      if (m_pstmtReplace != nullptr)
      {

         sqlite3_finalize(m_pstmtReplace);

         m_pstmtReplace = nullptr;

      }

   }


   ::e_status storage::initialize_simpledb_storage(server * pserver)
   {

      auto estatus = ::object::initialize(pserver);

      if (!estatus)
      {

         return estatus;

      }

      m_pserver = pserver;

      m_strUser = pserver->m_strUser;

      return estatus;

   }


} // namespace simpledb



