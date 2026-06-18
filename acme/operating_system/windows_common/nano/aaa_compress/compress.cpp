//
// Created by camilo on 2025-07-11 04:42 <3ThomasBorregaardSorensen!!
//
//
// Created by camilo on 2024-05-27 02:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "compress.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/scoped_restore.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows_common/com/bstring.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include "acme/operating_system/windows_common/com/variant.h"
#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include <Shldisp.h>


namespace windows_common
{
    namespace nano
    {
        namespace compress
        {
            compress::compress()
            {
            }


            compress::~compress()
            {
            }


            void compress::unzip(const ::file::path& pathFolder, const ::payload& payloadZip)
            {
                comptr<IShellDispatch> pISD;

                comptr<Folder> pZippedFile;
                comptr<Folder> pDestination;

                long FilesCount = 0;
                comptr<IDispatch> pItem;
                comptr<FolderItems> pFilesInside;

                variant Options, OutFolder, InZipFile, Item;

                CoInitialize(NULL);

                directory_system()->create(pathFolder);


                {
                    // speccylad@twitch contribution recalled
                    at_end_of_scope
                    {
                        CoUninitialize();
                    };

                    HRESULT hr = pISD.CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER);

                    defer_throw_hresult(hr);

                    bstring bstrZip(payloadZip.as_file_path());

                    InZipFile.vt = VT_BSTR;
                    InZipFile.bstrVal = bstrZip;
                    pISD->NameSpace(InZipFile, &pZippedFile);
                    if (!pZippedFile)
                    {
                        //pISD->Release();
                        throw ::exception(error_failed, "pISD->NameSpace(InZipFile, &pZippedFile)");
                    }

                    bstring bstrFolder(pathFolder);

                    OutFolder.vt = VT_BSTR;
                    OutFolder.bstrVal = bstrFolder;
                    pISD->NameSpace(OutFolder, &pDestination);
                    if (!pDestination)
                    {
                        //pZippedFile->Release();
                        //pISD->Release();
                        throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (1)");
                    }

                    pZippedFile->Items(&pFilesInside);
                    if (!pFilesInside)
                    {
                        //pDestination->Release();
                        //pZippedFile->Release();
                        //pISD->Release();
                        throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (2)");
                    }

                    pFilesInside->get_Count(&FilesCount);
                    if (FilesCount < 1)
                    {
                        //pFilesInside->Release();
                        //pDestination->Release();
                        //pZippedFile->Release();
                        //pISD->Release();
                        throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (3)");
                    }

                    pFilesInside->QueryInterface(IID_IDispatch, (void**)&pItem);

                    Item.vt = VT_DISPATCH;
                    Item.pdispVal = pItem;

                    Options.vt = VT_I4;
                    Options.lVal = 1024 | 512 | 16 | 4; //http://msdn.microsoft.com/en-us/library/bb787866(VS.85).aspx

                    bool retval = pDestination->CopyHere(Item, Options) == S_OK;

                    //pItem->Release(); pItem = 0L;
                    //pFilesInside->Release(); pFilesInside = 0L;
                    //pDestination->Release(); pDestination = 0L;
                    //pZippedFile->Release(); pZippedFile = 0L;
                    //pISD->Release(); pISD = 0L;
                }
            }
        } // namespace compress
    } // namespace nano
} // namespace windows_common
