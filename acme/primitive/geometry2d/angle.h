#pragma once


template < primitive_floating FLOAT >
class angle_type
{
public:

   
   using UNIT_TYPE = FLOAT;
   

   UNIT_TYPE m_fAngle; // in radians


   constexpr angle_type() : m_fAngle(0.0) {}
   constexpr angle_type(no_initialize_t) {}
   //constexpr angle_type(nullptr_t) : m_fAngle(0.0) {}
   template < primitive_floating FLOATING1 >
   constexpr angle_type(const ::angle_type <FLOATING1 > & angle) : m_fAngle((UNIT_TYPE) angle.m_fAngle) {}

   angle_type operator -() const { return radians(-m_fAngle); }

   operator UNIT_TYPE() const { return m_fAngle; }

   UNIT_TYPE radian() const { return m_fAngle; }

   UNIT_TYPE degree() const { return (UNIT_TYPE) m_fAngle * (UNIT_TYPE)180.0 / (UNIT_TYPE)MATH_PI; }

   angle_type operator - (const angle_type & angle) const { return radians(m_fAngle - angle.m_fAngle); }
   angle_type operator + (const angle_type & angle) const { return radians(m_fAngle + angle.m_fAngle); }
   angle_type operator / (FLOAT f) const { return radians(m_fAngle / f); }
   FLOAT operator / (const angle_type & angle) const { return m_fAngle / angle.m_fAngle; }
   angle_type operator * (FLOAT f) const { return m_fAngle * f; }

   double normalized() const { auto d = (FLOAT) fmod(m_fAngle, 2.0 * MATH_PI); return d <  (FLOAT) 0.0 ? d + (FLOAT) (2.0 * MATH_PI) : d; }
   void normalize() { m_fAngle = normalized(); }

   
   static constexpr angle_type radians(UNIT_TYPE fAngle)
   {
      
      angle_type angle;
      
      angle.m_fAngle = fAngle;
      
      return angle;
      
   }

   
   template < primitive_number NUMBER >
   static constexpr angle_type degrees(NUMBER degrees)
   {
      
      return radians(degrees * MATH_PI / 180.0);
      
   }

   
};


using angle_f32 = angle_type < ::f32 >;
using angle_f64 = angle_type < ::f64 >;

template < primitive_floating FLOATING >
constexpr angle_type < FLOATING > radians(FLOATING fAngle)
{
   
   return angle_type < FLOATING >::radians(fAngle);
   
}





inline angle_f64 operator "" _degree(long double degrees)
{

   return radians(degrees * MATH_PI / 180.0);

}


inline angle_f64 operator "" _degrees(long double degrees)
{

   return operator "" _degree(degrees);

}


inline angle_f64 operator "" _degree(unsigned long long int degrees)
{

   return radians(degrees * MATH_PI / 180.0);

}


inline angle_f64 operator "" _degrees(unsigned long long int ull)
{

   return operator "" _degree(ull);

}



template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline auto angle(const ::point_type < NUMBER1 > & center, const ::point_type < NUMBER2 > & point)
{

   return radians(::std::atan2(point.y() - center.y(), point.x() - center.x()));

}



