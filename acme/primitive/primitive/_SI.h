// Created by camilo on 2023-06-29 08:47 <3ThomasBorregaardSorensen!!
#pragma once


constexpr long double operator "" η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator "" η(unsigned long long int i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator "" μ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator "" μ(unsigned long long int i)
{

   return i / (1'000 * 1'000);

}


constexpr long double operator ""m(long double d)
{

   return d / 1'000.0;

}


constexpr unsigned long long operator "" m(unsigned long long i)
{

   return i / 1'000;

}



constexpr long double operator ""k(long double d)
{

   return 1000.0 * d;

}


constexpr unsigned long long operator ""k(unsigned long long i)
{

   return 1'000 * i;

}

constexpr long double operator ""M(long double d)
{

   return 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""M(unsigned long long i)
{

   return 1'000 * 1'000 * i;

}


constexpr long double operator ""G(long double d)
{

   return 1'000.0 * 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""G(unsigned long long i)
{

   return 1'000 * 1'000 * 1'000 * i;

}



