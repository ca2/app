#include "framework.h"
#include "process.h"
#include "acme/operating_system.h"
#include "acme/platform/version.h"
#include "acme/primitive/string/command_line.h"
#include "acme/primitive/string/string.h"




CLASS_DECL_ACME string process_version_dir_name()
{

   return framework_is_stage() ? "stage" : "basis";

}
