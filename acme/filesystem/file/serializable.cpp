#include "framework.h"


namespace file
{


   //element::element()
   //{

   //}

   //void element::write(ostream & ostream)
   //{

   //   ((const element *) this)->write(ostream);

   //}

   //void element::write(ostream & ostream) const
   //{
   //
   //   ((element *) this)->write(ostream);

   //}

   //void element::read(istream & istream)
   //{

   //}

} // namespace file












// CLASS_DECL_ACME bool file_put(const char * path, ::element & s, ::acme::application * papp)
// {

//    try
//    {

//       if (papp == nullptr)
//       {

//          papp = get_context_application();

//       }

//       if (papp == nullptr)
//       {

//          return false;

//       }

//       file_pointer pfile = App(papp).file().get_file(path, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory | ::file::share_exclusive);

//       if (pfile.is_null())
//       {

//          return false;

//       }

//       ::stream writer((::file::file *) pfile);

//       writer << s;

//       return true;

//    }
//    catch (...)
//    {


//    }

//    return false;

// }


// CLASS_DECL_ACME bool file_as(::element & s, const char * path, ::acme::application * papp)
// {

//    try
//    {

//       if (papp == nullptr)
//       {

//          papp = get_context_application();

//       }

//       if (papp == nullptr)
//       {

//          return false;

//       }

//       file_pointer pfileInput = App(papp).file().get_reader(path, ::file::share_deny_write);

//       if (pfileInput.is_null())
//       {

//          return false;

//       }

//       ::stream streamInput((::file::file *) pfileInput);

//       streamInput >> s;

//       return true;

//    }
//    catch (...)
//    {


//    }

//    return false;

// }






