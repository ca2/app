#pragma once


//#include  "aura/user/edit_window.h"


//#include <windowsx.h>
#include <msctf.h>
#include <olectl.h>
//#include <commctrl.h>

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

      comptr < IUnknown> punkID;
      comptr < ITextStoreACPSink> pTextStoreACPSink;
      DWORD                   dwMask;
      DWORD                   dwUIElementCookie;

   }ADVISE_SINK, * PADVISE_SINK;


   typedef struct
   {

      DWORD                dwFlags;
      const TS_ATTRID * attrid;
      VARIANT              varValue;
      VARIANT              varDefaultValue;

   }ATTRIBUTES, * PATTRIBUTES;



   class CLASS_DECL_AURA edit_window :
      virtual public ITfContextOwnerCompositionSink,
      virtual public ITextStoreACP,
      virtual public ITfUIElementSink,
      virtual public ITfFunctionProvider,
      virtual public ::user::interaction
   {
   public:

      //::user::interaction *               m_puserinteraction;



      //DWORD                             m_ObjRefCount;
      HINSTANCE                           m_hInst;
      //HWND                              m_hWnd;
      //HWND                              m_hwndParent;
      //HWND                                m_hwndEdit2;
      //HWND                              m_hwndStatus;
      comptr < ITfThreadMgr >             m_pthreadmgr;
      TfClientId                          m_tfClientID;
      comptr < ITfDocumentMgr >           m_pDocMgr;
      comptr < ITfDocumentMgr >           m_pPrevDocMgr;
      comptr < ITfContext >               m_pContext;
      TfEditCookie                        m_EditCookie;
      ADVISE_SINK                         m_AdviseSink;
      BOOL                                m_fLocked;
      DWORD                               m_dwLockType;
      BOOL                                m_fPendingLockUpgrade;
      DWORD                               m_dwInternalLockType;
      LONG                                m_acpStart;
      LONG                                m_acpEnd;
      BOOL                                m_fInterimChar;
      TsActiveSelEnd                      m_ActiveSelEnd;
      comptr < ITextStoreACPServices >    m_pServices;
      ULONG                               m_cCompositions;
      comptr < ITfCompositionView >       m_rgCompositions[MAX_COMPOSITIONS];
      ATTRIBUTES                          m_rgAttributes[NUM_SUPPORTED_ATTRS];
      comptr < ITfCategoryMgr >           m_pCategoryMgr;
      comptr < ITfDisplayAttributeMgr >   m_pDisplayAttrMgr;
      BOOL                                m_fLayoutChanged;
      BOOL                                m_fNotify;
      ULONG                               m_cchOldLength;

      //public:
      edit_window();
      ~edit_window();


      virtual void install_message_routing(::channel* pchannel);


      //public utility methods
      BOOL _Initialize(ITfThreadMgr * pThreadMgr, TfClientId tfcId);
      void _Uninitialize();
      //HWND _GetWindow();
      HRESULT _OnGetPreservedKey();
      void _OnTest(void);
      void _GetDisplayAttributes(void);
      void _GetTextOwner(void);
      void _GetReadingText(void);
      bool _GetComposing(void);
      HRESULT _TerminateAllCompositions(void);
      void _Reconvert(void);
      void _Playback(void);
      void _OnUpdate(void);
      //LRESULT _OnInitMenuPopup(WPARAM, LPARAM);
      //void _SaveToFile(LPTSTR pszFile);
      //void _LoadFromFile(LPTSTR pszFile);

      //IUnknown methods
      STDMETHOD(QueryInterface)(REFIID, LPVOID *);
      STDMETHOD_(DWORD, AddRef)();
      STDMETHOD_(DWORD, Release)();

      //ITextStoreACP methods
      STDMETHODIMP AdviseSink(REFIID riid, IUnknown * punk, DWORD dwMask);
      STDMETHODIMP UnadviseSink(IUnknown * punk);
      STDMETHODIMP RequestLock(DWORD dwLockFlags, HRESULT * phrSession);
      STDMETHODIMP GetStatus(TS_STATUS * pdcs);
      STDMETHODIMP QueryInsert(LONG acpTestStart, LONG acpTestEnd, ULONG cch, LONG * pacpResultStart, LONG * pacpResultEnd);
      STDMETHODIMP GetSelection(ULONG ulIndex, ULONG ulCount, TS_SELECTION_ACP * pSelection, ULONG * pcFetched);
      STDMETHODIMP SetSelection(ULONG ulCount, const TS_SELECTION_ACP * pSelection);
      STDMETHODIMP GetText(LONG acpStart, LONG acpEnd, WCHAR * pchPlain, ULONG cchPlainReq, ULONG * pcchPlainOut, TS_RUNINFO * prgRunInfo, ULONG ulRunInfoReq, ULONG * pulRunInfoOut, LONG * pacpNext);
      STDMETHODIMP SetText(DWORD dwFlags, LONG acpStart, LONG acpEnd, const WCHAR * pchText, ULONG cch, TS_TEXTCHANGE * pChange);
      STDMETHODIMP GetFormattedText(LONG acpStart, LONG acpEnd, IDataObject ** ppDataObject);
      STDMETHODIMP GetEmbedded(LONG acpPos, REFGUID rguidService, REFIID riid, IUnknown ** ppunk);
      STDMETHODIMP QueryInsertEmbedded(const GUID * pguidService, const FORMATETC * pFormatEtc, BOOL * pfInsertable);
      STDMETHODIMP InsertEmbedded(DWORD dwFlags, LONG acpStart, LONG acpEnd, IDataObject * pDataObject, TS_TEXTCHANGE * pChange);
      STDMETHODIMP RequestSupportedAttrs(DWORD dwFlags, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs);
      STDMETHODIMP RequestAttrsAtPosition(LONG acpPos, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, DWORD dwFlags);
      STDMETHODIMP RequestAttrsTransitioningAtPosition(LONG acpPos, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, DWORD dwFlags);
      STDMETHODIMP FindNextAttrTransition(LONG acpStart, LONG acpHalt, ULONG cFilterAttrs, const TS_ATTRID * paFilterAttrs, DWORD dwFlags, LONG * pacpNext, BOOL * pfFound, LONG * plFoundOffset);
      STDMETHODIMP RetrieveRequestedAttrs(ULONG ulCount, TS_ATTRVAL * paAttrVals, ULONG * pcFetched);
      STDMETHODIMP GetEndACP(LONG * pacp);
      STDMETHODIMP GetActiveView(TsViewCookie * pvcView);
      STDMETHODIMP GetACPFromPoint(TsViewCookie vcView, const POINT * pt, DWORD dwFlags, LONG * pacp);
      STDMETHODIMP GetTextExt(TsViewCookie vcView, LONG acpStart, LONG acpEnd, RECT * prc, BOOL * pfClipped);
      STDMETHODIMP GetScreenExt(TsViewCookie vcView, RECT * prc);
      STDMETHODIMP GetWnd(TsViewCookie vcView, HWND * phwnd);
      STDMETHODIMP InsertTextAtSelection(DWORD dwFlags, const WCHAR * pchText, ULONG cch, LONG * pacpStart, LONG * pacpEnd, TS_TEXTCHANGE * pChange);
      STDMETHODIMP InsertEmbeddedAtSelection(DWORD dwFlags, IDataObject * pDataObject, LONG * pacpStart, LONG * pacpEnd, TS_TEXTCHANGE * pChange);

      //ITfContextOwnerCompositionSink methods
      STDMETHODIMP OnStartComposition(ITfCompositionView * pComposition, BOOL * pfOk);
      STDMETHODIMP OnUpdateComposition(ITfCompositionView * pComposition, ITfRange * pRangeNew);
      STDMETHODIMP OnEndComposition(ITfCompositionView * pComposition);

      // ITfUIElementSink methods
      virtual HRESULT STDMETHODCALLTYPE BeginUIElement(DWORD dwUIElementId, BOOL * pbShow) override;
      virtual HRESULT STDMETHODCALLTYPE UpdateUIElement(DWORD dwUIElementId)  override;
      virtual HRESULT STDMETHODCALLTYPE EndUIElement(DWORD dwUIElementId)  override;

      // ITfFunctionProvider
      STDMETHODIMP GetType(GUID * pguid);
      STDMETHODIMP GetDescription(BSTR * pbstrDesc);
      STDMETHODIMP GetFunction(REFGUID rguid, REFIID riid, IUnknown ** ppunk);

      //private:
          //static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
      STDMETHODIMP _TestInsert(LONG acpTestStart, LONG acpTestEnd, ULONG cch, LONG * pacpResultStart, LONG * pacpResultEnd);
      //virtual LRESULT _OnCreate(VOID);
      //virtual LRESULT _OnDestroy(VOID);
      ////LRESULT _OnCommand(WORD, WORD, HWND);
      //virtual LRESULT _OnSetFocus(VOID);
      //virtual LRESULT _OnKillFocus(VOID);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);


      //void on_edit_set_focus(::user::interaction * pinteraction);

      virtual bool is_text_composition_active() override;

      //LRESULT _OnEditKillFocus(VOID);
      LRESULT _OnEditChange(void);
      //LRESULT _OnNotify(UINT, LPNMHDR);
      //LRESULT _OnSize(WPARAM, LPARAM);
      HRESULT _ClearAdviseSink(PADVISE_SINK pAdviseSink);
      BOOL _LockDocument(DWORD dwLockFlags);
      void _UnlockDocument();
      BOOL _InternalLockDocument(DWORD dwLockFlags);
      void _InternalUnlockDocument();
      BOOL _IsLocked(DWORD dwLockType);
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
