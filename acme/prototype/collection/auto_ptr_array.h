#pragma once


#include "acme/platform/_referencing_debugging.h"


template < typename POINTER_TYPE >
class auto_ptr_array :
   public pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >
{
public:

   
   using BASE_ARRAY = pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >;

   using pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >::pointer_array_process;


   auto_ptr_array() { }
   auto_ptr_array(auto_ptr_array && array) : pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >(::transfer(array)) { }
   ~auto_ptr_array() override { this->erase_all(); }


   POINTER_TYPE & object_at(::collection::index i) { return *this->element_at(i); }
   const POINTER_TYPE & object_at(::collection::index i) const { return *this->element_at(i); }

   
   void set_size(::collection::count c)
   {
      
      auto i = this->size();
      
      BASE_ARRAY::set_size(c);
      
      for(; i < c; i++)
      {
         
         this->element_at(i) = ___new POINTER_TYPE;
         
      }
      
   }
   
   
   ::collection::index erase_at(::collection::index i)
   {

      ::acme::del(this->element_at(i));

      return BASE_ARRAY::erase_at(i);

   }
   

   ::collection::count erase_all()
   {

      for(auto & p : *this)
      {

         ::acme::del(p);

      }

      return BASE_ARRAY::erase_all();

   }


};


namespace acme
{


   template < class TDST, class TSRC >
   ::collection::count copy(auto_ptr_array < TDST >& dsta, const auto_ptr_array < TSRC >& srca)
   {

      dsta.erase_all();

      dsta.set_size(srca.get_size());

      for (int i = 0; i < srca.get_size(); i++)
      {
         
         dsta[i] = ___new TDST(*srca[i]);

      }

      return dsta.get_size();

   }


} // namespace acme



