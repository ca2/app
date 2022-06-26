#pragma once

template < typename HOLDEE >
class shape_array :
    virtual public __pointer_array(___shape<HOLDEE>)
 {
public:

   
   using ::pointer_array < ___shape<HOLDEE> >::pointer_array;

   //void add_begin_clip();
   //void add_intersect_clip();
   //void add_begin_figure();
   //void add_close_figure();
   //void add_end_figure();

   template < typename GEOMETRY >
   void add_shape(const GEOMETRY & geometry);

};








