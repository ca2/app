// From path.h by camilo on 2022-06-25 22:31 <3ThomasBorregaardS�rensen!!
#pragma once


namespace draw2d
{


   class path_simple_optimization :
      virtual public path::optimization
   {
   public:

      int m_iTopic = 0;
      int m_iTopicLines = 0;
      int m_iClose = 0;
      ::point_f64_array m_pointa;
      __pointer(___shape< path>) m_pshapeTopic;

      path_simple_optimization(::draw2d::path * ppath);

      bool draw(::draw2d::graphics * pgraphics, ::draw2d::pen * ppen);

      bool fill(::draw2d::graphics * pgraphics, ::draw2d::brush * pbrush);


   };




} // namespace draw2d


