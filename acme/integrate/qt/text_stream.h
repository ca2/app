//
// Created by camilo on 2024-09-27 16:44 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <QString>
#include <QByteArray>


inline ::write_text_stream & operator <<(::write_text_stream & textstream, const ::QString & qstr)
{

   ::QByteArray utf8ByteArray = qstr.toUtf8();

   const_char_pointer utf8Buffer = utf8ByteArray.constData();

   textstream << utf8Buffer;

   return textstream;

}



