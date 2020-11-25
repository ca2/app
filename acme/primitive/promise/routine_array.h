#pragma once


//class ::promise::routine_array :
//   virtual public array < object_procedure >
//{
//public:
//
//
//   ::promise::routine_array(::matter * pobject) :
//      ::matter(pobject)
//   {
//
//   }
//
//
//   inline thread_ptra async_all()
//   {
//
//      thread_ptra threadptra;
//
//      auto & a = *this;
//
//      for(auto & proutine : a)
//      {
//
//         threadptra.add(fork([=]()
//         {
//
//            (get_object()->*proutine)();
//
//         }));
//
//      }
//
//      return threadptra;
//
//   }
//
//
//   inline void sync_all()
//   {
//
//      auto & a = *this;
//
//      for(auto & proutine : a)
//      {
//
//         try
//         {
//
//            if(!::thread_get_run())
//            {
//
//               break;
//
//            }
//
//         }
//         catch(...)
//         {
//
//         }
//
//         try
//         {
//
//            (get_object()->*proutine)();
//
//         }
//         catch(...)
//         {
//
//         }
//
//      }
//
//   }
//
//
//   inline ::status::result try_sync_catch_all()
//   {
//
//      ::status::result result;
//
//      auto & a = *this;
//
//      for(auto & proutine : a)
//      {
//
//         try
//         {
//
//            if(!::thread_get_run())
//            {
//
//               break;
//
//            }
//
//         }
//         catch(::exception_pointer e)
//         {
//
//            result.add(e);
//
//         }
//         catch(...)
//         {
//
//            result.add(::error_exception);
//
//         }
//
//         try
//         {
//
//            (get_object()->*proutine)();
//
//         }
//         catch(::exception_pointer e)
//         {
//
//            result.add(e);
//
//         }
//         catch(...)
//         {
//
//            result.add(::error_exception);
//
//         }
//
//      }
//
//      return result;
//
//   }
//
//
//};
//
//
//typedef __pointer(::promise::routine_array) procedure_array_pointer;
