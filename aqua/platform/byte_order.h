#pragma once
//#include <type_traits>
//#include <algorithm>
//#include <stdint.h>

namespace h2n2h_helper
{
   template <class T>
   T byteswap(T val, ::false_type)
   {
      return val;
   }

   template <class T>
   T byteswap(T val, ::true_type)
   {
      uint8_t c[sizeof(T)];
      memcpy(c, &val, sizeof(T));
      ::reverse(c, c+ sizeof(c));
      memcpy(&val, c, sizeof(T));
      return val;
   }

   struct Endian
   {
   private:
      static constexpr ::u32 uint32_ = 0x01020304;
      static constexpr ::u8 magic_ = (const ::u8&)uint32_;
   public:
      static constexpr bool little = magic_ == 0x04;
      static constexpr bool middle = magic_ == 0x02;
      static constexpr bool big = magic_ == 0x01;
      static_assert(little || middle || big, "Cannot determine endianness!");
      Endian() = delete;
   };

   using is_little_endian = ::integral_constant<bool, Endian::little>;
}

template <class T>
T host2network(T src)
{
   using namespace h2n2h_helper;
   static_assert(std::is_integral<T>::value, "Accepting integers only.");
   static_assert(sizeof(T) > 1, "Accepting 2 bytes or more integers only.");
   static_assert((sizeof(T) % 2) == 0, "Some weird byte length of integer supplied. Must never happen.");

   return byteswap<T>(src, is_little_endian{});
}


template <class T>
T network2host(T src)
{
   using namespace h2n2h_helper;
   static_assert(std::is_integral<T>::value, "Accepting integers only.");
   static_assert(sizeof(T) > 1, "Accepting 2 bytes or more integers only.");
   static_assert((sizeof(T) % 2) == 0, "Some weird byte length of integer supplied. Must never happen.");

   return byteswap<T>(src, is_little_endian{});
}
