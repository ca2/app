#pragma once


//class CLASS_DECL_CA2_TIME datetime_parsing_exception:
//   virtual public ::exception
//{
//public:
//
//
//   datetime_parsing_exception(const ::scoped_string & scopedstrMessage);
//   virtual ~datetime_parsing_exception();
//
//
//};



//
//class CLASS_DECL_CA2_TIME avoid_datetime_parsing_exception
//{
//public:
//
//   bool m_bBefore;
//
//   avoid_datetime_parsing_exception();
//   virtual ~avoid_datetime_parsing_exception();
//
//};


class CLASS_DECL_ACME avoid_datetime_parsing_exception :
   public ___keep_task_flag
{
public:


   //bool m_bAvoidParsingExceptionPrevious;


   avoid_datetime_parsing_exception() : ___keep_task_flag(e_task_flag_avoid_datetime_parsing_exception) {}
   //   ~avoid_parsing_exception() override;


};
