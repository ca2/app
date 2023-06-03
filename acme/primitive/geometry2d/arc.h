#pragma once


#include "angle.h"
#include "point.h"
#include "size.h"
#include "ellipse.h"
//#include "contains.h"


template < primitive_number NUMBER >
class arc_type :
   public ellipse_type < NUMBER >
{
public:

   using UNIT_TYPE = NUMBER;

   //::point_type < UNIT_TYPE >       m_pointCenter;
   //::size_type < UNIT_TYPE>         m_sizeRadius;
   ::point_type < UNIT_TYPE >       m_pointBegin;
   ::point_type < UNIT_TYPE >       m_pointEnd;
   ::angle_f64                      m_angleBeg;
   ::angle_f64                      m_angleExt;
   ::angle_f64                      m_angleEnd2;
   ::angle_f64                      m_angleRotation;


   void offset(const ::size_type < UNIT_TYPE > & offset)
   {

      ellipse_type < NUMBER >::offset(offset);
      //m_pointCenter += offset;
      m_pointBegin += offset;
      m_pointEnd += offset;

   }

   bool contains(const ::point_type < UNIT_TYPE > & point)
   {

      if(!::rectangle_type < NUMBER >::contains(point))
      {
         
         return false;
         
      }
      
      auto center = this->center();

      auto radius = this->radius();

      if (!::ellipse_type < NUMBER >::contains(center, radius, point))
      {

         return false;

      }

      //auto angle = ::ellipse_angle(m_pointCenter, m_sizeRadius, point);

      auto angle = ::angle(center, point);

      if (angle < m_angleBeg || angle > m_angleEnd2)
      {

         return false;

      }

      return true;

   }


};



