#pragma once


class CLASS_DECL_AURA progress_listener :
   virtual public object
{
public:

   virtual void on_progress(double dRate);

};



class CLASS_DECL_AURA int_progress :
   virtual public int_scalar_listener
{
public:


   double               m_dProgressStart;
   double               m_dProgressEnd;
   int_scalar           m_scalar;
   progress_listener *  m_plistener;


   int_progress();
   virtual ~int_progress();

   virtual void trace_progress();

   virtual void trace_progress(i64 iStep);

   virtual void progress_step();

   virtual void on_set_scalar(int_scalar_source * psource,e_scalar escalar,i64 iValue,int iFlags);

   int_scalar & operator ()(){ return m_scalar;  }

};




class CLASS_DECL_AURA progress_control :
   virtual public double_scalar_source,
   virtual public object
{
public:


   string                  m_strStatus;
   ::index                 m_iStep;
   ::count                 m_iStepCount;
   string                  m_strTitle;


   progress_control();
   virtual ~progress_control();


   virtual void on_set_scalar(e_scalar escalar, double d, int iFlags);
   virtual void get_scalar_minimum(e_scalar escalar, double& d);
   virtual void get_scalar(e_scalar escalar, double& d);
   virtual void get_scalar_maximum(e_scalar escalar, double& d);

   virtual void format_status(const char* pszFormat);

   virtual void redraw();
   virtual void step();

   virtual void close_progress();


};


class CLASS_DECL_AURA progress :
   public __pointer(::progress_control)
{
public:

   progress(::user::interaction * puiParent, const char* pszTitle, int iStepCount);

   ~progress()
   {

      m_p->close_progress();

      release();

   }

};
