#include "framework.h"



//#define LOG(format, ...) TRACE(format, __VA_ARGS__)
CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);



namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {


         department::department(::object * pobject) :
            ::object(pobject),
            ::apex::department(pobject),
            ::music::midi::midi(pobject),
            ::music::midi::object(pobject)
         {

            m_pmidiRealTime = music_midi_real_time_new_midi(this);
            
            m_pmidiCoreMidi = music_midi_core_midi_new_midi(this);
            
            //m_uiMidiOutDevice = 0;

         }


         department::~department()
         {

         }

         
         bool department::Initialize()
         {
            
            if(!::music::midi::midi::Initialize())
            {
               
               return false;
               
            }
            
            //m_pmessageout = create_message_out();
            
            
            return true;

         }
         

         void department::enumerate_midi_out_devices()
         {
            
            for(auto pmessageout : m_messageouta)
            {

               string strName = pmessageout->m_strName + " (audio_unit)";
            
               add_midi_out_device(strName, "audio_unit");
               
            }
            
            ::music::midi::midi::enumerate_midi_out_devices();

            m_pmidiCoreMidi->call_enumerate_midi_out_devices();

         }
         

         ::e_status     department::enumerate_midi_devices()
         {

            return ::success;

         }


         ::e_status     department::translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText)
         {

            ::e_status     estatus = iOsResult == 0 ? ::success : error_failed;

            if (estatus == ::success)
            {
               
               return ::success;
               
            }

            return estatus;

         }
      
         
         __pointer(sequencer) department::create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice)
         {
            
            string strEngine = device_engine(strDevice);
            
            if (strEngine.compare_ci("real_time") == 0)
            {
               
               return m_pmidiRealTime->create_midi_sequencer(psequence, strDevice);
               
            }
            
            return m_pmidiCoreMidi->create_midi_sequencer(psequence, strDevice);
;
            
         }
            
         
                                                          __pointer(::music::midi::midi) department::get_device_midi(const string & strDevice)
         {

         string strEngine = device_engine(strDevice);

         if (m_pmidiCoreMidi->m_strName.compare_ci(strEngine) == 0)
         {

            return m_pmidiCoreMidi;

         }

            return ::music::midi::midi::get_device_midi(strEngine);

         }

         
      
      } // namespace core_midi
   
   
   } // namespace midi


} // namespace music


