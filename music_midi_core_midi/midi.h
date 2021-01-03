#pragma once


namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {
      
      
         struct Endpoint
         {
               
            MIDIEndpointRef      m_endpoint;
            string               m_strName;
               
         };


         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI midi :
            virtual public ::music::midi::midi
         {
         public:
            
            
            __pointer_array(::music::midi::message_out)              m_messageouta;
            __pointer_array(::music::midi::message_in)               m_messageina;


            midi();
            virtual ~midi();

            
            virtual bool Initialize() override;
            
            
            array < Endpoint > get_source_endpoints();

            array < Endpoint > get_destination_endpoints();
            

            virtual void enumerate_midi_out_devices() override;

            virtual void enumerate_midi_in_devices() override;

            
            virtual ::e_status enumerate_midi_devices() override;

            using ::music::midi::midi::translate_os_result;
            virtual ::e_status translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText) override;

            virtual __pointer(::music::midi::sequencer) create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice) override;
            
            __pointer(::music::midi::message_out)
            get_message_out(const string & strDevice) override;
            
            __pointer(::music::midi::message_in)
            get_message_in(const string & strDevice) override;

            
            virtual __pointer(::music::midi::midi) get_device_midi(const string & strDevice);
            
            
            
         };
         
         
      } // namespace core_midi


   } // namespace midi


} // namespace music



