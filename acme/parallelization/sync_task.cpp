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
//::estatus sync_task::call()
//{
//
//   ::estatus estatus;
//
//   try
//   {
//
//      estatus = m_pobjectRunnable->call();
//
//   }
//   catch (const ::exception::exception& e)
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
