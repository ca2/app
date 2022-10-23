#include "framework.h"
#include "interface_only.h"


interface_only::interface_only(const char * pszMessage, const ::e_status & estatus) :
   not_implemented(pszMessage, estatus)
{

}



interface_only::~interface_only()
{

}




//
//CLASS_DECL_ACME void throw_interface_only_exception(const char * psz)
//{
//
//   throw ::exception(interface_only_exception(psz));
//
//}
//





