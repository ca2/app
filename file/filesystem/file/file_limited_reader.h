// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


/*#include "../../Common/MyCom.h"
#include "../../Common/MyVector.h"
#include "../IStream.h"*/


namespace file
{

   class limited_reader:
      public reader
   {
      reader * _stream;
      filesize _size;
      filesize _pos;
      bool _wasFinished;
   public:
      void SetStream(reader *stream) { _stream = stream; }
      void ReleaseStream() 
      {
         //_stream.Release(); 
      }
      void Init(filesize streamSize)
      {
         _size = streamSize;
         _pos = 0;
         _wasFinished = false;
      }

      memsize read(void *data, memsize size);
      filesize GetSize() const { return _pos; }
      bool WasFinished() const { return _wasFinished; }
   };

} // namespace file
