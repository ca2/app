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


         point_i32    m_point;
         size_i32     m_size;


         graphical();
         virtual ~graphical();


      };


   } // namespace clock


} // namespace datetime








