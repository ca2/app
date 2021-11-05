#include "framework.h"

#define ACID

extern int APIENTRY app_browser_deferred_run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      char * lpCmdLine,
      int nCmdShow);

//int app_browser_runner(HINSTANCE hInstance);

//#define MAIN_RUNNER0 &::app_browser_runner
#define MAIN_DEFERRED_RUN &::app_browser_deferred_run

#include "aura/inline/app.inl"
