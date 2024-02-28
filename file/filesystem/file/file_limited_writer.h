// LimitedStreams.h
// from 7-zip on 2012-12-23, lunch time
#pragma once


namespace file
{

   class limited_writer:
      public writer
   {
      writer *    _stream;
      memsize      _size;
      bool        _overflow;
      bool        _overflowIsAllowed;
   public:
      void write(const void * data, memsize size, memsize * processedSize);
      void SetStream(writer * stream) { _stream = stream; }
      void ReleaseStream() 
      { 
         //_stream.Release(); 
      }
      void Init(u64 size, bool overflowIsAllowed = false)
      {
         _size = size;
         _overflow = false;
         _overflowIsAllowed = overflowIsAllowed;
      }
      bool IsFinishedOK() const { return (_size == 0 && !_overflow); }
      u64 GetRem() const { return _size; }
   };

} // namespace file
