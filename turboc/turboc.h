#pragma once


#include "aura/_.h"
#include "aura/filesystem/filemanager/filemanager.h"
#include "aura/user/user.h"


//#include "ft2build.h"
//#include FT_FREETYPE_H


#if defined(_app_turboc_project)
#define CLASS_DECL_TURBOC  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TURBOC  CLASS_DECL_IMPORT
#endif


namespace turboc
{

   class application;
   class top_impact;
   class main_impact;
   class document;
   class impact;

} // namespace flag

namespace turboc
{


   class application;
   class action_context;


} // namespace turboc


#undef APP_TYPE
#define APP_TYPE ::turboc::application


#include "src/turboc.h"


#include "turboc_document.h"
#include "turboc_edit_impact.h"
#include "turboc_toggle_impact.h"
#include "turboc_top_impact.h"
#include "turboc_impact.h"
#include "turboc_lite_impact.h"
#include "turboc_full_impact.h"
#include "turboc_main_impact.h"
#include "turboc_switcher_impact.h"
#include "turboc_frame.h"

#include "turboc_pane_impact.h"
