#pragma once


namespace visual
{


   class CLASS_DECL_CA2_TIME clock:
      virtual public ::datetime::clock
   {
   public:


      ::draw2d::font_pointer    m_font;
      ::draw2d::font_pointer    m_fontHour;
      ::draw2d::font_pointer    m_fontMinute;
      ::draw2d::font_pointer    m_fontSpin;


      clock(::object * pobject);

      void GetRect(LPRECT lprect,enum EElement eelement);

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void set_pos(const ::point & point,size sz);



   };


} // namespace visual



