#pragma once


namespace file
{


   class CLASS_DECL_ACME path_object :
      virtual public elemental,
      virtual public path
   {
   public:

      path_object() {}
      path_object(::elemental*) {}
      path_object(const ::file::path& path) : ::file::path(path) {}
      path_object(::file::path&& path) : ::file::path(::move(path)) {}

      virtual ~path_object();


      virtual void exchange(::stream& s) override;

      virtual strsize sz_len() const override;
      virtual void to_sz(char* sz, strsize size) const override;
      virtual void to_string(const string_exchange& string) const override;

      using elemental::set;
      using elemental::has;

      using path::set;
      using path::has;

   };


   using path_pointer = __pointer(path_object);


} // namespace file



