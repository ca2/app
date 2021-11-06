#pragma once


class CLASS_DECL_ACME parsing_exception:
   public ::exception
{
public:


   parsing_exception(const char * pszMessage);
   ~parsing_exception() override;


};


CLASS_DECL_ACME bool should_avoid_parsing_exception();
//CLASS_DECL_ACME void set_avoid_parsing_exception(bool bSet);
CLASS_DECL_ACME bool throw_parsing_exception(const ::string & strMessage);


class CLASS_DECL_ACME avoid_parsing_exception :
   public ___keep_task_flag
{
public:

   
   //bool m_bAvoidParsingExceptionPrevious;


   avoid_parsing_exception() : ___keep_task_flag(e_task_flag_avoid_parsing_exception) {}
//   ~avoid_parsing_exception() override;
   

};



class network_payload_parsing_exception :
   public ::parsing_exception
{
public:

   network_payload_parsing_exception(const char * pszMessage = nullptr);
   virtual ~network_payload_parsing_exception();

};


CLASS_DECL_ACME bool throw_network_payload_parsing_exception(const ::string & strMessage);
