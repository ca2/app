#pragma once


class x11_button :
   virtual public element
{
public:


   string            m_strLabel;
   bool              m_bTextRect;
   ::rect            m_rect;
   XGlyphInfo        m_infoText;
   bool              m_bPress;
   bool              m_bHover;
   string            m_strResult;


   x11_button(const char * psz, const char * pszResult);

   virtual ~x11_button();


};



