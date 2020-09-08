#pragma once


namespace exception
{


   class CLASS_DECL_ACME error :
      public ::exception::exception
   {
   public:


      error(const char * pszMessage = nullptr, const ::estatus & estatus = error_exception);
      virtual ~error();


   };


} // namespace exception


class CLASS_DECL_ACME index_out_of_bounds :
   public ::exception::error
{
public:


   index_out_of_bounds(const char * pszMessage = nullptr);
   virtual ~index_out_of_bounds();


};



