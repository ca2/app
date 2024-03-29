//////////////////////////////////////////////////////////////////////////////
// chronometer.cpp
// =========
// High Resolution chronometer.
// This chronometer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (ca) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "chronometer.h"



namespace acme
{

   ///////////////////////////////////////////////////////////////////////////////
   // constructor
   ///////////////////////////////////////////////////////////////////////////////
   chronometer::chronometer()
   {

      m_bStopped = false;

   }



   ///////////////////////////////////////////////////////////////////////////////
   // distructor
   ///////////////////////////////////////////////////////////////////////////////
   chronometer::~chronometer()
   {
   }



   ///////////////////////////////////////////////////////////////////////////////
   // start chronometer.
   // startCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void chronometer::start()
   {
      
      m_bStopped = false; // reset stop flag

      m_timeStart.Now();

   }



   ///////////////////////////////////////////////////////////////////////////////
   // stop the chronometer.
   // endCount will be set at this point.
   ///////////////////////////////////////////////////////////////////////////////
   void chronometer::stop()
   {
      
      m_bStopped = true; // set chronometer stopped flag

      m_timeEnd.Now();

   }



   ///////////////////////////////////////////////////////////////////////////////
   // compute elapsed time in micro-second resolution.
   // other getElapsedTime will call this first, then convert to correspond resolution.
   ///////////////////////////////////////////////////////////////////////////////
   class time chronometer::elapsed()
   {

      if (!m_bStopped)
      {

         stop();

      }

      return m_timeEnd - m_timeStart;

   }


   class time chronometer::now()
   {

      return ::time::now();

   }



} // namespace acme



