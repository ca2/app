#pragma once


namespace visual
{


   class CLASS_DECL_CA2_TIME clock:
      virtual public ::datetime::clock
   {
   public:


      ::draw2d::font    m_font;
      ::draw2d::font    m_fontHour;
      ::draw2d::font    m_fontMinute;
      ::draw2d::font    m_fontSpin;


      clock(::aura::application * papp);

      void GetRect(LPRECT lprect,enum EElement eelement);

      void _001OnDraw(::draw2d::graphics * pgraphics);

      void set_pos(point pt,size sz);



   };


} // namespace visual





