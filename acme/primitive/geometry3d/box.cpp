#include "framework.h"
#include "_.h"
#include "acme/primitive/collection/array.h"
#include "acme/primitive/collection/numeric_array.h"


locationd box::center()
{


   locationd point;


   point = m_origin + locationd(m_dimension.cx / 2.0,m_dimension.cy / 2.0,m_dimension.cz / 2.0).rotate(m_direction);

   //point.x = m_dimension.cx *cos(m_direction.z) / 2.0 - m_dimension.cy * sin(m_direction.z) / 2.0;
   //point.y = m_dimension.cx *sin(m_direction.z) / 2.0 + m_dimension.cy * cos(m_direction.z) / 2.0;
   //point.y = m_dimension.cy *cos(m_direction.x) / 2.0 - m_dimension.cz * sin(m_direction.x) / 2.0;
   //point.z = m_dimension.cy *sin(m_direction.x) / 2.0 + m_dimension.cz * cos(m_direction.x) / 2.0;
   //point.z = m_dimension.cz *cos(m_direction.y) / 2.0 - m_dimension.cx * sin(m_direction.y) / 2.0;
   //point.x = m_dimension.cz *sin(m_direction.y) / 2.0 + m_dimension.cx * cos(m_direction.y) / 2.0;

   //point += m_origin;

   return point;


}

void box::rotate(locationd point,locationd pointRotation)
{

   operator -=(point);


   //locationd OriginDirection(0, acos(m_origin.z / (sqrt(m_origin.x * m_origin.x + m_origin.y * m_origin.y + m_origin.z * m_origin.z))), atan2(m_origin.y,m_origin.x));

   m_direction += pointRotation;
   m_origin = m_origin.rotate(pointRotation);

   operator +=(point);


}





array < int_array > box::faces()
{

   array < int_array > a2;

   // front
   {

      int_array a;

      a.add(0);
      a.add(1);
      a.add(3);

      a2.add(a);

   }

   // right
   {

      int_array a;

      a.add(1);
      a.add(5);
      a.add(2);

      a2.add(a);

   }

   // back
   {

      int_array a;

      a.add(5);
      a.add(4);
      a.add(6);

      a2.add(a);

   }

   // left
   {

      int_array a;

      a.add(4);
      a.add(0);
      a.add(7);

      a2.add(a);

   }

   // down
   {

      int_array a;

      a.add(2);
      a.add(3);
      a.add(6);

      a2.add(a);

   }

   // up
   {

      int_array a;

      a.add(4);
      a.add(5);
      a.add(0);

      a2.add(a);

   }


   return a2;
}



array < array < locationd > > box::faces_vertices()
{

   array < locationd > v = vertices();
   array < int_array > f = faces();

   array < array < locationd > > fv;
   array < locationd > vertices;

   for(index i = 0; i < f.get_count(); i++)
   {
      int_array & ia = f[i];
      vertices.erase_all();
      for(index j = 0; j < ia.get_count(); j++)
      {
         vertices.add(v[ia[j]]);
      }
      fv.add(vertices);
   }
   return fv;


}

array < locationd > box::vertices()
{

   array < locationd >  point;

   point.set_size(8);


   point[0] = m_origin;
   point[1] = point[0] + locationd(m_dimension.cx,0,0).rotate(m_direction);
   point[2] = point[0] + locationd(m_dimension.cx,m_dimension.cy,0).rotate(m_direction);
   point[3] = point[0] + locationd(0,m_dimension.cy,0).rotate(m_direction);

   point[4] = m_origin + locationd(0,0,m_dimension.cz).rotate(m_direction);
   point[5] = point[4] + locationd(m_dimension.cx,0,0).rotate(m_direction);
   point[6] = point[4] + locationd(m_dimension.cx,m_dimension.cy,0).rotate(m_direction);
   point[7] = point[4] + locationd(0,m_dimension.cy,0).rotate(m_direction);

   return point;
}



inline double sqr(double x)
{
   return x*x;
}

locationd box::get_nearest_vertice(locationd point)
{

   array < locationd >  verts = vertices();

   double dMin = sqrt(::sqr(point.x - verts[0].x) + sqr(point.y - verts[0].y) + sqr(point.z - verts[0].z));

   double d;

   index iFound = 0;

   for (index i = 1; i < verts.get_count(); i++)
   {
      d = sqrt(::sqr(point.x - verts[i].x) + sqr(point.y - verts[i].y) + sqr(point.z - verts[i].z));

      if (d < dMin)
      {
         dMin = d;
         iFound = i;
      }
   }


   return verts[iFound];

}

index box::find_nearest_vertice(locationd point)
{

   array < locationd >  verts = vertices();

   double dMin = sqrt(::sqr(point.x - verts[0].x) + sqr(point.y - verts[0].y) + sqr(point.z - verts[0].z));

   double d;

   index iFound = 0;

   for (index i = 1; i < verts.get_count(); i++)
   {
      d = sqrt(::sqr(point.x - verts[i].x) + sqr(point.y - verts[i].y) + sqr(point.z - verts[i].z));

      if (d < dMin)
      {
         dMin = d;
         iFound = i;
      }
   }


   return iFound;

}


index box::find_nearest_vertice(::i32 x, ::i32 y)
{

   array < locationd >  verts = vertices();

   double dMin = sqrt(::sqr(x - verts[0].x) + sqr(y - verts[0].y));

   double d;

   index iFound = 0;

   for (index i = 1; i < verts.get_count(); i++)
   {
      d = sqrt(::sqr(x - verts[i].x) + sqr(y - verts[i].y));

      if (d < dMin)
      {
         dMin = d;
         iFound = i;
      }
   }


   return iFound;

}


