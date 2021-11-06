#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH value
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


      value();
      ~value();

      string to_string(e_mode mode = mode_rectangular) const;


   };


   CLASS_DECL_CA2_MATH double pi();

   CLASS_DECL_CA2_MATH calculator::value operator + (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_CA2_MATH calculator::value operator - (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_CA2_MATH calculator::value operator * (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_CA2_MATH calculator::value operator / (const calculator::value & val1, const calculator::value & val2);

   CLASS_DECL_CA2_MATH value pow(const value & val1, const value & val2);

   CLASS_DECL_CA2_MATH value sqr(const value & val);
   CLASS_DECL_CA2_MATH value sqrt(const value & val);
   CLASS_DECL_CA2_MATH value exp(const value & val);
   CLASS_DECL_CA2_MATH value log(const value & val);

   CLASS_DECL_CA2_MATH value atan(const value & val);
   CLASS_DECL_CA2_MATH value acos(const value & val);
   CLASS_DECL_CA2_MATH value asin(const value & val);

   CLASS_DECL_CA2_MATH value tan(const value & val);
   CLASS_DECL_CA2_MATH value cos(const value & val);
   CLASS_DECL_CA2_MATH value sin(const value & val);

} // namespace calculator




namespace str
{


   template < >
   CLASS_DECL_CA2_MATH void format_type(::string_format * pformat,const ::calculator::value & val);


} // namespace str



