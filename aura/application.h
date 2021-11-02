#include "aura/inline/application.h"
#include "acme/platform/set_app_id.h"

static set_app_id g_setappid(__APP_ID);

#ifdef CUBE

#include "acme/_start.h"
#include "aura/_.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"




// #define DO_FACTORY_EXCHANGE(do) \
// do(node_windows); \
// do(draw2d_gdiplus); \
// do(write_text_win32); \
// do(imaging_wic); \
// do(experience_core); \
// do(database_sqlite3); \
// do(regular_expression_pcre2);

#include "_static_factory_exchange.inl"


#endif


#include "acme/inline/_static_setup.h"







