//
// Created by camilo on 9/19/23 01:01 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "xkb_input.h"
#include <xkbcommon/xkbcommon.h>


namespace xkb_input
{


   xkb_input::xkb_input()
   {

      m_iXkbKeymapFormat = 0;
      m_iXkbKeymapFlags = 0;
      m_bNewXkbKeymap = false;

      m_pxkbcontext = nullptr;
      m_pxkbkeymap = nullptr;
      m_pxkbstate = nullptr;


   }


   xkb_input::~xkb_input()
   {

      if(m_pxkbstate)
      {

         xkb_state_unref(m_pxkbstate);

         m_pxkbstate = nullptr;

      }

      if(m_pxkbkeymap)
      {

         xkb_keymap_unref(m_pxkbkeymap);

         m_pxkbkeymap = nullptr;

      }

      if(m_pxkbcontext)
      {

         ::xkb_context_unref(m_pxkbcontext);

         m_pxkbcontext = nullptr;

      }

   }


   void xkb_input::xkb_keymap_new_from_string(const char * p, int format, int flags)
   {

      m_strXkbKeymapString = p;

      m_iXkbKeymapFormat = format;

      m_iXkbKeymapFlags = flags;

      m_bNewXkbKeymap = true;

   }


   void xkb_input::defer_update_xkb_keymap()
   {

      if(m_bNewXkbKeymap)
      {

         m_bNewXkbKeymap = false;

         __xkb_keymap_new_from_string(m_strXkbKeymapString, m_iXkbKeymapFormat, m_iXkbKeymapFlags);

      }

   }


   void xkb_input::__xkb_keymap_new_from_string(const char * p, int iFormat, int iFlags)
   {

      if(!m_pxkbcontext)
      {

         m_pxkbcontext = xkb_context_new({});

      }

      if(m_pxkbstate)
      {

         xkb_state_unref(m_pxkbstate);

         m_pxkbstate = nullptr;

      }

      if(m_pxkbkeymap)
      {

         xkb_keymap_unref(m_pxkbkeymap);

         m_pxkbkeymap = nullptr;

      }

      auto format = (xkb_keymap_format) iFormat;

      auto flags = (xkb_keymap_compile_flags) iFlags;

      m_pxkbkeymap = ::xkb_keymap_new_from_string(
            m_pxkbcontext, (const char *) p, format,
            flags);

      if(!m_pxkbkeymap)
      {

         warning() << "Failed to xkb_keymap_new_from_string";

      }

      m_pxkbstate = xkb_state_new(m_pxkbkeymap);

      if(!m_pxkbstate)
      {

         warning() << "Failed to xkb_state_new";

      }

   }


} // namespace xkb_input



