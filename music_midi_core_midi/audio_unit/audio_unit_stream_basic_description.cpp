//
//  CAStreamBasicDescription.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "audio_unit.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace audio_unit
      {

            inline bool fiszero(Float64 f) { return (f == 0.); }
            inline bool fiszero(Float32 f) { return (f == 0.f); }
            inline bool fnonzero(Float64 f) { return !fiszero(f); }
            inline bool fnonzero(Float32 f) { return !fiszero(f); }

            inline bool fequal(const Float64 &a, const Float64 &b) { return a == b; }
            inline bool fequal(const Float32 &a, const Float32 &b) { return a == b; }

            inline bool fnotequal(const Float64 &a, const Float64 &b) { return !fequal(a, b); }
            inline bool fnotequal(const Float32 &a, const Float32 &b) { return !fequal(a, b); }

            char *CAStringForOSType (OSType t, char *writeLocation)
            {
               char *p = writeLocation;
               unsigned char str[4], *q = str;
               *(::u32 *)str = CFSwapInt32HostToBig(t);
               
               bool hasNonPrint = false;
               for (int i = 0; i < 4; ++i) {
                  if (!(isprint(*q) && *q != '\\')) {
                     hasNonPrint = true;
                     break;
                  }
               }
               
               if (hasNonPrint)
                  p += sprintf (p, "0x");
               else
                  *p++ = '\'';
               
               for (int i = 0; i < 4; ++i) {
                  if (hasNonPrint) {
                     p += sprintf(p, "%02X", *q++);
                  } else {
                     *p++ = *q++;
                  }
               }
               if (!hasNonPrint)
                  *p++ = '\'';
               *p = '\0';
               return writeLocation;
            }


            const AudioStreamBasicDescription	CAStreamBasicDescription::sEmpty = { 0.0, 0, 0, 0, 0, 0, 0, 0, 0 };

            CAStreamBasicDescription::CAStreamBasicDescription(double inSampleRate,		::u32 inFormatID,
                                                               ::u32 inBytesPerPacket,	::u32 inFramesPerPacket,
                                                               ::u32 inBytesPerFrame,		::u32 inChannelsPerFrame,
                                                               ::u32 inBitsPerChannel,	::u32 inFormatFlags)
            {
               mSampleRate = inSampleRate;
               mFormatID = inFormatID;
               mBytesPerPacket = inBytesPerPacket;
               mFramesPerPacket = inFramesPerPacket;
               mBytesPerFrame = inBytesPerFrame;
               mChannelsPerFrame = inChannelsPerFrame;
               mBitsPerChannel = inBitsPerChannel;
               mFormatFlags = inFormatFlags;
               mReserved = 0;
            }

            char *CAStreamBasicDescription::AsString(char *buf, size_t _bufsize) const
            {
               int bufsize = (int)_bufsize;	// must be signed to protect against overflow
               char *theBuffer = buf;
               int nc;
               char formatID[24];
               CAStringForOSType (mFormatID, formatID);
               nc = snprintf(buf, bufsize, "%2d ch, %6.0f Hz, %s (0x%08X) ", (int)NumberChannels(), mSampleRate, formatID, (int)mFormatFlags);
               buf += nc; if ((bufsize -= nc) <= 0) goto exit;
               if (mFormatID == kAudioFormatLinearPCM) {
                  bool isInt = !(mFormatFlags & kLinearPCMFormatFlagIsFloat);
                  int wordSize = SampleWordSize();
                  const char *endian = (wordSize > 1) ?
                  ((mFormatFlags & kLinearPCMFormatFlagIsBigEndian) ? " big-endian" : " little-endian" ) : "";
                  const char *sign = isInt ?
                  ((mFormatFlags & kLinearPCMFormatFlagIsSignedInteger) ? " signed" : " unsigned") : "";
                  const char *floatInt = isInt ? "integer" : "float";
                  char packed[32];
                  if (wordSize > 0 && PackednessIsSignificant()) {
                     if (mFormatFlags & kLinearPCMFormatFlagIsPacked)
                        snprintf(packed, sizeof(packed), "packed in %d bytes", wordSize);
                     else
                        snprintf(packed, sizeof(packed), "unpacked in %d bytes", wordSize);
                  } else
                     packed[0] = '\0';
                  const char *align = (wordSize > 0 && AlignmentIsSignificant()) ?
                  ((mFormatFlags & kLinearPCMFormatFlagIsAlignedHigh) ? " high-aligned" : " low-aligned") : "";
                  const char *deinter = (mFormatFlags & kAudioFormatFlagIsNonInterleaved) ? ", deinterleaved" : "";
                  const char *commaSpace = (packed[0]!='\0') || (align[0]!='\0') ? ", " : "";
                  char bitdepth[20];
                  
                  int fracbits = (mFormatFlags & kLinearPCMFormatFlagsSampleFractionMask) >> kLinearPCMFormatFlagsSampleFractionShift;
                  if (fracbits > 0)
                     snprintf(bitdepth, sizeof(bitdepth), "%d.%d", (int)mBitsPerChannel - fracbits, fracbits);
                  else
                     snprintf(bitdepth, sizeof(bitdepth), "%d", (int)mBitsPerChannel);
                  
                  nc = snprintf(buf, bufsize, "%s-bit%s%s %s%s%s%s%s",
                                bitdepth, endian, sign, floatInt,
                                commaSpace, packed, align, deinter);
                  // buf += nc; if ((bufsize -= nc) <= 0) goto exit;
               } else if (mFormatID == 'alac') {	//	kAudioFormatAppleLossless
                  int sourceBits = 0;
                  switch (mFormatFlags)
                  {
                     case 1:	//	kAppleLosslessFormatFlag_16BitSourceData
                        sourceBits = 16;
                        break;
                     case 2:	//	kAppleLosslessFormatFlag_20BitSourceData
                        sourceBits = 20;
                        break;
                     case 3:	//	kAppleLosslessFormatFlag_24BitSourceData
                        sourceBits = 24;
                        break;
                     case 4:	//	kAppleLosslessFormatFlag_32BitSourceData
                        sourceBits = 32;
                        break;
                  }
                  if (sourceBits)
                     nc = snprintf(buf, bufsize, "from %d-bit source, ", sourceBits);
                  else
                     nc = snprintf(buf, bufsize, "from UNKNOWN source bit depth, ");
                  buf += nc; if ((bufsize -= nc) <= 0) goto exit;
                  nc = snprintf(buf, bufsize, "%d frames/packet", (int)mFramesPerPacket);
                  //	buf += nc; if ((bufsize -= nc) <= 0) goto exit;
               }
               else
                  nc = snprintf(buf, bufsize, "%d bits/channel, %d bytes/packet, %d frames/packet, %d bytes/frame",
                                (int)mBitsPerChannel, (int)mBytesPerPacket, (int)mFramesPerPacket, (int)mBytesPerFrame);
            exit:
               return theBuffer;
            }

            void	CAStreamBasicDescription::NormalizeLinearPCMFormat(AudioStreamBasicDescription& ioDescription)
            {
               //  the only thing that changes is to make mixable linear PCM into the canonical linear PCM format
               if((ioDescription.mFormatID == kAudioFormatLinearPCM) && ((ioDescription.mFormatFlags & kIsNonMixableFlag) == 0))
               {
                  //  the canonical linear PCM format
                  ioDescription.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked;
                  ioDescription.mBytesPerPacket = sizeof(CoreAudioSampleType) * ioDescription.mChannelsPerFrame;
                  ioDescription.mFramesPerPacket = 1;
                  ioDescription.mBytesPerFrame = sizeof(CoreAudioSampleType) * ioDescription.mChannelsPerFrame;
                  ioDescription.mBitsPerChannel = 8 * sizeof(CoreAudioSampleType);
               }
            }

            void	CAStreamBasicDescription::ResetFormat(AudioStreamBasicDescription& ioDescription)
            {
               ioDescription.mSampleRate = 0;
               ioDescription.mFormatID = 0;
               ioDescription.mBytesPerPacket = 0;
               ioDescription.mFramesPerPacket = 0;
               ioDescription.mBytesPerFrame = 0;
               ioDescription.mChannelsPerFrame = 0;
               ioDescription.mBitsPerChannel = 0;
               ioDescription.mFormatFlags = 0;
            }

            void	CAStreamBasicDescription::FillOutFormat(AudioStreamBasicDescription& ioDescription, const AudioStreamBasicDescription& inTemplateDescription)
            {
               if(fiszero(ioDescription.mSampleRate))
               {
                  ioDescription.mSampleRate = inTemplateDescription.mSampleRate;
               }
               if(ioDescription.mFormatID == 0)
               {
                  ioDescription.mFormatID = inTemplateDescription.mFormatID;
               }
               if(ioDescription.mFormatFlags == 0)
               {
                  ioDescription.mFormatFlags = inTemplateDescription.mFormatFlags;
               }
               if(ioDescription.mBytesPerPacket == 0)
               {
                  ioDescription.mBytesPerPacket = inTemplateDescription.mBytesPerPacket;
               }
               if(ioDescription.mFramesPerPacket == 0)
               {
                  ioDescription.mFramesPerPacket = inTemplateDescription.mFramesPerPacket;
               }
               if(ioDescription.mBytesPerFrame == 0)
               {
                  ioDescription.mBytesPerFrame = inTemplateDescription.mBytesPerFrame;
               }
               if(ioDescription.mChannelsPerFrame == 0)
               {
                  ioDescription.mChannelsPerFrame = inTemplateDescription.mChannelsPerFrame;
               }
               if(ioDescription.mBitsPerChannel == 0)
               {
                  ioDescription.mBitsPerChannel = inTemplateDescription.mBitsPerChannel;
               }
            }

            void	CAStreamBasicDescription::GetSimpleName(const AudioStreamBasicDescription& inDescription, char* outName, ::u32 inMaxNameLength, bool inAbbreviate)
            {
               switch(inDescription.mFormatID)
               {
                  case kAudioFormatLinearPCM:
                  {
                     const char* theEndianString = nullptr;
                     if((inDescription.mFormatFlags & kAudioFormatFlagIsBigEndian) != 0)
                     {
            #if	TARGET_RT_LITTLE_ENDIAN
                        theEndianString = "Big Endian";
            #endif
                     }
                     else
                     {
            #if	TARGET_RT_BIG_ENDIAN
                        theEndianString = "Little Endian";
            #endif
                     }
                     
                     const char* theKindString = nullptr;
                     if((inDescription.mFormatFlags & kAudioFormatFlagIsFloat) != 0)
                     {
                        theKindString = (inAbbreviate ? "Float" : "Floating Point");
                     }
                     else if((inDescription.mFormatFlags & kAudioFormatFlagIsSignedInteger) != 0)
                     {
                        theKindString = (inAbbreviate ? "SInt" : "Signed Integer");
                     }
                     else
                     {
                        theKindString = (inAbbreviate ? "::u32" : "Unsigned Integer");
                     }
                     
                     const char* thePackingString = nullptr;
                     if((inDescription.mFormatFlags & kAudioFormatFlagIsPacked) == 0)
                     {
                        if((inDescription.mFormatFlags & kAudioFormatFlagIsAlignedHigh) != 0)
                        {
                           thePackingString = "High";
                        }
                        else
                        {
                           thePackingString = "Low";
                        }
                     }
                     
                     const char* theMixabilityString = nullptr;
                     if((inDescription.mFormatFlags & kIsNonMixableFlag) == 0)
                     {
                        theMixabilityString = "Mixable";
                     }
                     else
                     {
                        theMixabilityString = "Unmixable";
                     }
                     
                     if(inAbbreviate)
                     {
                        if(theEndianString != nullptr)
                        {
                           if(thePackingString != nullptr)
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Ch %s %s %s%d/%s%d", theMixabilityString, (int)inDescription.mChannelsPerFrame, theEndianString, thePackingString, theKindString, (int)inDescription.mBitsPerChannel, theKindString, (int)(inDescription.mBytesPerFrame / inDescription.mChannelsPerFrame) * 8);
                           }
                           else
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Ch %s %s%d", theMixabilityString, (int)inDescription.mChannelsPerFrame, theEndianString, theKindString, (int)inDescription.mBitsPerChannel);
                           }
                        }
                        else
                        {
                           if(thePackingString != nullptr)
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Ch %s %s%d/%s%d", theMixabilityString, (int)inDescription.mChannelsPerFrame, thePackingString, theKindString, (int)inDescription.mBitsPerChannel, theKindString, (int)((inDescription.mBytesPerFrame / inDescription.mChannelsPerFrame) * 8));
                           }
                           else
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Ch %s%d", theMixabilityString, (int)inDescription.mChannelsPerFrame, theKindString, (int)inDescription.mBitsPerChannel);
                           }
                        }
                     }
                     else
                     {
                        if(theEndianString != nullptr)
                        {
                           if(thePackingString != nullptr)
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Channel %d Bit %s %s Aligned %s in %d Bits", theMixabilityString, (int)inDescription.mChannelsPerFrame, (int)inDescription.mBitsPerChannel, theEndianString, theKindString, thePackingString, (int)(inDescription.mBytesPerFrame / inDescription.mChannelsPerFrame) * 8);
                           }
                           else
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Channel %d Bit %s %s", theMixabilityString, (int)inDescription.mChannelsPerFrame, (int)inDescription.mBitsPerChannel, theEndianString, theKindString);
                           }
                        }
                        else
                        {
                           if(thePackingString != nullptr)
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Channel %d Bit %s Aligned %s in %d Bits", theMixabilityString, (int)inDescription.mChannelsPerFrame, (int)inDescription.mBitsPerChannel, theKindString, thePackingString, (int)(inDescription.mBytesPerFrame / inDescription.mChannelsPerFrame) * 8);
                           }
                           else
                           {
                              snprintf(outName, inMaxNameLength, "%s %d Channel %d Bit %s", theMixabilityString, (int)inDescription.mChannelsPerFrame, (int)inDescription.mBitsPerChannel, theKindString);
                           }
                        }
                     }
                  }
                     break;
                     
                  case kAudioFormatAC3:
                     strlcpy(outName, "AC-3", sizeof(outName));
                     break;
                     
                  case kAudioFormat60958AC3:
                     strlcpy(outName, "AC-3 for SPDIF", sizeof(outName));
                     break;
                     
                  default:
            #define CACopy4CCToCString(theCString, the4CC)	{ theCString[0] = ((char*)&the4CC)[3]; theCString[1] = ((char*)&the4CC)[2]; theCString[2] = ((char*)&the4CC)[1]; theCString[3] = ((char*)&the4CC)[0]; theCString[4] = 0; }
                     CACopy4CCToCString(outName, inDescription.mFormatID);
                     break;
               };
            }

            #if CoreAudio_Debug
            #include "CALogMacros.h"

            void	CAStreamBasicDescription::PrintToLog(const AudioStreamBasicDescription& inDesc)
            {
               PrintFloat		("  Sample Rate:        ", inDesc.mSampleRate);
               Print4CharCode	("  Format ID:          ", inDesc.mFormatID);
               PrintHex		("  Format Flags:       ", inDesc.mFormatFlags);
               PrintInt		("  Bytes per Packet:   ", inDesc.mBytesPerPacket);
               PrintInt		("  Frames per Packet:  ", inDesc.mFramesPerPacket);
               PrintInt		("  Bytes per Frame:    ", inDesc.mBytesPerFrame);
               PrintInt		("  Channels per Frame: ", inDesc.mChannelsPerFrame);
               PrintInt		("  Bits per Channel:   ", inDesc.mBitsPerChannel);
            }
            #endif

            bool	operator<(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y)
            {
               bool theAnswer = false;
               bool isDone = false;
               
               //	note that if either side is 0, that field is skipped
               
               //	format ID is the first order sort
               if((!isDone) && ((x.mFormatID != 0) && (y.mFormatID != 0)))
               {
                  if(x.mFormatID != y.mFormatID)
                  {
                     //	formats are sorted numerically except that linear
                     //	PCM is always first
                     if(x.mFormatID == kAudioFormatLinearPCM)
                     {
                        theAnswer = true;
                     }
                     else if(y.mFormatID == kAudioFormatLinearPCM)
                     {
                        theAnswer = false;
                     }
                     else
                     {
                        theAnswer = x.mFormatID < y.mFormatID;
                     }
                     isDone = true;
                  }
               }
               
               
               //  mixable is always better than non-mixable for linear PCM and should be the second order sort item
               if((!isDone) && ((x.mFormatID == kAudioFormatLinearPCM) && (y.mFormatID == kAudioFormatLinearPCM)))
               {
                  if(((x.mFormatFlags & kIsNonMixableFlag) == 0) && ((y.mFormatFlags & kIsNonMixableFlag) != 0))
                  {
                     theAnswer = true;
                     isDone = true;
                  }
                  else if(((x.mFormatFlags & kIsNonMixableFlag) != 0) && ((y.mFormatFlags & kIsNonMixableFlag) == 0))
                  {
                     theAnswer = false;
                     isDone = true;
                  }
               }
               
               //	floating point vs integer for linear PCM only
               if((!isDone) && ((x.mFormatID == kAudioFormatLinearPCM) && (y.mFormatID == kAudioFormatLinearPCM)))
               {
                  if((x.mFormatFlags & kAudioFormatFlagIsFloat) != (y.mFormatFlags & kAudioFormatFlagIsFloat))
                  {
                     //	floating point is better than integer
                     theAnswer = y.mFormatFlags & kAudioFormatFlagIsFloat;
                     isDone = true;
                  }
               }
               
               //	bit depth
               if((!isDone) && ((x.mBitsPerChannel != 0) && (y.mBitsPerChannel != 0)))
               {
                  if(x.mBitsPerChannel != y.mBitsPerChannel)
                  {
                     //	deeper bit depths are higher quality
                     theAnswer = x.mBitsPerChannel < y.mBitsPerChannel;
                     isDone = true;
                  }
               }
               
               //	sample rate
               if((!isDone) && fnonzero(x.mSampleRate) && fnonzero(y.mSampleRate))
               {
                  if(fnotequal(x.mSampleRate, y.mSampleRate))
                  {
                     //	higher sample rates are higher quality
                     theAnswer = x.mSampleRate < y.mSampleRate;
                     isDone = true;
                  }
               }
               
               //	number of channels
               if((!isDone) && ((x.mChannelsPerFrame != 0) && (y.mChannelsPerFrame != 0)))
               {
                  if(x.mChannelsPerFrame != y.mChannelsPerFrame)
                  {
                     //	more channels is higher quality
                     theAnswer = x.mChannelsPerFrame < y.mChannelsPerFrame;
                     isDone = true;
                  }
               }
               
               return theAnswer;
            }

            static bool MatchFormatFlags(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y)
            {
               ::u32 xFlags = x.mFormatFlags;
               ::u32 yFlags = y.mFormatFlags;
               
               // match wildcards
               if (x.mFormatID == 0 || y.mFormatID == 0 || xFlags == 0 || yFlags == 0)
                  return true;
               
               if (x.mFormatID == kAudioFormatLinearPCM)
               {
                  // knock off the all clear flag
                  xFlags = xFlags & ~kAudioFormatFlagsAreAllClear;
                  yFlags = yFlags & ~kAudioFormatFlagsAreAllClear;
                  
                  // if both kAudioFormatFlagIsPacked bits are set, then we don't care about the kAudioFormatFlagIsAlignedHigh bit.
                  if (xFlags & yFlags & kAudioFormatFlagIsPacked) {
                     xFlags = xFlags & ~kAudioFormatFlagIsAlignedHigh;
                     yFlags = yFlags & ~kAudioFormatFlagIsAlignedHigh;
                  }
                  
                  // if both kAudioFormatFlagIsFloat bits are set, then we don't care about the kAudioFormatFlagIsSignedInteger bit.
                  if (xFlags & yFlags & kAudioFormatFlagIsFloat) {
                     xFlags = xFlags & ~kAudioFormatFlagIsSignedInteger;
                     yFlags = yFlags & ~kAudioFormatFlagIsSignedInteger;
                  }
                  
                  //	if the bit depth is 8 bits or less and the format is packed, we don't care about endianness
                  if((x.mBitsPerChannel <= 8) && ((xFlags & kAudioFormatFlagIsPacked) == kAudioFormatFlagIsPacked))
                  {
                     xFlags = xFlags & ~kAudioFormatFlagIsBigEndian;
                  }
                  if((y.mBitsPerChannel <= 8) && ((yFlags & kAudioFormatFlagIsPacked) == kAudioFormatFlagIsPacked))
                  {
                     yFlags = yFlags & ~kAudioFormatFlagIsBigEndian;
                  }
                  
                  //	if the number of channels is 0 or 1, we don't care about non-interleavedness
                  if (x.mChannelsPerFrame <= 1 && y.mChannelsPerFrame <= 1) {
                     xFlags &= ~kLinearPCMFormatFlagIsNonInterleaved;
                     yFlags &= ~kLinearPCMFormatFlagIsNonInterleaved;
                  }
               }
               return xFlags == yFlags;
            }

            bool	operator==(const AudioStreamBasicDescription& x, const AudioStreamBasicDescription& y)
            {
               //	the semantics for equality are:
               //		1) Values must match exactly
               //		2) wildcard's are ignored in the comparison
               
            #define MATCH(name) ((x.name) == 0 || (y.name) == 0 || (x.name) == (y.name))
               
               return
                     //	check the sample rate
               (fiszero(x.mSampleRate) || fiszero(y.mSampleRate) || fequal(x.mSampleRate, y.mSampleRate))
               
                     //	check the format ids
               && MATCH(mFormatID)
               
                     //	check the format flags
               && MatchFormatFlags(x, y)
               
                     //	check the bytes per packet
               && MATCH(mBytesPerPacket)
               
                     //	check the frames per packet
               && MATCH(mFramesPerPacket)
               
                     //	check the bytes per frame
               && MATCH(mBytesPerFrame)
               
                     //	check the channels per frame
               && MATCH(mChannelsPerFrame)
               
                     //	check the channels per frame
               && MATCH(mBitsPerChannel) ;
            }

            bool	CAStreamBasicDescription::IsEqual(const AudioStreamBasicDescription &other, bool interpretingWildcards) const
            {
               if (interpretingWildcards)
                  return *this == other;
               return __memcmp(this, &other, offsetof(AudioStreamBasicDescription, mReserved)) == 0;
            }

            bool SanityCheck(const AudioStreamBasicDescription& x)
            {
               // This function returns false if there are sufficiently insane values in any field.
               // It is very conservative so even some very unlikely values will pass.
               // This is just meant to catch the case where the data from a file is corrupted.
               
               return
               (x.mSampleRate >= 0.)
               && (x.mBytesPerPacket < 1000000)
               && (x.mFramesPerPacket < 1000000)
               && (x.mBytesPerFrame < 1000000)
               && (x.mChannelsPerFrame <= 1024)
               && (x.mBitsPerChannel <= 1024)
               && (x.mFormatID != 0)
               && !(x.mFormatID == kAudioFormatLinearPCM && (x.mFramesPerPacket != 1 || x.mBytesPerPacket != x.mBytesPerFrame));
            }

         
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




