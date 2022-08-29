#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "operation_document.h"


namespace filemanager
{


   operation_document::operation_document()
   {

   }


   bool operation_document::on_new_document()
   {
      return true;
   }


} // namespace filemanager



























