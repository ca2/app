#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


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


bool simple_pane_document::on_open_document(const payload & varFile)
{

   return true;

}

#ifdef DEBUG

i64 simple_pane_document::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return  ::user::document::add_ref(OBJ_REF_DBG_ARGS);

}

i64 simple_pane_document::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return  ::user::document::dec_ref(OBJ_REF_DBG_ARGS);

}

#endif

