#define NO_TEMPLATE

struct TIME;


class matter;
class topic;
class context;
class payload;
class time;
class task_pool;
class object;
//class stream;
//class payload_stream;


namespace message
{

   class message;

} // namespace message


#include "acme/_start.h"
#include "acme/include/_c.h"
//#include "acme/platform/object_reference_count_debug.h"
//
//  
//  // C-includes
////#include "acme/_c.h"
//#include "acme/memory/memory_allocate.h"
//#include "acme/memory/secondary_memory_allocate.h"
//#include "acme/memory/heap_c.h"
//
//
//#include "acme/constant/_.h"
//
//
//#include "acme/constant/thread.h"
//#include "acme/constant/message.h"
//#include "acme/constant/impact.h"


//#include "_macro.h"
#include "acme/include/_configuration.h"
#include "acme/include/_types.h"
#include "acme/constant/_.h"
#include "acme/include/_forward_declaration.h"
#include "acme/include/_structures.h"
#include "acme/include/_initial_concepts.h"
#include "acme/include/_template_forward_declaration.h"
#include "acme/include/_template_structures.h"
#include "acme/include/_enumeration.h"
#include "acme/include/_c.h"
#include "acme/include/_function_declarations.h"
#include "acme/include/_template_function_declarations.h"
#include "acme/include/_inline_functions.h"
#include "acme/include/_template_inline_functions.h"
#include "acme/exception/_.h"
#include "acme/filesystem/_.h"
#include "acme/graphics/_.h"
#include "acme/parallelization/_.h"
#include "acme/primitive/_.h"
#include "acme/user/_.h"


#include "acme/parallelization/_preamble.h"


#include "acme/memory/allocation.h"
#include "acme/platform/object_reference_count_debug.h"
#include "acme/platform/object_type_counter.h"
#include "acme/memory/memory_allocate.h"
#include "acme/primitive/primitive/_c_memory.h"
#include "acme/memory/heap_c.h"
#include "acme/memory/allocate_processor_cache_oriented.h"
#include "acme/memory/_heap.h"


#include "acme/constant/parallelization.h"
#include "acme/filesystem/file/_c.h"
#include "acme/parallelization/critical_section.h"
#include "acme/platform/display.h"
#include "acme/platform/lparam.h"
#include "acme/primitive/comparison/compare.h"
//#include "acme/primitive/primitive/e_status.h"
#include "acme/primitive/logic/tristate.h"
#include "acme/primitive/primitive/logic.h"
#include "acme/primitive/mathematics/c_number.h"
#include "acme/primitive/mathematics/numeric_info.h"
#include "acme/primitive/primitive/e_check.h"
#include "acme/primitive/primitive/transfer.h"


#include  "acme/primitive/time/_.h"
#include  "acme/primitive/string/string.h"
#include  "acme/primitive/primitive/payload.h"
#include  "acme/primitive/primitive/object.h"
#include  "acme/exception/exception.h"
#include  "acme/platform/class.h"
#include  "acme/platform/factory_function.h"


#include "acme/primitive/string/scoped_string_base.h"

#include "_string.h"


#include "acme/filesystem/_impl.h"
#include "acme/primitive/string/_impl.h"
#include "_impl.h"
#include "acme/primitive/time/_impl.h"
#include "acme/primitive/mathematics/_impl.h"
#include "acme/primitive/primitive/_impl.h"
#include "acme/primitive/_impl.h"
#include "acme/memory/_impl.h"
