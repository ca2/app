//
// Created by camilo on 2026-04-04.
//
#pragma once


namespace innate_subsystem
{


   class Control;

   class BaseDialog;


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


   class Control;
   class ControlInterface;
   class Window;
   class WindowInterface;

   class Cursor;

    class Tab;
    class TabInterface;

    class ComboBox;
    class ComboBoxInterface;

   class SystemMetrics;
   class SystemMetricsInterface;


} // namespace innate_subsystem



#include "apex/innate_subsystem/drawing/_.h"



