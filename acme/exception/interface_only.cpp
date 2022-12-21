#include "framework.h"
#include "interface_only.h"


interface_only::interface_only(const ::scoped_string & scopedstrMessage, const ::e_status & estatus) :
   not_implemented(scopedstrMessage, estatus)
{

}



interface_only::~interface_only()
{

}




//
//CLASS_DECL_ACME void throw_interface_only_exception(const ::scoped_string & scopedstr)
//{
//
//   throw ::exception(interface_only_exception(psz));
//
//}
//





