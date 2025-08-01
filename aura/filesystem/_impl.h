#pragma once




template < class T >
bool file_context::output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
{

   ::file::path pathDownloading;

   try
   {

      //stream outputstream(pparticle, FIRST_VERSION);

      //if (!prepare_output(pparticle, outputstream, pathDownloading, os))
      //{

      //   return false;

      //}

      //stream inputstream(pparticle, FIRST_VERSION);

      //if (!prepare_input(pparticle, inputstream, is))
      //{

      //   return false;

      //}

      if (!(p->*pfnOuput)(pfileOut, pfileIn))
      {

         return false;

      }

   }
   catch (...)
   {

      return false;

   }

   //try
   //{

   //   if (!post_output(pparticle, os.m_pfile->GetFilePath(), pathDownloading))
   //   {

   //      return false;

   //   }

   //}
   //catch (...)
   //{

   //   return false;

   //}

   return true;

}


//template < class T >
//bool ::file::system::output(::particle * pparticle, const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pparticle, FIRST_VERSION);

//      if (!prepare_output(pparticle, os, pathDownloading, pathOut, nullptr))
//      {

//         return false;

//      }

//      stream is(pparticle, FIRST_VERSION);

//      if (!prepare_input(pparticle, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(int_point->*pfnOuput)(&os, &is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }


//   try
//   {

//      if (!post_output(pparticle, pathOut, pathDownloading))
//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool system::output(::particle * pparticle, const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pparticle, FIRST_VERSION);

//      if (!prepare_output(pparticle, os, pathDownloading, pathOut, nullptr))
//      {

//         return false;

//      }

//      if (!prepare_input(pparticle, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(p->*pfnOuput)(&os, &is))
//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   try
//   {

//      if (!post_output(pparticle, pathOut, pathDownloading))
//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;
//}


//template < class T >
//bool ::file::system::output(::particle * pparticle, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pparticle, FIRST_VERSION);

//      if (!prepare_output(pparticle, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      stream is(pparticle, FIRST_VERSION);

//      if (!prepare_input(pparticle, is, pathIn))
//      {

//         return false;

//      }

//      if (!(p->*pfnOuput)(&os, &is))
//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool ::file::system::output(::particle * pparticle, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pparticle, FIRST_VERSION);

//      if (!prepare_output(pparticle, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      stream is(pparticle, FIRST_VERSION);

//      if (!prepare_input(pparticle, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(p->*pfnOuput)(&os, &is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool system::output(::particle * pparticle, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pparticle, FIRST_VERSION);

//      if (!prepare_output(pparticle, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      if (!prepare_input(pparticle, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(p->*pfnOuput)(&os, &is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool ::file::system::output(::particle * pparticle, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is(pparticle, FIRST_VERSION);

//      if (!prepare_input(pparticle, is, pathIn))
//      {

//         return false;

//      }

//      if (!(int_point->*pfnOuput)(os, is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool ::file::system::output(::particle * pparticle, ::file::file & os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file * pfileIn)

//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is(pparticle, FIRST_VERSION);

//      if (!prepare_input(pparticle, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(int_point->*pfnOuput)(os, is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}


//template < class T >
//bool system::output(::particle * pparticle, ::file::file & os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file * preader)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is;

//      if (!prepare_input(pparticle, is, preader))
//      {

//         return false;

//      }

//      if (!(int_point->*pfnOuput)(os, is))

//      {

//         return false;

//      }

//   }
//   catch (...)
//   {

//      return false;

//   }

//   return true;

//}

//}

//template < class T >
//bool file_context::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{
//
//   return file()->output(get_app(), pfileOut, p, pfnOuput, pfileIn);
//
//}


//template < class T >
//bool application::output(const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), pathOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), pathOut, point, pfnOuput, istream);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   return file()->output(get_app(), pfileOut, point, pfnOuput, pathIn);


//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), pfileOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), pfileOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::* pfnOuput)(::file::file*, ::file::file*), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), os, p, pfnOuput, pathIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return file()->output(get_app(), os, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file& os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file & istream)

//{

//   return file()->output(get_app(), os, point, pfnOuput, istream);


//}


//} // namespace file


//inline ::file::path operator + (const ::scoped_string & scopedstr,const ::file::path & path) { return ::file::path(str + string(path)); }
//inline ::file::path operator + (const ::scoped_string & scopedstr,const ::file::path & path) {  return ::file::path(scopedstr + string(path)); }
// xxxabc inline ::file::path operator + (const ::payload & payload,const ::file::path & path) { return ::file::path(payload.get_string() + string(path)); }
//inline ::file::path operator / (const ::scoped_string & scopedstr,const ::file::path & path) { ::file::path int_point(str);  return point / path; }
//inline ::file::path operator / (const ::scoped_string & scopedstr,const ::file::path & path) { ::file::path int_point(scopedstr);  return point / path; }
// xxxabc inline ::file::path operator / (const ::payload & payload,const ::file::path & path) { ::file::path int_point(payload.get_file_path());  return point / path; }



// template < class ARRAY >
// bool file_put_array(const ::scoped_string & scopedstrPath, ARRAY & a, ::aura::application * papp)
// {


//   try
//   {

//      if (papp == nullptr)
//      {

//         papp = get_app();

//      }

//      if (papp == nullptr)
//      {

//         return false;

//      }

//      file_pointer pfile = App(papp).file()->get_file(path, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary | ::file::e_open_defer_create_directory);

//      if (pfile.is_null())
//      {

//         return false;

//      }

//      stream stream(pfile, FIRST_VERSION);

//      ::collection::count count = a.get_count();

//      stream.write(count);

//      for (::collection::index index = 0; index < count; index++)
//      {

//         stream << a.element_at(index);

//      }

//      return true;

//   }
//   catch (...)
//   {

//   }

//   return false;

// }


// template < class ARRAY >
// bool file_as_array(ARRAY & a, const ::scoped_string & scopedstrPath, ::aura::application * papp)
// {

//   try
//   {

//      if (papp == nullptr)
//      {

//         papp = get_app();

//      }

//      if (papp == nullptr)
//      {

//         return false;

//      }

//      file_pointer pfile = App(papp).file()->get_file(path, ::file::e_open_read | ::file::e_open_binary);

//      if (pfile.is_null())
//      {

//         return false;

//      }

//      stream istream(pfile, FIRST_VERSION);

//      ::collection::count count;

//      istream.read(count);

//      if (istream.fail())
//      {

//         return false;

//      }

//      a.allocate(count);

//      for (::collection::index index = 0; index < count; index++)
//      {

//         istream >> a.element_at(index);

//         if (istream.fail())
//         {

//            return false;

//         }

//      }

//      a.on_after_read();

//      return true;

//   }
//   catch (...)
//   {


//   }

//   return false;

// }



inline stream & operator << (stream & s, const ::file::path_object & path)
{

   return s << (const ::file::path&)path;

}


inline stream & operator >>(stream & s, ::file::path_object & path)
{

   return s >> (::file::path &)path;

}

// namespace file
//{

//inline string path_object::to_string() const
//{

//   return (const path&)*this;

//}







//} // namespace file





inline const_char_pointer FormatArgument(const ::file::path & value) noexcept
{
   return value.c_str();
}


template < >
inline ::hash32 as_hash32 < const ::file::path & >(const ::file::path & key)
{

   return as_hash32 < const string & >(key);

}


inline stream & operator << (stream & s, const ::file::path & path)
{

   return s << (const string &)path;

}


inline stream & operator >> (stream & s, ::file::path & path)
{

   string str;

   s >> str;

   path = str;

   return s;

}


inline filesize stream_meta::precision(filesize prec)
{

   return m_precision = prec;

}


inline filesize stream_meta::width() const
{

   return m_width;

}

inline filesize stream_meta::width(filesize prec)
{

   return m_width = prec;

}


inline filesize stream_meta::precision() const
{

   return m_precision;

}



