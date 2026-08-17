#ifndef _FILTERS_H_
#define _FILTERS_H_

class CGenericFilter
{
public:

   CGenericFilter(::f64 dWidth) : m_dWidth(dWidth) {}
   virtual ~CGenericFilter() {}

   ::f64 GetWidth() { return m_dWidth; }
   void   SetWidth(::f64 dWidth) { m_dWidth = dWidth; }

   virtual ::f64 Filter(::f64 dVal) = 0;

protected:

#define FILTER_PI  ::f64 (3.1415926535897932384626433832795)
#define FILTER_2PI ::f64 (2.0 * 3.1415926535897932384626433832795)
#define FILTER_4PI ::f64 (4.0 * 3.1415926535897932384626433832795)

   ::f64  m_dWidth;
};

class CBoxFilter : public CGenericFilter
{
public:

   CBoxFilter(::f64 dWidth = ::f64(0.5)) : CGenericFilter(dWidth) {}
   virtual ~CBoxFilter() {}

   ::f64 Filter(::f64 dVal) { return (fabs(dVal) <= m_dWidth ? 1.0 : 0.0); }
};

class CBilinearFilter : public CGenericFilter
{
public:

   CBilinearFilter(::f64 dWidth = ::f64(1.0)) : CGenericFilter(dWidth) {}
   virtual ~CBilinearFilter() {}

   ::f64 Filter(::f64 dVal)
   {
      dVal = fabs(dVal);
      return (dVal < m_dWidth ? m_dWidth - dVal : 0.0);
   }
};

class CGaussianFilter : public CGenericFilter
{
public:

   CGaussianFilter(::f64 dWidth = ::f64(3.0)) : CGenericFilter(dWidth) {}
   virtual ~CGaussianFilter() {}

   ::f64 Filter(::f64 dVal)
   {
      if (fabs(dVal) > m_dWidth)
      {
         return 0.0;
      }
      return exp(-dVal * dVal / 2.0) / sqrt(FILTER_2PI);
   }
};

class CHammingFilter : public CGenericFilter
{
public:

   CHammingFilter(::f64 dWidth = ::f64(0.5)) : CGenericFilter(dWidth) {}
   virtual ~CHammingFilter() {}

   ::f64 Filter(::f64 dVal)
   {
      if (fabs(dVal) > m_dWidth)
      {
         return 0.0;
      }
      ::f64 dWindow = 0.54 + 0.46 * cos(FILTER_2PI * dVal);
      ::f64 dSinc = (dVal == 0) ? 1.0 : sin(FILTER_PI * dVal) / (FILTER_PI * dVal);
      return dWindow * dSinc;
   }
};

class CBlackmanFilter : public CGenericFilter
{
public:

   CBlackmanFilter(::f64 dWidth = ::f64(0.5)) : CGenericFilter(dWidth) {}
   virtual ~CBlackmanFilter() {}

   ::f64 Filter(::f64 dVal)
   {
      if (fabs(dVal) > m_dWidth)
      {
         return 0.0;
      }
      ::f64 dN = 2.0 * m_dWidth + 1.0;
      return 0.42 + 0.5 * cos(FILTER_2PI * dVal / (dN - 1.0)) +
             0.08 * cos(FILTER_4PI * dVal / (dN - 1.0));
   }
};


#endif  // _FILTERS_H_
