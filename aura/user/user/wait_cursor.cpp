#include "framework.h"

#include "wait_cursor.h"
#include "aura/platform/node.h"


wait_cursor::wait_cursor(::object * pobject)
{

   //auto estatus =
   
   initialize(pobject);

   //if (!estatus)
   //{

   //   throw ::exception(estatus);

   //}

   auto pnode = m_psystem->m_pauranode;

   pnode->BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    auto pnode = m_psystem->m_pauranode;

    pnode->EndWaitCursor();

}


void wait_cursor::restore()
{

   auto pnode = m_psystem->m_pauranode;

	pnode->RestoreWaitCursor();

}


