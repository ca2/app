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


#include "acid/_start.h"
#include "acid/include/_c.h"


#include "acid/include/_configuration.h"
#include "acid/include/_types.h"
#include "acid/constant/_.h"
#include "acid/include/_forward_declaration.h"
#include "acid/include/_structures.h"
#include "acid/include/_initial_concepts.h"
#include "acid/include/_template_forward_declaration.h"
#include "acid/include/_template_structures.h"
#include "acid/include/_enumeration.h"
#include "acid/include/_c.h"
#include "acid/include/_function_declarations.h"
#include "acid/include/_template_function_declarations.h"
#include "acid/include/_inline_functions.h"
#include "acid/include/_template_inline_functions.h"
#include "acid/exception/_.h"
#include "acid/filesystem/_.h"
#include "acid/graphics/_.h"
#include "acid/parallelization/_.h"
#include "acid/primitive/_.h"
#include "acid/user/_.h"


#include "acid/parallelization/_preamble.h"


#include "acid/memory/allocation.h"
#include "acid/platform/reference_count_debug.h"
#include "acid/platform/object_type_counter.h"
#include "acid/memory/::acid::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate.h"
#include "acid/primitive/primitive/_c_memory.h"
#include "acid/memory/heap_c.h"
#include "acid/memory/allocate_processor_cache_oriented.h"
#include "acid/memory/_heap.h"


#include "acid/constant/parallelization.h"
#include "acid/filesystem/file/_c.h"
#include "acid/parallelization/critical_section.h"
#include "acid/platform/display.h"
#include "acid/platform/lparam.h"
#include "acid/primitive/comparison/compare.h"
//#include "acid/primitive/primitive/e_status.h"
#include "acid/primitive/logic/boolean.h"
#include "acid/primitive/primitive/logic.h"
#include "acid/primitive/mathematics/c_number.h"
#include "acid/primitive/mathematics/numeric_info.h"
#include "acid/primitive/primitive/e_check.h"
#include "acid/primitive/primitive/transfer.h"


#include  "acid/primitive/time/_.h"
#include  "acid/primitive/string/string.h"
#include  "acid/primitive/primitive/payload.h"
#include  "acid/primitive/primitive/object.h"
#include  "acid/exception/exception.h"
#include  "acid/platform/class.h"


#include "acid/primitive/string/scoped_string_base.h"

#include "_string.h"


#include "acid/filesystem/_impl.h"
#include "acid/primitive/string/_impl.h"
#include "_impl.h"
#include "acid/primitive/time/_impl.h"
#include "acid/primitive/mathematics/_impl.h"
#include "acid/primitive/primitive/_impl.h"
#include "acid/primitive/_impl.h"
#include "acid/memory/_impl.h"
