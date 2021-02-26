#pragma once


namespace promise
{


   class CLASS_DECL_ACME handler :
           public ::function_pointer
   {
   public:


      using ::function_pointer::function_pointer;


      inline void operator()(::message::message * pmessage) const;

      inline bool should_run_async() const;


   };



} // namespace promise



