// Created by camilo on 2023-06-29 08:47 <3ThomasBorregaardSorensen!!
#pragma once


constexpr long double operator ""_η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator ""_η(unsigned long long int i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator ""_μ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator ""_μ(unsigned long long int i)
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


constexpr long double operator ""_k(long double d)
{

   return 1000.0 * d;

}


constexpr unsigned long long operator ""_k(unsigned long long i)
{

   return 1'000 * i;

}

constexpr long double operator ""_M(long double d)
{

   return 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""_M(unsigned long long i)
{

   return 1'000 * 1'000 * i;

}


constexpr long double operator ""_G(long double d)
{

   return 1'000.0 * 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""_G(unsigned long long i)
{

   return 1'000 * 1'000 * 1'000 * i;

}



