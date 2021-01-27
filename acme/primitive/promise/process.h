#pragma once


namespace promise
{


   class CLASS_DECL_ACME process :
           public ::matter_pointer
   {
   public:


      using ::matter_pointer::matter_pointer;

      inline void operator()(const ::payload & payload) const;

      inline bool should_run_async() const;


   };


} // namespace promise



