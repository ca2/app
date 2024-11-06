#pragma once


#include "time/datetime/clock.h"


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME graphical :
         virtual public clock
      {
      public:


         int_point    m_point;
         int_size     m_size;


         graphical();
         virtual ~graphical();


      };


   } // namespace clock


} // namespace datetime








