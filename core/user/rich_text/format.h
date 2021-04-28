#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE format :
         virtual public object
      {
      public:


         __pointer_array(format) *     m_pcontainer;
         index                         m_iIndex;

         bool                          m_bBold;
         bool                          m_bItalic;
         bool                          m_bUnderline;
         string                        m_strFontFamily;
         double                        m_dFontSize;
         color32_t                     m_colorForeground;
         color32_t                     m_colorBackground;
         e_script                      m_escript;
         e_line_height                 m_elineheight;


         // cache or transport (not serialized)
         mutable bool                 m_bUpdated;
         mutable ::write_text::font_pointer    m_font;
         mutable ::e_align              m_ealign;


         format();
         format(__pointer_array(format)* pcontainer);
         format(const format & format);
         virtual ~format();


         virtual ::e_status initialize_user_rich_text_format(__pointer_array(format)* pcontainer);
         //virtual ::stream & write(::stream & stream) const override;
         //virtual ::stream & read(::stream & stream) override;

         virtual void exchange(::stream & stream) override;


         void apply(const format * pformat, const eattribute & eattribute);

         ::write_text::font * get_font(::draw2d::graphics_pointer & pgraphics) const;

         bool operator == (const format & format) const;
         format & operator = (const format & format);

         void intersect(const format & format);


      };


   } // namespace rich_text


} // namespace user




