#include "framework.h"


namespace draw2d
{


   ::f32 Cosines[360];
   ::f32 Sines[360];

   ::i64 CosN[360]; // * 1 << 31
   ::i64 SinN[360];

   ::i64 Cos10N[10]; // until 10 degress
   ::i64 Sin10N[10]; // more precision * 1 << 34

   ::f64 dPi;


   void static_initialize()
   {

      ::f64 dCos;
      ::f64 dSin;
      ::f64 d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;
      ::i32 i;
      for (i = 0; i < 360; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cosines[i] = ::f32(dCos);
         Sines[i] = ::f32(dSin);
         CosN[i] = (::i64)(dCos * d32);
         SinN[i] = (::i64)(dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for (i = 0; i < 10; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cos10N[i] = (::i64)(dCos * d32);
         Sin10N[i] = (::i64)(dSin * d32);
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

      ::f64 dCos;
      ::f64 dSin;
      ::f64 d32 = (1U << 31);
      ::draw2d::dPi = atan(1.0) * 4.0;;
      ::i32 i;
      for (i = 0; i < 360; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cosines[i] = ::f32(dCos);
         Sines[i] = ::f32(dSin);
         CosN[i] = (::i64)(dCos * d32);
         SinN[i] = (::i64)(dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for (i = 0; i < 10; i++)
      {
         dCos = ::cos(i / 180.0 * dPi);
         dSin = ::sin(i / 180.0 * dPi);
         Cos10N[i] = (::i64)(dCos * d32);
         Sin10N[i] = (::i64)(dSin * d32);
      }

   }


} // namespace draw2d


//PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeDraw2d = nullptr;
//PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeImaging = nullptr;





