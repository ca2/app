#pragma once


class shape_array :
   virtual public __pointer_array(___shape)
{
public:

   
   using ::pointer_array < ___shape >::pointer_array;

   //void add_begin_clip();
   //void add_intersect_clip();
   //void add_begin_figure();
   //void add_close_figure();
   //void add_end_figure();

   template < typename GEOMETRY >
   void add_shape(const GEOMETRY & geometry)
   {

      add(__create_shape(geometry));

   }


};








