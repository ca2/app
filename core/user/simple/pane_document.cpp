#include "framework.h"
#include "core/user/simple/_simple.h"


simple_pane_document::simple_pane_document()
{

}


simple_pane_document::~simple_pane_document()
{

}





void simple_pane_document::assert_valid() const
{

   ::user::document::assert_valid();

}


void simple_pane_document::dump(dump_context & dumpcontext) const
{

   ::user::document::dump(dumpcontext);

}


bool simple_pane_document::on_new_document()
{

   return ::user::document::on_new_document();

}


bool simple_pane_document::on_open_document(const ::payload & payloadFile)
{

   return true;

}

#ifdef _DEBUG

i64 simple_pane_document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}

i64 simple_pane_document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}

#endif

