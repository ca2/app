#pragma once


namespace file
{


   class CLASS_DECL_AURA path_object :
      virtual public generic_object,
      virtual public path
   {
   public:

      path_object() {}
      path_object(::object*) {}
      path_object(const ::file::path& path) : ::file::path(path) {}
      path_object(::file::path&& path) : ::file::path(::move(path)) {}

      virtual ~path_object();


      virtual void exchange(::stream& s) override;

      virtual strsize sz_len() const override;
      virtual void to_sz(char* sz, strsize size) const override;
      virtual void to_string(string& str) const override;

      using generic_object::set;
      using generic_object::has;

      using path::set;
      using path::has;

   };


   using path_pointer = __pointer(path_object);


} // namespace file



