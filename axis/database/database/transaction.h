#pragma once


#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/pointer.h"


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



