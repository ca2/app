//
// Created by camilo on 2022-10-23 10:10 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace earth
{


   class CLASS_DECL_ACME time_shift
   {
   public:


      double m_d; // in seconds;


      time_shift(double d = 0.0) : m_d(d) {}


      static inline time_shift none() // UTC
      {

         return {0.0};

      }

      static time_shift local();

      operator double &() { return m_d; }

      operator double() const { return m_d; }

   };


} // namespace earth



