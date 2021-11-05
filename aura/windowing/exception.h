// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
// X11Exception.h
// C++ exception that wraps X11 errors.
// Copyright (C) 2008 Jay Bromley <jbromley@gmail.com>
//
// $Id: X11Exception.h 26 2008-04-09 08:47:11Z jay $
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA exception
   {
   public:


      exception() : m_strReason("unknown") {}
      exception(const string &what) : m_strReason(what) {}
      virtual ~exception() throw() {};


      virtual const char * what() const throw() { return m_strReason.c_str(); }


   private:


      string m_strReason;


   };


} // namespace windowing



