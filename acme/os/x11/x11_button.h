#pragma once


class x11_button :
   virtual public matter
{
public:


   string            m_strLabel;
   bool              m_bTextRect;
   ::rect            m_rect;
   XGlyphInfo        m_infoText;
   bool              m_bPress;
   bool              m_bHover;
   int               m_iResult;


   x11_button(const char * psz, int iResult);

   virtual ~x11_button();


};



