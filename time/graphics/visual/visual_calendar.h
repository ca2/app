#pragma once


namespace visual
{


   class CLASS_DECL_CA2_TIME calendar:
      virtual public ::calendar
   {
   public:


      ::draw2d::font_sp    m_font;
      ::draw2d::font_sp    m_fontYear;
      ::draw2d::font_sp    m_fontMonth;
      ::draw2d::font_sp    m_fontSpin;


      calendar(::aura::application * papp);


      virtual void GetRectDay(::datetime::time & time,LPRECT lprect);
      virtual void GetRectDay(int32_t iWeekDay,int32_t iLine,LPRECT lprect);
      virtual void GetRect(LPRECT lprect,enum EElement eelement);

      void _001OnDraw(::draw2d::graphics * pgraphics);

      void set_pos(point pt,size sz);

      virtual EElement hit_test(point pt);
      virtual bool hit_test(EElement eelement,point pt);
      virtual bool time_hit_test(::datetime::time & time,point pt);

   };




} // namespace visual



