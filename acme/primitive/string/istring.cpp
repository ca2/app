#include "framework.h"


istring::istring(::generic * pobject)
{

   m_papp = ::get_context_application(pobject);

}


istring::~istring()
{


}


void istring::update_string()
{

   m_str = get_context_application()->lstr(m_strTemplate, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{

   m_strTemplate = psz;

   update_string();

   return *this;

}


