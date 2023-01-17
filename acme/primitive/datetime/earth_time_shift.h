//
// Created by camilo on 2022-10-23 10:10 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace earth
{


   class time_shift
   {
   public:


      double m_d; // in seconds;


      time_shift(double d = 0.0) : m_d(d) {}


      static inline time_shift none() // UTC
      {

         return {0.0};

      }

      static inline time_shift local()
      {

         time_t zero = 0;

         const tm *lt = localtime(&zero);

         int unaligned = lt->tm_sec + (lt->tm_min + (lt->tm_hour * 60)) * 60;

         return {(double) (lt->tm_mon ? unaligned - 24 * 60 * 60 : unaligned)};

      }


      operator double &() { return m_d; }

      operator double() const { return m_d; }

   };


} // namespace earth



