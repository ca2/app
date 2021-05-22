#include "framework.h"
#include "aqua/multimedia/_.h"
#include "tts_speaker.h"


#pragma comment(lib, "Shlwapi")

inline bool SpGetDefaultTokenFromCategoryIdAndLang(
   ::application * papp,
   const WCHAR * pszCategoryId,
   ISpObjectToken ** ppToken,
   const char * pszLang,
   const char * pszAttributes,
   BOOL fCreateCategoryIfNotExist = true);


//////////////////////////////////////////////////////////////////////////
//
// FILE: TextSpeaker.h
//
// Defines a simple C++ class to speak some text.
//
// by Giovanni Dicanio <gdicanio@mvps.org>
//
// 2010, December 28th
//
//////////////////////////////////////////////////////////////////////////

HRESULT out_file(::memory_file * f, WAVEFORMATEX & fmt, IStream * pStream)
{

   // Write the file headers
   f->write("RIFF----WAVEfmt ", 16);     // (chunk size_i32 to be filled in later)
   ::u32 dw = fmt.cbSize;
   f->write(&dw, sizeof(dw));
   f->write(&fmt, fmt.cbSize);
   // Write the data chunk header
   size_t data_chunk_pos = (size_t)f->get_position();
   f->write("data----", 8);  // (chunk size_i32 to be filled in later)




   // SAPI wrote to the stream and filled it up
   // but the position is still at the end
   // so we need to rewind back to the beginning
   // before we can read it
   ULARGE_INTEGER end;
   LARGE_INTEGER zero = {};
   HRESULT hr = pStream->Seek(zero, STREAM_SEEK_END, &end);
   if (FAILED(hr))
   {
      return hr;
   }
   hr = pStream->Seek(zero, STREAM_SEEK_SET, nullptr);
   if (FAILED(hr))
   {
      return hr;
   }
   auto iPos = f->get_size();
   f->set_size(f->get_size() + end.QuadPart);
   ULONG read = 0;
   hr = pStream->Read(&f->get_data()[iPos], (ULONG)f->get_size(), &read);

   size_t file_length = (size_t)f->get_size();

   // Fix the data chunk header to contain the data size_i32
   f->seek(data_chunk_pos + 4, ::file::seek_begin);
   dw = (::u32)(file_length - data_chunk_pos + 8);
   f->write(&dw, sizeof(::u32));


   // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
   f->seek(0 + 4, ::file::seek_begin);
   dw = (::u32)(file_length - 8);
   f->write(&dw, sizeof(::u32));
   return S_OK;
}


// Declare local identifiers:

inline HRESULT SpGetCategoryFromId(const WCHAR * pszCategoryId, ISpObjectTokenCategory ** ppCategory, BOOL fCreateIfNotExist = false)
{
   HRESULT hr;

   comptr < ISpObjectTokenCategory > pcategory;
   hr = pcategory.CoCreateInstance(CLSID_SpObjectTokenCategory);

   if (SUCCEEDED(hr))
   {
      hr = pcategory->SetId(pszCategoryId, fCreateIfNotExist);
   }

   if (SUCCEEDED(hr))
   {
      *ppCategory = pcategory.detach();
   }

   return hr;
}

inline HRESULT SpGetTokenFromId(const WCHAR * pszTokenId, ISpObjectToken ** ppToken, BOOL fCreateIfNotExist = false)
{
   HRESULT hr;

   comptr < ISpObjectToken > ptoken;
   hr = ptoken.CoCreateInstance(CLSID_SpObjectToken);

   if (SUCCEEDED(hr))
   {
      hr = ptoken->SetId(nullptr, pszTokenId, fCreateIfNotExist);
   }

   if (SUCCEEDED(hr))
   {
      *ppToken = ptoken.detach();
   }


   return hr;

}

inline HRESULT SpGetDefaultTokenFromCategoryId(
   const WCHAR * pszCategoryId,
   ISpObjectToken ** ppToken,
   BOOL fCreateCategoryIfNotExist = true)
{
   HRESULT hr;

   comptr<ISpObjectTokenCategory> pcategory;
   hr = SpGetCategoryFromId(pszCategoryId, &pcategory, fCreateCategoryIfNotExist);

   if (SUCCEEDED(hr))
   {
      cotaskptr < LPWSTR > pszTokenId;
      hr = pcategory->GetDefaultTokenId(&pszTokenId);
      if (SUCCEEDED(hr))
      {
         hr = SpGetTokenFromId(pszTokenId, ppToken);

      }
   }

   return hr;
}

inline bool SpGetDefaultTokenFromCategoryIdAndLang(
   ::application * papp,
   const WCHAR * pszCategoryId,
   ISpObjectToken ** ppToken,
   const char * pszLang,
   const char * pszAttributes,
   BOOL fCreateCategoryIfNotExist)
{

   HRESULT hr;

   comptr<ISpObjectTokenCategory> pcategory;

   hr = SpGetCategoryFromId(pszCategoryId, &pcategory, fCreateCategoryIfNotExist);

   string str(pszLang);

   str.make_lower();

   string strLang;

   if (str == "en" || str == "us" || str == "english")
   {

      strLang = "409";

   }
   else if (str == "pt" || str == "br" || str == "portugues" || str == unitext("português"))
   {

      strLang = "416";

   }
   else
   {

      ::property_set set;

      string strJson = papp->file().as_string(papp->dir().matter("speech/windows/lang.json"));

      const char * pszJson = strJson;

      try
      {

         set.parse_json(pszJson);

      }
      catch (...)
      {

      }

      if (set[str].get_string().has_char())
      {

         strLang = set[str];

      }
      else
      {

         strLang = "409";

      }

   }

   string strAttributes(pszAttributes);

   string_array straAttributes;

   straAttributes.add_smallest_tokens(strAttributes, { ";" });

   straAttributes.insert_at(0, "Language=" + strLang);

   //auto iFind = straAttributes.find_first_begins_ci("voice=");

   //string strVoice;

   //if (iFind >= 0)
   //{

   //   strVoice = straAttributes.erase_at(iFind);

   //}

   if (SUCCEEDED(hr))
   {
      //      WCHAR * pszTokenId;
      // Declare local identifiers:
      HRESULT                           hr = S_OK;
      comptr<IEnumSpObjectTokens>      cpSpEnumTokens;

      if (SUCCEEDED(hr))
      {

         hr = pcategory->EnumTokens(nullptr, nullptr, &cpSpEnumTokens);

      }

      ULONG ulCount;

      if (SUCCEEDED(hr))
      {

         cpSpEnumTokens->GetCount(&ulCount);

      }

      auto iAttributesToMatchCount = straAttributes.get_count();

      for (; iAttributesToMatchCount >= 0; iAttributesToMatchCount--)
      {

         for (ULONG i = 0; i < ulCount; i++)
         {

            comptr<ISpObjectToken> ptoken;

            hr = cpSpEnumTokens->Item(i, &ptoken);

            if (SUCCEEDED(hr))
            {

               bool bAllMatch = true;

               for (int iAttribute = 0; iAttribute < iAttributesToMatchCount; iAttribute++)
               {

                  wstring wstrAttribute = straAttributes[iAttribute];

                  BOOL bMatches;

                  hr = ptoken->MatchesAttributes(wstrAttribute, &bMatches);

                  if (FAILED(hr) || !bMatches)
                  {

                     bAllMatch = false;

                     break;

                  }

               }

               if (bAllMatch)
               {

                  *ppToken = ptoken;

                  ptoken.m_p = nullptr;

                  return true;

               }

            }

         }

      }

      //for (ULONG i = 0; i < ulCount; i++)
      //{

      //   comptr<ISpObjectToken> ptoken;

      //   hr = cpSpEnumTokens->Item(i, &ptoken);

      //   if (SUCCEEDED(hr))
      //   {

      //      wstring wstrLang;

      //      wstrLang = L"Language=";
      //      wstrLang += wstring(strLang);
      //      BOOL bMatches;

      //      hr = ptoken->MatchesAttributes(wstrLang, &bMatches);


      //      if (SUCCEEDED(hr) && bMatches)
      //      {
      //         *ppToken = ptoken;
      //         ptoken.m_p = nullptr;
      //         return true;
      //      }


      //   }

      //}

      return SUCCEEDED(SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, ppToken, false));

   }

   return SUCCEEDED(hr);
}


namespace tts_sapi
{


   namespace tts
   {


      //------------------------------------------------------------------------
      // Simple class to speak some text (using SAPI).
      //------------------------------------------------------------------------

      speaker::speaker()
      {

         defer_create_mutex();

         m_strDefaultLang = "en";

      }


      speaker::~speaker()
      {

      }

      //--------------------------------------------------------------------
      // Initializes the text speaker.
      //--------------------------------------------------------------------
      bool speaker::initialize(string strLang)
      {

         //finalize(strLang);

         //bool bOk = false;

         //fork([&]()
         //{

         //   defer_co_initialize_ex(true);


         ////
         //// Create text to speech engine
         ////
         //HRESULT hr = m_voice[strLang].CoCreateInstance(CLSID_SpVoice);
         //if (FAILED(hr))
         //{

         //   return;

         //}

         //if (strLang.is_empty())
         //{

         //   //
         //   // Get token corresponding to default voice
         //   //
         //   hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &m_token[strLang], false);

         //   if (FAILED(hr))
         //   {

         //      return;

         //   }

         //}
         //else
         //{

         //   //
         //   // Get token corresponding to default voice
         //   //
         //   hr = SpGetDefaultTokenFromCategoryIdAndLang(get_application(), L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", &m_token[strLang], strLang, false);

         //   if (FAILED(hr))
         //   {

         //      return;

         //   }

         //}


         //
         // Set default voice
         //
         //   hr = m_voice[strLang]->SetVoice(m_token[strLang]);

         //   if (FAILED(hr))
         //   {

         //      return;

         //   }

         //   bOk = true;

         //})->wait();

         //return bOk;
         return true;

      }


      bool speaker::initialize_translator(string strLang)
      {

         return false;

      }


      bool speaker::finalize(string strLang)
      {

         //fork([&]()
         //{

         //   defer_co_initialize_ex(true);


         //   if (m_voice[strLang].is_set())
         //   {

         //      m_voice[strLang]->Pause();

         //   }

         //   m_token[strLang].Release();

         //   m_voice[strLang].Release();

         //})->wait();


         return true;

      }


      bool speaker::finalize_translator(string strLang)
      {

         return false;

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & text)
      {

         return speak(m_strDefaultLang, text);

      }


      bool speaker::is_lang_ok(string strLang)
      {

         bool bTts = false;

         //if((!m_tts.lookup(strLang, bTts) || bTts) && m_voice[strLang].is_set() || (!is_speaking(strLang) && m_time.elapsed()[strLang] > 30 * 1000))
         //if (!m_tts.lookup(strLang, bTts))
         //{

         //   if (initialize(strLang))
         //   {

         //      bTts = true;

         //   }
         //   else
         //   {

         //      bTts = false;

         //   }

         //   m_tts[strLang] = bTts;

         //}

         return true;

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & strLangParam, const string & strTextParam, bool bSync)
      {

         string strLang(strLangParam);

         string strText(strTextParam);

         //
         // Input text must not be empty
         //
         if (strText.is_empty())
         {

            // nothing to speak?!?!
            return false;

         }

         //if (!is_lang_ok(strLang))
         //{

         //   return ::tts::speaker::speak(strLang, strText, bSync);

         //}

         synchronous_lock synchronouslock(mutex());

         defer_co_initialize_ex(false);

         comptr < ISpVoice > & pvoice = m_voice[strLang];

         HRESULT hr = S_OK;

         if (pvoice.is_null())
         {

            pvoice.CoCreateInstance(CLSID_SpVoice);

         }

         comptr < ISpObjectToken > & ptoken = m_token[strLang];

         if (ptoken.is_null())
         {

            if (strLang.is_empty())
            {

               hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &ptoken, false);

               if (FAILED(hr))
               {

                  return false;

               }

            }
            else
            {

               hr = SpGetDefaultTokenFromCategoryIdAndLang(get_application(), L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", &ptoken, strLang, "", false);

               if (FAILED(hr))
               {

                  return false;

               }

            }

            hr = pvoice->SetVoice(ptoken);

            if (FAILED(hr))
            {

               return false;

            }

         }

         comptr < ISpStream > pSpStream;

         hr = pSpStream.CoCreateInstance(CLSID_SpStream);

         if (FAILED(hr))
         {

            return false;

         }

         comptr < IStream > pStream;

         pStream = SHCreateMemStream(nullptr, 0);

         if (pStream.is_null())
         {

            return false;

         }

         WAVEFORMATEX fmt;

         fmt.cbSize = sizeof(WAVEFORMATEX);
         fmt.wBitsPerSample = 16;
         fmt.nChannels = 2;
         fmt.nBlockAlign = fmt.nChannels * fmt.wBitsPerSample / 8;
         fmt.wFormatTag = WAVE_FORMAT_PCM;
         fmt.nSamplesPerSec = 44100;
         fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nChannels * fmt.wBitsPerSample / 8;

         hr = pSpStream->SetBaseStream(
            pStream,
            SPDFID_WaveFormatEx,
            &fmt
         );

         if (FAILED(hr))
         {

            return false;

         }

         hr = pvoice->SetOutput(pSpStream, true);

         if (FAILED(hr))
         {

            return false;

         }

         string strT(strText);

         ::u32 uFlag = 0;

         strT.trim();

         //if (::str::begins_eat_ci(strT, "xml:"))
         {

            uFlag |= SPF_IS_XML;

         }
         //else
         //{

         // uiFlag |= SPF_IS_NOT_XML;

         //}

         wstring wstr(strT);


         //
         // Speak input text
         //
         ULONG streamNumber;

         //pvoice->WaitUntilDone(5 * 60 * 60 * 1000);

         hr = pvoice->Speak(
            wstr,
            //SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
            uFlag,
            &streamNumber);

         if (FAILED(hr))
         {

            return false;

         }

         auto pfile = create_memory_file();

         hr = out_file(pfile, fmt, pStream);

         if (FAILED(hr))
         {

            return false;

         }

         auto paudio = m_psystem->m_paquasystem->audio();

         paudio->play_audio(pfile, bSync);

         return true;

      }


      //--------------------------------------------------------------------
      // Speaks some text.
      // (The input text must not be empty.)
      //--------------------------------------------------------------------
      bool speaker::speak(const string & strAttributes, const string & strLangParam, const string & strTextParam, bool bSync)
      {

         string strLang(strLangParam);

         string strText(strTextParam);

         //
         // Input text must not be empty
         //
         if (strText.is_empty())
         {

            // nothing to speak?!?!
            return false;

         }

         //if (!is_lang_ok(strLang))
         //{

         //   return ::tts::speaker::speak(strLang, strText, bSync);

         //}

         synchronous_lock synchronouslock(mutex());

         defer_co_initialize_ex(false);

         comptr < ISpVoice > & pvoice = m_voice[strLang];

         HRESULT hr = S_OK;

         if (pvoice.is_null())
         {

            pvoice.CoCreateInstance(CLSID_SpVoice);

         }

         comptr < ISpObjectToken > & ptoken = m_token[strLang];

         if (ptoken.is_null())
         {

            if (strLang.is_empty())
            {

               hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &ptoken, false);

               if (FAILED(hr))
               {

                  return false;

               }

            }
            else
            {

               hr = SpGetDefaultTokenFromCategoryIdAndLang(get_application(), L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", &ptoken, strLang, strAttributes, false);

               if (FAILED(hr))
               {

                  return false;

               }

            }

            hr = pvoice->SetVoice(ptoken);

            if (FAILED(hr))
            {

               return false;

            }

         }

         comptr < ISpStream > pSpStream;

         hr = pSpStream.CoCreateInstance(CLSID_SpStream);

         if (FAILED(hr))
         {

            return false;

         }

         comptr < IStream > pStream;

         pStream = SHCreateMemStream(nullptr, 0);

         if (pStream.is_null())
         {

            return false;

         }

         WAVEFORMATEX fmt;

         fmt.cbSize = sizeof(WAVEFORMATEX);
         fmt.wBitsPerSample = 16;
         fmt.nChannels = 2;
         fmt.nBlockAlign = fmt.nChannels * fmt.wBitsPerSample / 8;
         fmt.wFormatTag = WAVE_FORMAT_PCM;
         fmt.nSamplesPerSec = 44100;
         fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nChannels * fmt.wBitsPerSample / 8;

         hr = pSpStream->SetBaseStream(
            pStream,
            SPDFID_WaveFormatEx,
            &fmt
         );

         if (FAILED(hr))
         {

            return false;

         }

         hr = pvoice->SetOutput(pSpStream, true);

         if (FAILED(hr))
         {

            return false;

         }

         string strT(strText);

         ::u32 uFlag = 0;

         strT.trim();

         //if (::str::begins_eat_ci(strT, "xml:"))
         {

            uFlag |= SPF_IS_XML;

         }
         //else
         //{

         // uiFlag |= SPF_IS_NOT_XML;

         //}

         wstring wstr(strT);


         //
         // Speak input text
         //
         ULONG streamNumber;

         //pvoice->WaitUntilDone(5 * 60 * 60 * 1000);

         hr = pvoice->Speak(
            wstr,
            //SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
            uFlag,
            &streamNumber);

         if (FAILED(hr))
         {

            return false;

         }

         auto pfile = create_memory_file();

         hr = out_file(pfile, fmt, pStream);

         if (FAILED(hr))
         {

            return false;

         }

         auto paudio = m_psystem->m_paquasystem->audio();

         paudio->play_audio(pfile, bSync);

         return true;

      }


      bool speaker::is_speaking(string strLang)
      {

         if (!is_lang_ok(strLang))
         {

            return ::tts::speaker::is_speaking(strLang);

         }

         synchronous_lock synchronouslock(mutex());

         if (m_voice[strLang].is_null())
         {

            return false;

         }

         SPVOICESTATUS status = {};

         HRESULT hr = m_voice[strLang]->GetStatus(&status, nullptr);

         if (FAILED(hr))
         {

            return false;

         }

         return (status.dwRunningState & SPRS_IS_SPEAKING) != false;

      }


      bool speaker::stop(string strLang)
      {

         if (!is_lang_ok(strLang))
         {

            return ::tts::speaker::stop(strLang);

         }

         //if (m_tts[strLang])
         //{

         //   finalize(strLang);

         //}
         //else
         //{

         //   finalize_translator(strLang);

         //}

         return true;

      }


   } // namespace tts


} // namespace tts_sapi


void tts_sapi_tts_speaker_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::tts_sapi::tts::speaker, ::tts::speaker >();

}







