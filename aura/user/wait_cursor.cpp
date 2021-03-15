#include "framework.h"
#include "aura/user/_user.h"
#include "wait_cursor.h"


wait_cursor::wait_cursor(::context_object * pcontextobject)
{

   auto estatus = initialize(pcontextobject);

   if (!estatus)
   {

      __throw(estatus);

   }

   __pointer(::aura::application) papplication = get_application();

	papplication->BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    __pointer(::aura::application) papplication = get_application();

    papplication->EndWaitCursor();

}


void wait_cursor::restore()
{

   __pointer(::aura::application) papplication = get_application();

	papplication->RestoreWaitCursor();

}


