#pragma once


#ifdef CUBE


class draw2d_impl
{
public:


   draw2d_impl()
   {

      initialize_draw2d_factory(::factory::factory * pfactory);

      initialize_imaging_factory(::factory::factory * pfactory);

   }

};


draw2d_impl g_draw2dimpl;


#endif



