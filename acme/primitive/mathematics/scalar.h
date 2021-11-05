#pragma once

template < typename SCALAR >
inline string get_default_scalar_format()
{
   return "";
}


template <  >
inline string get_default_scalar_format < double >()
{
   return "%d";
}

template <  >
inline string get_default_scalar_format < i64 >()
{
   return "%lli";
}

namespace str
{

   template < typename FORMATABLE >
   inline string printf(const ::string & strFormat, const FORMATABLE & f)
   {

      string str;

      str.format(strFormat,f);

      return str;

   }


} // namespace str



template < typename SCALAR >
class scalar_source :
   virtual public matter
{
public:


   class listener :
      virtual public matter
   {
   public:


      virtual void on_set_scalar(scalar_source * psource,e_scalar escalar,SCALAR d,int iFlags);


   };


   listener *           m_plistener;
   ::id                   m_id;

   scalar_source();


   bool set_scalar(e_scalar escalar,SCALAR d,bool bForce = false,int iFlags = scalar_none);
   bool constrain_scalar(e_scalar escalar,SCALAR & d);
   void increment_scalar(e_scalar  escalar,SCALAR iIncrement);
   double get_rate(e_scalar escalar,double dDefault = 0.0);
   bool set_rate(e_scalar escalar,double dValue,int iFlags);
   bool constrain(e_scalar escalar,SCALAR & d);
   bool contains(e_scalar escalar,SCALAR d);



   virtual void on_set_scalar(e_scalar escalar,SCALAR d,int iFlags);
   virtual void get_scalar_minimum(e_scalar escalar,SCALAR & d);
   virtual void get_scalar(e_scalar escalar,SCALAR & d);
   virtual void get_scalar_maximum(e_scalar escalar,SCALAR & d);

};




class CLASS_DECL_ACME scalar_base
{
public:


   string            m_strFormat;


   virtual double get_rate(double dDefault = 0.0);

   virtual bool set_rate(double dRate, int iFlags);

   string Format(const ::string & strFormat);

   string to_string() { return Format(m_strFormat); }


};













template < typename SCALAR >
class  scalar :
   virtual public scalar_base
{
public:


   scalar(scalar_source < SCALAR > * psource = nullptr,e_scalar escalar = scalar_none,const ::string & strFormat = ::get_default_scalar_format< SCALAR>());


   scalar_source < SCALAR > *    m_psource;
   e_scalar                      m_escalar;

   void set(SCALAR dValue);
   SCALAR get();

   virtual double get_rate(double dDefault = 0.0);
   virtual bool set_rate(double dRate,int iFlags);


   SCALAR maximum();
   SCALAR minimum();


   bool is_null() const { return m_psource == nullptr || m_escalar == scalar_none; }
   bool is_setl() const { return !is_null(); }


   operator SCALAR () { return get(); }

   scalar & operator = (SCALAR dValue) { set(dValue); return *this; }

   virtual string printf(const ::string & strFormat);

   void increment(SCALAR iValue = ::numeric_info<SCALAR>::unitary()) { set(get() + iValue); }
   void decrement(SCALAR iValue = ::numeric_info<SCALAR>::unitary()) { set(get() - iValue); }

   scalar & operator ++(int) { increment(); return *this; }
   scalar & operator --(int) { decrement(); return *this; }


};






























template < typename SCALAR >
void scalar_source < SCALAR > ::listener::on_set_scalar(scalar_source * psource,e_scalar escalar,SCALAR iValue,int iFlags)
{

   __UNREFERENCED_PARAMETER(psource);
   __UNREFERENCED_PARAMETER(escalar);
   __UNREFERENCED_PARAMETER(iValue);
   __UNREFERENCED_PARAMETER(iFlags);

}

template < typename SCALAR >
scalar_source < SCALAR > ::scalar_source()
{

   m_plistener = nullptr;

}

template < typename SCALAR >
bool scalar_source < SCALAR > ::set_scalar(e_scalar escalar,SCALAR iValue,bool bForce,int iFlags)
{

   if(!bForce)
   {
      if(!contains(escalar,iValue))
         return false;
   }

   on_set_scalar(escalar,iValue,iFlags);

   if(m_plistener != nullptr)
   {

      m_plistener->on_set_scalar(this,escalar,iValue,iFlags);

   }

   return true;

}
template < typename SCALAR >
bool scalar_source < SCALAR > ::constrain_scalar(e_scalar escalar,SCALAR & iValue)
{

   bool bConstrain;

   if((bConstrain = constrain(escalar,iValue)))
   {

      SCALAR i = 0;

      get_scalar(escalar,i);

      if(iValue == i)
         return true;

   }

   bool bSet = set_scalar(escalar,iValue);

   return bConstrain && bSet;

}
template < typename SCALAR >
void scalar_source < SCALAR > ::increment_scalar(e_scalar escalar,SCALAR iIncrement)
{

   SCALAR i = 0;

   get_scalar(escalar,i);

   set_scalar(escalar,i + iIncrement);

}
template < typename SCALAR >
bool scalar_source < SCALAR > ::contains(e_scalar escalar,SCALAR iValue)
{

   SCALAR iMin = 0;

   get_scalar_minimum(escalar,iMin);

   if(iValue < iMin)
      return false;

   SCALAR iMax = 0;

   get_scalar_maximum(escalar,iMax);

   if(iValue > iMax)
      return false;

   return true;

}

template < typename SCALAR >
bool scalar_source < SCALAR > ::constrain(e_scalar escalar,SCALAR & iValue)
{

   SCALAR iMin = 0;

   get_scalar_minimum(escalar,iMin);

   if(iValue < iMin)
   {

      iValue = iMin;

      return true;

   }

   SCALAR iMax = 0;

   get_scalar_maximum(escalar,iMax);

   if(iValue > iMax)
   {

      iValue = iMax;

      return true;

   }

   return false;

}


template < typename SCALAR >
void scalar_source < SCALAR > ::on_set_scalar(e_scalar escalar,SCALAR iValue,int iFlags)
{

   __UNREFERENCED_PARAMETER(escalar);

   __UNREFERENCED_PARAMETER(iValue);

   __UNREFERENCED_PARAMETER(iFlags);

   // does nothing by default.

}
template < typename SCALAR >
void scalar_source < SCALAR > ::get_scalar_minimum(e_scalar escalar,SCALAR & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   i = 0; // by default

}
template < typename SCALAR >
void scalar_source < SCALAR > ::get_scalar(e_scalar escalar,SCALAR & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   i = 1; // by default

}
template < typename SCALAR >
void scalar_source < SCALAR > ::get_scalar_maximum(e_scalar escalar,SCALAR & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   i = 1; // by default

}
template < typename SCALAR >
double scalar_source < SCALAR > ::get_rate(e_scalar escalar,double dDefault)
{

   SCALAR iMax = 0;

   get_scalar_maximum(escalar,iMax);

   SCALAR iMin = 0;

   get_scalar_minimum(escalar,iMin);

   SCALAR iDenominator = iMax - iMin;

   if(iDenominator == 0)
      return dDefault;

   SCALAR iVal = 0;

   get_scalar(escalar,iVal);

   SCALAR iNumerator = iVal - iMin;

   return (double)iNumerator / (double)iDenominator; // aproximate value along iDenominator and iNumerator evaluation

}

template < typename SCALAR >
bool scalar_source < SCALAR > ::set_rate(e_scalar escalar,double dValue,int iFlags)
{

   if(dValue < 0.0)
      return false;

   if(dValue > 1.0)
      return false;

   SCALAR iMax = 0;

   get_scalar_maximum(escalar,iMax);

   SCALAR iMin = 0;

   get_scalar_minimum(escalar,iMin);

   SCALAR iDenominator = iMax - iMin;

   on_set_scalar(escalar,(SCALAR) (dValue * iDenominator) + iMin,iFlags);

   return true;

}



template < typename SCALAR >
scalar < SCALAR > ::scalar(scalar_source<SCALAR> * psource,e_scalar escalar,const ::string & strFormat)
{

   m_psource = psource;
   m_escalar = escalar;
   m_strFormat = strFormat;

}

template < typename SCALAR >
void scalar < SCALAR > ::set(SCALAR iValue)
{

   if(m_psource == nullptr || m_escalar == scalar_none)
      return;

   m_psource->set_scalar(m_escalar,iValue);

}

template < typename SCALAR >
SCALAR scalar < SCALAR > ::get()
{

   if(m_psource == nullptr || m_escalar == scalar_none)
      return 0;

   SCALAR i = 0;

   m_psource->get_scalar(m_escalar,i);

   return i;

}

template < typename SCALAR >
double scalar < SCALAR > ::get_rate(double dDefault)
{

   if(m_psource == nullptr || m_escalar == scalar_none)
      return dDefault;

   return m_psource->get_rate(m_escalar,dDefault);

}

template < typename SCALAR >
bool scalar < SCALAR > ::set_rate(double dValue,int iFlags)
{

   if(m_psource == nullptr || m_escalar == scalar_none)
      return false;

   return m_psource->set_rate(m_escalar,dValue,iFlags);

}

template < typename SCALAR >
SCALAR scalar < SCALAR > ::minimum()
{

   if(is_null())
      return 0;

   SCALAR i = 0;

   m_psource->get_scalar_minimum(m_escalar,i);

   return i;

}


template < typename SCALAR >
SCALAR scalar < SCALAR > ::maximum()
{

   if(is_null())
      return 0;

   SCALAR i = 0;

   m_psource->get_scalar_maximum(m_escalar,i);

   return i;

}




template < typename SCALAR >
string scalar < SCALAR > ::printf(const ::string & strFormat)
{

   return ::str::printf(strFormat,get());

}




using double_scalar_source = scalar_source < double >;
using int_scalar_source  = scalar_source < i64 >;

using double_scalar_listener = scalar_source < double >::listener;
using int_scalar_listener  = scalar_source < i64 >::listener;


using double_scalar = scalar < double >;
using int_scalar  = scalar < i64 >;



