#pragma once


namespace database
{


   class CLASS_DECL_AXIS transaction :
      virtual public ::particle
   {
   public:


      bool                    m_bProcessed;
      ::pointer<database>     m_pdatabase;


      transaction(database* pdatabase);
      ~transaction() override;


      virtual void rollback();
      virtual void commit();


   };


} // namespace database



