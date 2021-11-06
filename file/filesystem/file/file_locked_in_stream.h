// LockedStream.h
#pragma once


namespace file
{

   class locked_in_stream
   {
   public:

      
      __pointer(stream)     _stream;
      critical_section     _criticalSection;


      void Init(stream *stream)
      { 
         _stream = stream; 
      }
      
      memsize read(filesize startPos, void * data, memsize size);

   };

   class locked_reader :
      virtual public ::file::file
   {
   public:


      locked_in_stream *_lockedInStream;
      filesize _pos;


      void Init(locked_in_stream *lockedInStream, filesize startPos)
      {
         _lockedInStream = lockedInStream;
         _pos = startPos;
      }

      memsize read(void *data, memsize size);

   };


} // namespace file









