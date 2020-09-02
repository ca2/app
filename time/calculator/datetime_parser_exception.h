#pragma once


class CLASS_DECL_CA2_TIME datetime_parser_exception:
   virtual public simple_exception
{
public:


   datetime_parser_exception(::aura::application * papp,const string & strMessage);
   virtual ~datetime_parser_exception();


};


CLASS_DECL_CA2_TIME bool get_avoid_datetime_parser_exception();
CLASS_DECL_CA2_TIME bool throw_datetime_parser_exception(const string & strMessage);


class CLASS_DECL_CA2_TIME avoid_datetime_parser_exception
{
public:

   int_ptr m_iBefore;

   avoid_datetime_parser_exception();
   virtual ~avoid_datetime_parser_exception();

};