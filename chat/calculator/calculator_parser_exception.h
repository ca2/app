#pragma once


class CLASS_DECL_CA2_MATH numeric_parser_exception:
   virtual public ::exception::exception
{
public:


   numeric_parser_exception(::object * pobject,const string & strMessage);
   virtual ~numeric_parser_exception();


};


CLASS_DECL_CA2_MATH bool get_avoid_numeric_parser_exception();
CLASS_DECL_CA2_MATH bool throw_numeric_parser_exception(const string & strMessage);


class CLASS_DECL_CA2_MATH avoid_numeric_parser_exception
{
public:

   iptr m_iBefore;

   avoid_numeric_parser_exception();
   virtual ~avoid_numeric_parser_exception();

};