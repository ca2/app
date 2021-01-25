#pragma once


namespace datetime
{


   class CLASS_DECL_ACME ::payload
   {
   public:

      i32            m_iYear;
      i32            m_iMonth;
      i32            m_iDay;
      i32            m_iHour;
      i32            m_iMinute;
      i32            m_iSecond;
      bool           m_bSpan;

<<<<<<< HEAD
      ::payload(const ::datetime::time & time);
      ::payload();
      ~payload();
=======
      value(const ::datetime::time & time);
      value();
      ~value();
>>>>>>> origin/basis

      // ano gregoriano mdio de 365,2425 dias solares
      double get_years() const;
      // baseado no ano gregoriano mdio de 365,2425 dias solares * 12.0
      double get_months() const;
      double get_days() const;
      double get_hours() const;
      double get_minutes() const;
      double get_seconds() const;

      ::datetime::time get_time() const;
      ::datetime::time_span GetSpan() const;
<<<<<<< HEAD
      ::payload & operator = (const ::datetime::time & time);
=======
      value & operator = (const ::datetime::time & time);
>>>>>>> origin/basis

   };



} // namespace datetime


CLASS_DECL_ACME datetime::result operator + (const datetime::result & val1, const datetime::result & val2);
CLASS_DECL_ACME datetime::result operator - (const datetime::result & val1, const datetime::result & val2);
CLASS_DECL_ACME datetime::result operator * (const datetime::result & val1, double d);
CLASS_DECL_ACME datetime::result operator / (const datetime::result & val1, double d);
<<<<<<< HEAD
<<<<<<< HEAD
::payload
=======

>>>>>>> origin/basis
=======

>>>>>>> origin/basis


