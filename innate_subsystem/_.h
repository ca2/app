//
// Created by camilo on 2026-04-04.
//
#pragma once



#include "subsystem/_.h"
#include "apex/_.h"


#if defined(_innate_subsystem_project)
#define CLASS_DECL_INNATE_SUBSYSTEM CLASS_DECL_EXPORT
#else
#define CLASS_DECL_INNATE_SUBSYSTEM CLASS_DECL_IMPORT
#endif



#include "subsystem/platform/particle.h"


namespace innate_subsystem
{


   class ResourceLoader;


   class DeviceContext;
    class DeviceContextInterface;
   //using DeviceContextInterface = particle_interface<DeviceContextInterface>;
   class Bitmap;
    class BitmapInterface;
   //using BitmapInterface = particle_interface<BitmapContextInterface>;
   class Brush;
    class BrushInterface;
   //using BrushInterface = particle_interface<BrushContextInterface>;
   class Font;
    class FontInterface;
   //using FontInterface = particle_interface<FontContextInterface>;
   class Pen;
    class PenInterface;
   //using PenInterface = particle_interface<PenContextInterface>;
   class Icon;
    class IconInterface;
   //using IconInterface = particle_interface<IconContextInterface>;
   class Cursor;
    class CursorInterface;
   //using CursorInterface = particle_interface<CursorContextInterface>;
   class Menu;
    class MenuInterface;
   //using MenuInterface = particle_interface<MenuContextInterface>;

   class GraphicsObject;


    enum enum_control_id
    {
        e_control_id_ok = 1, // IDOK// is one of the standard IDs, others include:
        e_control_id_cancel = 2, // IDCANCEL
        e_control_id_abort = 3, // IDABORT
        e_control_id_retry = 4, // IDRETRY
        e_control_id_ignore = 5, // IDIGNORE
        e_control_id_yes = 6, // IDYES
        e_control_id_no = 7, // IDNO
    };


   class Window;
   class WindowInterface;
   ///using WindowInterface = particle_interface<WindowInterface>;
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


   class KeyboardLayout;
   class KeyboardLayoutInterface;


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



#include "innate_subsystem/drawing/_.h"



