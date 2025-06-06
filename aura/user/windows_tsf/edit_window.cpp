#include "framework.h"
#include "acme/operating_system.h"
////#include "aura/user/user/_component.h"
#include "edit_window.h"
//#include "aura/message.h"
#include "apex/platform/app_core.h"
#include "aura/user/interaction_thread.h"
#include "aura/os/windows_common/variant.h"
#include "Globals.h"
#include <ctffunc.h>


/*
None of the GUIDs in TSATTRS.H are defined in a LIB, so you have to include 
INITGUID.H just before the first time you include TSATTRS.H
*/
#include <initguid.h>
#include <tsattrs.h>
#include <tchar.h>


namespace tsf
{

   TCHAR   g_szTSFEditClassName[] = TEXT("TSFEditWndClass");

   #define THIS_POINTER_OFFSET   GWLP_USERDATA


   edit_window::edit_window()
   {
       //m_hWnd = NULL;
       //m_hwndEdit = hwndEdit;
       //m_hwndStatus = NULL;
      m_tfClientID = NULL;


       m_hInst = NULL;
       //m_ObjRefCount = 1;
       //m_hwndParent = hwndParent;
       //m_pthreadmgr = NULL;
       ///m_pDocMgr = NULL;
       //m_pPrevDocMgr = NULL;
       //m_pContext = NULL;
       m_fLocked = false;
       m_dwLockType = 0;
       m_fPendingLockUpgrade = false;
       m_acpStart = 0;
       m_acpEnd = 0;
       m_fInterimChar = false;
       m_ActiveSelEnd = TS_AE_START;
       m_pServices = NULL;
       m_cCompositions = 0;
       //m_pCategoryMgr = NULL;
       //m_pDisplayAttrMgr = NULL;
       m_fLayoutChanged = false;
       m_fNotify = true;
       m_cchOldLength = 0;

       ZeroMemory(&m_AdviseSink, sizeof(m_AdviseSink));

   }

   edit_window::~edit_window()
   {
       /*
       Make sure the advise sink is cleaned up. This should have been done 
       before, but this is just in case.
       */
       _ClearAdviseSink(&m_AdviseSink);

       if(m_pServices)
       {
           m_pServices->Release();
           m_pServices = NULL;
       }
    
       _Uninitialize();
   }


   void edit_window::install_message_routing(::channel* pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &edit_window::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &edit_window::on_message_destroy);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &edit_window::on_message_set_focus);
      MESSAGE_LINK(e_message_kill_focus, pchannel, this, &edit_window::on_message_kill_focus);

   }

   BOOL edit_window::_Initialize(ITfThreadMgr *ptm, TfClientId tfcId)
   {
       HRESULT hr;

       //InitCommonControls();

       //m_AdviseSink.dwMask |= TS_AS_TEXT_CHANGE;
    
       m_tfClientID = tfcId;
       hr = ptm->QueryInterface(IID_ITfThreadMgr, (LPVOID*)&m_pthreadmgr);
       if(FAILED(hr))
       {
           return false;
       }

       hr = CoCreateInstance(  CLSID_TF_CategoryMgr,
                               NULL, 
                               CLSCTX_INPROC_SERVER, 
                               IID_ITfCategoryMgr, 
                               (LPVOID*)&m_pCategoryMgr);
       if(FAILED(hr))
       {
           return false;
       }
    

       //create the display attribute manager
       hr = CoCreateInstance(  CLSID_TF_DisplayAttributeMgr,
                               NULL, 
                               CLSCTX_INPROC_SERVER, 
                               IID_ITfDisplayAttributeMgr, 
                               (LPVOID*)&m_pDisplayAttrMgr);
       if(FAILED(hr))
       {
           return false;
       }

    
       //create the document manager
       hr = m_pthreadmgr->CreateDocumentMgr(&m_pDocMgr);
       if(FAILED(hr))
       {
           return false;
       }

       //create the context
       hr = m_pDocMgr->CreateContext(  tfcId, 
                                       0, 
                                       (ITextStoreACP*)this, 
                                       &m_pContext, 
                                       &m_EditCookie);
       if(FAILED(hr))
       {
           return false;
       }

       //push the context onto the document stack
       hr = m_pDocMgr->Push(m_pContext);
       if(FAILED(hr))
       {
           return false;
       }

       comptr < ITfSource > psource;

       hr = m_pthreadmgr.As(psource);

       if (FAILED(hr))
       {
          return false;
       }

       hr = psource->AdviseSink(IID_ITfUIElementSink, (ITfUIElementSink *)this, &m_AdviseSink.dwUIElementCookie);
       
    
       //WNDCLASS  wc;

       ////If the class is not already registered, register it.
       //if(!GetClassInfo(m_hInst, g_szTSFEditClassName, &wc))
       //{
       //    ZeroMemory(&wc, sizeof(wc));

       //    wc.style          = CS_HREDRAW | CS_VREDRAW;
       //    wc.lpfnWndProc    = edit_window::_WndProc;
       //    wc.cbClsExtra     = 0;
       //    wc.cbWndExtra     = sizeof(edit_window*);
       //    wc.hInstance      = m_hInst;
       //    wc.hIcon          = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MAIN_ICON));
       //    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
       //    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
       //    wc.lpszMenuName   = MAKEINTRESOURCE(IDR_MAIN_MENU);
       //    wc.lpszClassName  = g_szTSFEditClassName;

       //    if(0 == RegisterClass(&wc))
       //    {
       //        return false;
       //    }
       //}
       //create the main window
       //m_hWnd = CreateWindowEx(    0,
       //                            g_szTSFEditClassName,
       //                            NULL,
       //                            WS_OVERLAPPED |
       //                                WS_CHILD |
       //                                WS_VISIBLE |
       //                                WS_TABSTOP,
       //                            CW_USEDEFAULT,
       //                            CW_USEDEFAULT,
       //                            CW_USEDEFAULT,
       //                            CW_USEDEFAULT,
       //                            m_hwndParent,
       //                            NULL,
       //                            m_hInst,
       //                            (LPVOID)this);

       //if(m_hwndEdit != NULL)
       //{
           //m_hwndEdit = CreateWindowEx(    WS_EX_CLIENTEDGE,
           //                                TEXT("edit"),
           //                                NULL,
           //                                WS_CLIPSIBLINGS | 
           //                                    WS_CHILD | 
           //                                    WS_VISIBLE | 
           //                                    WS_BORDER | 
           //                                    WS_VSCROLL | 
           //                                    ES_AUTOVSCROLL | 
           //                                    ES_MULTILINE,
           //                                0, 0, 0, 0,
           //                                m_hWnd,
           //                                (HMENU)IDC_EDIT,
           //                                m_hInst,
           //                                NULL);
           //if(NULL == m_hwndEdit)
           //{
           //    return false;
           //}

           ////create the status bar
           //m_hwndStatus = CreateStatusWindow(  WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
           //                                    NULL,
           //                                    m_hWnd,
           //                                    IDC_STATUSBAR);

           //if(m_hwndStatus)
           //{
           //    _UpdateStatusBar();
           //}


           //initialize the supported attributes
           TfGuidAtom guidatom;
        
           //mode bias
           m_rgAttributes[ATTR_INDEX_MODEBIAS].dwFlags = 0;
           m_rgAttributes[ATTR_INDEX_MODEBIAS].attrid = &GUID_PROP_MODEBIAS;
           VariantInit(&(m_rgAttributes[ATTR_INDEX_MODEBIAS].varValue));
           hr = m_pCategoryMgr->RegisterGUID(GUID_MODEBIAS_NONE, &guidatom);
           if(FAILED(hr))
           {
               guidatom = TF_INVALID_GUIDATOM;
           }
           m_rgAttributes[ATTR_INDEX_MODEBIAS].varDefaultValue.vt = VT_I4;
           m_rgAttributes[ATTR_INDEX_MODEBIAS].varDefaultValue.lVal = guidatom;

           //text orientation - this is a VT_I4 that is always zero in this app
           m_rgAttributes[ATTR_INDEX_TEXT_ORIENTATION].dwFlags = 0;
           m_rgAttributes[ATTR_INDEX_TEXT_ORIENTATION].attrid = &TSATTRID_Text_Orientation;
           VariantInit(&m_rgAttributes[ATTR_INDEX_TEXT_ORIENTATION].varValue);
           m_rgAttributes[ATTR_INDEX_TEXT_ORIENTATION].varDefaultValue.vt = VT_I4;
           m_rgAttributes[ATTR_INDEX_TEXT_ORIENTATION].varDefaultValue.lVal = 0;

           //vertical writing - this is a VT_BOOL that is always false in this app
           m_rgAttributes[ATTR_INDEX_TEXT_VERTICALWRITING].dwFlags = 0;
           m_rgAttributes[ATTR_INDEX_TEXT_VERTICALWRITING].attrid = &TSATTRID_Text_VerticalWriting;
           VariantInit(&m_rgAttributes[ATTR_INDEX_TEXT_VERTICALWRITING].varValue);
           m_rgAttributes[ATTR_INDEX_TEXT_VERTICALWRITING].varDefaultValue.vt = VT_BOOL;
           m_rgAttributes[ATTR_INDEX_TEXT_VERTICALWRITING].varDefaultValue.lVal = false;

           _InitFunctionProvider();
        

   #ifdef USE_ASSOC_FOCUS
           /*
           Associate the focus with this window. The TSF Manager watches for
           focus changes throughout the system. When a window handle that has
           been associated gets the focus, it then knows the window receiving
           the focus is TSF enabled.
           */
           hr = m_pthreadmgr->AssociateFocus(m_hwndEdit2, m_pDocMgr, &m_pPrevDocMgr);
   #endif

           //UpdateWindow(m_hWnd);

           return true;
       //}

       //return false;
   }

   /**************************************************************************

      edit_window::_Uninitialize()

   **************************************************************************/

   void edit_window::_Uninitialize()
   {
       if(m_pthreadmgr)
       {
           _UninitFunctionProvider();

   #ifdef USE_ASSOC_FOCUS
           ITfDocumentMgr *pTempDocMgr = NULL;

           /*
           Its okay if m_pPrevDocMgr is NULL as this will just disassociate the 
           focus from the window.
           */
           m_pthreadmgr->AssociateFocus(m_hwndEdit, m_pPrevDocMgr, &pTempDocMgr);

           if(pTempDocMgr)
           {
               pTempDocMgr->Release();
           }
    
           if(m_pPrevDocMgr)
           {
               m_pPrevDocMgr->Release();
               m_pPrevDocMgr = NULL;
           }
   #endif

           int i;

           for (i = 0; i < NUM_SUPPORTED_ATTRS; i++)
           {
               VariantClear(&m_rgAttributes[i].varValue);
               VariantClear(&m_rgAttributes[i].varDefaultValue);
               m_rgAttributes[i].dwFlags = ATTR_FLAG_NONE;
           }

           if(m_pDocMgr)
           {
               //pop all of the contexts off of the stack
               m_pDocMgr->Pop(TF_POPF_ALL);
        
               m_pDocMgr->Release();
               m_pDocMgr = NULL;
           }

           if(m_pDisplayAttrMgr)
           {
               m_pDisplayAttrMgr->Release();
               m_pDisplayAttrMgr = NULL;
           }
        
           if(m_pContext)
           {
               m_pContext->Release();
               m_pContext = NULL;
           }
    
           if(m_pCategoryMgr)
           {
               m_pCategoryMgr->Release();
               m_pCategoryMgr = NULL;
           }

           m_pthreadmgr->Release();
           m_pthreadmgr = NULL;
       }
   }

   /**************************************************************************

      edit_window::_GetWindow()
   
   **************************************************************************/

   //HWND edit_window::_GetWindow()
   //{
   //    return m_hWnd;
   //}

   /**************************************************************************

      edit_window::_OnGetPreservedKey()
   
   **************************************************************************/

   HRESULT edit_window::_OnGetPreservedKey()
   {
       HRESULT hr;
       ITfKeystrokeMgr *pKeyMgr;
    
       hr = m_pthreadmgr->QueryInterface(IID_ITfKeystrokeMgr, (LPVOID*)&pKeyMgr);
       if(SUCCEEDED(hr))
       {
           GUID            guid;
           TF_PRESERVEDKEY tfPreKey;

           tfPreKey.uVKey = 'F';
           tfPreKey.uModifiers = TF_MOD_CONTROL;
        
           hr = pKeyMgr->GetPreservedKey(m_pContext, &tfPreKey, &guid);

           if(SUCCEEDED(hr) && !IsEqualGUID(guid, GUID_NULL))
           {
               BOOL fPreserved;

               hr = pKeyMgr->IsPreservedKey(guid, &tfPreKey, &fPreserved);

        
               BOOL    fEaten;

               guid.Data1 = 12;
               hr = pKeyMgr->SimulatePreservedKey(m_pContext, guid, &fEaten);
           }
        
           pKeyMgr->Release();
       }

       return S_OK;
   }

   /**************************************************************************

      edit_window::_WndProc()
   
   **************************************************************************/

   //lresult CALLBACK edit_window::_WndProc( HWND hWnd, 
   //                                        unsigned int uMessage,
   //                                        wparam wParam, 
   //                                        lparam lParam)
   //{
   //    edit_window *pThis = (edit_window*)GetWindowLongPtr(hWnd, THIS_POINTER_OFFSET);
   //
   //    if((NULL == pThis) && (uMessage != e_message_non_client_create))
   //    {
   //        return default_window_procedure(hWnd, uMessage, wParam, lParam);
   //    }
   //    
   //    switch (uMessage)
   //    {
   //    case e_message_non_client_create:
   //        {
   //            LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
   //            pThis = (edit_window*)(lpcs->lpCreateParams);
   //            SetWindowLongPtr(hWnd, THIS_POINTER_OFFSET, (LONG_PTR)pThis);
   //
   //            //set the window handle
   //            pThis->m_hWnd = hWnd;
   //
   //            /*
   //            AddRef() the object. Release() will be called in e_message_non_client_destroy.
   //            Many owners will call Release during their e_message_destroy, but the 
   //            child window isn't destroyed until after the parent, so the object 
   //            gets deleted while the window still exists. Calling Release() 
   //            ourselves in e_message_non_client_destroy ensures the object exists for the entire
   //            life of the window.
   //            */
   //            pThis->AddRef();
   //        }
   //        break;
   //
   //    case e_message_create:
   //        return pThis->_OnCreate();
   //
   //    case e_message_size:
   //        return pThis->_OnSize(wParam, lParam);
   //
   //    case e_message_destroy:
   //        return pThis->_OnDestroy();
   //
   //    case e_message_set_focus:
   //        return pThis->_OnSetFocus();
   //
   //    case e_message_kill_focus:
   //        return pThis->_OnKillFocus();
   //
   //    case e_message_command:
   //        return pThis->_OnCommand(   GET_WM_COMMAND_ID(wParam, lParam), 
   //                                    GET_WM_COMMAND_CMD(wParam, lParam), 
   //                                    GET_WM_COMMAND_HWND(wParam, lParam));
   //
   //    case e_message_non_client_destroy:
   //        pThis->Release();
   //        
   //        pThis->m_hWnd = NULL;
   //        break;
   //
   //    }
   //
   //    return default_window_procedure(hWnd, uMessage, wParam, lParam);
   //}

   /**************************************************************************

      edit_window::_OnCreate()

   **************************************************************************/

   lresult edit_window::_OnCreate(VOID)
   {

      m_hInst = psystem->m_hinstance;

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

      _Initialize(get_wnd()->m_pimpl2->m_puserthread->m_pthreadmgr, get_wnd()->m_pimpl2->m_puserthread->m_tfClientID);

#endif

      return 0;

   }


   /**************************************************************************

      edit_window::_OnDestroy()

   **************************************************************************/

   lresult edit_window::_OnDestroy(VOID)
   {
       _Uninitialize();
    
       //PostQuitMessage(0);
    
       return 0;
   }

   /**************************************************************************

      edit_window::_OnCommand()

   **************************************************************************/

   //lresult edit_window::_OnCommand(unsigned short wID, unsigned short wCmd, HWND hWnd)
   //{
   //    switch(wID)
   //    {
   //    case IDC_EDIT:
   //        switch(wCmd)
   //        {
   //        case EN_SETFOCUS:
   //            _OnEditSetFocus();
   //            break;
   //
   //        case EN_KILLFOCUS:
   //            _OnEditKillFocus();
   //            break;
   //        
   //        case EN_CHANGE:
   //            _OnEditChange();
   //            break;
   //
   //        }
   //        break;
   //    }
   //
   //    return 0;
   //}

   /**************************************************************************

      edit_window::_OnSetFocus()

   **************************************************************************/

   //lresult edit_window::_OnSetFocus(VOID)
   //{
   //    OutputDebugString(TEXT("edit_window::_OnSetFocus\n"));
   //    
   //    XXXSetFocus(m_hwndEdit);
   //
   //    return 0;
   //}

   /**************************************************************************

      edit_window::_OnEditSetFocus()

   **************************************************************************/

   lresult edit_window::_OnSetFocus()
   {

       OutputDebugString(TEXT("edit_window::_OnEditSetFocus\n"));
    
   #ifndef USE_ASSOC_FOCUS
       m_pthreadmgr->XXXSetFocus(m_pDocMgr);
   #endif

       return 0;

   }

   /**************************************************************************

      edit_window::_OnEditChange()

   **************************************************************************/

   lresult edit_window::_OnEditChange(void)
   {
       if(m_fNotify && m_AdviseSink.pTextStoreACPSink && (m_AdviseSink.dwMask & TS_AS_TEXT_CHANGE))
       {
           unsigned int           dwFlags;
           TS_TEXTCHANGE   tc;
           character_count           cch;

           //cch = GetWindowTextLength(m_hwndEdit);
           cch = get_text_length();

           /*
           dwFlags can be 0 or TS_TC_CORRECTION
           */
           dwFlags = 0;

           tc.acpStart = 0;
           tc.acpOldEnd = m_cchOldLength;
           tc.acpNewEnd = (LONG_cast)cch;

           m_AdviseSink.pTextStoreACPSink->OnTextChange(dwFlags, &tc);

           m_cchOldLength = (ULONG_cast)cch;
       }
    
       return 0;
   }

   /**************************************************************************

      edit_window::_OnKillFocus()

   **************************************************************************/

   //lresult edit_window::_OnKillFocus(VOID)
   //{
   //    OutputDebugString(TEXT("edit_window::_OnKillFocus\n"));
   //    
   //    return 0;
   //}

   /**************************************************************************

      edit_window::_OnEditKillFocus()

   **************************************************************************/

   lresult edit_window::_OnKillFocus(VOID)
   {
       OutputDebugString(TEXT("edit_window::_OnEditKillFocus\n"));
    
       return 0;
   }


   /**************************************************************************

      edit_window::_OnNotify()

   **************************************************************************/

   //lresult edit_window::_OnNotify(unsigned int, LPNMHDR)
   //{
   //    return 0;
   //}

   /**************************************************************************

      edit_window::_OnSize()

   **************************************************************************/

   //lresult edit_window::_OnSize(wparam wParam, lparam lParam)
   //{
   //    //adjust the int_size and location of the status bar
   //    //SendMessage(m_hwndStatus, e_message_size, wParam, lParam);
   //
   //    ::int_rectangle    rc;
   //
   //    //GetWindowRect(m_hwndStatus, &rc);
   //    
   //    /*MoveWindow( m_hwndEdit, 
   //                0, 
   //                0, 
   //                LOWORD(lParam), 
   //                HIWORD(lParam) - (rc.bottom() - rc.top()), 
   //                true);
   //*/
   //    m_AdviseSink.pTextStoreACPSink->OnLayoutChange(TS_LC_CHANGE, EDIT_VIEW_COOKIE);
   //
   //    return 0;
   //}

   /**************************************************************************

      edit_window::_IsLocked()

   **************************************************************************/

   BOOL edit_window::_IsLocked(unsigned int dwLockType)
   { 
       if(m_dwInternalLockType)
       {
           return true;
       }

       return m_fLocked && (m_dwLockType & dwLockType); 
   }

   /**************************************************************************

      edit_window::_ClearAdviseSink()

   **************************************************************************/

   HRESULT edit_window::_ClearAdviseSink(PADVISE_SINK pAdviseSink)
   {
       if(pAdviseSink->punkID)
       {
           pAdviseSink->punkID->Release();
           pAdviseSink->punkID = NULL;
       }

       if(pAdviseSink->pTextStoreACPSink)
       {
           pAdviseSink->pTextStoreACPSink->Release();
           pAdviseSink->pTextStoreACPSink = NULL;
       }

       pAdviseSink->dwMask = 0;

       return S_OK;
   }

   /**************************************************************************

      edit_window::_LockDocument()

   **************************************************************************/

   BOOL edit_window::_LockDocument(unsigned int dwLockFlags)
   {
       if(m_fLocked)
       {
           return false;
       }
    
       m_fLocked = true;
       m_dwLockType = dwLockFlags;
    
       return true;
   }

   /**************************************************************************

       edit_window::_InternalLockDocument()

   **************************************************************************/

   BOOL edit_window::_InternalLockDocument(unsigned int dwLockFlags)
   {
       m_dwInternalLockType = dwLockFlags;
    
       return true;
   }

   /**************************************************************************

      edit_window::_UnlockDocument

   **************************************************************************/

   void edit_window::_UnlockDocument()
   {
       HRESULT hr;
    
       m_fLocked = false;
       m_dwLockType = 0;
    
       //if there is a pending lock upgrade, grant it
       if(m_fPendingLockUpgrade)
       {
           m_fPendingLockUpgrade = false;

           RequestLock(TS_LF_READWRITE, &hr);
       }

       //if any layout changes occurred during the lock, notify the manager
       if(m_fLayoutChanged)
       {
           m_fLayoutChanged = false;
           m_AdviseSink.pTextStoreACPSink->OnLayoutChange(TS_LC_CHANGE, EDIT_VIEW_COOKIE);
       }
   }

   /**************************************************************************

       edit_window::_InternalUnlockDocument()

   **************************************************************************/

   void edit_window::_InternalUnlockDocument()
   {
       m_dwInternalLockType = 0;
   }

   /**************************************************************************

      edit_window::_GetCurrentSelection()

   **************************************************************************/

   BOOL edit_window::_GetCurrentSelection(void)
   {

      //get the selection from the edit control
   
      ///::SendMessage(m_hwndEdit, EM_GETSEL, (wparam)&m_acpStart, (lparam)&m_acpEnd);

      character_count iSelStart = 0;

      character_count iSelEnd = 0;

      _001GetSel(iSelStart, iSelEnd);

      m_acpStart = (LONG_cast) iSelStart;

      m_acpEnd = (LONG_cast)iSelEnd;

      return true;

   }


   /**************************************************************************

       edit_window::_OnUpdate()

   **************************************************************************/

   void edit_window::_OnUpdate(void)
   {
       //something changed, but it is not known what specifically changed
       //just update the status bar
       _UpdateStatusBar();
   }

   /**************************************************************************

      edit_window::_UpdateStatusBar()

   **************************************************************************/

   void edit_window::_UpdateStatusBar(void)
   {
       //int     nParts[2];
       //HDC     hdc;
       //HFONT   hFont;
       //::int_size    size;
       //TCHAR   szComposition[MAX_PATH];

       //hdc = GetDC(m_hwndStatus);
       //hFont = (HFONT)SendMessage(m_hwndStatus, WM_GETFONT, 0, 0);
       // hFont = (HFONT)set(hdc, hFont);

       //if(m_cCompositions)
       //{
       //    _tcscpy_s(szComposition, ARRAYSIZE(szComposition), TEXT("In Composition"));
       //}
       //else
       //{
       //    _tcscpy_s(szComposition, ARRAYSIZE(szComposition), TEXT("No Composition"));
       //}

       //GetTextExtentPoint32(hdc, szComposition, lstrlen(szComposition), &size);
       //nParts[0] = size.cx() + (GetSystemMetrics(SM_CXEDGE) * 4);

       //nParts[1] = -1;
    
       //SendMessage(m_hwndStatus, SB_SIMPLE, false, 0);
       //SendMessage(m_hwndStatus, SB_SETPARTS, ARRAYSIZE(nParts), (lparam)nParts);

       //SendMessage(m_hwndStatus, SB_SETTEXT, 0, (lparam)szComposition);
       //SendMessage(m_hwndStatus, SB_SETTEXT, 1, (lparam)TEXT(""));

       //reset the DC
       //set(hdc, hFont);
       //ReleaseDC(m_hwndStatus, hdc);

       ////enable/disable the menu items as necessary
       //HMENU hMenu = GetMenu(m_hwndParent);
       //if(NULL != hMenu)
       //{
       //}

   }


   //lresult edit_window::_OnInitMenuPopup(wparam wParam, lparam lParam)
   //{
   //    HMENU hMenu = (HMENU)wParam;
   // 
   //    //if(NULL != hMenu)
   //    //{
   //    //    EnableMenuItem(hMenu, IDM_TERMINATE_COMPOSITION, m_cCompositions ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
   //    //    EnableMenuItem(hMenu, IDM_RECONVERT, _CanReconvertSelection() ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
   //    //    EnableMenuItem(hMenu, IDM_PLAYBACK, _CanPlaybackSelection() ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
   //    //    EnableMenuItem(hMenu, IDM_LOAD, !_IsLocked(TS_LF_READ) ? MF_ENABLED : MF_DISABLED | MF_GRAYED);
   //    //}

   //    return 0;
   //}



   void edit_window::_ClearRequestedAttributes(void)
   {
       int i;

       for (i = 0; i < NUM_SUPPORTED_ATTRS; i++)
       {
           VariantClear(&m_rgAttributes[i].varValue);
           m_rgAttributes[i].dwFlags = ATTR_FLAG_NONE;
       }
   }

   /**************************************************************************

       edit_window::_ClearText()

   **************************************************************************/

   void edit_window::_ClearText(void)
   {
       //can't do this if someone has a lock
       if(_IsLocked(TS_LF_READ))
       {
           return;
       }

       _LockDocument(TS_LF_READWRITE);
    
       //empty the text in the edit control, but don't send a change notification
       BOOL    fOldNotify = m_fNotify;
       m_fNotify = false;
       //SetWindowTextW(m_hwndEdit, NULL);
       set_text("", ::e_source_user);
       m_fNotify = fOldNotify;

       //update current selection
       m_acpStart = m_acpEnd = 0;
    
       //notify TSF about the changes
       m_AdviseSink.pTextStoreACPSink->OnSelectionChange();
    
       _OnEditChange();
    
       _UnlockDocument();
    
       // make sure to send the OnLayoutChange notification AFTER releasing the lock
       // so clients can do something useful during the notification
       m_AdviseSink.pTextStoreACPSink->OnLayoutChange(TS_LC_CHANGE, EDIT_VIEW_COOKIE);
   }

   /**************************************************************************

       edit_window::_GetText()

   **************************************************************************/

   HRESULT edit_window::_GetText(LPWSTR *ppwsz, LPLONG pcch)
   {
       unsigned int   cch;
       LPWSTR  pwszText;
    
       *ppwsz = NULL;
    
       //cch = GetWindowTextLength(m_hwndEdit);
       cch = (DWORD_cast)get_text_length();
       pwszText = (LPWSTR)GlobalAlloc(GMEM_FIXED, (cch + 1) * sizeof(WCHAR));
       if(NULL == pwszText)
       {
           return E_OUTOFMEMORY;
       }
    
       //GetWindowTextW(m_hwndEdit, pwszText, cch + 1);
       string str;
       get_text(str);
       wstring wstr(str);
       wcscpy(pwszText, wstr);
       cch = (DWORD_cast)get_text_length();

       *ppwsz = pwszText;
    
       if(pcch)
       {
           *pcch = (LONG_cast) wstr.get_length();
       }
    
       return S_OK;
   }

   /**************************************************************************

       edit_window::_GetDisplayAttributes()

   **************************************************************************/

   void edit_window::_GetDisplayAttributes(void)
   {
       HRESULT             hr;
       const GUID          *rGuidProperties[1];
       ITfReadOnlyProperty *pTrackProperty;

       //get the tracking property for the attributes
       rGuidProperties[0] = &GUID_PROP_ATTRIBUTE;
       hr = m_pContext->TrackProperties(   rGuidProperties,
                                           1,
                                           NULL,
                                           0,
                                           &pTrackProperty);
       if(SUCCEEDED(hr))
       {
           ITfRangeACP *pRangeAllText;
           int        acpEnd;

           //get the range of the entire text
           //acpEnd = GetWindowTextLength(m_hwndEdit);
           acpEnd = (LONG_cast)get_text_length();
           hr = m_pServices->CreateRange(0, acpEnd, &pRangeAllText);
           if(SUCCEEDED(hr))
           {
               IEnumTfRanges   *pEnumRanges;

               hr = pTrackProperty->EnumRanges(m_EditCookie, &pEnumRanges, pRangeAllText);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pPropRange;
                   ULONG       uFetched;

                   /*
                   Each range in pEnumRanges represents a span of text that has 
                   the same properties specified in TrackProperties.
                   */
                   while((hr = pEnumRanges->Next(1, &pPropRange, &uFetched)) == S_OK && uFetched) 
                   {
                       //get the attribute property for the property range
                       VARIANT ::payload;

                       VariantInit(&payload);

                       hr = pTrackProperty->GetValue(m_EditCookie, pPropRange, &payload);
                       if(SUCCEEDED(hr))
                       {
                           /*
                           The property is actually a VT_UNKNOWN that contains an 
                           IEnumTfPropertyValue object.
                           */
                           IEnumTfPropertyValue    *pEnumPropertyVal;

                           hr = payload.punkVal->QueryInterface(IID_IEnumTfPropertyValue, (LPVOID*)&pEnumPropertyVal);
                           if(SUCCEEDED(hr))
                           {
                               TF_PROPERTYVAL tfPropVal;

                               while((hr = pEnumPropertyVal->Next(1, &tfPropVal, &uFetched)) == S_OK && uFetched) 
                               {
                                   if(VT_EMPTY == tfPropVal.varValue.vt)
                                   {
                                       //the property for this range has no value
                                       continue;
                                   }
                                   else if(VT_I4 == tfPropVal.varValue.vt)
                                   {
                                       //the property is a guidatom
                                       TfGuidAtom  gaVal;
                                       GUID        guid;

                                       gaVal = (TfGuidAtom)tfPropVal.varValue.lVal;

                                       hr = m_pCategoryMgr->GetGUID(gaVal, &guid);
                                       if(SUCCEEDED(hr))
                                       {
                                           ITfDisplayAttributeInfo *pDispInfo;

                                           hr = m_pDisplayAttrMgr->GetDisplayAttributeInfo(guid, &pDispInfo, NULL);
                                           if(SUCCEEDED(hr))
                                           {
                                               TF_DISPLAYATTRIBUTE da;
                                            
                                               hr = pDispInfo->GetAttributeInfo(&da);

                                               {
                                                   GUID    guidDispInfo;
                                                   hr = pDispInfo->GetGUID(&guidDispInfo);
                                                   guidDispInfo.Data1 = 0;
                                               }

                                               {
                                                   BSTR    bstr;

                                                   hr = pDispInfo->GetDescription(&bstr);
                                                   if(SUCCEEDED(hr))
                                                   {
                                                       SysFreeString(bstr);
                                                   }
                                               }
                                            
                                               pDispInfo->Release();
                                           }
                                       }
                                   }
                                   else
                                   {
                                       //the property is not recognized
                                   }
                               }
                            
                               pEnumPropertyVal->Release();
                           }
                        
                           VariantClear(&payload);
                       }
                    
                       pPropRange->Release();
                   }
                
                   pEnumRanges->Release();
               }

               pRangeAllText->Release();
           }
        
           pTrackProperty->Release();
       }
   }

   /**************************************************************************

       edit_window::_GetTextOwner()

   **************************************************************************/

   void edit_window::_GetTextOwner(void)
   {
       HRESULT             hr;
       const GUID          *rGuidProperties[1];
       ITfReadOnlyProperty *pTrackProperty;

       //get the tracking property for the attributes
       rGuidProperties[0] = &GUID_PROP_TEXTOWNER;
       hr = m_pContext->TrackProperties(   rGuidProperties,
                                           1,
                                           NULL,
                                           0,
                                           &pTrackProperty);
       if(SUCCEEDED(hr))
       {
           ITfRangeACP *pRangeAllText;
           int        acpEnd;

           //get the range of the entire text
           //acpEnd = GetWindowTextLength(m_hwndEdit);
           acpEnd = (LONG_cast)get_text_length();
           hr = m_pServices->CreateRange(0, acpEnd, &pRangeAllText);
           if(SUCCEEDED(hr))
           {
               IEnumTfRanges   *pEnumRanges;

               hr = pTrackProperty->EnumRanges(m_EditCookie, &pEnumRanges, pRangeAllText);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pPropRange;
                   ULONG       uFetched;

                   /*
                   Each range in pEnumRanges represents a span of text that has 
                   the same properties specified in TrackProperties.
                   */
                   while((hr = pEnumRanges->Next(1, &pPropRange, &uFetched)) == S_OK && uFetched) 
                   {
                       //get the attribute property for the property range
                       VARIANT ::payload;

                       VariantInit(&payload);

                       hr = pTrackProperty->GetValue(m_EditCookie, pPropRange, &payload);
                       if(SUCCEEDED(hr))
                       {
                           /*
                           The property is actually a VT_UNKNOWN that contains an 
                           IEnumTfPropertyValue object.
                           */
                           IEnumTfPropertyValue    *pEnumPropertyVal;

                           hr = payload.punkVal->QueryInterface(IID_IEnumTfPropertyValue, (LPVOID*)&pEnumPropertyVal);
                           if(SUCCEEDED(hr))
                           {
                               TF_PROPERTYVAL tfPropVal;

                               while((hr = pEnumPropertyVal->Next(1, &tfPropVal, &uFetched)) == S_OK && uFetched) 
                               {
                                   /*
                                   The GUID_PROP_TEXTOWNER attribute value is the CLSID of the text service that owns the text. If the text is not owned, the value is VT_EMPTY.
                                   */
                                   if(VT_EMPTY == tfPropVal.varValue.vt)
                                   {
                                       //the text is not owned
                                       continue;
                                   }
                                   else if(VT_I4 == tfPropVal.varValue.vt)
                                   {
                                       //the property is a guidatom that represents the CLSID of the text service that owns the text.
                                       TfGuidAtom  gaVal;
                                       CLSID       clsidOwner;

                                       gaVal = (TfGuidAtom)tfPropVal.varValue.lVal;

                                       hr = m_pCategoryMgr->GetGUID(gaVal, &clsidOwner);
                                       if(SUCCEEDED(hr))
                                       {
                                       }
                                   }
                                   else
                                   {
                                       //the property is not recognized
                                   }
                               }
                            
                               pEnumPropertyVal->Release();
                           }
                        
                           VariantClear(&payload);
                       }
                    
                       pPropRange->Release();
                   }
                
                   pEnumRanges->Release();
               }

               pRangeAllText->Release();
           }
        
           pTrackProperty->Release();
       }
   }

   /**************************************************************************

       edit_window::_GetReadingText()

   **************************************************************************/

   void edit_window::_GetReadingText(void)
   {
       HRESULT             hr;
       const GUID          *rGuidProperties[1];
       ITfReadOnlyProperty *pTrackProperty;

       //get the tracking property for the attributes
       rGuidProperties[0] = &GUID_PROP_READING;
       hr = m_pContext->TrackProperties(   rGuidProperties,
                                           1,
                                           NULL,
                                           0,
                                           &pTrackProperty);
       if(SUCCEEDED(hr))
       {
           ITfRangeACP *pRangeAllText;
           int        acpEnd;

           //get the range of the entire text
           //acpEnd = GetWindowTextLength(m_hwndEdit);
           acpEnd = (LONG_cast)get_text_length();
           hr = m_pServices->CreateRange(0, acpEnd, &pRangeAllText);
           if(SUCCEEDED(hr))
           {
               IEnumTfRanges   *pEnumRanges;

               hr = pTrackProperty->EnumRanges(m_EditCookie, &pEnumRanges, pRangeAllText);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pPropRange;
                   ULONG       uFetched;

                   /*
                   Each range in pEnumRanges represents a span of text that has 
                   the same properties specified in TrackProperties.
                   */
                   while((hr = pEnumRanges->Next(1, &pPropRange, &uFetched)) == S_OK && uFetched) 
                   {
                       //get the attribute property for the property range
                       VARIANT ::payload;

                       VariantInit(&payload);

                       hr = pTrackProperty->GetValue(m_EditCookie, pPropRange, &payload);
                       if(SUCCEEDED(hr))
                       {
                           /*
                           The property is actually a VT_UNKNOWN that contains an 
                           IEnumTfPropertyValue object.
                           */
                           IEnumTfPropertyValue    *pEnumPropertyVal;

                           hr = payload.punkVal->QueryInterface(IID_IEnumTfPropertyValue, (LPVOID*)&pEnumPropertyVal);
                           if(SUCCEEDED(hr))
                           {
                               TF_PROPERTYVAL tfPropVal;

                               while((hr = pEnumPropertyVal->Next(1, &tfPropVal, &uFetched)) == S_OK && uFetched) 
                               {
                                   /*
                                   The GUID_PROP_TEXTOWNER attribute value is the CLSID of the text service that owns the text. If the text is not owned, the value is VT_EMPTY.
                                   */
                                   if(VT_EMPTY == tfPropVal.varValue.vt)
                                   {
                                       //the text is not owned
                                       continue;
                                   }
                                   else if(VT_BSTR == tfPropVal.varValue.vt)
                                   {
                                       //the property is a BSTR.
                                       tfPropVal.varValue.bstrVal;

                                       HRESULT hr;
                                       WCHAR   wsz[MAX_PATH];
                                       ULONG   cch;
                                       hr = pPropRange->GetText(m_EditCookie, 0, wsz, MAX_PATH-1, &cch);
                                       wsz[cch] = 0;
                                   }
                                   else
                                   {
                                       //the property is not recognized
                                   }
                               }
                            
                               pEnumPropertyVal->Release();
                           }
                        
                           VariantClear(&payload);
                       }
                    
                       pPropRange->Release();
                   }
                
                   pEnumRanges->Release();
               }

               pRangeAllText->Release();
           }
        
           pTrackProperty->Release();
       }
   }

   /**************************************************************************

       edit_window::_GetComposing()

   **************************************************************************/

   bool edit_window::_GetComposing(void)
   {
       HRESULT             hr;
       const GUID          *rGuidProperties[1];
       comptr < ITfReadOnlyProperty > pTrackProperty;

       //get the tracking property for the attributes
       rGuidProperties[0] = &GUID_PROP_COMPOSING;
       hr = m_pContext->TrackProperties(   rGuidProperties,
                                           1,
                                           NULL,
                                           0,
                                           &pTrackProperty);
       if(SUCCEEDED(hr))
       {
           comptr <ITfRangeACP>pRangeAllText;
           int        acpEnd;

           //get the range of the entire text
           //acpEnd = GetWindowTextLength(m_hwndEdit);
           acpEnd = (LONG_cast)get_text_length();
           hr = m_pServices->CreateRange(0, acpEnd, &pRangeAllText);
           if(SUCCEEDED(hr))
           {
               comptr < IEnumTfRanges > pEnumRanges;

               hr = pTrackProperty->EnumRanges(m_EditCookie, &pEnumRanges, pRangeAllText);
               if(SUCCEEDED(hr))
               {
                   comptr < ITfRange > pPropRange;
                   ULONG       uFetched;

                   /*
                   Each range in pEnumRanges represents a span of text that has 
                   the same properties specified in TrackProperties.
                   */
                   while((hr = pEnumRanges->Next(1, &pPropRange, &uFetched)) == S_OK && uFetched) 
                   {
                       //get the attribute property for the property range
                       variant ::payload;

                       
                       hr = pTrackProperty->GetValue(m_EditCookie, pPropRange, &payload);
                       if(SUCCEEDED(hr))
                       {
                           /*
                           The property is actually a VT_UNKNOWN that contains an 
                           IEnumTfPropertyValue object.
                           */
                           comptr< IEnumTfPropertyValue  > pEnumPropertyVal;

                           hr = payload.punkVal->QueryInterface(IID_IEnumTfPropertyValue, (LPVOID*)&pEnumPropertyVal);
                           if(SUCCEEDED(hr))
                           {
                               TF_PROPERTYVAL tfPropVal;

                               while((hr = pEnumPropertyVal->Next(1, &tfPropVal, &uFetched)) == S_OK && uFetched) 
                               {
                                   /*
                                   The GUID_PROP_COMPOSING attribute value is a VT_I4 that contains a boolean indicating if the text is part of a composition.
                                   */
                                   BOOL    fComposing = false;

                                   if(VT_EMPTY == tfPropVal.varValue.vt)
                                   {
                                       //the text is not part of a composition
                                   }
                                   else if(VT_I4 == tfPropVal.varValue.vt)
                                   {
                                       //the property is a VT_I4.
                                       if(tfPropVal.varValue.lVal)
                                       {
                                           //The text is part of a composition
                                           //fComposing = true;
                                          return true;
                                       }
                                   }
                                   else
                                   {
                                       //the property is not recognized
                                   }
                               }
                            
                           }
                        
                           //VariantClear(&payload);
                       }
                    
                       //pPropRange->Release();
                   }
                
                   //pEnumRanges->Release();
               }

               //pRangeAllText->Release();
           }
        
           //pTrackProperty->Release();
       }

       return false;
   }

   bool edit_window::is_text_composition_active()
   {

      return _GetComposing();

   }

   /**************************************************************************

       edit_window::_CanReconvertSelection()

   **************************************************************************/

   BOOL edit_window::_CanReconvertSelection(void)
   {
       BOOL                fConv = false;
       HRESULT             hr;
       ITfFunctionProvider *pFuncProv;
    
       _InternalLockDocument(TS_LF_READ);

       hr = m_pthreadmgr->GetFunctionProvider(GUID_SYSTEM_FUNCTIONPROVIDER, &pFuncProv);
       if(SUCCEEDED(hr))
       {
           ITfFnReconversion  *pRecon;
        
           hr = pFuncProv->GetFunction(GUID_NULL, IID_ITfFnReconversion, (IUnknown**)&pRecon);
           if(SUCCEEDED(hr))
           {
               TF_SELECTION    ts;
               ULONG           uFetched;

               hr = m_pContext->GetSelection(m_EditCookie, TF_DEFAULT_SELECTION, 1, &ts, &uFetched);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pRange = NULL;
            
                   hr = pRecon->QueryRange(ts.range, &pRange, &fConv);
                   if(SUCCEEDED(hr) && pRange)
                   {
                       pRange->Release();
                   }
            
               ts.range->Release();
               }
            
               pRecon->Release();
           }

           pFuncProv->Release();
       }

       _InternalUnlockDocument();

       return fConv;
   }

   /**************************************************************************

       edit_window::_Reconvert()

   **************************************************************************/

   void edit_window::_Reconvert(void)
   {
       HRESULT hr;
       ITfFunctionProvider *pFuncProv;
    
       _InternalLockDocument(TS_LF_READ);

       hr = m_pthreadmgr->GetFunctionProvider(GUID_SYSTEM_FUNCTIONPROVIDER, &pFuncProv);
       if(SUCCEEDED(hr))
       {
           ITfFnReconversion  *pRecon;
        
           hr = pFuncProv->GetFunction(GUID_NULL, IID_ITfFnReconversion, (IUnknown**)&pRecon);
           if(SUCCEEDED(hr))
           {
               TF_SELECTION    ts;
               ULONG           uFetched;

               hr = m_pContext->GetSelection(m_EditCookie, TF_DEFAULT_SELECTION, 1, &ts, &uFetched);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pRange;
                   BOOL        fConv;
            
                   //get the range that covers the text to be reconverted
                   hr = pRecon->QueryRange(ts.range, &pRange, &fConv);
                   if(SUCCEEDED(hr) && pRange)
                   {
                       {
                           WCHAR   wsz[MAX_PATH];
                           ULONG   cch = 0;
                           pRange->GetText(m_EditCookie, 0, wsz, MAX_PATH-1, &cch);
                           wsz[cch] = 0;
                       }
                    
                       //get the list of reconversion candidates
                       ITfCandidateList    *pCandList;
                       hr = pRecon->GetReconversion(pRange, &pCandList);
                       if(SUCCEEDED(hr))
                       {
                           ULONG   i;
                           ULONG   uCandidateCount = 0;

                           hr = pCandList->GetCandidateNum(&uCandidateCount);

                           for(i = 0; i < uCandidateCount; i++)
                           {
                               ITfCandidateString  *pCandString;

                               hr = pCandList->GetCandidate(i, &pCandString);
                               if(SUCCEEDED(hr))
                               {
                                   BSTR    bstr;

                                   hr = pCandString->GetString(&bstr);
                                   if(SUCCEEDED(hr))
                                   {
                                       OutputDebugString(TEXT("\tCandidate - \""));
                                       OutputDebugStringW(bstr);
                                       OutputDebugString(TEXT("\"\n"));
                                       SysFreeString(bstr);
                                   }

                                   pCandString->Release();
                               }
                           }
                        
                           pCandList->Release();
                       }
                       //cause the reconversion to happen
                       hr = pRecon->Reconvert(pRange);

                   }
               }
            
               pRecon->Release();
           }

           pFuncProv->Release();
       }
    
       _InternalUnlockDocument();
   }

   /**************************************************************************

       edit_window::_CanPlaybackSelection()

   **************************************************************************/

   BOOL edit_window::_CanPlaybackSelection(void)
   {
       BOOL                fCanPlayback = false;
       HRESULT             hr;
       ITfFunctionProvider *pFuncProv;
    
       _InternalLockDocument(TS_LF_READ);

       hr = m_pthreadmgr->GetFunctionProvider(CLSID_SapiLayr, &pFuncProv);
       if(SUCCEEDED(hr))
       {
           ITfFnPlayBack *pPlayback;
        
           hr = pFuncProv->GetFunction(GUID_NULL, IID_ITfFnPlayBack, (IUnknown**)&pPlayback);
           if(SUCCEEDED(hr))
           {
               TF_SELECTION    ts;
               ULONG           uFetched;

               hr = m_pContext->GetSelection(m_EditCookie, TF_DEFAULT_SELECTION, 1, &ts, &uFetched);
               if(SUCCEEDED(hr))
               {
                   ITfRange    *pRange = NULL;
            
                   hr = pPlayback->QueryRange(ts.range, &pRange, &fCanPlayback);
                   if(SUCCEEDED(hr) && pRange)
                   {
                       pRange->Release();
                   }
            
               ts.range->Release();
               }
            
               pPlayback->Release();
           }

           pFuncProv->Release();
       }

       _InternalUnlockDocument();

       return fCanPlayback;
   }

   /**************************************************************************

       edit_window::_Playback()

   **************************************************************************/

   void edit_window::_Playback(void)
   {
       HRESULT             hr;
       ITfFunctionProvider *pFuncProv;
    
       _InternalLockDocument(TS_LF_READ);

       hr = m_pthreadmgr->GetFunctionProvider(CLSID_SapiLayr, &pFuncProv);
       if(SUCCEEDED(hr))
       {
           ITfFnPlayBack *pPlayback;
        
           hr = pFuncProv->GetFunction(GUID_NULL, IID_ITfFnPlayBack, (IUnknown**)&pPlayback);
           if(SUCCEEDED(hr))
           {
               TF_SELECTION    ts;
               ULONG           uFetched;

               hr = m_pContext->GetSelection(m_EditCookie, TF_DEFAULT_SELECTION, 1, &ts, &uFetched);
               if(SUCCEEDED(hr))
               {
                   BOOL        fCanPlayback;
                   ITfRange    *pRange = NULL;
            
                   hr = pPlayback->QueryRange(ts.range, &pRange, &fCanPlayback);
                   if(SUCCEEDED(hr) && pRange)
                   {
                       hr = pPlayback->Play(pRange);
                    
                       pRange->Release();
                   }
            
               ts.range->Release();
               }
            
               pPlayback->Release();
           }

           pFuncProv->Release();
       }

       _InternalUnlockDocument();
   }


   ///////////////////////////////////////////////////////////////////////////
   //
   // IUnknown Implementation
   //

   /**************************************************************************

      edit_window::QueryInterface

   **************************************************************************/

   STDMETHODIMP edit_window::QueryInterface(REFIID riid, LPVOID *ppReturn)
   {
       *ppReturn = NULL;

       //IUnknown
       if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ITextStoreACP))
       {
           *ppReturn = (ITextStoreACP*)this;
       }

       //ITfContextOwnerCompositionSink
       else if(IsEqualIID(riid, IID_ITfContextOwnerCompositionSink))
       {
           *ppReturn = (ITfContextOwnerCompositionSink*)this;
       }
       else if (IsEqualIID(riid, IID_ITfUIElementSink))
       {

          *ppReturn = (ITfUIElementSink *)this;

       }


       //ITfFunctionProvider
       else if(IsEqualIID(riid, IID_ITfFunctionProvider))
       {
           *ppReturn = (ITfFunctionProvider*)this;
       }

       if(*ppReturn)
       {
           (*(LPUNKNOWN*)ppReturn)->AddRef();
           return S_OK;
       }

       return E_NOINTERFACE;
   }                                             

   /**************************************************************************

      edit_window::AddRef

   **************************************************************************/

   STDMETHODIMP_(unsigned int) edit_window::AddRef()
   {
      return (unsigned int) increment_reference_count();
   }


   /**************************************************************************

      edit_window::Release

   **************************************************************************/

   STDMETHODIMP_(unsigned int) edit_window::Release()
   {
       //if(--m_ObjRefCount == 0)
       //{
       //    delete this;
       //    return 0;
       //}
   
       //return m_ObjRefCount;

      return (unsigned int) release();
   }


} // namespace tsf



