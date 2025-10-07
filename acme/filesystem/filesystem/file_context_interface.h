// From file_context.h by camilo on 2024-06-28 09:39 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME file_context_interface :
   virtual public object
{
public:


   ::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;

   virtual string safe_get_string(const ::payload& payloadFile, ::e_status* pestatus = nullptr);
   virtual void safe_get_memory(const ::payload& payloadFile, memory_base& mem, ::e_status* pestatus = nullptr);
   virtual ::memory safe_get_memory(const ::payload& payloadFile);
   virtual string_array_base safe_get_lines(const ::payload& payloadFile, ::e_status* pestatus = nullptr);


};



