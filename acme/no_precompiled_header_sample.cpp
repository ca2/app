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
#include "acme/prototype/_.h"
#include "acme/user/_.h"


#include "acme/parallelization/_preamble.h"


#include "acme/memory/allocation.h"
#include "acme/platform/reference_count_debug.h"
#include "acme/platform/object_type_counter.h"
#include "acme/memory/::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate.h"
#include "acme/prototype/prototype/_c_memory.h"
#include "acme/memory/heap_c.h"
#include "acme/memory/allocate_processor_cache_oriented.h"
#include "acme/memory/_heap.h"


#include "acme/constant/parallelization.h"
#include "acme/filesystem/file/_c.h"
#include "acme/parallelization/critical_section.h"
#include "acme/platform/display.h"
#include "acme/platform/lparam.h"
#include "acme/prototype/comparison/compare.h"
//#include "acme/prototype/prototype/e_status.h"
#include "acme/prototype/logic/boolean.h"
#include "acme/prototype/prototype/logic.h"
#include "acme/prototype/mathematics/c_number.h"
#include "acme/prototype/mathematics/numeric_info.h"
#include "acme/prototype/prototype/e_check.h"
#include "acme/prototype/prototype/transfer.h"


#include  "acme/prototype/time/_.h"
#include  "acme/prototype/string/string.h"
#include  "acme/prototype/prototype/payload.h"
#include  "acme/prototype/prototype/object.h"
#include  "acme/exception/exception.h"
#include  "acme/platform/class.h"


#include "acme/prototype/string/scoped_string_base.h"

#include "_string.h"


#include "acme/filesystem/_impl.h"
#include "acme/prototype/string/_impl.h"
#include "_impl.h"
#include "acme/prototype/time/_impl.h"
#include "acme/prototype/mathematics/_impl.h"
#include "acme/prototype/prototype/_impl.h"
#include "acme/prototype/_impl.h"
#include "acme/memory/_impl.h"
