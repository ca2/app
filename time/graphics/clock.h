#pragma once


#include "time/graphical/clock.h"
//#include "acme/prototype/prototype/pointer.h"


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::clock::graphical
      {
      public:


         ::write_text::font_pointer    m_pfont;
         ::write_text::font_pointer    m_pfontHour;
         ::write_text::font_pointer    m_pfontMinute;
         ::write_text::font_pointer    m_pfontSpin;


         graphics();
         ~graphics() override;

         
         void initialize(::particle * pparticle) override;


         void GetRect(::int_rectangle * lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(int_point pt, int_size sz);



      };


   } // namespace clock


} // namespace datetime



