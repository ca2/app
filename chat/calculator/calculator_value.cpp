#include "framework.h"
#define _USE_MATH_DEFINES
#include <math.h>


namespace calculator
{


   value pow(const value & val1, double ca);


   value::value()
   {
      m_dR = 0.0;
      m_dI = 0.0;
   }

   value::~value()
   {
   }

   double value::arg() const
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
            //__throw(::exception("<h1>undefined</h1>: <strong>could</strong> be any <strong>well defined</strong> value:<br> <strong>specif details</strong>: seems to be too small modulus"));
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
            //__throw(::exception("<h1>undefined</h1>: <strong>could</strong> be any <strong>well defined</strong> value:<br> <strong>specif details</strong>: seems to be too small modulus"));
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

   double value::mod() const
   {
      return ::sqrt(m_dR * m_dR + m_dI * m_dI);
   }

   string value::to_string(e_mode emode) const
   {
      string str;
      if(emode == mode_rectangular)
      {
         if(m_dI == 0.0)
         {
            str.Format("%f", m_dR);
            return str;
         }
         else if(m_dR == 0.0 || fabs(m_dR) < (1.0 / 1000000000.0) && (fabs(m_dI) / fabs(m_dR)) > 1000000000.0)
         {
            // Real part is precisely or almost 0
            str.Format("i%f",m_dI);
            return str;
         }
         else if(m_dI > 0.0)
         {
            str.Format("%f + i%f", m_dR, m_dI);
            return str;
         }
         else
         {
            str.Format("%f - i%f", m_dR, fabs(m_dI));
            return str;
         }
      }
      else if(emode == mode_polar_radian)
      {
         str.Format("%f arg(%f)", mod(), arg());
         return str;
      }
      else if(emode == mode_polar_degree)
      {
         str.Format(unitext("%f arg(%f°)"), mod(), arg() * 180.0 / pi());
         return str;
      }
      return "";
   }

   double g_dPi = ::atan(1.0) * 4.0;

   double pi()
   {
      return M_PI;
   }


   value operator + (const value & val1, const value & val2)
   {
      value val;
      val.m_dR = val1.m_dR + val2.m_dR;
      val.m_dI = val1.m_dI + val2.m_dI;
      return val;
   }

   value operator - (const value & val1, const value & val2)
   {
      value val;
      val.m_dR = val1.m_dR - val2.m_dR;
      val.m_dI = val1.m_dI - val2.m_dI;
      return val;
   }

   value operator * (const value & val1, const value & val2)
   {
      value val;
      val.m_dR = val1.m_dR * val2.m_dR - val1.m_dI * val2.m_dI;
      val.m_dI = val1.m_dR * val2.m_dI + val2.m_dR * val1.m_dI;
      return val;
   }

   value operator / (const value & val1, const value & val2)
   {
      value val;
      double dDiv = val2.m_dR * val2.m_dR + val2.m_dI * val2.m_dI;
      val.m_dR = (val1.m_dR * val2.m_dR + val1.m_dI * val2.m_dI) / dDiv;
      val.m_dI = (val1.m_dI * val2.m_dR - val1.m_dR * val2.m_dI) / dDiv;
      return val;
   }

   value pow(const value & val1, double ca)
   {
      value val;
      double dMod = val1.mod();
      double dArg = val1.arg();
      dMod = ::pow(dMod, ca);
      dArg = dArg * ca;
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dMod * ::sin(dArg);

      return val;
   }

   value pow(const value & val1, const value & val2)
   {
      value val;
      double dMod1 = val1.mod();
      double dArg1 = val1.arg();
      double dArg = val2.m_dR * dArg1 + val2.m_dI * ::log(dMod1);
      double dMod = ::pow(dMod1, val2.m_dR) * ::exp(-val2.m_dI * dArg1);
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dMod * ::sin(dArg);
      return val;
   }

   value sqr(const value & val)
   {
      return val * val;
   }

   value sqrt(const value & val)
   {
      return pow(val, 0.5);
   }

   value exp(const value & val1)
   {
      value val;
      double dMod = ::exp(val1.m_dR);
      double dArg = val1.arg();
      val.m_dR = dMod * ::cos(dArg);
      val.m_dI = dArg * ::sin(dArg);
      return val;
   }

   // main calculator::value
   value log(const value & val1)
   {
      value val;
      val.m_dR = ::log(val1.mod());
      val.m_dI = val1.arg();
      return val;
   }


   value atan(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::atan(dMod);
      val.m_dI = 0;
      return val;
   }

   value acos(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::acos(dMod);
      val.m_dI = 0;
      return val;
   }

   value asin(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::asin(dMod);
      val.m_dI = 0;
      return val;
   }

   value tan(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::tan(dMod);
      val.m_dI = 0;
      return val;
   }

   value cos(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::cos(dMod);
      val.m_dI = 0;
      return val;
   }

   value sin(const value & val1)
   {
      // TODO imaginary
      value val;
      double dMod = val1.mod();
      val.m_dR = ::sin(dMod);
      val.m_dI = 0;
      return val;
   }

} // namespace calculator




//#ifndef NO_VARIADIC_TEMPLATE



namespace str
{

   template < >
   void format_type(string_format * pformat,const calculator::value  & cval)
   {

      pformat->append(cval.to_string());

   }




} // namespace str



//#endif
