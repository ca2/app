// Created by camilo on 2024-04-17 01:10 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "operation.h"
#include "acme/exception/runtime_check.h"
#include "acme/operating_system/shared_posix/c_error_number.h"


#include <string.h>
#include <wchar.h>


CLASS_DECL_ACME void safe_memory_copy_bytes(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size)
{

#ifdef WINDOWS
   
   errno_t iErrNo = ::memcpy_s(ptarget, (rsize_t)sizeTargetMax, psource, (rsize_t)size);

   if (iErrNo)
   {

      throw ::runtime_check_exception(error_failed, { c_error_number(iErrNo) }, "safe_memory_copy");

   }

#else
   
   ::memory_copy(ptarget, psource, size);

#endif

}


CLASS_DECL_ACME void safe_wide_memory_transfer(::wide_character* ptarget, strsize sizeTargetMax, const ::wide_character* psource, strsize size)
{

#ifdef WINDOWS

   errno_t iErrNo = ::wmemcpy_s(ptarget, (rsize_t)sizeTargetMax, psource, (rsize_t)size);

   if (iErrNo)
   {

      throw ::runtime_check_exception(error_runtime_check, { c_error_number(iErrNo) }, "safe_wide_memory_transfer");

   }

#else

   ::memory_copy(ptarget, psource, size * sizeof(::wide_character));

#endif

}


CLASS_DECL_ACME void safe_memory_transfer_bytes(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size)
{

#ifdef WINDOWS

   errno_t iErrNo = ::memmove_s(ptarget, (rsize_t)sizeTargetMax, psource, (rsize_t)size);

   if (iErrNo)
   {

      throw ::runtime_check_exception(error_runtime_check, { c_error_number(iErrNo) }, "safe_memory_transfer");

   }

#else
   
   memory_transfer(ptarget, psource, size);

#endif

}



