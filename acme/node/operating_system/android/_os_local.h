#pragma once


class os_local :
   virtual public matter
{
public:


   string         m_strApplicationIdentifier;
   string         m_strCommandLineParameters;
   ::file::path   m_pathCacheDirectory;
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
   rectangle_i32           m_rectangleEditFocus;
   bool           m_bEditFocusKill;
   
   bool           m_bRedraw;

   bool           m_bEditorSelectionUpdated;
   int            m_iEditorSelectionStart;
   int            m_iEditorSelectionEnd;

   bool           m_bEditorTextUpdated;
   string         m_strEditorText;


   bool           m_bInputMethodManagerUpdateSelection;
   int            m_iInputMethodManagerSelectionStart;
   int            m_iInputMethodManagerSelectionEnd;
   int            m_iInputMethodManagerCandidateStart;
   int            m_iInputMethodManagerCandidateEnd;


};



