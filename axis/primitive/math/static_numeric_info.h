#pragma once

//#include <limits.h>

template < class T >
class static_numeric_info
{
   public:

}; // numeric_info




template <>
class CLASS_DECL_AURA static_numeric_info < u32 >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info



template <>
class CLASS_DECL_AURA static_numeric_info < u64 >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info


#if defined(WINDOWS) || defined(APPLEOS)

template <>
class CLASS_DECL_AURA static_numeric_info < long unsigned int >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info


#endif




