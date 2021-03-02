#pragma once


namespace message
{


   class CLASS_DECL_APEX handler :
           public ::function_pointer
   {
   public:


      using ::function_pointer::function_pointer;


      inline void operator()(::message::message * pmessage) const;

      inline bool should_run_async() const;


   };


   using handler_array = ::array < handler >;

   
   template<typename PRED>
   void add_handler(handler_array& array, PRED pred);


} // namespace message



