﻿// From datetime/department.h by camilo on 2022-10-17 21:31 <3ThomasBorregaardSorensen!!
#pragma once


namespace datetime
{


   class time_zone
   {
   public:

      string            m_strZone;
      double            m_dZone;
      ::earth::time  m_duration; /// time when this time zone record was last updated

      time_zone()
      {

         m_dZone = -1000.0;

      }

      bool is_valid(const ::duration & durationTimeOut) const
      {

         return m_strZone.has_char() && m_dZone > -25.0 && m_dZone < 25.0 && m_duration.elapsed() < durationTimeOut;

      }

   };


} // namespace datetime



