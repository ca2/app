#pragma once

class html_file;


#include "time/datetime/calendar.h"


namespace datetime
{


   namespace calendar
   {


      class CLASS_DECL_CA2_TIME graphical :
         virtual public calendar
      {
      public:


         point_i32          m_point;
         size_i32           m_size;
         int32_t        m_iColWidth;
         int32_t        m_iLineHeight;


         graphical();
         virtual ~graphical();


         virtual void initialize(::particle * pparticle) override;


         virtual void _001GetHtml(::html_file* pfile);






      };


   } // namespace calendar


} // namespace datetime



