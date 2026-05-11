// Created by camilo on 2023-06-29 08:47 <3ThomasBorregaardSorensen!!
#pragma once


constexpr long double operator""_η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr ::u64 operator""_η(::u64 i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator""_μ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr ::u64 operator""_μ(::u64 i)
{

   return i / (1'000 * 1'000);

}


constexpr long double operator""_m(long double d)
{

   return d / 1'000.0;

}


constexpr ::u64 operator""_m(::u64 i)
{

   return i / 1'000;

}


constexpr long double operator""_k(long double d)
{

   return 1000.0 * d;

}


constexpr ::u64 operator""_k(::u64 i)
{

   return 1'000 * i;

}

constexpr long double operator""_M(long double d)
{

   return 1'000.0 * 1'000.0 * d;

}


constexpr ::u64 operator""_M(::u64 i)
{

   return 1'000 * 1'000 * i;

}


constexpr long double operator""_G(long double d)
{

   return 1'000.0 * 1'000.0 * 1'000.0 * d;

}


constexpr ::u64 operator""_G(::u64 i)
{

   return 1'000 * 1'000 * 1'000 * i;

}



