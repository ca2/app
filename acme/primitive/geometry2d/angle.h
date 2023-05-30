#pragma once


template < primitive_floating FLOAT >
class angle_type
{
public:

   
   using UNIT_TYPE = FLOAT;
   

   UNIT_TYPE m_fAngle; // in radians


   angle_type() : m_fAngle(0.0) {}
   angle_type(enum_no_initialize) {}
   angle_type(nullptr_t) : m_fAngle(0.0) {}
   angle_type(UNIT_TYPE d) : m_fAngle(d) {}

   angle_type operator -() const { return (angle_type)-m_fAngle; }

   operator UNIT_TYPE() const { return m_fAngle; }

   UNIT_TYPE radian() const { return m_fAngle; }

   UNIT_TYPE degree() const { return (UNIT_TYPE) m_fAngle * (UNIT_TYPE)180.0 / (UNIT_TYPE)MATH_PI; }

   angle_type operator - (const angle_type & angle) const { return m_fAngle - angle.m_fAngle; }
   angle_type operator + (const angle_type & angle) const { return m_fAngle + angle.m_fAngle; }
   angle_type operator / (FLOAT f) const { return m_fAngle / f; }
   FLOAT operator / (const angle_type & angle) const { return m_fAngle / angle.m_fAngle; }
   angle_type operator * (FLOAT f) const { return m_fAngle * f; }

   double normalized() const { auto d = (FLOAT) fmod(m_fAngle, 2.0 * MATH_PI); return d <  (FLOAT) 0.0 ? d + (FLOAT) (2.0 * MATH_PI) : d; }
   void normalize() { m_fAngle = normalized(); }

};


using angle_f32 = angle_type < ::f32 >;
using angle_f64 = angle_type < ::f64 >;


inline angle_f64 operator "" _degree(long double d)
{

   return (angle_f64)(d * MATH_PI / 180.0);

}


inline angle_f64 operator "" _degrees(long double d)
{

   return operator "" _degree(d);

}


inline angle_f64 operator "" _degree(unsigned long long int ull)
{

   return ((long double)ull) * MATH_PI / 180.0;

}


inline angle_f64 operator "" _degrees(unsigned long long int ull)
{

   return operator "" _degree(ull);

}



