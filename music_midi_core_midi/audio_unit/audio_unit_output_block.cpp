//
//  AUOutputBL.cpp
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
         
                  
         AUOutputBL::AUOutputBL (const CAStreamBasicDescription &inDesc, UInt32 inDefaultNumFrames)
         : mFormat (inDesc),
         mBufferMemory(nullptr),
         mBufferList (nullptr),
         mNumberBuffers (0), // keep this here, so can ensure integrity of ABL
         mBufferSize (0),
         mFrames(inDefaultNumFrames)
         {
            mNumberBuffers = mFormat.IsInterleaved() ? 1 : mFormat.NumberChannels();
            mBufferList = reinterpret_cast<AudioBufferList*>(new Byte[offsetof(AudioBufferList, mBuffers) + (mNumberBuffers * sizeof(AudioBuffer))]);
         }

         AUOutputBL::~AUOutputBL()
         {
            if (mBufferMemory)
               delete[] mBufferMemory;
            
            if (mBufferList)
               delete [] (Byte *)mBufferList;
         }

         void 	AUOutputBL::Prepare (UInt32 inNumFrames, bool inWantNullBufferIfAllocated)
         {
            UInt32 channelsPerBuffer = mFormat.IsInterleaved() ? mFormat.NumberChannels() : 1;
            
            if (mBufferMemory == nullptr || inWantNullBufferIfAllocated)
            {
               mBufferList->mNumberBuffers = mNumberBuffers;
               AudioBuffer *buf = &mBufferList->mBuffers[0];
               for (UInt32 i = 0; i < mNumberBuffers; ++i, ++buf) {
                  buf->mNumberChannels = channelsPerBuffer;
                  buf->mDataByteSize = mFormat.FramesToBytes (inNumFrames);
                  buf->mData = nullptr;
               }
            }
            else
            {
               UInt32 nBytes = mFormat.FramesToBytes (inNumFrames);
               if ((nBytes * mNumberBuffers) > AllocatedBytes())
                  throw(OSStatus(kAudioUnitErr_TooManyFramesToProcess));
               
               mBufferList->mNumberBuffers = mNumberBuffers;
               AudioBuffer *buf = &mBufferList->mBuffers[0];
               Byte* p = mBufferMemory;
               for (UInt32 i = 0; i < mNumberBuffers; ++i, ++buf) {
                  buf->mNumberChannels = channelsPerBuffer;
                  buf->mDataByteSize = nBytes;
                  buf->mData = p;
                  p += mBufferSize;
               }
            }
         }


         void	AUOutputBL::Allocate (UInt32 inNumFrames)
         {
            if (inNumFrames)
            {
               UInt32 nBytes = mFormat.FramesToBytes (inNumFrames);
               
               if (nBytes <= AllocatedBytes())
                  return;
               
               // align successive buffers for Altivec and to take alternating
               // cache line hits by spacing them by odd multiples of 16
               if (mNumberBuffers > 1)
                  nBytes = (nBytes + (0x10 - (nBytes & 0xF))) | 0x10;
               
               mBufferSize = nBytes;
               
               UInt32 memorySize = mBufferSize * mNumberBuffers;
               Byte *newMemory = new Byte[memorySize];
               __memset(newMemory, 0, memorySize);	// make buffer "hot"
               
               Byte *oldMemory = mBufferMemory;
               mBufferMemory = newMemory;
               delete[] oldMemory;
               
               mFrames = inNumFrames;
            }
            else
            {
               if (mBufferMemory) {
                  delete [] mBufferMemory;
                  mBufferMemory = nullptr;
               }
               mBufferSize = 0;
               mFrames = 0;
            }
         }

         #ifdef _DEBUG
         void			AUOutputBL::Print()
         {
            printf ("AUOutputBL::Print\n");
            mFormat.Print();
            printf ("Num Buffers:%d, mFrames:%d, allocatedMemory:%c\n", (int)mBufferList->mNumberBuffers, (int)mFrames, (mBufferMemory != nullptr ? 'T' : 'F'));
            AudioBuffer *buf = &mBufferList->mBuffers[0];
            for (UInt32 i = 0; i < mBufferList->mNumberBuffers; ++i, ++buf)
               printf ("\tBuffer:%d, Size:%d, Chans:%d, Buffer:%p\n", (int)i, (int)buf->mDataByteSize, (int)buf->mNumberChannels, buf->mData);
         }
         #endif
                  
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




