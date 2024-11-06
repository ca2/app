#pragma once

#include <windowsx.h>
#include <msctf.h>
#include <olectl.h>
#include <commctrl.h>


#define EDIT_VIEW_COOKIE    0

#define IDC_EDIT            1000
#define IDC_STATUSBAR       1001

#define NUM_SUPPORTED_ATTRS 3

#define ATTR_INDEX_MODEBIAS             0
#define ATTR_INDEX_TEXT_ORIENTATION     1
#define ATTR_INDEX_TEXT_VERTICALWRITING 2

#define ATTR_FLAG_NONE      0
#define ATTR_FLAG_REQUESTED 1
#define ATTR_FLAG_DEFAULT   2

#define MAX_COMPOSITIONS    5



namespace tsf
{

   typedef struct
   {
      IUnknown * punkID;
      ITextStoreACPSink * pTextStoreACPSink;
      ::u32                   dwMask;
   }ADVISE_SINK, * PADVISE_SINK;

   typedef struct
   {
      ::u32   dwFlags;
      const TS_ATTRID * attrid;
      VARIANT varValue;
      VARIANT varDefaultValue;
   }ATTRIBUTES, * PATTRIBUTES;


   class edit_window : 
      public ITextStoreACP,
      public ITfContextOwnerCompositionSink,
      public ITfFunctionProvider
   {
   public:

      ::user::interaction * m_puserinteraction;

      ::u32                   m_ObjRefCount;
      HINSTANCE               m_hInst;
      //HWND                    m_hWnd;
      //HWND                    m_hwndParent;
      HWND                    m_hwndEdit2;
      //HWND                    m_hwndStatus;
      ITfThreadMgr * m_pthreadmgr;
      TfClientId              m_tfClientID;
      ITfDocumentMgr * m_pDocMgr;
      ITfDocumentMgr * m_pPrevDocMgr;
      ITfContext * m_pContext;
      TfEditCookie            m_EditCookie;
      ADVISE_SINK             m_AdviseSink;
      BOOL                    m_fLocked;
      ::u32                   m_dwLockType;
      BOOL                    m_fPendingLockUpgrade;
      ::u32                   m_dwInternalLockType;
      int                    m_acpStart;
      int                    m_acpEnd;
      BOOL                    m_fInterimChar;
      TsActiveSelEnd          m_ActiveSelEnd;
      ITextStoreACPServices * m_pServices;
      ULONG                   m_cCompositions;
      ITfCompositionView * m_rgCompositions[MAX_COMPOSITIONS];
      ATTRIBUTES              m_rgAttributes[NUM_SUPPORTED_ATTRS];
      ITfCategoryMgr * m_pCategoryMgr;
      ITfDisplayAttributeMgr * m_pDisplayAttrMgr;
      BOOL                    m_fLayoutChanged;
      BOOL                    m_fNotify;
      ULONG                   m_cchOldLength;

      edit_window(HINSTANCE hInstance, HWND hwndEdit);
      virtual ~edit_window();

      BOOL _Initialize(ITfThreadMgr * pThreadMgr, TfClientId tfcId);
      void _Uninitialize();
      //HWND _GetWindow();
      HRESULT _OnGetPreservedKey();
      void _OnTest(void);
      void _GetDisplayAttributes(void);
      void _GetTextOwner(void);
      void _GetReadingText(void);
      void _GetComposing(void);
      HRESULT _TerminateAllCompositions(void);
      void _Reconvert(void);
      void _Playback(void);
      void _OnUpdate(void);
      LRESULT _OnInitMenuPopup(WPARAM, LPARAM);
      //void _SaveToFile(char * pszFile);
      //void _LoadFromFile(char * pszFile);

      //IUnknown methods
      STDMETHOD(QueryInterface)(REFIID, LPVOID *);
      STDMETHOD_(::u32, AddRef)();
      STDMETHOD_(::u32, Release)();

      //ITextStoreACP methods
      STDMETHODIMP AdviseSink(REFIID riid, IUnknown * punk, ::u32 dwMask);
      STDMETHODIMP UnadviseSink(IUnknown * punk);
      STDMETHODIMP RequestLock(::u32 dwLockFlags, HRESULT * phrSession);
      STDMETHODIMP GetStatus(TS_STATUS * pdcs);
      STDMETHODIMP QueryInsert(int acpTestStart, int acpTestEnd, ULONG cch, int * pacpResultStart, int * pacpResultEnd);
      STDMETHODIMP GetSelection(ULONG ulIndex, ULONG ulCount, TS_SELECTION_ACP * pSelection, ULONG * pcFetched);
      STDMETHODIMP SetSelection(ULONG ulCount, const TS_SELECTION_ACP * pSelection);
      STDMETHODIMP GetText(int acpStart, int acpEnd, WCHAR * pchPlain, ULONG cchPlainReq, ULONG * pcchPlainOut, TS_RUNINFO * prgRunInfo, ULONG ulRunInfoReq, ULONG * pulRunInfoOut, int * pacpNext);
      STDMETHODIMP SetText(::u32 dwFlags, int acpStart, int acpEnd, const WCHAR * pchText, ULONG cch, TS_TEXTCHANGE * pChange);
      STDMETHODIMP GetFormattedText(int acpStart, int acpEnd, IDataObject ** ppDataObject);
      STDMETHODIMP GetEmbedded(int acpPos, REFGUID rguidService, REFIID riid, IUnknown ** ppunk);
      STDMETHODIMP QueryInsertEmbedded(const GUID * pguidService, const FORMATETC * pFormatEtc, BOOL * pfInsertable);
      STDMETHODIMP InsertEmbedded(::u32 dwFlags, int acpStart, int acpEnd, IDataObject * pDataObject, TS_TEXTCHANGE * pChange);
      STDMETHODIMP RequestSupportedAttrs(::u32 dwFlags, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs);
      STDMETHODIMP RequestAttrsAtPosition(int acpPos, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, ::u32 dwFlags);
      STDMETHODIMP RequestAttrsTransitioningAtPosition(int acpPos, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, ::u32 dwFlags);
      STDMETHODIMP FindNextAttrTransition(int acpStart, int acpHalt, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, ::u32 dwFlags, int * pacpNext, BOOL * pfFound, int * plFoundOffset);
      STDMETHODIMP RetrieveRequestedAttrs(ULONG ulCount, TS_ATTRVAL * paAttrVals, ULONG * pcFetched);
      STDMETHODIMP GetEndACP(int * pacp);
      STDMETHODIMP get_active_impact(TsViewCookie * pvcView);
      STDMETHODIMP GetACPFromPoint(TsViewCookie vcView, const POINT32 * pt, ::u32 dwFlags, int * pacp);
      STDMETHODIMP GetTextExt(TsViewCookie vcView, int acpStart, int acpEnd, RECT32 * prc, BOOL * pfClipped);
      STDMETHODIMP GetScreenExt(TsViewCookie vcView, RECT32 * prc);
      STDMETHODIMP GetWnd(TsViewCookie vcView, HWND * phwnd);
      STDMETHODIMP InsertTextAtSelection(::u32 dwFlags, const WCHAR * pchText, ULONG cch, int * pacpStart, int * pacpEnd, TS_TEXTCHANGE * pChange);
      STDMETHODIMP InsertEmbeddedAtSelection(::u32 dwFlags, IDataObject * pDataObject, int * pacpStart, int * pacpEnd, TS_TEXTCHANGE * pChange);

      //ITfContextOwnerCompositionSink methods
      STDMETHODIMP OnStartComposition(ITfCompositionView * pComposition, BOOL * pfOk);
      STDMETHODIMP OnUpdateComposition(ITfCompositionView * pComposition, ITfRange * pRangeNew);
      STDMETHODIMP OnEndComposition(ITfCompositionView * pComposition);

      // ITfFunctionProvider
      STDMETHODIMP GetType(GUID * pguid);
      STDMETHODIMP GetDescription(BSTR * pbstrDesc);
      STDMETHODIMP GetFunction(REFGUID rguid, REFIID riid, IUnknown ** ppunk);

      //private:
          //static LRESULT CALLBACK _WndProc(HWND hWnd, ::u32 uMessage, WPARAM wParam, LPARAM lParam);
      STDMETHODIMP _TestInsert(int acpTestStart, int acpTestEnd, ULONG cch, int * pacpResultStart, int * pacpResultEnd);
      //LRESULT _OnCreate(VOID);
      LRESULT _OnDestroy(VOID);
      //LRESULT _OnCommand(::u16, ::u16, HWND);
      //LRESULT _OnSetFocus(VOID);
      //LRESULT _OnKillFocus(VOID);

      void on_edit_set_focus(::user::interaction * pinteraction);

      LRESULT _OnEditKillFocus(VOID);
      LRESULT _OnEditChange(void);
      //LRESULT _OnNotify(::u32, LPNMHDR);
      //LRESULT _OnSize(WPARAM, LPARAM);
      HRESULT _ClearAdviseSink(PADVISE_SINK pAdviseSink);
      BOOL _LockDocument(::u32 dwLockFlags);
      void _UnlockDocument();
      BOOL _InternalLockDocument(::u32 dwLockFlags);
      void _InternalUnlockDocument();
      BOOL _IsLocked(::u32 dwLockType);
      BOOL _GetCurrentSelection(void);
      void _UpdateStatusBar(void);
      void _ClearRequestedAttributes(void);
      void _ClearText(void);
      HRESULT _GetText(LPWSTR * ppwsz, LPLONG pcch = NULL);
      BOOL _InitFunctionProvider();
      void _UninitFunctionProvider();
      BOOL _CanReconvertSelection(void);
      BOOL _CanPlaybackSelection(void);
      //void _Save(IStream *pStream);
      //void _Load(IStream *pStream);

   };


} // namespace tsf



