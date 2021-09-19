#include "framework.h"


//namespace file
//{
//
//
//   void seekable::seek_to_begin()
//   {
//
//      seek(0, seek_begin);
//
//   }
//
//
//   filesize seekable::seek_to_end()
//   {
//
//      return seek(0, seek_end);
//
//   }
//
//
//   filesize seekable::seek_from_begin(filesize position)
//   {
//
//      return seek((filesize) position, seek_begin);
//
//   }
//
//   filesize seekable::seek(filesize offset, enum_seek seekOrigin)
//   {
//      __UNREFERENCED_PARAMETER(offset);
//      __UNREFERENCED_PARAMETER(seekOrigin);
//      throw ::interface_only_exception();
//      return 0;
//   }
//
//   filesize seekable::get_position() const
//   {
//      return const_cast < seekable * > (this)->seek(0, seek_current);
//   }
//
//
//} // namespace file
//
//
//
//
