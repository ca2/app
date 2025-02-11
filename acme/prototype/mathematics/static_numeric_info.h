#pragma once

//#include <limits.h>

template < class T >
class static_numeric_info
{
   public:

}; // numeric_info




template <>
class CLASS_DECL_ACME static_numeric_info < unsigned int >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info



template <>
class CLASS_DECL_ACME static_numeric_info < unsigned long long >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info


#if defined(WINDOWS) || defined(__APPLE__)

template <>
class CLASS_DECL_ACME static_numeric_info < long unsigned int >
{
   public:

      static const bool is_signed = false;
      static const bool is_integer = true;

}; // numeric_info


#endif




