// From path.h by camilo on 2022-09-06 18:54 <3ThomasBorregaardSorensen!!
#pragma once


namespace draw2d
{


    class path_optimization :
        virtual public ::element
    {
    public:

        
        virtual bool draw(::draw2d::graphics * pgraphics, ::draw2d::pen * ppen)
        {

            return false;

        }


        virtual bool fill(::draw2d::graphics * pgraphics, ::draw2d::brush * pbrush)
        {

            return false;

        }


    };


} // namespace draw2d



