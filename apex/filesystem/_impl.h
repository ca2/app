#pragma once


namespace file
{

   //   inline path::path(const var & var,e_path epath): path(var.get_file_path(),epath){}
   //   inline path::path(const property & property,e_path epath, int iDir): path(property.get_file_path(),epath, iDir) {}
   inline path & path::operator = (const var & var) { return operator = (var.get_string()); }
   inline path & path::operator += (const var & var) { return operator += (var.get_string()); }
   inline path & path::operator = (const property & property) { return operator = ((const var &)property); }
   inline path & path::operator += (const property & property) { return operator += ((const var &) property); }
   inline path path::operator + (const var & var) const { return operator + (var.get_string()); }
   inline path path::operator + (const property & property) const { return operator + (property.get_string()); }
   inline path path::operator + (const id & id) const { return operator + (id.str()); }
   inline path path::operator / (const var & var) const { return operator /(::file::path(var)); }
   inline path path::operator / (const property & property) const { return operator /(::file::path(property)); }
   inline path path::operator * (const property & property) const { return operator *(::file::path(property)); }
   inline path & path::operator *= (const property & property) { return operator *=(::file::path(property)); }
   inline path path::folder() const { return { ::dir::name(*this), m_epath }; }
   inline path path::sibling(const path & path) const { return { ::dir::name(*this) + sep() + ::sz::trim_left_path_sep(path), m_epath }; }
   inline path path::sibling(const string & str) const { return { ::dir::name(*this) + sep() + ::sz::trim_left_path_sep(str), m_epath }; }
   inline path path::sibling(const char * psz) const { return { ::dir::name(*this) + sep() + ::sz::trim_left_path_sep(psz), m_epath }; }
   inline string path::extension() const { return &m_pdata[find_skip_or_length('.', rfind(sep()) + 1)]; }
   inline string path::final_extension() const { return file_final_extension_dup(operator const char * ()); }
   inline patha path::ascendants_path() const { patha patha; return ascendants_path(patha); }
   inline string_array path::ascendants_name() const { string_array patha; return ascendants_name(patha); }
   //   inline path path::folder() const { return ::dir::name(*this); }
   inline bool path::operator == (const var & var) const { return operator == (string(var)); }
   inline bool path::operator != (const var & var) const { return operator != (string(var)); }

} // namespace file


template < class T >
bool file_context::output(::file::file * pfileOut, T * p, bool (T:: * pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
{

   ::file::path pathDownloading;

   try
   {

      //stream outputstream(pobject, FIRST_VERSION);

      //if (!prepare_output(pobject, outputstream, pathDownloading, os))
      //{

      //   return false;

      //}

      //stream inputstream(pobject, FIRST_VERSION);

      //if (!prepare_input(pobject, inputstream, is))
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

   //   if (!post_output(pobject, os.m_pfile->GetFilePath(), pathDownloading))
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
//bool ::file::system::output(::object * pobject, const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pobject, FIRST_VERSION);

//      if (!prepare_output(pobject, os, pathDownloading, pathOut, nullptr))
//      {

//         return false;

//      }

//      stream is(pobject, FIRST_VERSION);

//      if (!prepare_input(pobject, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(point->*pfnOuput)(&os, &is))

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

//      if (!post_output(pobject, pathOut, pathDownloading))
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
//bool system::output(::object * pobject, const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pobject, FIRST_VERSION);

//      if (!prepare_output(pobject, os, pathDownloading, pathOut, nullptr))
//      {

//         return false;

//      }

//      if (!prepare_input(pobject, is, pfileIn))
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

//      if (!post_output(pobject, pathOut, pathDownloading))
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
//bool ::file::system::output(::object * pobject, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pobject, FIRST_VERSION);

//      if (!prepare_output(pobject, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      stream is(pobject, FIRST_VERSION);

//      if (!prepare_input(pobject, is, pathIn))
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
//bool ::file::system::output(::object * pobject, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pobject, FIRST_VERSION);

//      if (!prepare_output(pobject, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      stream is(pobject, FIRST_VERSION);

//      if (!prepare_input(pobject, is, pfileIn))
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
//bool system::output(::object * pobject, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream os(pobject, FIRST_VERSION);

//      if (!prepare_output(pobject, os, pathDownloading, "", pfileOut))
//      {

//         return false;

//      }

//      if (!prepare_input(pobject, is, pfileIn))
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
//bool ::file::system::output(::object * pobject, ::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is(pobject, FIRST_VERSION);

//      if (!prepare_input(pobject, is, pathIn))
//      {

//         return false;

//      }

//      if (!(point->*pfnOuput)(os, is))

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
//bool ::file::system::output(::object * pobject, ::file::file & os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file * pfileIn)

//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is(pobject, FIRST_VERSION);

//      if (!prepare_input(pobject, is, pfileIn))
//      {

//         return false;

//      }

//      if (!(point->*pfnOuput)(os, is))

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
//bool system::output(::object * pobject, ::file::file & os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file * preader)
//{

//   ::file::path pathDownloading;

//   try
//   {

//      stream is;

//      if (!prepare_input(pobject, is, preader))
//      {

//         return false;

//      }

//      if (!(point->*pfnOuput)(os, is))

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
//   return Context.file().output(get_context_application(), pfileOut, p, pfnOuput, pfileIn);
//
//}


//template < class T >
//bool application::output(const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), pathOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(const ::file::path & pathOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), pathOut, point, pfnOuput, istream);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), const ::file::path & pathIn)
//{

//   return Context.file().output(get_context_application(), pfileOut, point, pfnOuput, pathIn);


//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), pfileOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), pfileOut, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::* pfnOuput)(::file::file*, ::file::file*), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), os, p, pfnOuput, pathIn);

//}


//template < class T >
//bool application::output(::file::file * pfileOut, T * p, bool (T::*pfnOuput)(::file::file *, ::file::file *), ::file::file * pfileIn)
//{

//   return Context.file().output(get_context_application(), os, p, pfnOuput, pfileIn);

//}


//template < class T >
//bool application::output(::file::file& os, T * point, bool (T::*pfnOuput)(::file::file &, ::file::file &), ::file::file & istream)

//{

//   return Context.file().output(get_context_application(), os, point, pfnOuput, istream);


//}


//} // namespace file


//inline ::file::path operator + (const string & str,const ::file::path & path) { return ::file::path(str + string(path)); }
//inline ::file::path operator + (const char * psz,const ::file::path & path) {  return ::file::path(psz + string(path)); }
// xxxabc inline ::file::path operator + (const var & var,const ::file::path & path) { return ::file::path(var.get_string() + string(path)); }
//inline ::file::path operator / (const string & str,const ::file::path & path) { ::file::path point(str);  return point / path; }
//inline ::file::path operator / (const char * psz,const ::file::path & path) { ::file::path point(psz);  return point / path; }
// xxxabc inline ::file::path operator / (const var & var,const ::file::path & path) { ::file::path point(var.get_file_path());  return point / path; }



// template < class ARRAY >
// bool file_put_array(const char * path, ARRAY & a, ::apex::application * papp)
// {


//   try
//   {

//      if (papp == nullptr)
//      {

//         papp = get_context_application();

//      }

//      if (papp == nullptr)
//      {

//         return false;

//      }

//      file_pointer pfile = App(papp).file().get_file(path, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

//      if (pfile.is_null())
//      {

//         return false;

//      }

//      stream stream(pfile, FIRST_VERSION);

//      ::count count = a.get_count();

//      stream.write(count);

//      for (index index = 0; index < count; index++)
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
// bool file_as_array(ARRAY & a, const char * path, ::apex::application * papp)
// {

//   try
//   {

//      if (papp == nullptr)
//      {

//         papp = get_context_application();

//      }

//      if (papp == nullptr)
//      {

//         return false;

//      }

//      file_pointer pfile = App(papp).file().get_file(path, ::file::mode_read | ::file::type_binary);

//      if (pfile.is_null())
//      {

//         return false;

//      }

//      stream istream(pfile, FIRST_VERSION);

//      ::count count;

//      istream.read(count);

//      if (istream.fail())
//      {

//         return false;

//      }

//      a.allocate(count);

//      for (index index = 0; index < count; index++)
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





inline const char * FormatArgument(const ::file::path & value) noexcept
{
   return value.c_str();
}


template<>
inline uptr uptr_hash < const ::file::path & >(const ::file::path & key)
{

   return uptr_hash < const string & >(key);

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



