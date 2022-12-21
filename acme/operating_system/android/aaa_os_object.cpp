#include "framework.h"
#include "_os_impl.h"


extern thread_local JNIEnv* t_pjnienv;


os_object::os_object(jobject jobject)
{

   ::jclass jclass = t_pjnienv->GetObjectClass(jobject);

   m_jclass = (::jclass) t_pjnienv->NewGlobalRef(jclass);

   m_jobject = t_pjnienv->NewGlobalRef(jobject);

}


os_object::~os_object()
{

   t_pjnienv->DeleteGlobalRef(m_jobject);

   t_pjnienv->DeleteGlobalRef(m_jclass);

}


jfieldID os_object::field_str(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "Ljava/lang/String;");

}


jfieldID os_object::field_b(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "Z");

}


jfieldID os_object::field_uch(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "B");

}


jfieldID os_object::field_ch(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "C");

}


jfieldID os_object::field_sh(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "S");

}


jfieldID os_object::field_i(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "I");

}


jfieldID os_object::field_l(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "J");

}



jfieldID os_object::field_f(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "F");

}


jfieldID os_object::field_d(const ::scoped_string & scopedstr)
{

   return t_pjnienv->GetFieldID(m_jclass, psz, "D");

}


void os_object::set_str(const ::scoped_string & scopedstrField, const ::scoped_string & scopedstr)
{

   set_str(field_str(pszField), psz);

}


string os_object::get_str(const ::scoped_string & scopedstrField)
{

   return get_str(field_str(pszField));

}


void os_object::set_b(const ::scoped_string & scopedstrField, bool b)
{

   set_b(field_b(pszField), b);

}


bool os_object::get_b(const ::scoped_string & scopedstrField)
{

   return get_b(field_b(pszField));

}



void os_object::set_uch(const ::scoped_string & scopedstrField, byte b)
{

   set_uch(field_uch(pszField), b);

}


byte os_object::get_uch(const ::scoped_string & scopedstrField)
{

   return get_uch(field_uch(pszField));

}



void os_object::set_ch(const ::scoped_string & scopedstrField, char ch)
{

   set_ch(field_ch(pszField), ch);

}


char os_object::get_ch(const ::scoped_string & scopedstrField)
{

   return get_ch(field_ch(pszField));

}



void os_object::set_sh(const ::scoped_string & scopedstrField, short sh)
{

   set_sh(field_sh(pszField), sh);

}


short os_object::get_sh(const ::scoped_string & scopedstrField)
{

   return get_sh(field_sh(pszField));

}



void os_object::set_i(const ::scoped_string & scopedstrField, int i)
{

   set_i(field_i(pszField), i);

}



int os_object::get_i(const ::scoped_string & scopedstrField)
{

   return get_i(field_i(pszField));

}



void os_object::set_l(const ::scoped_string & scopedstrField, long long ll)
{

   set_l(field_l(pszField), ll);

}



long long os_object::get_l(const ::scoped_string & scopedstrField)
{

   return get_l(field_l(pszField));

}


void os_object::set_f(const ::scoped_string & scopedstrField, float f)
{

   set_f(field_f(pszField), f);

}


float os_object::get_f(const ::scoped_string & scopedstrField)
{

   return get_f(field_f(pszField));

}


void os_object::set_d(const ::scoped_string & scopedstrField, double d)
{

   set_d(field_d(pszField), d);

}


double os_object::get_d(const ::scoped_string & scopedstrField)
{

   return get_d(field_d(pszField));

}


void os_object::set_str(jfieldID jfieldid, const ::scoped_string & scopedstr)
{

   jstring jstring = t_pjnienv->NewStringUTF(psz);

   if (!jstring)
   {

      return;

   }

   t_pjnienv->SetObjectField(m_jobject, jfieldid, jstring);

   t_pjnienv->DeleteLocalRef(jstring);

}


string os_object::get_str(jfieldID jfieldid)
{

   jstring jstring = (::jstring) t_pjnienv->GetObjectField(m_jobject, jfieldid);

   string str = get_string(jstring);

   t_pjnienv->DeleteLocalRef(jstring);

   return str;

}


void os_object::set_b(jfieldID fid, bool b)
{

   t_pjnienv->SetBooleanField(m_jobject, fid, b);

}


bool os_object::get_b(jfieldID fid)
{

   return t_pjnienv->GetBooleanField(m_jobject, fid);

}


void os_object::set_uch(jfieldID fid, byte b)
{

   t_pjnienv->SetByteField(m_jobject, fid, b);

}


byte os_object::get_uch(jfieldID fid)
{

   return t_pjnienv->GetByteField(m_jobject, fid);

}


void os_object::set_ch(jfieldID fid, char ch)
{

   t_pjnienv->SetCharField(m_jobject, fid, ch);

}


char os_object::get_ch(jfieldID fid)
{

   return t_pjnienv->GetCharField(m_jobject, fid);

}


void os_object::set_sh(jfieldID fid, short sh)
{

   t_pjnienv->SetShortField(m_jobject, fid, sh);

}


short os_object::get_sh(jfieldID fid)
{

   return t_pjnienv->GetShortField(m_jobject, fid);

}


void os_object::set_i(jfieldID fid, int i)
{

   t_pjnienv->SetIntField(m_jobject, fid, i);

}


int os_object::get_i(jfieldID fid)
{

   return t_pjnienv->GetIntField(m_jobject, fid);

}



void os_object::set_l(jfieldID fid, long long ll)
{

   t_pjnienv->SetLongField(m_jobject, fid, ll);

}


long long os_object::get_l(jfieldID fid)
{

   return t_pjnienv->GetLongField(m_jobject, fid);

}


void os_object::set_f(jfieldID fid, float f)
{

   t_pjnienv->SetFloatField(m_jobject, fid, f);

}


float os_object::get_f(jfieldID fid)
{

   return t_pjnienv->GetFloatField(m_jobject, fid);

}



void os_object::set_d(jfieldID fid, double d)
{

   t_pjnienv->SetDoubleField(m_jobject, fid, d);

}


double os_object::get_d(jfieldID fid)
{

   return t_pjnienv->GetDoubleField(m_jobject, fid);

}




