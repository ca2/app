#include "framework.h"
#include <X11/Xft/Xft.h>
// Ubuntu apt-get install libxft-dev
// CentOS yum install libXft-devel
// openSUSE zypper install libxft-devel





namespace draw2d_xlib
{


   font::font(::layered * pobjectContext) :
   ::object(pobject)
   {

      m_pdisplay = nullptr;
      m_pfont = nullptr;
      m_fontset = None;
      m_pft = nullptr;

   }


   font::~font()
   {

      if(m_fontset != None && m_pdisplay != nullptr)
      {
         XFreeFontSet(m_pdisplay, m_fontset);
         m_fontset = nullptr;
      }

      if(m_pfont != nullptr && m_pdisplay != nullptr)
      {
         XFreeFont(m_pdisplay, m_pfont);
         m_pfont = nullptr;
      }

      if(m_pft != nullptr && m_pdisplay != nullptr)
      {
         XftFontClose(m_pdisplay, m_pft);
         m_pft = nullptr;
      }

      m_pdisplay = nullptr;

   }


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::font::dump(dumpcontext);

   }


   void * font::get_os_data() const
   {

      return (void *) m_fontset;

   }


} // namespace draw2d_xlib





