//
//  CAStreamBasicDescription.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once

namespace music
{
   
   
   namespace midi
   {
      
      
      namespace audio_unit
      {

         #if !CA_PREFER_FIXED_POINT
         typedef Float32     CoreAudioSampleType;
         typedef Float32     CoreAudioUnitSampleType;
         #else
         typedef SInt16      CoreAudioSampleType;
         typedef SInt32      CoreAudioUnitSampleType;
         #define kAudioUnitSampleFractionBits 24
         #endif

         extern char *CAStringForOSType (OSType t, char *writeLocation);

         enum { kIsNonMixableFlag = kAudioFormatFlagIsNonMixable };

         //=============================================================================
         //	CAStreamBasicDescription
         //
         //	This is a wrapper class for the AudioStreamBasicDescription struct.
         //	It adds a number of convenience routines, but otherwise adds nothing
         //	to the footprint of the original struct.
         //=============================================================================
         class CAStreamBasicDescription :
         public AudioStreamBasicDescription
         {
            
            //	Constants
         public:
            static const AudioStreamBasicDescription	sEmpty;
            
            //	Construction/Destruction
         public:
            CAStreamBasicDescription() { __memset (this, 0, sizeof(AudioStreamBasicDescription)); }
            
            CAStreamBasicDescription(const AudioStreamBasicDescription &desc)
            {
               SetFrom(desc);
            }
            
            CAStreamBasicDescription(		double inSampleRate,		::u32 inFormatID,
                                     ::u32 inBytesPerPacket,	::u32 inFramesPerPacket,
                                     ::u32 inBytesPerFrame,		::u32 inChannelsPerFrame,
                                     ::u32 inBitsPerChannel,	::u32 inFormatFlags);
            
            //	Assignment
            CAStreamBasicDescription&	operator=(const AudioStreamBasicDescription& v) { SetFrom(v); return *this; }
            
            void	SetFrom(const AudioStreamBasicDescription &desc)
            {
               ::memcpy_dup(this, &desc, sizeof(AudioStreamBasicDescription));
            }
            
            // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //
            // interrogation
            
            bool	IsPCM() const { return mFormatID == kAudioFormatLinearPCM; }
            
            bool	PackednessIsSignificant() const
            {
               //Assert(IsPCM(), "PackednessIsSignificant only applies for PCM");
               return (SampleWordSize() << 3) != mBitsPerChannel;
            }
            
            bool	AlignmentIsSignificant() const
            {
               return PackednessIsSignificant() || (mBitsPerChannel & 7) != 0;
            }
            
            bool	IsInterleaved() const
            {
               return !IsPCM() || !(mFormatFlags & kAudioFormatFlagIsNonInterleaved);
            }
            
            bool	IsNativeEndian() const
            {
               return (mFormatFlags & kAudioFormatFlagIsBigEndian) == kAudioFormatFlagsNativeEndian;
            }
            
            // for sanity with interleaved/deinterleaved possibilities, never access mChannelsPerFrame, use these:
            ::u32	NumberInterleavedChannels() const	{ return IsInterleaved() ? mChannelsPerFrame : 1; }
            ::u32	NumberChannelStreams() const		{ return IsInterleaved() ? 1 : mChannelsPerFrame; }
            ::u32	NumberChannels() const				{ return mChannelsPerFrame; }
            ::u32	SampleWordSize() const				{
               return (mBytesPerFrame > 0 && NumberInterleavedChannels()) ? mBytesPerFrame / NumberInterleavedChannels() :  0;
            }
            
            ::u32	FramesToBytes(::u32 nframes) const	{ return nframes * mBytesPerFrame; }
            ::u32	BytesToFrames(::u32 nbytes) const	{
               //Assert(mBytesPerFrame > 0, "bytesPerFrame must be > 0 in BytesToFrames");
               return nbytes / mBytesPerFrame;
            }
            
            bool	SameChannelsAndInterleaving(const CAStreamBasicDescription &a) const
            {
               return this->NumberChannels() == a.NumberChannels() && this->IsInterleaved() == a.IsInterleaved();
            }
            
            // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //
            //	manipulation
            
            void	SetCanonical(::u32 nChannels, bool interleaved)
            // note: leaves sample rate untouched
            {
               mFormatID = kAudioFormatLinearPCM;
               int sampleSize = sizeof(CoreAudioSampleType);
               mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked;
               mBitsPerChannel = 8 * sampleSize;
               mChannelsPerFrame = nChannels;
               mFramesPerPacket = 1;
               if (interleaved)
                  mBytesPerPacket = mBytesPerFrame = nChannels * sampleSize;
               else {
                  mBytesPerPacket = mBytesPerFrame = sampleSize;
                  mFormatFlags |= kAudioFormatFlagIsNonInterleaved;
               }
            }
            
            bool	IsCanonical() const
            {
               if (mFormatID != kAudioFormatLinearPCM) return false;
               ::u32 reqFormatFlags;
               ::u32 flagsMask = (kLinearPCMFormatFlagIsFloat | kLinearPCMFormatFlagIsBigEndian | kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked | kLinearPCMFormatFlagIsAlignedHigh | kLinearPCMFormatFlagsSampleFractionMask);
               bool interleaved = (mFormatFlags & kAudioFormatFlagIsNonInterleaved) == 0;
               unsigned sampleSize = sizeof(CoreAudioSampleType);
               reqFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked;
               ::u32 reqFrameSize = interleaved ? (mChannelsPerFrame * sampleSize) : sampleSize;
               
               return ((mFormatFlags & flagsMask) == reqFormatFlags
                       && mBitsPerChannel == 8 * sampleSize
                       && mFramesPerPacket == 1
                       && mBytesPerFrame == reqFrameSize
                       && mBytesPerPacket == reqFrameSize);
            }
            
            void	SetAUCanonical(::u32 nChannels, bool interleaved)
            {
               mFormatID = kAudioFormatLinearPCM;
         #if CA_PREFER_FIXED_POINT
               mFormatFlags = kAudioFormatFlagsCanonical | (kAudioUnitSampleFractionBits << kLinearPCMFormatFlagsSampleFractionShift);
         #else
               mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked;
         #endif
               mChannelsPerFrame = nChannels;
               mFramesPerPacket = 1;
               mBitsPerChannel = 8 * sizeof(CoreAudioUnitSampleType);
               if (interleaved)
                  mBytesPerPacket = mBytesPerFrame = nChannels * sizeof(CoreAudioUnitSampleType);
               else {
                  mBytesPerPacket = mBytesPerFrame = sizeof(CoreAudioUnitSampleType);
                  mFormatFlags |= kAudioFormatFlagIsNonInterleaved;
               }
            }
            
            void	ChangeNumberChannels(::u32 nChannels, bool interleaved)
            // alter an existing format
            {
               //Assert(IsPCM(), "ChangeNumberChannels only works for PCM formats");
               ::u32 wordSize = SampleWordSize();	// get this before changing ANYTHING
               if (wordSize == 0)
                  wordSize = (mBitsPerChannel + 7) / 8;
               mChannelsPerFrame = nChannels;
               mFramesPerPacket = 1;
               if (interleaved) {
                  mBytesPerPacket = mBytesPerFrame = nChannels * wordSize;
                  mFormatFlags &= ~kAudioFormatFlagIsNonInterleaved;
               } else {
                  mBytesPerPacket = mBytesPerFrame = wordSize;
                  mFormatFlags |= kAudioFormatFlagIsNonInterleaved;
               }
            }
            
            // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
            //
            //	other
            
            bool	IsEqual(const AudioStreamBasicDescription &other, bool interpretingWildcards=true) const;
            
            void	Print() const {
               Print (stdout);
            }
            
            void	Print(FILE* file) const {
               PrintFormat (file, "", "AudioStreamBasicDescription:");
            }
            
            void	PrintFormat(FILE *f, const char *indent, const char *name) const {
               char buf[256];
               fprintf(f, "%s%s %s\n", indent, name, AsString(buf, sizeof(buf)));
            }
            
            void	PrintFormat2(FILE *f, const char *indent, const char *name) const { // no trailing newline
               char buf[256];
               fprintf(f, "%s%s %s", indent, name, AsString(buf, sizeof(buf)));
            }
            
            char *	AsString(char *buf, size_t bufsize) const;
            
            static void Print (const AudioStreamBasicDescription &inDesc)
            {
               CAStreamBasicDescription desc(inDesc);
               desc.Print ();
            }
            
            OSStatus			Save(CFPropertyListRef *outData) const;
            
            OSStatus			Restore(CFPropertyListRef &inData);
            
            //	Operations
            static bool			IsMixable(const AudioStreamBasicDescription& inDescription) { return (inDescription.mFormatID == kAudioFormatLinearPCM) && ((inDescription.mFormatFlags & kIsNonMixableFlag) == 0); }
            static void			NormalizeLinearPCMFormat(AudioStreamBasicDescription& ioDescription);
            static void			ResetFormat(AudioStreamBasicDescription& ioDescription);
            static void			FillOutFormat(AudioStreamBasicDescription& ioDescription, const AudioStreamBasicDescription& inTemplateDescription);
            static void			GetSimpleName(const AudioStreamBasicDescription& inDescription, char* outName, ::u32 inMaxNameLength, bool inAbbreviate);
         #if CoreAudio_Debug
            static void			PrintToLog(const AudioStreamBasicDescription& inDesc);
         #endif
         };

         bool		operator<(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y);
         bool		operator==(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y);
         #if TARGET_OS_MAC || (TARGET_OS_WIN32 && (_MSC_VER > 600))
         inline bool	operator!=(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y) { return !(x == y); }
         inline bool	operator<=(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y) { return (x < y) || (x == y); }
         inline bool	operator>=(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y) { return !(x < y); }
         inline bool	operator>(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y) { return !((x < y) || (x == y)); }
         #endif

         bool SanityCheck(const AudioStreamBasicDescription& x);

         
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




