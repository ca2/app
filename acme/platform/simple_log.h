#pragma once


class CLASS_DECL_ACME simple_log :
   virtual public generic
{
   public:


      simple_log *         m_psimplelog;
      index                m_iLogTarget;


      simple_log();
      simple_log(simple_log * psimplelog, index iLogTarget);
      virtual ~simple_log();


      virtual void log_line(string str, index iLogTarget);
      virtual void log_line(string str);


};


