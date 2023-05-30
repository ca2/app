#pragma once


class CLASS_DECL_ACME angle
{
public:


   double m_d; // in radians


   angle() : m_d(0.0) {}
   angle(enum_no_initialize) {}
   angle(nullptr_t) : m_d(0.0) {}
   angle(double d) : m_d(d) {}

   angle operator -() const { return (angle)-m_d; }

   operator double() const { return m_d; }

   double radian() const { return m_d; }

   double degree() const { return m_d * 180.0 / MATH_PI; }

   angle operator - (const ::angle & angle) const { return m_d - angle.m_d; }
   angle operator + (const ::angle & angle) const { return m_d + angle.m_d; }
   angle operator / (double d) const { return m_d / d; }
   angle operator * (double d) const { return m_d * d; }

   double normalized() const { auto d = fmod(m_d, 360); return d < 0.0 ? d + 360.0 : d; }
   void normalize() { m_d = normalized(); }

};


inline angle operator "" _degree(long double d)
{

   return (angle)(d * MATH_PI / 180.0);

}


inline angle operator "" _degrees(long double d)
{

   return operator "" _degree(d);

}


inline angle operator "" _degree(unsigned long long int ull)
{

   return ((long double)ull) * MATH_PI / 180.0;

}


inline angle operator "" _degrees(unsigned long long int ull)
{

   return operator "" _degree(ull);

}



