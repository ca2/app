// From path.h by camilo on 2022-06-25 22:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "path_optimization.h"
#include "acme/primitive/geometry2d/_collection.h"


namespace geometry2d
{

   class item;

} // namespace geometry2d


namespace draw2d
{


   class path_simple_optimization :
      virtual public path_optimization
   {
   public:

      
      int                                 m_iTopic;
      int                                 m_iTopicLines;
      int                                 m_iClose;
      ::point_f64_array                   m_pointa;
      ::pointer < ::geometry2d::item >    m_pitemTopic;

      
      path_simple_optimization(::draw2d::path * ppath);

      bool draw(::draw2d::graphics * pgraphics, ::draw2d::pen * ppen);

      bool fill(::draw2d::graphics * pgraphics, ::draw2d::brush * pbrush);

      bool intersect_clip(::draw2d::graphics * pgraphics);

   };




} // namespace draw2d



