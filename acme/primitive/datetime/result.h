#pragma once


namespace datetime
{


   class CLASS_DECL_ACME result
   {
   public:


      i32            m_iYear;
      i32            m_iMonth;
      i32            m_iDay;
      i32            m_iHour;
      i32            m_iMinute;
      i32            m_iSecond;
      bool           m_bSpan;


      result(const ::earth::time & time);
      result();
      ~result();

      // ano gregoriano mdio de 365,2425 dias solares
      double get_years() const;
      // baseado no ano gregoriano mdio de 365,2425 dias solares * 12.0
      double get_months() const;
      double get_days() const;
      double get_hours() const;
      double get_minutes() const;
      double get_seconds() const;

      ::earth::time get_time() const;
      ::earth::time_span GetSpan() const;
      result & operator = (const ::earth::time & time);


   };


} // namespace datetime


CLASS_DECL_ACME datetime::result operator + (const datetime::result & result1, const datetime::result & result2);
CLASS_DECL_ACME datetime::result operator - (const datetime::result & result1, const datetime::result & result2);
CLASS_DECL_ACME datetime::result operator * (const datetime::result & result1, double d);
CLASS_DECL_ACME datetime::result operator / (const datetime::result & result1, double d);



