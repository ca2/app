#include "framework.h"


namespace draw2d
{


   float Cosines[360];
   float Sines[360];

   long long CosN[360]; // * 1 << 31
   long long SinN[360];

   long long Cos10N[10]; // until 10 degress
   long long Sin10N[10]; // more precision * 1 << 34

   double dPi;


   void static_initialize()
   {

      double dCos;
      double dSin;
      double d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;
      int i;
      for (i = 0; i < 360; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cosines[i] = float(dCos);
         Sines[i] = float(dSin);
         CosN[i] = (long long)(dCos * d32);
         SinN[i] = (long long)(dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for (i = 0; i < 10; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cos10N[i] = (long long)(dCos * d32);
         Sin10N[i] = (long long)(dSin * d32);
      }

   }


} // namespace draw2d

//
//image::image::image()
//{
//
//}


//image::image::image(nullptr_t)
//{
//
//}
//
//
//image::image::image(::particle * pparticle)
//{
//
//   m_pimpl = pparticle->create_image();
//
//}


//image::image::image(::image::image *pimage)
//{
//
//   m_pimpl = pimpl;
//
//}


//image::image::image(const ::image::image_pointer & pimpl)
//{
//
//   m_pimpl = pimpl;
//
//}


//image::image::image(::image::image_pointer && pimpl) :
//   m_pimpl(::transfer(pimpl))
//{
//
//}


//image::image::image(const image & image)
//{
//
//   operator = (pimage);
//
//}

//image::image::image(image && image) :
//   m_pimpl(::transfer(pimage)), m_dynamic(pimage->m_dynamic)
//{
//
//}

//
//image::~image()
//{
//
//   //if(m_pimpl.is_set())
//   //{
//
//   //   m_pimpl.release();
//
//   //}
//
//}


namespace draw2d
{


   void static_start()
   {

      double dCos;
      double dSin;
      double d32 = (1U << 31);
      ::draw2d::dPi = atan(1.0) * 4.0;;
      int i;
      for (i = 0; i < 360; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cosines[i] = float(dCos);
         Sines[i] = float(dSin);
         CosN[i] = (long long)(dCos * d32);
         SinN[i] = (long long)(dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for (i = 0; i < 10; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cos10N[i] = (long long)(dCos * d32);
         Sin10N[i] = (long long)(dSin * d32);
      }

   }


} // namespace draw2d


//PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeDraw2d = nullptr;
//PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeImaging = nullptr;





