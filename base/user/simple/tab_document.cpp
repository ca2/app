//
// Created by camilo on 2022-08-03
//
#include "framework.h"
#include "tab_document.h"
#include "base/user/user/impact.h"


simple_tab_document::simple_tab_document()
{

}


simple_tab_document::~simple_tab_document()
{

}


//void simple_tab_document::assert_ok() const
//{
//
//   ::user::document::assert_ok();
//
//}
//
//
//void simple_tab_document::dump(dump_context & dumpcontext) const
//{
//
//   ::user::document::dump(dumpcontext);
//
//}


bool simple_tab_document::on_new_document()
{

   return ::user::document::on_new_document();

}


bool simple_tab_document::on_open_document(const ::payload & payloadFile)
{

   return true;

}

#ifdef _DEBUG

i64 simple_tab_document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}

i64 simple_tab_document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}

#endif



