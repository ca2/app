//
// Created by camilo on 2026-04-04.
//
#pragma once


namespace innate_subsystem
{


   class resource_loader;


   class DeviceContext;
   class DeviceContextInterface;
   class Bitmap;
   class BitmapInterface;
   class Brush;
   class BrushInterface;
   class Pen;
   class PenInterface;
   class Icon;
   class IconInterface;



    enum enum_id
    {
        IDOK = 1, // is one of the standard IDs, others include:
        IDCANCEL = 2,
        IDABORT = 3,
        IDRETRY = 4,
        IDIGNORE = 5,
        IDYES = 6,
        IDNO = 7,
    };


   class Window;
   class WindowInterface;
   class Control;
   class ControlInterface;
   class Dialog;
   class DialogInterface;

   class StringFilter;

   class PaintWindow;
   class PaintWindowInterface;

   class Cursor;

    class Tab;
    class TabInterface;

   using TabContainer = ::pointer_array <TabInterface>;

   class TabControl;
   class TabControlInterface;

    class ComboBox;
    class ComboBoxInterface;

   class Tooltip;
   class TooltipInterface;

   class SystemMetrics;
   class SystemMetricsInterface;


   enum enum_system_command
   {
      e_system_command_none = 0,
      e_system_command_close =       0xF060,
   };


   enum enum_style : unsigned long long
   {

      e_style_child =            0x40000000L, // #define WS_CHILD
      e_style_visible =          0x10000000L, // #define WS_VISIBLE
      e_style_flat_toolbar =     0x0800,      // #define TBSTYLE_FLAT

   };


   struct toolbar_button_t
   {
      int iBitmap;
      int idCommand;
      unsigned char fsState;
      unsigned char fsStyle;
// #ifdef _WIN64
//       unsigned char bReserved[6];          // padding for alignment
// #elif defined(_WIN32)
//       unsigned char bReserved[2];          // padding for alignment
// #endif
      ::uptr  dwData;
      ::iptr iString;
   };


   enum enum_toolbar_item_state
   {

      e_toolbar_item_state_none     = 0,
// #define TBSTATE_CHECKED         0x01
// #define TBSTATE_PRESSED         0x02
// #define TBSTATE_ENABLED         0x04

      e_toolbar_item_state_checked  = 1,
      e_toolbar_item_state_pressed  = 2,
      e_toolbar_item_state_enabled  = 4,

   };


   enum enum_toolbar_item_style
   {
//#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead

      e_toolbar_item_style_button = 0,

   };

   struct draw_item_t;

} // namespace innate_subsystem



#include "apex/innate_subsystem/drawing/_.h"



