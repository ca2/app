
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/nano/user/window.h"


#include "acme/operating_system/x11/_.h"


#ifdef OPENBSD

#include <stdio.h>

#endif


#define MAXSTR 1000


//::e_status defer_initializex_x11();


int x11_init_threads();
//Display * x11_get_display();


void set_main_user_thread();


namespace x11
{


   namespace nano
   {
      namespace user
      {

         display * display::g_p = nullptr;


         display::display()
         {

            m_pdisplay = nullptr;

            m_bUnhook = false;

            if(!g_p)
            {

               g_p = this;

            }

            defer_create_synchronization();


         }


         display::~display()
         {


         }


         Atom display::intern_atom(const char *pszAtomName, bool bCreate)
         {

            return _intern_atom_unlocked(pszAtomName, bCreate);

            //      if (m_pdisplay == nullptr)
            //      {
            //
            //         return 0;
            //
            //      }
            //
            //      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
            //
            //      if (atom == None)
            //      {
            //
            //         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");
            //
            //         return None;
            //
            //      }
            //
            //      return atom;

         }


         Atom display::intern_atom(enum_atom eatom, bool bCreate)
         {

            return _intern_atom_unlocked(eatom, bCreate);

            //      if (eatom < 0 || eatom >= e_atom_count)
            //      {
            //
            //         return None;
            //
            //      }
            //
            //      Atom atom = m_atommap[eatom];
            //
            //      if (atom == None)
            //      {
            //
            //         atom = intern_atom(atom_name(eatom), bCreate);
            //
            //         m_atommap[eatom] = atom;
            //
            //      }
            //
            //      return atom;

         }



         Atom display::_intern_atom_unlocked(const char *pszAtomName, bool bCreate)
         {

            if (m_pdisplay == nullptr)
            {

               return 0;

            }

            auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);

            if (atom == None)
            {

               windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");

               return None;

            }

            return atom;

         }


         Atom display::_intern_atom_unlocked(enum_atom eatom, bool bCreate)
         {

            if (eatom < 0 || eatom >= e_atom_count)
            {

               return None;

            }

            Atom atom = m_atommap[eatom];

            if (atom == None)
            {

               atom = _intern_atom_unlocked(atom_name(eatom), bCreate);

               m_atommap[eatom] = atom;

            }

            return atom;

         }


         unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
         {

            unsigned char * prop;
            Atom actual_type, filter_atom;
            int actual_format, status;
            unsigned long nitems, bytes_after;

            filter_atom = XInternAtom(display, property_name, True);

            status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                                        &actual_type, &actual_format, &nitems, &bytes_after, &prop);

            x11_check_status(status, window);

            return prop;

         }


         unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
         {

            unsigned char *prop = _get_string_property(d, w, property_name);

            unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);

            XFree(prop);

            return long_property;

         }


         Window display::_get_active_window()
         {

            int screen = XDefaultScreen(m_pdisplay);

            Window windowRoot = RootWindow(m_pdisplay, screen);

            Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");

            return window;

         }


         Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
         {

            Window window, root, parent, *children;

            unsigned children_count;

            char *name = NULL;

            window = 0;

            /* If it does not: check all subwindows recursively. */
            if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
            {

               unsigned i;

               for(i = 0; i < children_count; ++i)
               {

                  /* Check if this window has the name we seek */
                  if(XFetchName(display,  children[i], &name) > 0)
                  {

                     int r = ansi_cmp(needle, name);

                     XFree(name);

                     if(r == 0)
                     {

                        window = children[i+iOffset];

                        break;

                     }

                  }

                  if(depth > 1)
                  {

                     Window win = window_from_name_search(display, children[i], needle, depth - 1);

                     if (win != 0)
                     {

                        window = win;

                        break;

                     }

                  }

               }

               XFree(children);

            }

            return window;

         }


         Window display::window_from_name(char const *name, int iOffset, int depth)
         {

            auto display = m_pdisplay;

            auto windowRoot = XDefaultRootWindow(display);

            auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);

            return window;

         }


         display * display::_nano_get_x11_display(::particle * pparticle, bool bBranch, Display * pdisplay)
         {

            critical_section_lock lock(pparticle->platform()->globals_critical_section());

            if (g_p == nullptr)
            {

               auto p = __new< display >();

               p->initialize(pparticle);

               p->add_listener(p);

               p->m_pdisplay = pdisplay;

               if(bBranch)
               {

                  p->branch_synchronously();

               }
               else
               {

                  p->init_task();

               }

            }

            return g_p;

         }


         void display::add_listener(event_listener * plistener)
         {

            synchronous_lock synchronouslock(this->synchronization());

            m_eventlistenera.add(plistener);

         }


         void display::add_window(nano::user::window * pwindow)
         {

            synchronous_lock synchronouslock(this->synchronization());

            m_windowa.add(pwindow);

         }


         void display::erase_listener(event_listener * plistener)
         {

            synchronous_lock synchronouslock(this->synchronization());

            m_eventlistenera.erase(plistener);

         }


         void display::erase_window(::x11::nano::user::window * pwindow)
         {

            synchronous_lock synchronouslock(this->synchronization());

            m_windowa.erase(pwindow);

         }


         bool display::message_loop_step()
         {

            if(::is_null(m_pdisplay))
            {

               return false;

            }

            if (!XPending(m_pdisplay))
            {

               return false;

            }

            XEvent event{};

            XNextEvent(m_pdisplay, &event);

            x11_event(&event);

            return true;

         }


         bool display::x11_posted()
         {

            return display_posted_routine_step();

         }


         bool display::x11_event(XEvent * pevent)
         {

            bool bHandled = false;

            ::collection::index i = 0;

            _synchronous_lock synchronouslock(this->synchronization());

            for (; i < m_eventlistenera.get_count(); i++)
            {

               auto plistener = m_eventlistenera[i];

               synchronouslock.unlock();

               if(i == 0)
               {

                  if (plistener->_on_event(pevent))
                  {

                     bHandled = true;

                     break;

                  }

               }
               else
               {

                  if (plistener->_on_event(pevent))
                  {

                     bHandled = true;

                     break;

                  }

               }

               synchronouslock._lock();

            }

            return bHandled;

         }


         void display::message_loop()
         {

            bool bHandled1;

            bool bHandled2;

            information() << "x11::nano::user::display::message_loop";

            while (::task_get_run())
            {

               if(m_bUnhook)
               {

                  break;

               }

               bHandled1 = false;

               bHandled2 = false;

               while(message_loop_step())
               {

                  bHandled1 = true;

               }

               if(!bHandled1)
               {

                  bHandled2 = x11_posted();

               }

               if(!bHandled1 && !bHandled2)
               {

                  preempt(5_ms);

               }

            }

            information() << "Finished display::message_loop for nano::display";

         }


         void display::init_task()
         {

            informationf("x11 nano display init_task");

            if(system()->m_ewindowing == e_windowing_none)
            {

               //set_main_user_thread();

               system()->m_ewindowing = e_windowing_x11;

            }

            // printf("\n\nx11::display::init_task Going to call x11_defer_initialize\n\n");
            //
            // fflush(stdout);
            //
            // node()->x11_defer_initialize();

            if(!m_pdisplay)
            {

               set_X11_Display((Display *) node()->x11_get_display());

            }

         }


         void display::set_X11_Display(Display * pdisplay)
         {

            m_pdisplay = pdisplay;

            if (!m_pdisplay)
            {

               throw ::exception(error_null_pointer);

            }

            ::rectangle_i32 rectangleMainScreen;

            auto pscreen = DefaultScreenOfDisplay(m_pdisplay);

            int wScreen = WidthOfScreen(pscreen);
            int hScreen = HeightOfScreen(pscreen);

            //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
            //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

            //rectangleMainScreen.left() = 0;
            //rectangleMainScreen.top() = 0;
            //rectangleMainScreen.right() = wScreen;
            //rectangleMainScreen.bottom() = hScreen;

            //operating_system_set_main_screen_rectangle(rectangleMainScreen);

         }


         bool display::is_branch_current() const
         {

            if(!m_bUnhook && ::object::is_branch_current())
            {

               return true;

            }

            if(m_bUnhook && ::is_main_thread())
            {

               return true;

            }

            return false;

         }


         void display::run()
         {

            ::task_set_name("x11:display:run");

            information() << "x11::display::run";

            set_main_user_thread();

            message_loop();

            if (m_pdisplay != nullptr)
            {

               XCloseDisplay(m_pdisplay);

               m_pdisplay = nullptr;

            }

         }


         bool display::_on_event(XEvent * pevent)
         {

            if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
            {

               if(pevent->xany.type == PropertyNotify)
               {

                  Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);

                  if (atom == pevent->xproperty.atom)
                  {

                     auto windowActive = m_windowActive;

                     for(auto & pwindow : m_windowa)
                     {

                        bool bNcActive = windowActive == pwindow->m_window;

                        if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
                        {

                           pwindow->m_pinterface->m_bNcActive = bNcActive;

                           pwindow->redraw();

                        }

                     }

                     m_windowActive = windowActive;

                  }

               }

            }

            return false;

         }


         ::size_i32 display::get_main_screen_size()
         {

            auto snum = DefaultScreen(m_pdisplay);

            auto width = DisplayWidth(m_pdisplay, snum);

            auto height = DisplayHeight(m_pdisplay, snum);

            return { width, height };

         }


      // void * x11_get_display(::particle * pparticle)
      // {
      //
      //    auto pdisplay = ::x11::display::get(pparticle, false);
      //
      //    return pdisplay->m_pdisplay;
      //
      // }


      // void initialize_x11_display(::particle * pparticle, void * pX11Display)
      // {
      //
      //    ::x11::display::get(pparticle, false, (Display *) pX11Display);
      //
      // }


      // void * initialize_x11_display(::particle * pparticle)
      // {
      //
      //    auto pdisplay = ::x11::display::get(pparticle, false);
      //
      //    return pdisplay->m_pdisplay;
      //
      // }


      void process_messages()
      {

         if(::x11::nano::user::display::g_p)
         {

            ::x11::nano::user::display::g_p->message_loop_step();

         }

      }


      i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);

         //::e_status g_estatusInitializeX11 = error_not_initialized;



         int init_threads()
         {

            return XInitThreads();

         }





i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{

   const char * pszError;

   if(perrorevent->error_code == BadRequest)
   {

      pszError = "BadRequest";

   }
   else if(perrorevent->error_code == BadValue)
   {

      pszError = "BadValue";

   }
   else if(perrorevent->error_code == BadWindow)
   {

      pszError = "BadWindow";

   }
   else if(perrorevent->error_code == BadPixmap)
   {

      pszError = "BadPixmap";

   }
   else if(perrorevent->error_code == BadAtom)
   {

      pszError = "BadAtom";

   }
   else if(perrorevent->error_code == BadCursor)
   {

      pszError = "BadCursor";

   }
   else if(perrorevent->error_code == BadFont)
   {

      pszError = "BadFont";

   }
   else if(perrorevent->error_code == BadMatch)
   {

      pszError = "BadMatch";

   }
   else if(perrorevent->error_code == BadDrawable)
   {

      pszError = "BadDrawable";

   }
   else if(perrorevent->error_code == BadAccess)
   {

      pszError = "BadAccess";

   }
   else if(perrorevent->error_code == BadAlloc)
   {

      pszError = "BadAlloc";

   }
   else if(perrorevent->error_code == BadColor)
   {

      pszError = "BadColor";

   }
   else if(perrorevent->error_code == BadGC)
   {

      pszError = "BadGC";

   }
   else if(perrorevent->error_code == BadIDChoice)
   {

      pszError = "BadIDChoice";

   }
   else if(perrorevent->error_code == BadName)
   {

      pszError = "BadName";

   }
   else if(perrorevent->error_code == BadLength)
   {

      pszError = "BadLength";

   }
   else if(perrorevent->error_code == BadImplementation)
   {

      pszError = "BadImplementation";

   }
   else
   {

      pszError = " ( Unknown ) ";

   }

const char * pszRequest;
   if(perrorevent->request_code == 1)
   {

      pszRequest = "X_CreateWindow";

   }
   else if(perrorevent->request_code == 2)
   {

      pszRequest = "X_ChangeWindowAttributes";

   }
   else if(perrorevent->request_code == 3)
   {

      pszRequest = "X_GetWindowAttributes";

   }
   else if(perrorevent->request_code == 4)
   {

      pszRequest = "X_DestroyWindow";

   }
   else if(perrorevent->request_code == 5)
   {

      pszRequest = "X_DestroySubwindows";

   }
   else if(perrorevent->request_code == 6)
   {

      pszRequest = "X_ChangeSaveSet";

   }
   else if(perrorevent->request_code == 7)
   {

      pszRequest = "X_ReparentWindow";

   }
   else if(perrorevent->request_code == 8)
   {

      pszRequest = "X_MapWindow";

   }
   else if(perrorevent->request_code == 9)
   {

      pszRequest = "X_MapSubwindows";

   }
   else if(perrorevent->request_code == 10)
   {

      pszRequest = "X_UnmapWindow";

   }
   else if(perrorevent->request_code == 11)
   {

      pszRequest = "X_UnmapSubwindows";

   }
   else if(perrorevent->request_code == 12)
   {

      pszRequest = "X_ConfigureWindow";

   }


      #define X_CreateWindow                  1
#define X_ChangeWindowAttributes        2
#define X_GetWindowAttributes           3
#define X_DestroyWindow                 4
#define X_DestroySubwindows             5
#define X_ChangeSaveSet                 6
#define X_ReparentWindow                7
#define X_MapWindow                     8
#define X_MapSubwindows                 9
#define X_UnmapWindow                  10
#define X_UnmapSubwindows              11
#define X_ConfigureWindow              12
#define X_CirculateWindow              13
#define X_GetGeometry                  14
#define X_QueryTree                    15
#define X_InternAtom                   16
#define X_GetAtomName                  17
#define X_ChangeProperty               18
#define X_DeleteProperty               19
#define X_GetProperty                  20
#define X_ListProperties               21
#define X_SetSelectionOwner            22
#define X_GetSelectionOwner            23
#define X_ConvertSelection             24
#define X_SendEvent                    25
#define X_GrabPointer                  26
#define X_UngrabPointer                27
#define X_GrabButton                   28
#define X_UngrabButton                 29
#define X_ChangeActivePointerGrab      30
#define X_GrabKeyboard                 31
#define X_UngrabKeyboard               32
#define X_GrabKey                      33
#define X_UngrabKey                    34
#define X_AllowEvents                  35
#define X_GrabServer                   36
#define X_UngrabServer                 37
#define X_QueryPointer                 38
#define X_GetMotionEvents              39
#define X_TranslateCoords              40
#define X_WarpPointer                  41
#define X_SetInputFocus                42
#define X_GetInputFocus                43
#define X_QueryKeymap                  44
#define X_OpenFont                     45
#define X_CloseFont                    46
#define X_QueryFont                    47
#define X_QueryTextExtents             48
#define X_ListFonts                    49
#define X_ListFontsWithInfo    	       50
#define X_SetFontPath                  51
#define X_GetFontPath                  52
#define X_CreatePixmap                 53
#define X_FreePixmap                   54
#define X_CreateGC                     55
#define X_ChangeGC                     56
#define X_CopyGC                       57
#define X_SetDashes                    58
#define X_SetClipRectangles            59
#define X_FreeGC                       60
#define X_ClearArea                    61
#define X_CopyArea                     62
#define X_CopyPlane                    63
#define X_PolyPoint                    64
#define X_PolyLine                     65
#define X_PolySegment                  66
#define X_PolyRectangle                67
#define X_PolyArc                      68
#define X_FillPoly                     69
#define X_PolyFillRectangle            70
#define X_PolyFillArc                  71
#define X_PutImage                     72
#define X_GetImage                     73
#define X_PolyText8                    74
#define X_PolyText16                   75
#define X_ImageText8                   76
#define X_ImageText16                  77
#define X_CreateColormap               78
#define X_FreeColormap                 79
#define X_CopyColormapAndFree          80
#define X_InstallColormap              81
#define X_UninstallColormap            82
#define X_ListInstalledColormaps       83
#define X_AllocColor                   84
#define X_AllocNamedColor              85
#define X_AllocColorCells              86
#define X_AllocColorPlanes             87
#define X_FreeColors                   88
#define X_StoreColors                  89
#define X_StoreNamedColor              90
#define X_QueryColors                  91
#define X_LookupColor                  92
#define X_CreateCursor                 93
#define X_CreateGlyphCursor            94
#define X_FreeCursor                   95
#define X_RecolorCursor                96
#define X_QueryBestSize                97
#define X_QueryExtension               98
#define X_ListExtensions               99
#define X_ChangeKeyboardMapping        100
#define X_GetKeyboardMapping           101
#define X_ChangeKeyboardControl        102
#define X_GetKeyboardControl           103
#define X_Bell                         104
#define X_ChangePointerControl         105
#define X_GetPointerControl            106
#define X_SetScreenSaver               107
#define X_GetScreenSaver               108
#define X_ChangeHosts                  109
#define X_ListHosts                    110
#define X_SetAccessControl             111
#define X_SetCloseDownMode             112
#define X_KillClient                   113
#define X_RotateProperties	       114
#define X_ForceScreenSaver	       115
#define X_SetPointerMapping            116
#define X_GetPointerMapping            117
#define X_SetModifierMapping	       118
#define X_GetModifierMapping	       119
#define X_NoOperation                  127

   else
   {

      pszRequest = " ( Unknown ) ";

   }

   fprintf(stderr, "_c_XErrorHandler error=%d (%s) request =%d (%s)\n", perrorevent->error_code, pszError, perrorevent->request_code, pszRequest);

   return 0;

}




      } // namespace user

   }// namespace nano


} // namespace x11



namespace acme
{

   ::e_status node::x11_initialize()
   {

      informationf("acme::node::x11_initialize going to call x11_init_threads");

      fflush(stdout);

      if (!::x11::nano::user::init_threads())
      {

         return ::error_failed;

      }

      XSetErrorHandler(::x11::nano::user::_c_XErrorHandler);

      //g_pmutexX11 = __new< ::pointer < ::mutex > >();

      return ::success;

   }


   ::e_status node::x11_defer_initialize()
   {

      if (m_estatusInitializeX11 == error_not_initialized)
      {

         m_estatusInitializeX11 = x11_initialize();

      }

      return m_estatusInitializeX11;

   }


   //Display * g_pdisplayX11= nullptr;


   //int g_fdX11[2] = {};


   void * node::x11_get_display()
   {

      x11_defer_initialize();

      if(m_pvoidX11Display == NULL)
      {

         m_pvoidX11Display =  XOpenDisplay(NULL);

      }

      return m_pvoidX11Display;

   }


} // namespace acme



