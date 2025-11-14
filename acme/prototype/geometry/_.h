// Created by camilo on 2025-11-13 22:44 <3ThomasBorregaardSørensen!!

// two_pi two_π constant for different floating point types
template<typename T>
struct two_π_impl;

template<>
struct two_π_impl<float>
{
   static constexpr float payload = 6.283185307179586476925286766559f; // 2π
};

template<>
struct two_π_impl<double>
{
   static constexpr double payload = 6.283185307179586476925286766559;
};

template<>
struct two_π_impl<long double>
{
   static constexpr long double payload = 6.283185307179586476925286766559L;
};

template<typename T>
inline constexpr T two_π = two_π_impl<T>::payload;



