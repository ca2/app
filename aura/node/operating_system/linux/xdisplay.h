#pragma once

//
//class osdisplay_dataptra;
//class osdisplay_data;
//class ::mutex;


//CLASS_DECL_AURA i32 osdisplay_find(Display * pdisplay);
//CLASS_DECL_AURA osdisplay_data * osdisplay_get(Display * pdisplay);
//CLASS_DECL_AURA bool osdisplay_erase(Display * pdisplay);


//class CLASS_DECL_AURA xdisplay
//{
//public:
//
//
//   osdisplay_data *  m_pdata;
//   bool              m_bLocked;
//   bool              m_bOwn;
//
//   Atom              m_atomWmState;
//
//
//   xdisplay();
//   xdisplay(Display * pdisplay, bool bInitialLock = true);
//   ~ xdisplay();
//
//
//   bool open(char * display_name, bool bInitialLock = true);
//
//   void lock();
//   void unlock();
//
//   bool close();
//
//   inline operator Display *();
//   inline bool is_null();
//   inline bool is_set();
//
//   inline Display * display() { return operator Display *();}
//
//   Window default_root_window();
//
//   int default_screen();
//
//   inline Visual * default_visual() { return DefaultVisual(display(), DefaultScreen(display())); }
//
//   Atom intern_atom(const ::string & pszAtomName, bool bCreate);
//
//   inline auto white_pixel() { return WhitePixel(display(), default_screen()); }
//   inline auto black_pixel() { return BlackPixel(display(), default_screen()); }
//
//};
//
