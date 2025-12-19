#pragma once


struct with_t {};


template < prototype_floating FLOATING_TYPE >
class angle_type;


template < prototype_floating FLOATING >
constexpr angle_type < FLOATING > radians(FLOATING fAngle);



template < prototype_floating FLOATING_TYPE >
class angle_type
{
public:

   
   using FLOATING = FLOATING_TYPE;
   

   FLOATING m_fAngle; // in radians


   constexpr angle_type() : m_fAngle(0.0) {}
   constexpr angle_type(no_initialize_t) {}
   constexpr angle_type(with_t, FLOATING u):m_fAngle(u) {}
   //constexpr angle_type(nullptr_t) : m_fAngle(0.0) {}
   template < prototype_floating FLOATING1 >
   constexpr angle_type(const ::angle_type <FLOATING1 > & angle) : m_fAngle((FLOATING) angle.m_fAngle) {}

   template < prototype_number Y, prototype_number X >
   angle_type & atan(Y y, X x) { m_fAngle = ::std::atan2(y, x); return *this; }

   angle_type operator -() const { return radians(-m_fAngle); }

   operator FLOATING() const { return m_fAngle; }

   FLOATING radian() const { return m_fAngle; }

   FLOATING degree() const { return (FLOATING) m_fAngle * (FLOATING)180.0 / (FLOATING)MATH_PI; }

   angle_type operator - (const angle_type & angle) const { return radians(m_fAngle - angle.m_fAngle); }
   angle_type operator + (const angle_type & angle) const { return radians(m_fAngle + angle.m_fAngle); }

   /// assumes subtracting radians from angle
   template < prototype_number NUMBER >
   angle_type operator-(NUMBER radians) const { return ::radians(m_fAngle - (FLOATING)radians); }

   /// assumes adding radians from angle
   template<prototype_number NUMBER>
   angle_type operator+(NUMBER radians) const { return ::radians(m_fAngle + (FLOATING)radians); }

   template < prototype_number NUMBER >
   angle_type operator / (NUMBER n) const
   {
      return radians(m_fAngle / (FLOATING) n); 
   }

   FLOATING operator / (const angle_type & angle) const { return m_fAngle / angle.m_fAngle; }
   
   template<prototype_number NUMBER>
   angle_type operator * (NUMBER n) const
   {
      return ::radians(m_fAngle * (FLOATING) n); 
   }

   angle_type &operator-=(const angle_type &angle) 
   { 
      
      m_fAngle -= angle.m_fAngle;
      
      return *this;

   }

   angle_type &operator+=(const angle_type &angle)
   {
      
      m_fAngle += angle.m_fAngle;
      
      return *this; 

   }


      

   double normalized() const { auto d = (FLOATING) fmod(m_fAngle, 2.0 * MATH_PI); return d <  (FLOATING) 0.0 ? d + (FLOATING) (2.0 * MATH_PI) : d; }
   void normalize() { m_fAngle = normalized(); }

   
   static constexpr angle_type radians(FLOATING fAngle)
   {
      
      angle_type angle;
      
      angle.m_fAngle = fAngle;
      
      return angle;
      
   }

     
   constexpr FLOATING radians() const
   {

      return m_fAngle;

   }


   constexpr FLOATING degrees() const { return ::radians_to_degrees(m_fAngle); }

   
   template < prototype_number NUMBER >
   static constexpr angle_type degrees(NUMBER degrees)
   {
      
      return radians(degrees * MATH_PI / 180.0);
      
   }


   
   FLOATING cos() const
   {
      
      return ::std::cos(m_fAngle);
      
   }

   FLOATING sin() const
   {
      
      return ::std::sin(m_fAngle); 

   }

};





using float_angle = angle_type < float >;
using double_angle = angle_type < double >;


namespace geometry
{


   template<prototype_floating FLOATING>
   inline angle_type<FLOATING> atan2(FLOATING y, FLOATING x)
   {

      return ::radians(::std::atan2(y, x));

   }


   template<prototype_floating FLOATING>
   inline angle_type<FLOATING> asin(FLOATING s)
   {

      return ::radians(::std::asin(s));

   }


} // namespace geometry



/// assumes result of radians subtracted from angle
template<prototype_number NUMBER, prototype_floating FLOATING>
constexpr angle_type<FLOATING> operator-(NUMBER radians, const angle_type<FLOATING> &angle)
{
   
   return ::radians((FLOATING)radians - angle.m_fAngle);

}


/// assumes result of radians added to angle
template<prototype_number NUMBER, prototype_floating FLOATING>
constexpr angle_type<FLOATING> operator+(NUMBER radians, const angle_type<FLOATING> &angle)
{
   
   return ::radians((FLOATING)radians + angle.m_fAngle);

}


template<prototype_number NUMBER, prototype_floating FLOATING>
constexpr angle_type<FLOATING> operator *(NUMBER n, const angle_type<FLOATING> &angle)
{

   return ::radians((FLOATING)n * angle.m_fAngle);

}


 

template < prototype_floating FLOATING >
constexpr angle_type < FLOATING > radians(FLOATING fAngle)
{
   
   return angle_type < FLOATING >::radians(fAngle);
   
}


template<prototype_floating FLOATING>
constexpr angle_type<FLOATING> degrees(FLOATING fAngle)
{

   return angle_type<FLOATING>::degrees(fAngle);
}


inline double_angle operator"" _degree(long double degrees) {

   return radians(degrees_to_radians(degrees));

}


inline double_angle operator "" _degrees(long double degrees)
{

   return operator "" _degree(degrees);

}


inline float_angle operator"" f_degree(long double degrees) 
{
   
   return radians(degrees_to_radians((float)degrees)); 

}


inline float_angle operator"" f_degrees(long double degrees)
{
   
   return operator"" f_degree(degrees); 

}


inline double_angle operator "" _degree(unsigned long long degrees)
{

   return radians(degrees_to_radians((double)degrees));

}


inline double_angle operator "" _degrees(unsigned long long hn)
{

   return operator "" _degree(hn);

}


inline float_angle operator"" f_degree(unsigned long long degrees)
{

   return radians(degrees_to_radians((float)degrees));

}


inline float_angle operator"" f_degrees(unsigned long long hn) 
{
   
   return operator"" f_degree(hn); 

}


template < prototype_number NUMBER1, prototype_number NUMBER2 >
inline auto angle(const ::point_type < NUMBER1 > & center, const ::point_type < NUMBER2 > & point)
{

   return ::geometry::atan2(point.y - center.y, point.x - center.x);

}



