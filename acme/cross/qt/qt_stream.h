//
// Created by camilo on 2024-09-27 16:44 <3ThomasBorregaardSorensen!!
//
#pragma once




::file::binary_stream operator << (::file::binary_stream & stream, const QString & qstr)
{

   QByteArray utf8ByteArray = qstr.toUtf8();
   const char *utf8Buffer = utf8ByteArray.constData();
   stream << utf8Buffer;

   return stream;

}