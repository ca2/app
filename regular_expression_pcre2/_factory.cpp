#include "framework.h"
#include "context.h"


IMPLEMENT_FACTORY(regular_expression_pcre2)
{


   pfactory->add_factory_item < ::regular_expression_pcre2::context, ::regular_expression::context >();


}



