#include "framework.h"
#include "ortho.h"
#include <math.h>


namespace draw3d
{


   int_array ortho::draw_ortho_plain_wire_frame(::box * pbox,int iHint,int bA,bool bFirst)
   {

      double dA = bA / 255.0;

      array < locationd >  point = pbox->vertices();

      m_pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_pointer pen(e_create);

      double zmin = point_i32[0].z;
      double zmax = point_i32[0].z;

      index i;

      for(i = 1; i < point.get_count(); i++)
      {
         if(point_i32[i].z < zmin)
            zmin = point_i32[i].z;
         else if(point_i32[i].z > zmax)
            zmax = point_i32[i].z;
      }

      for(i = 0; i < point.get_count(); i++)
      {

         point_i32[i].z -= zmin;

      }

      zmax -=zmin;

      double d;

      if(zmax <= 0.0)
         d = 0.0;
      else
         d = 0.5 / zmax;


      int_array  point1;
      int_array  point2;



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

      index iMax;

      i = 0;
      int_array ia;

      while(point1.get_count() > 0)
      {

         iMax = 0;

         for(index j = 0; j < point1.get_count(); j++)
         {

            if((point_i32[point1[j]].z + point_i32[point2[j]].z) >(point_i32[point1[iMax]].z + point_i32[point2[iMax]].z))
            {
               iMax = j;
            }

         }

         if((bFirst && i < 6) || (!bFirst && i >= 6))
         {

            ia.add_unique(point1[iMax]);
            ia.add_unique(point2[iMax]);

            double r = (point_i32[point1[iMax]].z + point_i32[point2[iMax]].z) * d;

            ::color ca;

            double dPeriod = (5000) * 11;

            if(iHint == 0)
            {

               ca.set_hls(fmod(__double(::get_millis()),dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }
            else
            {
               ca.set_hls(fmod(__double(::get_millis()) + dPeriod / 2,dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }

            color32_t clr = ca.get_rgb();


            pen->create_solid((1.05 - r) * 10.0,ARGB((int)(dA * (255.0 - r * 200.0)),ca.red,ca.green,ca.blue));
            if(i < 6)
            {
               pen->m_epen = ::draw2d::e_pen_dot;
            }
            else
            {
               pen->m_epen = ::draw2d::e_pen_solid;
            }

            m_pdc->set(pen);

            m_pdc->draw_line(__pointd(point_i32[point1[iMax]]), __pointd(point_i32[point2[iMax]]));

         }

         point1.remove_at(iMax);
         point2.remove_at(iMax);

         i++;
      }


      //pen->create_solid(1.0,ARGB(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->set(pen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p03.x,(float)p03.y);
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p04.x,(float)p04.y);
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p01.x,(float)p01.y);

      //m_pdc->move_to(p05.x,p05.y);
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->line_to(p06.x,p06.y);
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->line_to(p07.x,p07.y);
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->line_to(p08.x,p08.y);
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->line_to(p05.x,p05.y);

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x,(float)p01.y,(float)p05.x,(float)p05.y);
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p06.x,(float)p06.y);
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p07.x,(float)p07.y);
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p08.x,(float)p08.y);

      return ia;
   }


   int_array ortho::draw_ortho_plain_fill(::box * pbox,int iHint,int bA,bool bFirst,::image * pimage)
   {

      ::draw2d::bitmap bm;

      ::point_i32 point2da[3];

      int_array ia;

      double dA = bA / 255.0;

      array < locationd > locationa = pbox->vertices();
      array < int_array > f = pbox->faces();

      m_pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::draw2d::pen_pointer pen(e_create);

      double zmin = 1000000.0;
      double zmax = -1000000.0;

      index i;
      index j;

      for(i = 0; i < f.get_count(); i++)
      {
         for(j = 0; j < f[i].get_count(); j++)
         {
            if(locationa[f[i][j]].z < zmin)
               zmin = locationa[f[i][j]].z;
            else if(locationa[f[i][j]].z > zmax)
               zmax = locationa[f[i][j]].z;
         }
      }

      for(i = 0; i < locationa.get_count(); i++)
      {
         //for(j = 0; j < f[i].get_count(); j++)
         {

            locationa[i].z -= zmin;

         }

      }

      zmax -=zmin;

      double d;

      if(zmax <= 0.0)
         d = 0.0;
      else
         d = 1.0 / (zmax * 3.0);


      index iMax;

      i = 0;

      int_array iaf;

      ::papaya::array::set_sequence(iaf,0,5);


      while(f.get_count() > 0)
      {

         iMax = 0;

         for(j = 0; j < f.get_count(); j++)
         {

            if((locationa[f[j][0]].z + locationa[f[j][1]].z + locationa[f[j][2]].z) >(locationa[f[iMax][0]].z + locationa[f[iMax][1]].z + locationa[f[iMax][2]].z))
            {
               iMax = j;
            }

         }

         if((bFirst && i < 3) || (!bFirst && i >= 3))
         {

            int iFace = iaf[iMax];

            ia.add_unique(iFace);

            double r = (locationa[f[iMax][0]].z + locationa[f[iMax][1]].z + locationa[f[iMax][2]].z) * d;

            ::color ca;

            double dPeriod = (5000) * 11;

            if(iHint == 0)
            {

               ca.set_hls(fmod(__double(::get_millis()),dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }
            else
            {
               ca.set_hls(fmod(__double(::get_millis()) + dPeriod / 2,dPeriod) / dPeriod,0.84 - r / 2.0,1.0 - r);
            }

            color32_t clr = ca.get_rgb();


            /*pen->create_solid((1.05 - r) * 10.0,ARGB((int)(dA * (255.0 - r * 200.0)),ca.m_iR,ca.m_iG,ca.m_iB));
            if(i < 6)
            {
            pen->m_etype = ::draw2d::e_pen_dot;
            }
            else
            {
            pen->m_etype = ::draw2d::e_pen_solid;
            }
            m_pdc->set(pen);*/

            pimage->fill((int)(dA * (184.0 - r * 128.0)),ca.red,ca.green,ca.blue);

            point2da[0]=::point_i32((::i32)locationa[f[iMax][0]].x,(::i32)locationa[f[iMax][0]].y);
            point2da[1]= ::point_i32((::i32)locationa[f[iMax][1]].x,(::i32)locationa[f[iMax][1]].y);
            point2da[2]= ::point_i32((::i32)locationa[f[iMax][2]].x,(::i32)locationa[f[iMax][2]].y);

            __throw(todo("plgblt"));
            //m_pdc->PlgBlt(point2da, pimage->g(),0,0,pimage->width(),pimage->width(),bm,0,0);

         }

         f.remove_at(iMax);
         iaf.remove_at(iMax);

         i++;

      }


      //pen->create_solid(1.0,ARGB(255,((int)(clr)),((int)(clr)),((int)(clr)))); m_pdc->set(pen)

      //SET_PCOLOR((p02.z + p03.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p03.x,(float)p03.y);
      //SET_PCOLOR((p03.z + p04.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p04.x,(float)p04.y);
      //SET_PCOLOR((p04.z + p01.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p01.x,(float)p01.y);

      //m_pdc->move_to(p05.x,p05.y);
      //SET_PCOLOR((p05.z + p06.z) / (2.0 * z));
      //m_pdc->line_to(p06.x,p06.y);
      //SET_PCOLOR((p06.z + p07.z) / (2.0 * z));
      //m_pdc->line_to(p07.x,p07.y);
      //SET_PCOLOR((p07.z + p08.z) / (2.0 * z));
      //m_pdc->line_to(p08.x,p08.y);
      //SET_PCOLOR((p08.z + p05.z) / (2.0 * z));
      //m_pdc->line_to(p05.x,p05.y);

      //SET_PCOLOR((p01.z + p05.z) / (2.0 * z));
      //m_pdc->draw_line((float)p01.x,(float)p01.y,(float)p05.x,(float)p05.y);
      //SET_PCOLOR((p02.z + p06.z) / (2.0 * z));
      //m_pdc->draw_line((float)p02.x,(float)p02.y,(float)p06.x,(float)p06.y);
      //SET_PCOLOR((p03.z + p07.z) / (2.0 * z));
      //m_pdc->draw_line((float)p03.x,(float)p03.y,(float)p07.x,(float)p07.y);
      //SET_PCOLOR((p04.z + p08.z) / (2.0 * z));
      //m_pdc->draw_line((float)p04.x,(float)p04.y,(float)p08.x,(float)p08.y);

      return ia;
   }


} // namespace draw3d





