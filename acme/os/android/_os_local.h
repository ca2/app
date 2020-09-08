#pragma once


class os_local :
   virtual public generic
{
public:


   string         m_strCommandLine;
   int            m_iWidth;
   int            m_iHeight;
   float          m_fDpiX;
   float          m_fDpiY;
   float          m_fDensity;
   bool           m_bShowKeyboard;
   bool           m_bHideKeyboard;
   string         m_strOpenUrl;
   
   string         m_strSetUserWallpaper;
   string         m_strGetUserWallpaper;
   bool           m_bGetUserWallpaper;

   int            m_iMessageBoxButton;
   string         m_strMessageBox;
   string         m_strMessageBoxCaption;
   bool           m_bMessageBox;
   bool           m_bMessageBoxOn;
   bool           m_iMessageBoxResult;
   long long      m_lMemFreeAvailableKb;


   bool           m_bEditFocusSet;
   rect           m_rectEditFocus;
   string         m_strEditFocus;
   int            m_iEditFocusSelBeg;
   int            m_iEditFocusSelEnd;
   bool           m_bEditFocusKill;


};



