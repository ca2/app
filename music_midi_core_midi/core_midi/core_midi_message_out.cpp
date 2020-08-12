//
//  message_out.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "core_midi.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {

         
         
         static mach_timebase_info_data_t sTimebaseInfo;

         UInt64 nano_to_absolute(UInt64 nano)
         {
            
            return nano * sTimebaseInfo.denom / sTimebaseInfo.numer;
            
         }



         // The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
         static CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal)
         {
            CFMutableStringRef result = CFStringCreateMutable(nullptr, 0);
            CFStringRef str;
            
            // begin with the endpoint's name
            str = nullptr;
            MIDIObjectGetStringProperty(endpoint, kMIDIPropertyName, &str);
            if (str != nullptr) {
               CFStringAppend(result, str);
               CFRelease(str);
            }
            
            MIDIEntityRef entity = 0;
            MIDIEndpointGetEntity(endpoint, &entity);
            if (entity == 0)
               // probably virtual
               return result;
            
            if (CFStringGetLength(result) == 0) {
               // endpoint name has zero length -- try the entity
               str = nullptr;
               MIDIObjectGetStringProperty(entity, kMIDIPropertyName, &str);
               if (str != nullptr) {
                  CFStringAppend(result, str);
                  CFRelease(str);
               }
            }
            // now consider the device's name
            MIDIDeviceRef device = 0;
            MIDIEntityGetDevice(entity, &device);
            if (device == 0)
               return result;
            
            str = nullptr;
            MIDIObjectGetStringProperty(device, kMIDIPropertyName, &str);
            if (str != nullptr) {
               // if an external device has only one entity, __throw( away
               // the endpoint name and just use the device name
               if (isExternal && MIDIDeviceGetNumberOfEntities(device) < 2) {
                  CFRelease(result);
                  return str;
               } else {
                  // does the entity name already start with the device name?
                  // (some drivers do this though they shouldn't)
                  // if so, do not prepend
                  if (CFStringCompareWithOptions(str /* device name */,
                                                 result /* endpoint name */,
                                                 CFRangeMake(0, CFStringGetLength(str)), 0) != kCFCompareEqualTo) {
                     // prepend the device name to the entity name
                     if (CFStringGetLength(result) > 0)
                        CFStringInsert(result, 0, CFSTR(" "));
                     CFStringInsert(result, 0, str);
                  }
                  CFRelease(str);
               }
            }
            return result;
         }


         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint)
         {
            CFMutableStringRef result = CFStringCreateMutable(nullptr, 0);
            CFStringRef str;
            OSStatus err;
            int i = 0;
            
            // Does the endpoint have connections?
            CFDataRef connections = nullptr;
            int nConnected = 0;
            bool anyStrings = false;
            err = MIDIObjectGetDataProperty(endpoint, kMIDIPropertyConnectionUniqueID, &connections);
            if (connections != nullptr) {
               // It has connections, follow them
               // Concatenate the names of all connected devices
               nConnected = (int) (CFDataGetLength(connections) / sizeof(MIDIUniqueID));
               if (nConnected) {
                  const SInt32 *pid = (SInt32*) CFDataGetBytePtr(connections);
                  for (i = 0; i < nConnected; ++i, ++pid) {
         #ifdef MACOS
                     MIDIUniqueID id = EndianS32_BtoN(*pid);
         #else
                     
               MIDIUniqueID id = *pid;
         #endif
                     MIDIObjectRef connObject;
                     MIDIObjectType connObjectType;
                     err = MIDIObjectFindByUniqueID(id, &connObject, &connObjectType);
                     if (err == noErr) {
                        if (connObjectType == kMIDIObjectType_ExternalSource  ||
                            connObjectType == kMIDIObjectType_ExternalDestination) {
                           // Connected to an external device's endpoint (10.3 and later).
                           str = EndpointName((MIDIEndpointRef)(connObject), true);
                           //str = EndpointName(connObject, true);
                        } else {
                           // Connected to an external device (10.2) (or something else, catch-all)
                           str = nullptr;
                           MIDIObjectGetStringProperty(connObject, kMIDIPropertyName, &str);
                        }
                        if (str != nullptr) {
                           if (anyStrings)
                              CFStringAppend(result, CFSTR(", "));
                           else anyStrings = true;
                           CFStringAppend(result, str);
                           CFRelease(str);
                        }
                     }
                  }
               }
               CFRelease(connections);
            }
            if (anyStrings)
               return result;
            
            // Here, either the endpoint had no connections, or we failed to obtain names for any of them.
            return EndpointName(endpoint, false);
         }

         // ------------------------------------------------------------------------------------------------------

         array < message_out::Destination > message_out::get_destinations()
         {
            
            array < message_out::Destination > destinations;
            
            ItemCount iEndpointCount = MIDIGetNumberOfDestinations();
            
            printf("[AUNotePlayer] %i MIDI destinations\n", (int)iEndpointCount);
            
            for (int iEndpoint =0; iEndpoint < (int) iEndpointCount; iEndpoint++)
            {
               
               MIDIEndpointRef endpoint = MIDIGetDestination(iEndpoint);
               
               CFStringRef name = ConnectedEndpointName(endpoint);
               
               char szBuffer[256];
               
               CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);
               
               CFRelease(name);
               
               printf("[AUNotePlayer]  %i - '%s'\n", iEndpoint, szBuffer);
               
               Destination destination;
               
               destination.m_endpoint = endpoint;
               
               destination.m_strName = szBuffer;
               
               destinations.add(destination);
               
            }
            
            return destinations;
            
         }


         message_out::message_out(::object * pobject, string driver)
         {
            
            auto estatus = initialize(pobject);
            
            if(!estatus)
            {
               
               throw ::exception::exception(estatus);
               
            }
            
            mach_timebase_info(&sTimebaseInfo);

            m_packetlist = nullptr;
            
            m_port = 0;
            
            OSStatus result = MIDIOutputPortCreate(m_client, CFSTR("music_midi_core_midi"), &m_port);

            if (result != 0)
            {
               
               string str;
               
               str.Format("MIDIOutputPortCreate failed with code %i\n", (int) result);
               
               throw resource_exception(str);
               
            }

            bool bFound = false;
            
            auto destinations  = get_destinations();
            
            for (unsigned int n = 0; n < destinations.size(); n++)
            {
               
               if (destinations[n].m_strName == driver)
               {
                  
                  m_endpoint = destinations[n].m_endpoint;
                  
                  bFound = true;
                  
                  return;
                  
               }
               
            }
            
            if(!bFound)
            {
            
               for (unsigned int n = 0; n < destinations.size(); n++)
               {
                  
                  if (destinations[n].m_strName == driver)
                  {
                  
                     m_endpoint = destinations[n].m_endpoint;
                  
                     bFound = true;
                  
                     return;
               
                  }
                  
               }
               
            }

            if (!bFound)
            {
               
               //wxMessageBox(_("Unknown MIDI port : ") + driver);
               
               m_endpoint = MIDIGetDestination(0);
               
            }
            
         }

      message_out::message_out()
      {
         
      }
     
      
      message_out::message_out(::object * pobject, int iPort)
      {
         auto estatus = initialize(pobject);
         
         if(!estatus)
         {
            
            throw ::exception::exception(estatus);
            
         }
         
         estatus = open(iPort);
         if(!estatus)
                {
                   
                   throw ::exception::exception(estatus);
                   
                }
                
      }
      
      
         ::estatus message_out::open(int iPort)
         {
         
            mach_timebase_info(&sTimebaseInfo);
            
            m_packetlist = nullptr;
            
            m_port = (MIDIPortRef) iPort;
            
            OSStatus result = MIDIOutputPortCreate(m_client, CFSTR("music_midi_core_midi"), &m_port);
            
            if (result != 0)
            {
               
               string str;
               
               str.Format("MIDIOutputPortCreate failed with code %i\n", (int) result);
               
               throw resource_exception(str);
               
            }
            
            bool bFound = false;
            
            auto destinations  = get_destinations();
            
            if(iPort >= 0 && iPort < destinations.size())
            {
               
                 m_endpoint = destinations[iPort].m_endpoint;
                  
                  bFound = true;
                  
            }
            
            if (!bFound)
            {
               
               //wxMessageBox(_("Unknown MIDI port : ") + driver);
               
               m_endpoint = MIDIGetDestination(0);
               
            }
            
            return ::success;
            
         }
         
         
         /*
         
         1. GM Reset (understood by every GM-compatible instrument)
         Sys-Ex String: F0 7E 7F 09 01 F7
         
         2. Roland GS Reset (Understood by all Roland GS instruments)
         Sys-Ex String: F0 41 10 42 12 40 00 7F 00 41 F7
         
         3. Yamaha XG reset (Understood by all Yamaha XG instruments)
         Sys-Ex String: F0 43 10 4C 00 00 7E 00 F7

         */

         void message_out::reset_all_controllers()
         {

            ::music::midi::message_out::reset_all_controllers();
            
         }


         message_out::~message_out()
         {
            
            MIDIPortDispose (m_port);
            
         }


         ::estatus message_out::note_off(int channel, unsigned char note, unsigned char velocity)
         {
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::note_off) | channel;
            
            message[1] = (byte) (0x7f & note);
            
            message[2] = (byte) (0x7f & velocity);
            
            add_short_message(message, 3);
            
            return ::success;
            
         }
         
         
         ::estatus message_out::note_on(int channel, unsigned char note, unsigned char volume)
         {

            Byte message[3];
            
            message[0] = (byte) (::music::midi::note_on) | channel;
            
            message[1] = (byte) (0x7f & note);
            
            message[2] = (byte) (0x7f & volume);
            
            add_short_message(message, 3);
            
            return ::success;
            
         }


         void message_out::control_change(int channel, unsigned char controller, unsigned char value)
         {
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::control_change) | channel;
            
            message[1] = (byte) (0x7f & controller);
            
            message[2] = (byte) (0x7f & value);
            
            add_short_message(message, 3);
            
         }
         
         
         ::estatus message_out::program_change(int channel, unsigned char instrument)
         {
            
            Byte message[2];
            
            message[0] = (byte) (::music::midi::program_change) | channel;
            
            message[1] = (byte) (0x7f & instrument);
            
            add_short_message(message, 2);
            
            return ::success;
            
         }
         
         
         void message_out::pitch_bend(int channel, unsigned short value)
         {
            
            int c1 = (value & 0x7F);
            
            int c2 = ((value >> 7) & 0x7F);
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::pitch_bend) | channel;
            
            message[1] = c1;
            
            message[2] = c2;
            
            add_short_message(message, 3);
            
         }
         
         
         void message_out::sysex(const ::block & block)
         {
            
#ifdef _DEBUG
            
            string strHex;
            
            strHex = ::hex::lower_from(block.get_data(), block.get_size());
            
            output_debug_string(strHex);
            
#endif
            
            m_memoryLongMessage.set_size(block.get_size() + 2);
            
            memcpy(&m_memoryLongMessage.get_data()[1], block.get_data(), block.get_size());
            
            m_memoryLongMessage[0] = 0xf0;
            
            m_memoryLongMessage[block.get_size() + 1] = 0xf7;
            
            add_long_message(m_memoryLongMessage.get_data(), (int) m_memoryLongMessage.get_size());
            
         }
         
         
         void message_out::step()
         {
            
            if(m_packetlist)
            {
            
               OSStatus result = MIDISend(m_port, m_endpoint, m_packetlist);
               
               if (result != 0)
               {
                  
                  fprintf(stderr, "MIDISend failed!!\n");
                  
               }
               
               m_packetlist = nullptr;
               
            }

         }


         void message_out::start()
         {

            
#ifdef MACOS2

            m_ui64Start =AudioGetCurrentHostTime();
         
#endif
            
         }
         
         
         void message_out::add_short_message(Byte * pmessage, int iSize)
         {
            
            if(iSize <= 0)
            {
               
               return;
               
            }
            
         #ifdef sysex
            MIDITimeStamp timestamp = m_ui64Start + nano_to_absolute((m_ps->m_timeFile - m_ps->m_timeFileStart + 100.0) * 1000000.0);
         #else
            MIDITimeStamp timestamp = 0;
         #endif
            
            if(m_packetlist == nullptr)
            {
            
               m_packetlist = (MIDIPacketList *) m_buffer;
            
               m_packet = MIDIPacketListInit(m_packetlist);
               
            }
            
            m_packet = MIDIPacketListAdd(m_packetlist, sizeof(m_buffer), m_packet, timestamp, iSize, pmessage);

         }

         
         void message_out::add_long_message(Byte * pmessage, int iSize)
         {
            
            step();
            
            add_short_message(pmessage, iSize);

         }
         

      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music



