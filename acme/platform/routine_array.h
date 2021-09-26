#pragma once


//class ::routine_array :
//   virtual public array < object_procedure >
//{
//public:
//
//
//   ::routine_array(::matter * pobject) :
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
//            (this->*proutine)();
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
//            if(!::task_get_run())
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
//            (this->*proutine)();
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
//   inline ::extended::status try_sync_catch_all()
//   {
//
//      ::extended::status result;
//
//      auto & a = *this;
//
//      for(auto & proutine : a)
//      {
//
//         try
//         {
//
//            if(!::task_get_run())
//            {
//
//               break;
//
//            }
//
//         }
//         catch(const ::exception & e)
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
//            (this->*proutine)();
//
//         }
//         catch(const ::exception & e)
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
//typedef __pointer(::routine_array) procedure_array_pointer;
