#pragma once


class CLASS_DECL_ACID not_supported_exception :
   virtual public interface_only_exception
{
public:


   not_supported_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~not_supported_exception();


};
