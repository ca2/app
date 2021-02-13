#include "framework.h"



namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {

      

         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);

         ::u3264 nano_to_absolute(::u3264 nano);

         // The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
         CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal);


         midi::midi()
         {
            
            mach_init_timebase();

            m_pmidiRealTime = music_midi_real_time_new_midi();
            
         }


         midi::~midi()
         {

         }

         
         bool midi::Initialize()
         {
            
            if(!::music::midi::midi::Initialize())
            {
               
               return false;
               
            }
            
            return true;

         }
      
      
         array < Endpoint > midi::get_source_endpoints()
         {

            array < Endpoint > sources;

            ItemCount iEndpointCount = MIDIGetNumberOfSources();

            printf("Found %i MIDI Sources\n", (int)iEndpointCount);

            for (int iEndpoint = 0; iEndpoint < (int) iEndpointCount; iEndpoint++)
            {

               MIDIEndpointRef endpoint = MIDIGetSource(iEndpoint);

               CFStringRef name = ConnectedEndpointName(endpoint);

               char szBuffer[256];

               CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);

               CFRelease(name);

               output_debug_string("Source:" + __str(iEndpoint) + " - '" + string(szBuffer) + "'\n");

               Endpoint source;

               source.m_endpoint = endpoint;

               source.m_strName = szBuffer;

               sources.add(source);

            }

            return sources;

         }

      
         array < Endpoint > midi::get_destination_endpoints()
         {
            
            array < Endpoint > destinations;
            
            ItemCount iEndpointCount = MIDIGetNumberOfDestinations();
            
            output_debug_string(__str(iEndpointCount) + " MIDI destinations\n");
            
            for (int iEndpoint =0; iEndpoint < (int) iEndpointCount; iEndpoint++)
            {
               
               MIDIEndpointRef endpoint = MIDIGetDestination(iEndpoint);
               
               CFStringRef name = ConnectedEndpointName(endpoint);
               
               char szBuffer[256];
               
               CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);
               
               CFRelease(name);
               
               output_debug_string("Destination:" + __str(iEndpoint) + " - '" + string(szBuffer) + "'\n");
               
               Endpoint destination;
               
               destination.m_endpoint = endpoint;
               
               destination.m_strName = szBuffer;
               
               destinations.add(destination);
               
            }
            
            return destinations;
            
         }

         
         void midi::enumerate_midi_out_devices()
         {
            
            ::output_debug_string("music::midi::core_midi::enumerate_midi_out_devices\n");
            
            add_midi_out_device("DLS Synth", "core_midi");
            
            auto sources = get_destination_endpoints();
            
            for(auto & source : sources)
            {
               
               add_midi_out_device(source.m_strName, "core_midi");
               
            }

            ::music::midi::midi::enumerate_midi_out_devices();

         }

      
         void midi::enumerate_midi_in_devices()
         {
            
            ::output_debug_string("music::midi::core_midi::enumerate_midi_in_devices\n");
            
            auto sources = get_source_endpoints();
            
            for(auto & source : sources)
            {
               
               add_midi_in_device(source.m_strName, "core_midi");
               
            }
            
            ::music::midi::midi::enumerate_midi_in_devices();

         }


         ::e_status     midi::enumerate_midi_devices()
         {

            return ::success;

         }


         ::e_status     midi::translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText)
         {

            ::e_status     estatus = iOsResult == 0 ? ::success : error_failed;

            if (estatus == ::success)
            {
               
               return ::success;
               
            }

            return estatus;

         }
      
         
         __pointer(::music::midi::sequencer) midi::create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice)
         {
            
            string strEngine = device_engine(strDevice);
            
            if (strEngine.is_empty() || strEngine.compare_ci(m_strName) == 0)
            {
               
               auto pmessageout = get_message_out(strDevice);
               
               return __new(::music::midi::sequencer(psequence, pmessageout));
               
            }
            
            return ::music::midi::midi::create_midi_sequencer(psequence, strDevice);
            
         }

      class my_message_out:
      public ::music::midi::message_out
      {
      public:
         
         
         AUNode                  m_nodeOutput;
         AUNode                  m_nodeSynth;
         AUGraph                 m_audiograph;
         
         AudioUnit               m_unitOutput;
         MusicDeviceComponent    m_unitSynth;
         
         
         
         my_message_out()
         {
            
            open(0);
            
         }
         
         
         virtual ::e_status open(int iPort) override
         {
            
            OSStatus result = noErr;
            
            result = NewAUGraph(&m_audiograph);
            
            if (noErr != result)
            {
                               
               return ::error_failed;
                               
            }

            AudioComponentDescription descriptionSynth ={};
            descriptionSynth.componentType           = kAudioUnitType_MusicDevice;
            descriptionSynth.componentSubType        = kAudioUnitSubType_DLSSynth;
            descriptionSynth.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionSynth.componentFlags          = 0;
            descriptionSynth.componentFlagsMask      = 0;
            
            result = AUGraphAddNode (m_audiograph, &descriptionSynth, &m_nodeSynth);

            if (noErr != result)
            {
                               
               return ::error_failed;
                               
            }
            
            AudioComponentDescription descriptionOutput={};
            descriptionOutput.componentType           = kAudioUnitType_Output;
            descriptionOutput.componentSubType        = kAudioUnitSubType_DefaultOutput;
            descriptionOutput.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionOutput.componentFlags          = 0;
            descriptionOutput.componentFlagsMask      = 0;

            result = AUGraphAddNode(m_audiograph, &descriptionOutput, &m_nodeOutput);
            
            if (noErr != result)
            {
                       
               return ::error_failed;
                       
            }
            
            // 6.connect input->eq->output node
            result = AUGraphConnectNodeInput(m_audiograph, m_nodeSynth, 0,m_nodeOutput, 0);
            if (noErr != result)
            {
                       
               return ::error_failed;
                       
            }
            
            result = AUGraphUpdate (m_audiograph, NULL);
            if (noErr != result)
                   {
                              
                      return ::error_failed;
                              
                   }

            // 3.open augraphic
            result = AUGraphOpen(m_audiograph);
            if (noErr != result)
            {
               
               return ::error_failed;
               
            }

            // 4.get audio unit instance from nodes
            result = AUGraphNodeInfo(m_audiograph, m_nodeOutput, NULL, &m_unitOutput);
            
            if (noErr != result)
            {
                       
               return ::error_failed;
                       
            }
            
            // 7. initialize graphic
              result = AUGraphInitialize(m_audiograph);
              if (noErr != result)
              {
                         
                 return ::error_failed;
                         
              }
              

            result = AUGraphNodeInfo(m_audiograph, m_nodeSynth, NULL, &m_unitSynth);
            
            if (noErr != result)
            {
                       
               return ::error_failed;
                       
            }



  
             CAShow(m_audiograph);
            
             
            // Start the graph
            result = AUGraphStart (m_audiograph);
             
            if (noErr != result)
              {
                         
                 return ::error_failed;
                         
              }
            return ::success;
         }
         
                     virtual ::e_status note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override
         {
            
            int noteOnCommand = ::u32(0x90 | iChannel);
            OSStatus result=MusicDeviceMIDIEvent (m_unitSynth, noteOnCommand, uchNote, uchVelocity, 0);
            
            if (noErr != result)
                  {
                             
                     return ::error_failed;
                             
                  }
            return ::success;
         }
         virtual ::e_status note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override
         {
            int noteOnCommand = ::u32(0x80 | iChannel);
                OSStatus result=    MusicDeviceMIDIEvent (m_unitSynth, noteOnCommand, uchNote, uchVelocity, 0);
                    
                    if (noErr != result)
                          {
                                     
                             return ::error_failed;
                                     
                          }
                    return ::success;
         }
         virtual ::e_status program_change(int iChannel, unsigned char uchProgram) override
         {
            
            
            return ::success;
            
         }

         
      };
         
         __pointer(::music::midi::message_out) midi::get_message_out(const string & strDevice)
         {
            
            if(strDevice == "core_midi:DLS Synth")
            {
               
               return __create_new<my_message_out>();
               
            }
            
            auto iPort = get_midi_out_device_port(strDevice);
            
            //if (iPort >= 0 && iPort < m_cPortCount)
            {
               
               auto & pmessageout = m_mapMessageOut[strDevice];
               
               if (!pmessageout)
               {
                  
                  auto pmidiout = __new(message_out(this, maximum(0, (int) iPort)));
                  
                  pmessageout = pmidiout;
                  
               }
               
               return pmessageout;
               
            }
            
            return nullptr;
            
         }

      
      __pointer(::music::midi::message_in) midi::get_message_in(const string & strDevice)
      {
         
//         if(strDevice == "core_midi:DLS Synth")
//         {
//            
//            return __create_new<my_message_in>();
//            
//         }
         
         auto iPort = get_midi_in_device_port(strDevice);
         
         if (iPort >= 0)
         {
            
            auto & pmessagein = m_mapMessageIn[strDevice];
            
            if (!pmessagein)
            {
               
               auto pmidiin = __new(message_in(this, maximum(0, (int) iPort)));
               
               pmessagein = pmidiin;
               
            }
            
            return pmessagein;
            
         }
         
         return nullptr;
         
      }

         
         __pointer(::music::midi::midi) midi::get_device_midi(const string & strDevice)
         {

            string strEngine = device_engine(strDevice);

            if (m_strName.compare_ci(strEngine) == 0)
            {

               return this;

            }

            return ::music::midi::midi::get_device_midi(strEngine);

         }

      
         // The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
         CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal)
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
            {

               return result;
               
            }
            
            // Here, either the endpoint had no connections, or we failed to obtain names for any of them.
            return EndpointName(endpoint, false);
         }

               
      } // namespace core_midi
   
   
   } // namespace midi


} // namespace music



