#pragma once


class CLASS_DECL_ACME memory_exception :
   public ::exception::exception
{
public:


   memory_exception(const char * pszMessage = "");
   virtual ~memory_exception();


};


#if defined(SOLARIS)


namespace std
{


   class CLASS_DECL_ACME bad_alloc :
      virtual public memory_exception
   {
   public:


      bad_alloc() :
         element(get_object()),
         ::callstack(get_object()),
         ::exception::exception(),
         ::exception::exception(),
         memory_exception()
      {

      }

      virtual ~bad_alloc() {}


   };


}

#endif



