#include "framework.h"


extern "C"
void regular_expression_pcre2_factory_exchange(::factory_map * pfactorymap)
{


   pfactorymap->create_factory < ::regular_expression_pcre2::context, ::regular_expression::context >();


}



