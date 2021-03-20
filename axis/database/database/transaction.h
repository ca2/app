#pragma once


namespace database
{


   class CLASS_DECL_AXIS transaction :
      virtual public context_object
   {
   public:


      bool                    m_bProcessed;
      __pointer(database)     m_pdatabase;


      transaction(database* pdatabase);
      virtual ~transaction();


      virtual void rollback();
      virtual void commit();


   };


} // namespace database



