#pragma once


//class procedure_array :
//   virtual public array < object_procedure >
//{
//public:
//
//
//   procedure_array(::layered * pobjectContext) :
//      ::object(pobject)
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
//      for(auto & pprocedure : a)
//      {
//
//         threadptra.add(fork([=]()
//         {
//
//            (get_object()->*pprocedure)();
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
//      for(auto & pprocedure : a)
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
//            (get_object()->*pprocedure)();
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
//      for(auto & pprocedure : a)
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
//            (get_object()->*pprocedure)();
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
//typedef __pointer(procedure_array) procedure_array_pointer;
