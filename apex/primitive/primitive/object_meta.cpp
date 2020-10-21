#include "framework.h"


object_meta::~object_meta()
{

}


void object_meta::finalize(::object * pReferer)
{

   for (auto& pthread : m_threada)
   {

      pthread->remove_notify(pReferer);

   }

}


::index object_meta::thread_add(::object* pReferer, ::thread* pthread)
{

   ::index i = m_threada.add_item(pthread OBJ_REF_DBG_ADD_P_FUNCTION_LINE(pReferer));

   pthread->add_notify(pReferer);

   return i;

}


void object_meta::thread_remove(::object* pReferer, ::thread* pthread)
{

   m_threada.remove_item(pthread OBJ_REF_DBG_ADD_P_NOTE(pReferer, ""));

   pthread->remove_notify(pReferer);

}



void object_meta::thread_remove_all(::object* pReferer)
{

   for (auto& pthread : m_threada)
   {

      pthread->remove_notify(pReferer);

   }

   m_threada.remove_all(OBJ_REF_DBG_P_NOTE(pReferer, ""));

}