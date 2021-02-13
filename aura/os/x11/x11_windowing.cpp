#include "framework.h"
#include "base/user/user/_user.h"
#include "aura/os/linux/_user.h"
//!!!#include <X11/extensions/Xinerama.h>


//http://rosettacode.org/wiki/Window_creation/X11

//!!!#include <X11/Xlib.h>
#include <stdio.h>

#include <string.h>
#include "_x11.h"

extern ::mutex * x11_mutex();

Visual * get_32bit_visual(Display * pdisplay);

static Display * s_pdisplay = NULL;

Display * x11_get_display()
{

   if(s_pdisplay == NULL)
   {

      s_pdisplay =  XOpenDisplay(NULL);

   }

   return s_pdisplay;

}

#define SIMPLE_UI_MAX_BUTTON_COUNT 8

class x11Button :
   virtual public matter
{
public:


   wstring           m_wstrLabel;
   bool              m_bTextRect;
   ::rectangle_i32            m_rectangle;
   XRectangle        m_rectText;
   bool              m_bPress;
   bool              m_bHover;
   string            m_strResult;


   x11Button(const char * psz, const char * pszResult) :
      m_wstrLabel(psz),
      m_strResult(pszResult)
   {

      m_bTextRect = false;
      m_bPress = false;
      m_bHover = false;

   }

   virtual ~x11Button()
   {

   }

};



