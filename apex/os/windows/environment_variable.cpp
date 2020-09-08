#include "framework.h"
#include "environment_variable.h"


// See property_set::parse_environment_variable

//
//CLASS_DECL_APEX void parse(environment_variable_value_array & array, const string_array & straEnvironment)
//{
//   
//   for (auto & strEnvironment : straEnvironment)
//   {
//
//      auto find = strEnvironment.find("=");
//
//      if (find <= 0)
//      {
//         
//         continue;
//
//      }
//
//      environment_variable_value variablevalue;
//
//      // get the left hand side (LHS) of "=" in the string
//      variablevalue.m_element1 = strEnvironment.Left(find);
//
//      variablevalue.m_element2 = strEnvironment.Mid(find + 1);
//
//      array.add(variablevalue);
//
//   }
//
//}
//
//
//
