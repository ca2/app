#pragma once


class CLASS_DECL_AURA progress_listener :
   virtual public object
{
public:

   virtual void on_progress(::f64 dRate);

};



class CLASS_DECL_AURA int_progress :
   virtual public int_scalar_listener
{
public:


   ::f64               m_dProgressStart;
   ::f64               m_dProgressEnd;
   int_scalar           m_scalar;
   progress_listener *  m_plistener;


   int_progress();
   virtual ~int_progress();

   virtual void trace_progress();

   virtual void trace_progress(::i64 iStep);

   virtual void progress_step();

   virtual void on_set_scalar(int_scalar_source * psource,e_scalar escalar,::i64 iValue,::i32 iFlags);

   int_scalar & operator ()(){ return m_scalar;  }

};




class CLASS_DECL_AURA progress_control :
   virtual public f64_scalar_source,
   virtual public object
{
public:


   string                  m_strStatus;
   ::collection::index                 m_iStep;
   ::collection::count                 m_iStepCount;
   string                  m_strTitle;


   progress_control();
   virtual ~progress_control();


   virtual void on_set_scalar(e_scalar escalar, ::f64 d, ::i32 iFlags);
   virtual void get_scalar_minimum(e_scalar escalar, ::f64& d);
   virtual void get_scalar(e_scalar escalar, ::f64& d);
   virtual void get_scalar_maximum(e_scalar escalar, ::f64& d);

   virtual void format_status(const ::scoped_string & scopedstrFormat);

   virtual void redraw();
   virtual void step();

   virtual void close_progress();


};


class CLASS_DECL_AURA progress :
   public ::pointer<::progress_control>
{
public:

   progress(::user::interaction * puiParent, const ::scoped_string & scopedstrTitle, ::i32 iStepCount);

   ~progress()
   {

      m_p->close_progress();

      release();

   }

};
