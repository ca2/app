#pragma once


#include "location.h"
#include "dimension.h"


class CLASS_DECL_ACME box
{
public:


   locationd     m_origin;
   locationd     m_direction;
   dimensiond    m_dimension;


   locationd center();

   void rotate(locationd point, locationd r);

   box & operator -= (const locationd& point)
   {

      m_origin -= point;

      return *this;

   }


   box & operator += (const locationd & point)
   {

      m_origin += point;

      return *this;


   }

   array < locationd > vertices();
   static array < int_array > faces();
   array < array < locationd > > faces_vertices();
   locationd get_nearest_vertice(locationd point);
   index find_nearest_vertice(locationd point);
   index find_nearest_vertice(::i32 x,::i32 y);



};

