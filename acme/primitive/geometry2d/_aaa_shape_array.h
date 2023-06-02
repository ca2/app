#pragma once


template < typename HOLDEE >
class shape_array :
    virtual public ::pointer_array < ___shape<HOLDEE> >
 {
public:

   
   using ::pointer_array < ___shape<HOLDEE> >::pointer_array;


   template < typename GEOMETRY >
   void add_shape(const GEOMETRY & geometry);


};



