#pragma once




class CLASS_DECL_APEX box
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
   index find_nearest_vertice(LONG x,LONG y);



};

