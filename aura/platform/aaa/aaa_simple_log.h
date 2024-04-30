#pragma once


class CLASS_DECL_AURA simple_log :
   virtual public object
{
   public:


      simple_log *         m_psimplelog;
      ::raw::index                m_iLogTarget;


      simple_log();
      simple_log(simple_log * psimplelog, ::raw::index iLogTarget);
      virtual ~simple_log();


      virtual void log_line(string str, ::raw::index iLogTarget);
      virtual void log_line(string str);


};


