// From path.h by camilo on 2022-09-06 18:54 <3ThomasBorregaardSorensen!!
#pragma once


namespace draw2d
{


    class path_optimization :
        virtual public ::particle
    {
    public:

        
       virtual bool draw(::draw2d::graphics * pgraphics, ::draw2d::pen * ppen);


       virtual bool fill(::draw2d::graphics * pgraphics, ::draw2d::brush * pbrush);
       
       
       virtual bool intersect_clip(::draw2d::graphics * pgraphics);


    };


} // namespace draw2d



