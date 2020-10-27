#include "framework.h"


object_meta::~object_meta()
{

}


//void object_meta::finalize(::object * pReferer)
//{
//
//   for (auto& ptask : m_taska)
//   {
//
//      ptask->remove_notify(pReferer);
//
//   }
//
//}


//::index object_meta::task_add(::object* pReferer, ::task* ptask)
//{
//
//   ::index i = m_taska.add_item(ptask OBJ_REF_DBG_COMMA_P_FUNCTION_LINE(pReferer));
//
//   ptask->add_notify(pReferer);
//
//   return i;
//
//}
//
//
//void object_meta::task_remove(::object* pReferer, ::task* ptask)
//{
//
//   m_taska.remove_item(ptask OBJ_REF_DBG_COMMA_P_NOTE(pReferer, ""));
//
//   ptask->remove_notify(pReferer);
//
//}
//
//
//
//void object_meta::task_remove_all(::object* pReferer)
//{
//
//   for (auto& ptask : m_taska)
//   {
//
//      ptask->remove_notify(pReferer);
//
//   }
//
//   m_taska.remove_all(OBJ_REF_DBG_P_NOTE(pReferer, ""));
//
//}