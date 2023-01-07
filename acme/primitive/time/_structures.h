// Created by CSTBS on 2021-10-06 19:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/primitive/comparison/compare.h"


struct TIME { ::i64 m_iSecond; ::i64 m_iNanosecond; };

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


