#pragma once


class CLASS_DECL_CORE numeric_parser_exception:
   virtual public ::exception::exception
{
public:


   numeric_parser_exception(const char * pszMessage = nullptr);
   virtual ~numeric_parser_exception();


};


CLASS_DECL_CORE bool get_avoid_numeric_parser_exception();
CLASS_DECL_CORE bool throw_numeric_parser_exception(const string & strMessage);


class CLASS_DECL_CORE avoid_numeric_parser_exception
{
public:

   iptr m_iBefore;

   avoid_numeric_parser_exception();
   virtual ~avoid_numeric_parser_exception();

};