#pragma once


//#include "exception.h"


class CLASS_DECL_ACME no_memory :
   public ::exception
{
public:


   no_memory(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr);
   ~no_memory() override;


};


#if defined(SOLARIS)


namespace std
{


   class CLASS_DECL_ACME bad_alloc :
      virtual public memory_exception
   {
   public:


      bad_alloc() :
         matter(this),
         ::callstack(this),
         ::exception(),
         ::exception(),
         memory_exception()
      {

      }

      virtual ~bad_alloc() {}


   };


}

#endif



