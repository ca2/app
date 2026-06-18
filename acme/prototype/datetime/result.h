#pragma once


namespace datetime
{


   class CLASS_DECL_ACME result
   {
   public:


      ::i32            m_iYear;
      ::i32            m_iMonth;
      ::i32            m_iDay;
      ::i32            m_iHour;
      ::i32            m_iMinute;
      ::i32            m_iSecond;
      bool           m_bSpan;


      result(const ::earth::time & time);
      result();
      ~result();

      // ano gregoriano mdio de 365,2425 dias solares
      ::f64 get_years() const;
      // baseado no ano gregoriano mdio de 365,2425 dias solares * 12.0
      ::f64 get_months() const;
      ::f64 get_days() const;
      ::f64 get_hours() const;
      ::f64 get_minutes() const;
      ::f64 get_seconds() const;

      ::earth::time get_time() const;
      ::earth::time_span GetSpan() const;
      result & operator = (const ::earth::time & time);


   };


} // namespace datetime


CLASS_DECL_ACME datetime::result operator + (const datetime::result & result1, const datetime::result & result2);
CLASS_DECL_ACME datetime::result operator - (const datetime::result & result1, const datetime::result & result2);
CLASS_DECL_ACME datetime::result operator * (const datetime::result & result1, ::f64 d);
CLASS_DECL_ACME datetime::result operator / (const datetime::result & result1, ::f64 d);



