#include "framework.h"


namespace file
{


   //matter::matter()
   //{

   //}

   //void matter::write(ostream & ostream)
   //{

   //   ((const matter *) this)->write(ostream);

   //}

   //void matter::write(ostream & ostream) const
   //{
   //
   //   ((matter *) this)->write(ostream);

   //}

   //void matter::read(istream & istream)
   //{

   //}

} // namespace file












// CLASS_DECL_ACME bool file_put(const char * path, ::matter & s, ::acme::application * papp)
// {

//    try
//    {

//       if (papp == nullptr)
//       {

//          papp = get_application();

//       }

//       if (papp == nullptr)
//       {

//          return false;

//       }

//       file_pointer pfile = App(papp).file().get_file(path, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_share_exclusive);

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


// CLASS_DECL_ACME bool file_as(::matter & s, const char * path, ::acme::application * papp)
// {

//    try
//    {

//       if (papp == nullptr)
//       {

//          papp = get_application();

//       }

//       if (papp == nullptr)
//       {

//          return false;

//       }

//       file_pointer pfileInput = App(papp).file().get_reader(path, ::file::e_open_share_deny_write);

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






