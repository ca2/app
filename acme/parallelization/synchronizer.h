//
// From synchronized_predicate?... by camilo on 2022-10-25 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "signalization.h"


namespace parallelization
{


   class CLASS_DECL_ACME synchronizer :
      virtual public signalization
   {
   public:


      manual_reset_event   m_evGoingToWrite;
      manual_reset_event   m_evResponse;


      synchronizer();
      ~synchronizer();


   };


} // namespace parallelization



