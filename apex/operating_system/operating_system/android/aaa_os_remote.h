#pragma once




class os_remote :
   public os_object
{
public:


   using os_object::os_object;


   //String m_strCommandLine;
   JX(str, CommandLine);
   //String m_strCacheDir;
   JX(str, CacheDir);
   //int m_iWidth;
   JX(i, Width);
   //int m_iHeight;
   JX(i, Height);
   //float m_fDpiX;
   JX(f, DpiX);
   //float m_fDpiY;
   JX(f, DpiY);
   //float m_fDensity;
   JX(f, Density);
   //boolean m_bShowKeyboard;
   JX(b, ShowKeyboard);
   //boolean m_bHideKeyboard;
   JX(b, HideKeyboard);
   //String m_strOpenUrl;
   JX(str, OpenUrl);
   //String m_strUserWallpaper;
   JX(str, UserWallpaper);
   //int m_iShowMessageBox;
   JX(i, ShowMessageBox);
   //String m_strMessageBox;
   JX(str, MessageBox);
   //String m_strMessageBoxCaption;
   JX(str, MessageBoxCaption);
   //int m_iMessageBoxButton;
   JX(i, MessageBoxButton);
   //int m_iMessageBoxResult;
   JX(i, MessageBoxResult);
   //long m_lMemFreeAvailableKb;
   JX(l, MemFreeAvailableKb);
   //boolean m_bEditFocusSet;
   JX(b, EditFocusSet);
   //int m_iEditFocusLeft;
   JX(i, EditFocusLeft);
   //int m_iEditFocusTop;
   JX(i, EditFocusTop);
   //int m_iEditFocusRight;
   JX(i, EditFocusRight);
   //int m_iEditFocusBottom;
   JX(i, EditFocusBottom);
   //String m_strEditFocusText;
   JX(str, EditFocusText);
   //int m_iEditFocusSelBeg;
   JX(i, EditFocusSelBeg);
   //int m_iEditFocusSelEnd;
   JX(i, EditFocusSelEnd);
   //boolean m_bEditFocusKill;
   JX(b, EditFocusKill);
   //boolean m_bRedraw;
   JX(b, Redraw);
   //int m_iEditorSelectionStart;
   JX(i, EditorSelectionStart);
   //int m_iEditorSelectionEnd;
   JX(i, EditorSelectionEnd);
   //String m_strEditorText;
   JX(str, EditorText);
   //boolean m_bInputMethodManagerUpdateSelection;
   JX(b, InputMethodManagerUpdateSelection);
   //int m_iInputMethodManagerSelectionStart;
   JX(i, InputMethodManagerSelectionStart);
   //int m_iInputMethodManagerSelectionEnd;
   JX(i, InputMethodManagerSelectionEnd);
   //int m_iInputMethodManagerCandidateStart;
   JX(i, InputMethodManagerCandidateStart);
   //int m_iInputMethodManagerCandidateEnd;
   JX(i, InputMethodManagerCandidateEnd);


};


