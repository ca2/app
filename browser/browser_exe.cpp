#include "framework.h"

#define ACID

extern ::i32 APIENTRY app_browser_deferred_run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      char_pointer lpCmdLine,
      ::i32 nCmdShow);

//::i32 app_browser_runner(HINSTANCE hInstance);

//#define MAIN_RUNNER0 &::app_browser_runner
#define MAIN_DEFERRED_RUN &::app_browser_deferred_run

#include "aura/inline/app.inl"
