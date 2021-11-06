#pragma once


class CLASS_DECL_CORE os_object :
   virtual public ::matter
{
public:


   jobject     m_jobject;
   jclass      m_jclass;


   os_object(jobject jobject);
   virtual ~os_object();


   jfieldID field_str(const ::string &psz);
   jfieldID field_b(const ::string & psz);
   jfieldID field_uch(const ::string & psz);
   jfieldID field_ch(const ::string & psz);
   jfieldID field_sh(const ::string & psz);
   jfieldID field_i(const ::string & psz);
   jfieldID field_l(const ::string & psz);
   jfieldID field_f(const ::string & psz);
   jfieldID field_d(const ::string & psz);


   void set_str(jfieldID jfieldid, const ::string & psz);

   string get_str(jfieldID jfieldid);

   void set_b(jfieldID jfieldid, bool b);

   bool get_b(jfieldID jfieldid);

   void set_uch(jfieldID jfieldid, byte b);

   byte get_uch(jfieldID jfieldid);

   void set_ch(jfieldID jfieldid, char ch);

   char get_ch(jfieldID jfieldid);

   void set_sh(jfieldID jfieldid, short sh);

   short get_sh(jfieldID jfieldid);

   void set_i(jfieldID jfieldid, int i);

   int get_i(jfieldID jfieldid);

   void set_l(jfieldID jfieldid, long long ll);

   long long get_l(jfieldID jfieldid);

   void set_f(jfieldID jfieldid, float f);

   float get_f(jfieldID jfieldid);

   void set_d(jfieldID jfieldid, double d);

   double get_d(jfieldID jfieldid);

   void set_str(const ::string & pszField, const ::string & psz);

   string get_str(const ::string & pszField);

   void set_b(const ::string & pszField, bool boolean);

   bool get_b(const ::string & pszField);

   void set_uch(const ::string & pszField, byte b);

   byte get_uch(const ::string & pszField);

   void set_ch(const ::string & pszField, char ch);

   char get_ch(const ::string & pszField);

   void set_sh(const ::string & pszField, short sh);

   short get_sh(const ::string & pszField);

   void set_i(const ::string & pszField, int i);

   int get_i(const ::string & pszField);

   void set_l(const ::string & pszField, long long ll);

   long long get_l(const ::string & pszField);

   void set_f(const ::string & pszField, float f);

   float get_f(const ::string & pszField);

   void set_d(const ::string & pszField, double f);

   double get_d(const ::string & pszField);


};


#define JX(type, name) \
jfieldID m_fid##name = field_##type("m_" # type # name); \
template < typename T > \
inline void set##name(T && t) { set_##type(m_fid##name, t); } \
inline auto get##name() { return get_##type(m_fid##name); }

