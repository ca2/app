// Created by camilo on 2023-02-07 20:55 BRT <3ThomasBorregaardSorensen!!
#pragma once


constexpr long double operator ""_η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr unsigned long long operator ""_η(unsigned long long i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator ""_µ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr unsigned long long operator ""_µ(unsigned long long i)
{

   return i / (1'000 * 1'000);

}


constexpr long double operator ""_m(long double d)
{

   return d / 1'000.0;

}


constexpr unsigned long long operator ""_m(unsigned long long i)
{

   return i / 1'000;

}


class integral_byte
{
public:


   memsize m_memsize;


   constexpr integral_byte(memsize memsize = 1) :
      m_memsize(memsize)
   {


   }

   operator memsize() const { return m_memsize; }


};


constexpr integral_byte operator ""_KiB(long double d)
{

   return (memsize) (1024.0 * d);

}


constexpr integral_byte operator ""_KiB(unsigned long long i)
{

   return 1'024 * i;

}


constexpr long double operator ""_k(long double d)
{

   return 1000.0 * d;

}


constexpr unsigned long long operator ""_k(unsigned long long i)
{

   return 1'000 * i;

}


constexpr integral_byte operator ""_MiB(long double d)
{

   return (memsize)(1024.0 * 1024.0 * d);

}


constexpr integral_byte operator ""_MiB(unsigned long long i)
{

   return (memsize)(1024 * 1024 * i);

}


constexpr long double operator ""_M(long double d)
{

   return (memsize) (1'000 * 1'000 * d);

}


constexpr unsigned long long operator ""_M(unsigned long long i)
{

   return (memsize) (1'000 * 1'000 * i);

}


constexpr integral_byte operator ""_GiB(long double d)
{

   return (memsize) (1'024.0 * 1'024.0 * 1'024.0 * d);

}


constexpr integral_byte operator ""_GiB(unsigned long long i)
{

   return (memsize) (1'024 * 1'024 * 1'024 * i);

}


constexpr long double operator ""_G(long double d)
{

   return (memsize) (1'000.0 * 1'000.0 * 1'000.0 * d);

}


constexpr unsigned long long operator ""_G(unsigned long long i)
{

   return (memsize) (1'000 * 1'000 * 1'000 * i);

}




