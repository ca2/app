// Created by CSTBS on 2021-10-06 19:38 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/comparison/compare.h"

struct posix_time_t {};

struct CLASS_DECL_ACME posix_time
{

   ::i64    m_iSecond;

   constexpr posix_time() : m_iSecond(0) {}
   template < primitive_integral INTEGRAL >
   constexpr posix_time(posix_time_t, INTEGRAL iSecond) : m_iSecond(iSecond) {}
   constexpr posix_time(const posix_time &) = default;
   posix_time(now_t);

   constexpr posix_time operator + (posix_time posixtime)  const
   {
      return { posix_time_t{}, m_iSecond + posixtime.m_iSecond };
   }

   constexpr posix_time operator - (posix_time posixtime)  const
   {
      return { posix_time_t{}, m_iSecond - posixtime.m_iSecond };
   }

   constexpr posix_time & operator += (posix_time posixtime)
   {
      m_iSecond += posixtime.m_iSecond;
      return *this;
   }

   constexpr posix_time & operator -=(posix_time posixtime)
   {
      m_iSecond = posixtime.m_iSecond;
      return *this;
   }

   template < primitive_integral INTEGRAL > 
   constexpr posix_time operator * (INTEGRAL i)  const
   {
      return { posix_time_t{}, m_iSecond * i };
   }


};


struct nanosecond_t {};

struct nanosecond
{

   ::i64    m_iNanosecond;

   constexpr nanosecond() : m_iNanosecond(0) {}
   template < primitive_integral INTEGRAL >
   constexpr nanosecond(nanosecond_t, INTEGRAL iNanosecond) : m_iNanosecond(iNanosecond) {}
   constexpr nanosecond(const nanosecond &) = default;


   constexpr nanosecond operator + (nanosecond nanosecond)  const
   {
      return { nanosecond_t{}, m_iNanosecond + nanosecond.m_iNanosecond };
   }

   constexpr nanosecond operator - (nanosecond nanosecond)  const
   {
      return { nanosecond_t {}, m_iNanosecond - nanosecond.m_iNanosecond };
   }

   constexpr nanosecond & operator += (nanosecond nanosecond)
   {
      m_iNanosecond += nanosecond.m_iNanosecond;
      return *this;
   }

   constexpr nanosecond & operator -=(nanosecond nanosecond)
   {
      m_iNanosecond -= nanosecond.m_iNanosecond;
      return *this;
   }

   template < primitive_integral INTEGRAL >
   constexpr nanosecond operator * (INTEGRAL i)  const
   {
      return { nanosecond_t{}, m_iNanosecond * i };
   }


};


struct TIME { posix_time m_posixtime; nanosecond m_nanosecond; };

struct FREQUENCY { double m_dHertz; };

constexpr FREQUENCY operator "" _Hz(long double d) { return { (double) d }; }


class time;


#define DECLARE_COMPARISON_WITH_TIME(EXPORT_CLAUSE_DECL) \
EXPORT_CLAUSE_DECL bool operator == (const class  ::time & time) const; \
EXPORT_CLAUSE_DECL ::std::strong_ordering operator <=> (const class  ::time & time) const; 
//\
//EXPORT_CLAUSE_DECL bool operator <= (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator > (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator >= (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator != (const class  ::time & time)  const;


#define DEFINE_COMPARISON_WITH_TIME(EXPORT_CLAUSE_DECL, TYPE) \
EXPORT_CLAUSE_DECL bool TYPE::operator == (const class  ::time & time) const { return ((class ::time)*this) == time; } \
EXPORT_CLAUSE_DECL ::std::strong_ordering TYPE::operator <=> (const class  ::time & time) const { return ((class ::time)*this) <=> time; } 
//\
//EXPORT_CLAUSE_DECL bool TYPE::operator <= (const class  ::time & time) const { return ((class ::time)*this) <= time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator > (const class  ::time & time) const { return ((class ::time)*this) > time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator >= (const class  ::time & time) const { return ((class ::time)*this) >= time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator != (const class  ::time & time) const { return ((class ::time)*this) != time; }


#define NON_INLINE


//#define DECLARE_COMPARISON_WITH_TIME \
//inline bool operator == (const class time & time); \
//inline bool operator < (const class time & time);  \
//inline bool operator <= (const class time & time); \
//inline bool operator > (const class time & time);  \
//inline bool operator >= (const class time & time); \
//inline bool operator != (const class time & time); 


//#define INLINE_COMPARISON_WITH_DURATION \
//inline bool operator == (const class time & time) const { return class ::time(*this) == time; } \
//inline bool operator < (const class time & time) const { return class ::time(*this) < time; } \
//inline bool operator <= (const class time & time) const { return class ::time(*this) <= time; } \
//inline bool operator > (const class time & time) const { return class ::time(*this) > time; } \
//inline bool operator >= (const class time & time) const { return class ::time(*this) >= time; } \
//inline bool operator != (const class time & time) const { return class ::time(*this) != time; } 


