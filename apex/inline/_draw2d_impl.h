#pragma once


#ifdef CUBE


class draw2d_impl
{
public:


   draw2d_impl()
   {

      initialize_draw2d_factory_exchange(::factory_map * pfactorymap);

      initialize_imaging_factory_exchange(::factory_map * pfactorymap);

   }

};


draw2d_impl g_draw2dimpl;


#endif



