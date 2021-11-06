//////////////////////////////////////////////////////////////////////////////
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


namespace acme
{


   class CLASS_DECL_ACME chronometer
   {
   public:


      bool              m_bStopped; /// stop flag
      ::duration        m_durationStart;
      ::duration        m_durationEnd;


      chronometer();                                  // default constructor
      ~chronometer();                                 // default destructor


      void        start();                            // start timer
      void        stop();                             // stop the timer
      duration    elapsed();                          // get elapsed time in second

      duration    now();                              // get time in second

   };


} // namespace acme



