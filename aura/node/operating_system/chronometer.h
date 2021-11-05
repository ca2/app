﻿//////////////////////////////////////////////////////////////////////////////
// timer.h
// =======
// High Resolution timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (ca) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////
#pragma once



namespace aura
{


   class CLASS_DECL_AURA chronometer
   {
   public:


      bool        m_bStopped; /// stop flag
      u64         m_beg; // nanosecond
      u64         m_end; // nanosecond


      chronometer();                                    // default constructor
      ~chronometer();                                   // default destructor

      void   start();                             // start timer
      void   stop();                              // stop the timer
      double getElapsedTime();                    // get elapsed time in second
      double getElapsedTimeInSec();               // get elapsed time in second (same as getElapsedTime)
      double getElapsedTimeInMilliSec();          // get elapsed time in milli-second
      double getElapsedTimeInMicroSec();          // get elapsed time in micro-second

      double getTime();                           // get time in second
      double getTimeInSec();                      // get time in second (same as getElapsedTime)
      double getTimeInMilliSec();                 // get time in milli-second
      double getTimeInMicroSec();                 // get time in micro-second

   };



} // namespace aura



