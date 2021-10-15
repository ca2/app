#pragma once


class CLASS_DECL_AXIS numeric_parser_exception:
   public ::exception
{
public:


   numeric_parser_exception(const ::string & pszMessage = nullptr);
   ~numeric_parser_exception() override;


};


CLASS_DECL_AXIS bool get_avoid_numeric_parser_exception();
CLASS_DECL_AXIS bool throw_numeric_parser_exception(const ::string & strMessage);


class CLASS_DECL_AXIS avoid_numeric_parser_exception : 
   public ___keep_task_flag
{
public:

   avoid_numeric_parser_exception() : ___keep_task_flag(e_task_flag_avoid_numeric_parser_exception) {}
   //virtual ~avoid_numeric_parser_exception();

};