// Created by camilo on 2023-06-29 08:47 <3ThomasBorregaardSorensen!!
#pragma once


constexpr long double operator "" _η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr huge_natural operator "" _η(huge_natural i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator "" _μ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr huge_natural operator "" _μ(huge_natural i)
{

   return i / (1'000 * 1'000);

}


constexpr long double operator "" _m(long double d)
{

   return d / 1'000.0;

}


constexpr huge_natural operator "" _m(huge_natural i)
{

   return i / 1'000;

}


constexpr long double operator "" _k(long double d)
{

   return 1000.0 * d;

}


constexpr huge_natural operator "" _k(huge_natural i)
{

   return 1'000 * i;

}

constexpr long double operator "" _M(long double d)
{

   return 1'000.0 * 1'000.0 * d;

}


constexpr huge_natural operator "" _M(huge_natural i)
{

   return 1'000 * 1'000 * i;

}


constexpr long double operator "" _G(long double d)
{

   return 1'000.0 * 1'000.0 * 1'000.0 * d;

}


constexpr huge_natural operator "" _G(huge_natural i)
{

   return 1'000 * 1'000 * 1'000 * i;

}



