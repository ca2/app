#include "framework.h"
#include "result.h"
// #include "acme/primitive/string/string.h"
#include "acme/primitive/string/international.h"
#define _USE_MATH_DEFINES
#include <math.h>


namespace calculator
{


   result pow(const result & val1, double ca);


   result::result()
   {
      m_dR = 0.0;
      m_dI = 0.0;
   }

   result::~result()
   {
   }

   double result::arg() const
   {
      if(m_dR == 0.0)
      {
         if(m_dI < 0.0)
         {
            return  - 0.5 * pi();
         }
         else if(m_dI == 0.0)
         {
            return 0.0;
            //throw ::exception(::exception("<h1>undefined</h1>: <strong>could</strong> be any <strong>well defined</strong> result:<br> <strong>specif details</strong>: seems to be too small modulus"));
         }
         else
         {
            return  0.5 * pi();
         }
      }
      else if(m_dI == 0.0)
      {
         if(m_dR < 0.0)
         {
            return pi();
         }
         else if(m_dR == 0.0)
         {
            return 0.0;
            //throw ::exception(::exception("<h1>undefined</h1>: <strong>could</strong> be any <strong>well defined</strong> result:<br> <strong>specif details</strong>: seems to be too small modulus"));
         }
         else
         {
            return 0.0;
         }
      }
      else
      {
         return atan2(m_dR, m_dI);
      }
   }

   double result::mod() const
   {
      return ::sqrt(m_dR * m_dR + m_dI * m_dI);
   }

   string result::to_string(e_mode emode) const
   {
      string str;
      if(emode == mode_rectangular)
      {
         if(m_dI == 0.0)
         {
            str.format("%f", m_dR);
            return str;
         }
         else if(m_dR == 0.0 || (fabs(m_dR) < (1.0 / 1000000000.0) && (fabs(m_dI) / fabs(m_dR)) > 1000000000.0))
         {
            // Real part is precisely or almost 0
            str.format("i%f",m_dI);
            return str;
         }
         else if(m_dI > 0.0)
         {
            str.format("%f + i%f", m_dR, m_dI);
            return str;
         }
         else
         {
            str.format("%f - i%f", m_dR, fabs(m_dI));
            return str;
         }
      }
      else if(emode == mode_polar_radian)
      {
         str.format("%f arg(%f)", mod(), arg());
         return str;
      }
      else if(emode == mode_polar_degree)
      {
         str.format(unitext("%f arg(%f°)"), mod(), arg() * 180.0 / pi());
         return str;
      }
      return "";
   }

   double g_dPi = ::atan(1.0) * 4.0;

   double pi()
   {
      return M_PI;
   }


   result operator + (const result & val1, const result & val2)
   {
      result val;
      val.m_dR = val1.m_dR + val2.m_dR;
      val.m_dI = val1.m_dI + val2.m_dI;
      return val;
   }

   result operator - (const result & val1, const result & val2)
   {
      result val;
      val.m_dR = val1.m_dR - val2.m_dR;
      val.m_dI = val1.m_dI - val2.m_dI;
      return val;
   }

   result operator * (const result & val1, const result & val2)
   {
      result val;
      val.m_dR = val1.m_dR * val2.m_dR - val1.m_dI * val2.m_dI;
      val.m_dI = val1.m_dR * val2.m_dI + val2.m_dR * val1.m_dI;
      return val;
   }

   result operator / (const result & val1, const result & val2)
   {
      result val;
      double dDiv = val2.m_dR * val2.m_dR + val2.m_dI * val2.m_dI;
      val.m_dR = (val1.m_dR * val2.m_dR + val1.m_dI * val2.m_dI) / dDiv;
      val.m_dI = (val1.m_dI * val2.m_dR - val1.m_dR * val2.m_dI) / dDiv;
      return val;
   }

   result pow(const result & val1, double ca)
   {
      result val;
      double dMod = val1.mod();
      double dArg = val1.arg();
      dMod = ::pow(dMod, ca);
      dArg = dArg * ca;
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dMod * ::sin(dArg);

      return val;
   }

   result pow(const result & val1, const result & val2)
   {
      result val;
      double dMod1 = val1.mod();
      double dArg1 = val1.arg();
      double dArg = val2.m_dR * dArg1 + val2.m_dI * ::log(dMod1);
      double dMod = ::pow(dMod1, val2.m_dR) * ::exp(-val2.m_dI * dArg1);
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dMod * ::sin(dArg);
      return val;
   }

   result sqr(const result & val)
   {
      return val * val;
   }

   result sqrt(const result & val)
   {
      return pow(val, 0.5);
   }

   result exp(const result & val1)
   {
      result val;
      double dMod = ::exp(val1.m_dR);
      double dArg = val1.arg();
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dArg * ::sin(dArg);
      return val;
   }

   // main calculatorresult
   result log(const result & val1)
   {
      result val;
      val.m_dR = ::log(val1.mod());
      val.m_dI = val1.arg();
      return val;
   }


   result atan(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::atan(dMod);
      val.m_dI = 0;
      return val;
   }

   result acos(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::acos(dMod);
      val.m_dI = 0;
      return val;
   }

   result asin(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::asin(dMod);
      val.m_dI = 0;
      return val;
   }

   result tan(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::tan(dMod);
      val.m_dI = 0;
      return val;
   }

   result cos(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::cos(dMod);
      val.m_dI = 0;
      return val;
   }

   result sin(const result & val1)
   {
      // TODO imaginary
      result val;
      double dMod = val1.mod();
      val.m_dR = ::sin(dMod);
      val.m_dI = 0;
      return val;
   }

} // namespace calculator




//#ifdef VARIADIC_TEMPLATE_FORMAT2



//namespace str
//{
//
//   template < >
//   void format_type(string_format * pformat,const calculatorresult  & cval)
//   {
//
//      pformat->append(cval.to_string());
//
//   }
//
//
//
//
//} // namespace str
//
//
//
//#endif
