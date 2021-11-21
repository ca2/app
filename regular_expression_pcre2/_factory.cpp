#include "framework.h"


__FACTORY_EXPORT void regular_expression_pcre2_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::regular_expression_pcre2::context, ::regular_expression::context >();


}



