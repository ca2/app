#pragma once


#include <X11/Xft/Xft.h>


class x11_button :
   virtual public matter
{
public:


   string               m_strLabel;
   bool                 m_bTextRect;
   ::rect               m_rect;
   XGlyphInfo           m_infoText;
   bool                 m_bPress;
   bool                 m_bHover;
   enum_dialog_result   m_edialogresult;


   x11_button(const char * psz, enum_dialog_result edialogresult);

   virtual ~x11_button();


};



