#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS result
   {
   public:


      enum e_mode
      {

         mode_rectangular,
         mode_polar_radian,
         mode_polar_degree,

      };

      double      m_dR; // real part
      double      m_dI; // imaginary part


      double arg() const;
      double mod() const;


      result();
      ~result();

      string to_string(e_mode mode = mode_rectangular) const;


   };


   CLASS_DECL_AXIS double pi();

   CLASS_DECL_AXIS result operator + (const result & payload1, const result & payload2);
   CLASS_DECL_AXIS result operator - (const result & payload1, const result & payload2);
   CLASS_DECL_AXIS result operator * (const result & payload1, const result & payload2);
   CLASS_DECL_AXIS result operator / (const result & payload1, const result & payload2);

   CLASS_DECL_AXIS result pow(const result & payload1, const result & payload2);

   CLASS_DECL_AXIS result sqr(const result & val);
   CLASS_DECL_AXIS result sqrt(const result & val);
   CLASS_DECL_AXIS result exp(const result & val);
   CLASS_DECL_AXIS result log(const result & val);

   CLASS_DECL_AXIS result atan(const result & val);
   CLASS_DECL_AXIS result acos(const result & val);
   CLASS_DECL_AXIS result asin(const result & val);

   CLASS_DECL_AXIS result tan(const result & val);
   CLASS_DECL_AXIS result cos(const result & val);
   CLASS_DECL_AXIS result sin(const result & val);


} // namespace calculator




//namespace str
//{
//
//
//   template < >
//   CLASS_DECL_AXIS void format_type(::string_format * pformat,const ::calculatorresult & val);
//
//
//} // namespace str
//


