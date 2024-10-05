#pragma once


namespace nano
{


   namespace user
   {


      class CLASS_DECL_ACME theme :
         virtual public ::particle
      {
      public:


         enum_font                                 m_efont;

         ::pointer<::nano::graphics::brush>                     m_pbrushWindow;
         ::pointer<::nano::graphics::brush>                     m_pbrushText;
         ::pointer<::nano::graphics::brush>                     m_pbrushHyperlink;
         ::pointer<::nano::graphics::brush>                     m_pbrushHyperlinkHover;
         ::pointer<::nano::graphics::pen>                       m_ppenBorder;
         ::pointer<::nano::graphics::pen>                       m_ppenBorderFocus;
         ::pointer<::nano::graphics::pen>                       m_ppenNull;
         ::pointer<::nano::graphics::font>                      m_pfont;
         ::color::color                            m_colorText;
         ::color::color                            m_colorHyperlink;
         ::color::color                            m_colorHyperlinkHover;
         ::color::color                            m_colorFocus;
         ::color::color                            m_colorWindow;

      };


   } // namespace user


} // namespace nano



