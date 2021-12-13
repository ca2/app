#include "framework.h"
#include "acme/_start.h"
#include "aura/_.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"


#define SYSTEM core
#define APPLICATION hellomultiverse
#define _APP_ID "app-core/hellomultiverse"


#define DO_FACTORY(do) \
do(node_windows); \
do(draw2d_gdiplus); \
do(write_text_win32); \
do(imaging_wic); \
do(experience_core); \
do(database_sqlite3); \
do(regular_expression_pcre2);

node_windows
draw2d_gdiplus
write_text_win32
.
.
.





#include "acme/inline/_static_setup.h"



#include "aura/application.h"





