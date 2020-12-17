#pragma once


namespace calculator
{


   class CLASS_DECL_AXIS payload
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


      payload();
      ~payload();

      string to_string(e_mode mode = mode_rectangular) const;


   };


   CLASS_DECL_AXIS double pi();

   CLASS_DECL_AXIS payload operator + (const payload & payload1, const payload & payload2);
   CLASS_DECL_AXIS payload operator - (const payload & payload1, const payload & payload2);
   CLASS_DECL_AXIS payload operator * (const payload & payload1, const payload & payload2);
   CLASS_DECL_AXIS payload operator / (const payload & payload1, const payload & payload2);

   CLASS_DECL_AXIS payload pow(const payload & payload1, const payload & payload2);

   CLASS_DECL_AXIS payload sqr(const payload & val);
   CLASS_DECL_AXIS payload sqrt(const payload & val);
   CLASS_DECL_AXIS payload exp(const payload & val);
   CLASS_DECL_AXIS payload log(const payload & val);

   CLASS_DECL_AXIS payload atan(const payload & val);
   CLASS_DECL_AXIS payload acos(const payload & val);
   CLASS_DECL_AXIS payload asin(const payload & val);

   CLASS_DECL_AXIS payload tan(const payload & val);
   CLASS_DECL_AXIS payload cos(const payload & val);
   CLASS_DECL_AXIS payload sin(const payload & val);

} // namespace calculator




//namespace str
//{
//
//
//   template < >
//   CLASS_DECL_AXIS void format_type(::string_format * pformat,const ::calculator::payload & val);
//
//
//} // namespace str
//


