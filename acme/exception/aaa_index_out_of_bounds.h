#pragma once


class CLASS_DECL_ACME index_out_of_bounds :
   public ::exception
{
public:


   index_out_of_bounds(const scoped_string & strMessage = nullptr);
   virtual ~index_out_of_bounds();


};



