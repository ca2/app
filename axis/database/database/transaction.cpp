#include "framework.h"


namespace database
{


   transaction::transaction(database* pdatabase) :
      m_pdatabase(pdatabase),
      m_bProcessed(false)
   {
      
      pdatabase->start_transaction();

   }


   transaction::~transaction()
   {

      rollback();

   }


   void transaction::commit()
   {
      if (!m_bProcessed)
      {
         m_bProcessed = true;
         m_pdatabase->commit_transaction();

      }
   }
   void transaction::rollback()
   {
      if (!m_bProcessed)
      {
         m_bProcessed = true;
         m_pdatabase->rollback_transaction();

      }
   }


} // namespace database



