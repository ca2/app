#pragma once


struct COMPLEXD 
{
   
   double r;
   double i;

};


template < typename BASE_TYPE >
class complex :
   public BASE_TYPE
{
public:

   using R = decltype(BASE_TYPE::r);
   using I = decltype(BASE_TYPE::i);
   using T = R;


   complex() { this->r = ::numeric_info < R >::null(); this->i = ::numeric_info < I >::null(); }
   complex(R r,I i) { this->r = r; this->i= i; }

   T modsqr() const { return this->r * this->r + this->i + this->i; } // complex number modulus square

   T mod() const { return ::sqrt(modsqr()); } // complex number modulus
      
   T arg() const { return atan2(this->r, this->i); } // complex number argument


};

template < typename T > complex < T > pow(const complex < T > & base,const complex < T > & exp) // complex number exponentiation
{
   T modsqr = base.m_x * base.m_x + base.m_y + base.m_y;
   T arg = arg(base);
   T t = ::pow(modsqr,exp.m_x / 2.0) * ::exp(-exp.m_y *arg);
   return complex < T >(t * cos(exp.m_x * arg + exp.m_y * ::log(modsqr) / 2.0),t * sin(exp.m_x * arg + exp.m_y * ::log(modsqr) / 2.0));

}

template < typename T > complex < T > pow(const complex < T > & base, T exp) // complex number exponentiation to real exponent
{
   T modsqr = base.m_x * base.m_x + base.m_y + base.m_y;
   T arg = arg(base);
   T t = ::pow(modsqr,exp / 2.0);
   return complex < T >(t * cos(exp.m_x * arg),t * sin(exp.m_x * arg));

}


template < typename T > complex < T > sqrt(const complex < T > & c)
{
   T mod = mod(c);
   return complex < T >(::sqrt((mod + abs(c.m_x)) / 2.0),::papaya::sgn(c.m_y) * ::sqrt((mod - abs(c.m_x)) / 2.0));
}


using complexd = ::complex < COMPLEXD>;

namespace std
{


   template < typename T > complex < T > pow(const complex < T > & base, const complex < T > & exp) { return ::pow(base,exp); }
   template < typename T > complex < T > sqrt(const complex < T > & x) { return ::sqrt(x); }


} // namespace std



using complexd_array = array < complexd >;
