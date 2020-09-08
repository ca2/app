#ifdef _UWP


typedef struct tagCREATESTRUCTA
{
   LPVOID      pCreateParams;

   HINSTANCE   hInstance;
   HMENU       hMenu;
   oswindow        hwndParent;
   i32         cy;
   i32         cx;
   i32         y;
   i32         x;
   LONG        style;
   LPCSTR      lpszName;

   LPCSTR      lpszClass;

   u32       dwExStyle;
} CREATESTRUCTA,*LPCREATESTRUCTA;

typedef struct tagCREATESTRUCTW
{
   LPVOID      pCreateParams;

   HINSTANCE   hInstance;
   HMENU       hMenu;
   oswindow    hwndParent;
   i32         cy;
   i32         cx;
   i32         y;
   i32         x;
   LONG        style;
   LPCWSTR     lpszName;

   LPCWSTR     lpszClass;

   u32       dwExStyle;
} CREATESTRUCTW,*LPCREATESTRUCTW;

#ifdef UNICODE
typedef CREATESTRUCTW CREATESTRUCT;
typedef LPCREATESTRUCTW LPCREATESTRUCT ;
#else
typedef CREATESTRUCTA CREATESTRUCT;
typedef LPCREATESTRUCTA LPCREATESTRUCT ;
#endif // UNICODE

#endif




#if defined(LINUX) || defined(APPLEOS)
#define WM_APP 0x8000
#define WM_USER                         0x0400
#endif

