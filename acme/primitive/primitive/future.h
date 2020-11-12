#pragma once


template < typename FUTURE >
class CLASS_DECL_ACME future :
   public ::matter_pointer
{
public:
   
   using ::matter_pointer::matter_pointer;


   inline void operator()(const FUTURE & payload) const;

   inline bool should_run_async() const;


};





//using future = ::matter_pointer;





