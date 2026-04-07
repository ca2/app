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

   class PaintWindow;
   class PaintWindowInterface;

   class Cursor;

    class Tab;
    class TabInterface;

    class ComboBox;
    class ComboBoxInterface;

   class SystemMetrics;
   class SystemMetricsInterface;


   enum enum_system_command
   {
      e_system_command_none = 0,
      e_system_command_close =       0xF060,
   };


} // namespace innate_subsystem



#include "apex/innate_subsystem/drawing/_.h"



