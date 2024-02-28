#pragma once


namespace database
{

   
   class client;
   class server;
   class client_array;

   class database;
   class dataset;

   class field;

   using field_array = pointer_array < field >;

   using row = payload_array;

   using row_array = pointer_array < row >;

   class result_set;

   class parameter_list;

} // namespace database



#include "_constant.h"

