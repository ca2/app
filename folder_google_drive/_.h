#pragma once
#include "apex/_.h"

#if defined(_folder_google_drive_project)
#define CLASS_DECL_FOLDER_GOOGLE_DRIVE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_FOLDER_GOOGLE_DRIVE CLASS_DECL_IMPORT
#endif

namespace folder_google_drive { class folder; }
