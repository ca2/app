#include "framework.h"

//
//sync_task::sync_task(::matter* pobjectRunnable) :
//      m_pobjectRunnable(pobjectRunnable)
//{
//
//   m_event.ResetEvent();
//
//}
//
//sync_task::~sync_task()
//{
//
//
//}
//
//
//void sync_task::call()
//{
//
//   ::e_status3 estatus;
//
//   try
//   {
//
//      estatus = m_pobjectRunnable->call();
//
//   }
//   catch (const ::exception& e)
//   {
//
//      estatus = e.m_estatus;
//
//   }
//   catch (...)
//   {
//
//      estatus = ::error_exception;
//
//   }
//
//   m_event.SetEvent();
//
//   return estatus;
//
//}
//
//
