#include "framework.h"
#include "ortho.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/geometry3d/box.h"
#include "acme/prototype/geometry3d/location.h"
//#include "acme/prototype/time/integral/operator.h"
//#include "acme/prototype/collection/numeric_array.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/image.h"


#include <math.h>


namespace draw3d
{


   ::int_array_base ortho::draw_ortho_plain_wire_frame(::box_double * pbox,int iHint,int bA,bool bFirst)
   {

      double dA = bA / 255.0;

      auto locationa = pbox->vertexes();

      m_pdc->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = øcreate < ::draw2d::pen > ();

      double zmin = locationa[0].z();
      double zmax = locationa[0].z();

      ::collection::index i;

      for(i = 1; i < locationa.get_count(); i++)
      {

          if (locationa[i].z() < zmin)
          {

              zmin = locationa[i].z();

          }
          else if (locationa[i].z() > zmax)
          {

              zmax = locationa[i].z();

          }

      }

      for(i = 0; i < locationa.get_count(); i++)
      {

          locationa[i].z() -= zmin;

      }

      zmax -=zmin;

      double d;

      if (zmax <= 0.0)
      {

          d = 0.0;

      }
      else
      {

          d = 0.5 / zmax;

      }


      ::int_array_base  point1;
      ::int_array_base  point2;



      point1.add(0);
      point2.add(1);

      point1.add(1);
      point2.add(2);

      point1.add(2);
      point2.add(3);

      point1.add(3);
      point2.add(0);



      point1.add(4);
      point2.add(5);

      point1.add(5);
      point2.add(6);

      point1.add(6);
      point2.add(7);

      point1.add(7);
      point2.add(4);



      point1.add(0);
      point2.add(4);

      point1.add(1);
      point2.add(5);

      point1.add(2);
      point2.add(6);

      point1.add(3);
      point2.add(7);

      ::collection::index iMax;

      i = 0;

      ::int_array_base ia;

      while(point1.get_count() > 0)
      {

         iMax = 0;

         for(::collection::index j = 0; j < point1.get_count(); j++)
         {

            if((locationa[point1[j]].z() + locationa[point2[j]].z()) >(locationa[point1[iMax]].z() + locationa[point2[iMax]].z()))
            {
               
               iMax = j;

            }

         }

         if((bFirst && i < 6) || (!bFirst && i >= 6))
         {

            ia.add_unique(point1[iMax]);

            ia.add_unique(point2[iMax]);

            double r = (locationa[point1[iMax]].z() + locationa[point2[iMax]].z()) * d;

            ::color::color colorA;

            auto period = 55000 / 2; // milliseconds

            if(iHint == 0)
            {

               colorA.set_hls((double) (::long_long_millisecond() % period) / (double)period, 0.9 - r / 2.0, 1.0 - r);

            }
            else
            {

               colorA.set_hls((double) (::long_long_millisecond() % period) / (double)period, 0.9 - r / 2.0, 1.0 - r);

            }

            ppen->create_solid((1.05 - r) * 10.0,argb((int)(dA * (255.0 - r * 200.0)),colorA.byte_red(), colorA.byte_green(), colorA.byte_blue()));
            if(i < 6)
            {
               ppen->m_epen = ::draw2d::e_pen_dot;
            }
            else
            {
               ppen->m_epen = ::draw2d::e_pen_solid;
            }

            m_pdc->set(ppen);

            m_pdc->line(::double_point(locationa[point1[iMax]].cxy()), ::double_point(locationa[point2[iMax]].cxy()));

         }

         point1.erase_at(iMax);
         point2.erase_at(iMax);

         i++;
      }


      //ppen->create_solid(1.0,argb(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->set(ppen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x(),(float)p02.y(),(float)p03.x(),(float)p03.y());
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x(),(float)p03.y(),(float)p04.x(),(float)p04.y());
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x(),(float)p04.y(),(float)p01.x(),(float)p01.y());

      //m_pdc->move_to(p05.x(),p05.y());
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->line_to(p06.x(),p06.y());
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->line_to(p07.x(),p07.y());
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->line_to(p08.x(),p08.y());
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->line_to(p05.x(),p05.y());

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x(),(float)p01.y(),(float)p05.x(),(float)p05.y());
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x(),(float)p02.y(),(float)p06.x(),(float)p06.y());
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x(),(float)p03.y(),(float)p07.x(),(float)p07.y());
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x(),(float)p04.y(),(float)p08.x(),(float)p08.y());

      return ia;
   }


   ::int_array_base ortho::draw_ortho_plain_fill(::box_double * pbox,int iHint,int bA,bool bFirst,::image::image *pimage)
   {

      ::draw2d::bitmap bm;

      ::int_point point2da[3];

      ::int_array_base ia;

      double dA = bA / 255.0;

      auto locationa = pbox->vertexes();
      array < ::int_array_base > f = pbox->faces();

      m_pdc->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      auto ppen = øcreate < ::draw2d::pen > ();

      double zmin = 1000000.0;
      double zmax = -1000000.0;

      ::collection::index i;
      ::collection::index j;

      for(i = 0; i < f.get_count(); i++)
      {
         for(j = 0; j < f[i].get_count(); j++)
         {
            if(locationa[f[i][j]].z() < zmin)
               zmin = locationa[f[i][j]].z();
            else if(locationa[f[i][j]].z() > zmax)
               zmax = locationa[f[i][j]].z();
         }
      }

      for(i = 0; i < locationa.get_count(); i++)
      {
         //for(j = 0; j < f[i].get_count(); j++)
         {

            locationa[i].z() -= zmin;

         }

      }

      zmax -=zmin;

      double d;

      if(zmax <= 0.0)
         d = 0.0;
      else
         d = 1.0 / (zmax * 3.0);


      ::collection::index iMax;

      i = 0;

      ::int_array_base iaf;

      //throw ::exception(todo);

      //::acme::array::set_sequence(iaf,0,5);

      while(f.get_count() > 0)
      {

         iMax = 0;

         for(j = 0; j < f.get_count(); j++)
         {

            if((locationa[f[j][0]].z() + locationa[f[j][1]].z() + locationa[f[j][2]].z()) >(locationa[f[iMax][0]].z() + locationa[f[iMax][1]].z() + locationa[f[iMax][2]].z()))
            {
               iMax = j;
            }

         }

         if((bFirst && i < 3) || (!bFirst && i >= 3))
         {

            int iFace = iaf[iMax];

            ia.add_unique(iFace);

            double r = (locationa[f[iMax][0]].z() + locationa[f[iMax][1]].z() + locationa[f[iMax][2]].z()) * d;

            ::color::color colorA;

            auto period = 50_s;
            
            throw ::exception(error_what_exclamation_exclamation);

////            if(iHint == 0)
////            {
////
////               colorA.set_hls(::time::now() + period / 2, 0.84 - r / 2.0, 1.0 - r);
////
////            }
////            else
////            {
////
////               colorA.set_hls(::time::now() + period / 2, 0.84 - r / 2.0, 1.0 - r);
////
////            }
//
//            //::color::color clr = colorA.get_rgb();
//
//
//            /*ppen->create_solid((1.05 - r) * 10.0,argb((int)(dA * (255.0 - r * 200.0)),colorA.m_iR,colorA.m_iG,colorA.m_iB));
//            if(i < 6)
//            {
//            ppen->m_etype = ::draw2d::e_pen_dot;
//            }
//            else
//            {
//            ppen->m_etype = ::draw2d::e_pen_solid;
//            }
//            m_pdc->set(ppen);*/
//
//            pimage->fill((int)(dA * (184.0 - r * 128.0)),colorA.red,colorA.green,colorA.blue);
//
//            point2da[0]=::int_point((int)locationa[f[iMax][0]].x(),(int)locationa[f[iMax][0]].y());
//            point2da[1]= ::int_point((int)locationa[f[iMax][1]].x(),(int)locationa[f[iMax][1]].y());
//            point2da[2]= ::int_point((int)locationa[f[iMax][2]].x(),(int)locationa[f[iMax][2]].y());
//
//            throw ::exception(todo, "plgblt");
//            //m_pdc->PlgBlt(point2da, pimage->g(),0,0,pimage->width(),pimage->width(),bm,0,0);

         }

         f.erase_at(iMax);
         iaf.erase_at(iMax);

         i++;

      }


      //ppen->create_solid(1.0,argb(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->set(ppen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x(),(float)p02.y(),(float)p03.x(),(float)p03.y());
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x(),(float)p03.y(),(float)p04.x(),(float)p04.y());
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x(),(float)p04.y(),(float)p01.x(),(float)p01.y());

      //m_pdc->move_to(p05.x(),p05.y());
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->line_to(p06.x(),p06.y());
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->line_to(p07.x(),p07.y());
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->line_to(p08.x(),p08.y());
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->line_to(p05.x(),p05.y());

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x(),(float)p01.y(),(float)p05.x(),(float)p05.y());
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x(),(float)p02.y(),(float)p06.x(),(float)p06.y());
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x(),(float)p03.y(),(float)p07.x(),(float)p07.y());
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x(),(float)p04.y(),(float)p08.x(),(float)p08.y());

      return ia;
   }


} // namespace draw3d





