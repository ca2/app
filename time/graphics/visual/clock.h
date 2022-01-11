#pragma once


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::clock::visual
      {
      public:


         ::write_text::font_pointer    m_pfont;
         ::write_text::font_pointer    m_pfontHour;
         ::write_text::font_pointer    m_pfontMinute;
         ::write_text::font_pointer    m_pfontSpin;


         graphics();
         virtual ~graphics();

         virtual ::e_status initialize(::object * pobject) override;


         void GetRect(RECTANGLE_I32 * lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(point_i32 pt, size_i32 sz);



      };


   } // namespace clock


} // namespace datetime



