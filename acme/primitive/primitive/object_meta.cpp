#include "framework.h"


//object_meta::~object_meta()
//{
//
//}


//void object_meta::destroy(::object * pReferer)
//{
//
//   for (auto& ptask : m_taska)
//   {
//
//      ptask->erase_notify(pReferer);
//
//   }
//
//}


//::index object_meta::task_add(::object* pReferer, ::task* ptask)
//{
//
//   ::index i = m_taska.add_item(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pReferer));
//
//   ptask->add_notify(pReferer);
//
//   return i;
//
//}
//
//
//void object_meta::task_erase(::object* pReferer, ::task* ptask)
//{
//
//   m_taska.erase_item(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(pReferer, ""));
//
//   ptask->erase_notify(pReferer);
//
//}
//
//
//
//void object_meta::task_erase_all(::object* pReferer)
//{
//
//   for (auto& ptask : m_taska)
//   {
//
//      ptask->erase_notify(pReferer);
//
//   }
//
//   m_taska.erase_all(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pReferer, ""));
//
//}
