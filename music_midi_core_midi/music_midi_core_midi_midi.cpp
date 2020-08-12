#include "framework.h"
#include "core_midi_output_base.h"
#include "core_midi/core_midi_sequencer.h"
#include "core_midi/core_midi_message_out.h"


//#define LOG(format, ...) TRACE(format, __VA_ARGS__)
CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);



namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {


         midi::midi()
         {

            m_pmidiRealTime = music_midi_real_time_new_midi();
            
            //m_pmidiCoreMidi = music_midi_core_midi_new_midi(this);
            
            //m_uiMidiOutDevice = 0;

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
            
            //m_pmessageout = create_message_out();
            
            
            return true;

         }
         

         void midi::enumerate_midi_out_devices()
         {
            
//            for(auto pmessageout : m_messageouta)
//            {
//
//               string strName = pmessageout->m_strName + " (audio_unit)";
//
//               add_midi_out_device(strName, "audio_unit");
//
//            }
            
            add_midi_out_device("DLS Synth", "core_midi");
            
            ::music::midi::midi::enumerate_midi_out_devices();

            //m_pmidiCoreMidi->call_enumerate_midi_out_devices();

         }
         

         ::estatus     midi::enumerate_midi_devices()
         {

            return ::success;

         }


         ::estatus     midi::translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText)
         {

            ::estatus     estatus = iOsResult == 0 ? ::success : error_failed;

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
         
         
         virtual ::estatus open(int iPort) override
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
         
                     virtual ::estatus note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override
         {
            
            int noteOnCommand = UInt32(0x90 | iChannel);
            OSStatus result=MusicDeviceMIDIEvent (m_unitSynth, noteOnCommand, uchNote, uchVelocity, 0);
            
            if (noErr != result)
                  {
                             
                     return ::error_failed;
                             
                  }
            return ::success;
         }
         virtual ::estatus note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override
         {
            int noteOnCommand = UInt32(0x80 | iChannel);
                OSStatus result=    MusicDeviceMIDIEvent (m_unitSynth, noteOnCommand, uchNote, uchVelocity, 0);
                    
                    if (noErr != result)
                          {
                                     
                             return ::error_failed;
                                     
                          }
                    return ::success;
         }
         virtual ::estatus program_change(int iChannel, unsigned char uchProgram) override
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
                  
                  auto pmidiout = __new(message_out(this, MAX(0, (int) iPort)));
                  
                  pmessageout = pmidiout;
                  
               }
               
               return pmessageout;
               
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

         
      } // namespace core_midi
   
   
   } // namespace midi


} // namespace music



