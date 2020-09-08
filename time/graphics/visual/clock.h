#pragma once


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME graphics :
         virtual public ::datetime::clock::visual
      {
      public:


         ::draw2d::font    m_font;
         ::draw2d::font    m_fontHour;
         ::draw2d::font    m_fontMinute;
         ::draw2d::font    m_fontSpin;


         graphics();
         virtual ~graphics();

         virtual ::estatus initialize(::object* pobjectContext) override;


         void GetRect(LPRECT lprect, enum enum_element eelement);

         void _001OnDraw(::draw2d::graphics* pgraphics);

         void set_pos(point pt, size sz);



      };


   } // namespace clock


} // namespace datetime



