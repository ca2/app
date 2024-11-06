


//#ifdef UNIVERSAL_WINDOWS
//
//
//typedef struct tagCREATESTRUCTA
//{
//   LPVOID      pCreateParams;
//
//   HINSTANCE   hInstance;
//   HMENU       hMenu;
//   oswindow        hwndParent;
//   int         cy;
//   int         cx;
//   int         y;
//   int         x;
//   int        style;
//   const char *      lpszName;
//
//   const char *      lpszClass;
//
//   unsigned int       dwExStyle;
//} CREATESTRUCTA,*LPCREATESTRUCTA;
//
//typedef struct tagCREATESTRUCTW
//{
//   LPVOID      pCreateParams;
//
//   HINSTANCE   hInstance;
//   HMENU       hMenu;
//   oswindow    hwndParent;
//   int         cy;
//   int         cx;
//   int         y;
//   int         x;
//   int        style;
//   const ::wide_character *     lpszName;
//
//   const ::wide_character *     lpszClass;
//
//   unsigned int       dwExStyle;
//} CREATESTRUCTW,*LPCREATESTRUCTW;
//
//#ifdef UNICODE
//typedef CREATESTRUCTW CREATESTRUCT;
//typedef LPCREATESTRUCTW LPCREATESTRUCT ;
//#else
//typedef CREATESTRUCTA CREATESTRUCT;
//typedef LPCREATESTRUCTA LPCREATESTRUCT ;
//#endif // UNICODE
//
//#endif




#if defined(LINUX) || defined(__APPLE__)
#define WM_APP 0x8000
#define WM_USER                         0x0400
#endif

