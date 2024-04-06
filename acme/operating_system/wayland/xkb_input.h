//
// Created by camilo on 9/19/23 01:01 <3ThomasBorregaardSorensen!!
//
#pragma once


struct xkb_keymap;
struct xkb_context;
struct xkb_state;


namespace xkb_input
{


   class xkb_input :
      virtual public ::particle
   {
   public:



      ::string          m_strXkbKeymapString;
      ::i32             m_iXkbKeymapFormat;
      ::i32             m_iXkbKeymapFlags;
      bool              m_bNewXkbKeymap;

      ::xkb_context *   m_pxkbcontext;
      ::xkb_keymap*     m_pxkbkeymap;
      ::xkb_state *     m_pxkbstate;


      xkb_input();
      ~xkb_input() override;



      virtual void __xkb_keymap_new_from_string(const char * p, int format, int flags);


      virtual void xkb_keymap_new_from_string(const char * p, int format, int flags);


      virtual void defer_update_xkb_keymap();


   };


} // namespace xkb_input



