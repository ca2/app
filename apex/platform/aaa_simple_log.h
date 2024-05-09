#pragma once


class CLASS_DECL_APEX simple_log :
   virtual public object
{
   public:


      simple_log *         m_psimplelog;
      ::collection::index                m_iLogTarget;


      simple_log();
      simple_log(simple_log * psimplelog, ::collection::index iLogTarget);
      virtual ~simple_log();


      virtual void log_line(string str, ::collection::index iLogTarget);
      virtual void log_line(string str);


};


