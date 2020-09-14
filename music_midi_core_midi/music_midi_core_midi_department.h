#pragma once


namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {


         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI department :
            virtual public ::music::midi::midi
         {
         public:
            
            __pointer_array(::music::midi::message_out)                 m_messageouta;

            __pointer(::music::midi::midi)                         m_pmidiRealTime;
            
            __pointer(::music::midi::midi)                         m_pmidiCoreMidi;
            
            __pointer(::music::midi::message_out)                  m_pmessageout;


            department(::layered * pobjectContext);
            virtual ~department();

            
            virtual bool Initialize() override;
            

            virtual void enumerate_midi_out_devices() override;

            
            virtual ::estatus     enumerate_midi_devices() override;

            using ::music::midi::midi::translate_os_result;
            virtual ::estatus     translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText) override;

            virtual __pointer(::music::midi::sequencer) create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice) override;

            
            virtual __pointer(::music::midi::midi) get_device_midi(const string & strDevice);
            
            
            
         };
         
         
      } // namespace core_midi


   } // namespace midi


} // namespace music



