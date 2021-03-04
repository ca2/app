#include "framework.h"
#include "aura/user/_user.h"
#include "wait_cursor.h"


wait_cursor::wait_cursor(::layered * pobjectContext)
{

   auto estatus = initialize(pobjectContext);

   if (!estatus)
   {

      __throw(estatus);

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


