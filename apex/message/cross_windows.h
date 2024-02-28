


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
//   i32         cy;
//   i32         cx;
//   i32         y;
//   i32         x;
//   ::i32        style;
//   const char *      lpszName;
//
//   const char *      lpszClass;
//
//   u32       dwExStyle;
//} CREATESTRUCTA,*LPCREATESTRUCTA;
//
//typedef struct tagCREATESTRUCTW
//{
//   LPVOID      pCreateParams;
//
//   HINSTANCE   hInstance;
//   HMENU       hMenu;
//   oswindow    hwndParent;
//   i32         cy;
//   i32         cx;
//   i32         y;
//   i32         x;
//   ::i32        style;
//   const ::wide_character *     lpszName;
//
//   const ::wide_character *     lpszClass;
//
//   u32       dwExStyle;
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

