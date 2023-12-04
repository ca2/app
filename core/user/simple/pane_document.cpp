#include "framework.h"
#include "pane_document.h"
#include "base/user/user/impact.h"


simple_pane_document::simple_pane_document()
{

}


simple_pane_document::~simple_pane_document()
{

}





//void simple_pane_document::assert_ok() const
//{
//
//   ::user::document::assert_ok();
//
//}
//
//
//void simple_pane_document::dump(dump_context & dumpcontext) const
//{
//
//   ::user::document::dump(dumpcontext);
//
//}


bool simple_pane_document::on_new_document()
{

   return ::user::document::on_new_document();

}


bool simple_pane_document::on_open_document(const ::payload & payloadFile)
{

   return true;

}

#ifdef _DEBUG

i64 simple_pane_document::increment_reference_count()
{

   return  ::user::document::increment_reference_count();

}

i64 simple_pane_document::decrement_reference_count()
{

   return  ::user::document::decrement_reference_count();

}

#endif

