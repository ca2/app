#pragma once


class CLASS_DECL_ACID index_out_of_bounds :
   public ::exception
{
public:


   index_out_of_bounds(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~index_out_of_bounds();


};



