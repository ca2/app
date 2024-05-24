#pragma once


//#include "exception.h"


class CLASS_DECL_ACID assert_exception :
   public ::exception
{
public:


   string m_strFile;
   long m_lLine;


   assert_exception(const ::scoped_string & scopedstrFile, long lLine);
   virtual ~assert_exception();


};



