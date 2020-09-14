#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "wait_cursor.h"


wait_cursor::wait_cursor(::layered * pobjectContext)
{

   auto estatus = initialize(pobjectContext);

   if (!estatus)
   {

      throw ::exception::exception(estatus);

   }

	Application.BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    Application.EndWaitCursor();

}


void wait_cursor::Restore()
{

	Application.RestoreWaitCursor();

}


