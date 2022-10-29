#include "framework.h"
#include "wait_cursor.h"
#include "acme/platform/system.h"
#include "aura/platform/node.h"


wait_cursor::wait_cursor(::particle * pparticle)
{

   //auto estatus =
   
   initialize(pparticle);

   //if (!estatus)
   //{

   //   throw ::exception(estatus);

   //}

   auto pnode = acmesystem()->m_pauranode;

   pnode->BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    auto pnode = acmesystem()->m_pauranode;

    pnode->EndWaitCursor();

}


void wait_cursor::restore()
{

   auto pnode = acmesystem()->m_pauranode;

	pnode->RestoreWaitCursor();

}


