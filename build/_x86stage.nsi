; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------


;!include "${NSISDIR}\Contrib\Modern UI\System.nsh"
!include x64.nsh
;!define MUI_ICON "C:\fraser\app-ca2\appmatter\tranquillum_composite\_std\_std\main\icon.ico"

	!define /date MyTIMESTAMP "%Y-%m-%d-%H-%M-%S"
	!define MUI_PRODUCT "app ${MyTIMESTAMP}" 
	Name "app ${MyTIMESTAMP}"
	
;--------------------------------
;General

	;Properly display all languages (Installer will not work on Windows 95, 98 or ME!)
	Unicode true


; The default installation directory
InstallDir "$PROGRAMFILES\app_core_build"

; The file to write
OutFile "A:\\Dropbox\\stage\\app_core_build ${MyTIMESTAMP}.exe"


; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\ca2\app-core\hellomultiverse" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "app_core_build (required)"

  SectionIn RO

  SetShellVarContext current

  ; Set output path to the installation directory.
  ;SetOutPath "$PROFILE\School Composite Example"
  
  ; Put file there
  ;File /r "C:\Users\camilo\School Composite Template\"
  
  ; Set output path to the installation directory.
  SetOutPath "$APPDATA\ca2\appmatter\app\_matter\main"
  
  ; Put file there
  File /r "C:\basis\source\app\_matter\main\"
  
  ; Set output path to the installation directory.
  SetOutPath "$APPDATA\ca2\appmatter\app-core\_matter\hellomultiverse"
  
  ; Put file there
  File /r "C:\basis\source\app-core\_matter\hellomultiverse\"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\time\stage\Win32"
  
  ; Put file there
  File "C:\basis\time-windows\Win32\stage\acme.dll"
  File "C:\basis\time-windows\Win32\stage\apex.dll"
  File "C:\basis\time-windows\Win32\stage\aqua.dll"
  File "C:\basis\time-windows\Win32\stage\aura.dll"
  File "C:\basis\time-windows\Win32\stage\axis.dll"
  File "C:\basis\time-windows\Win32\stage\base.dll"
  File "C:\basis\time-windows\Win32\stage\bred.dll"
  File "C:\basis\time-windows\Win32\stage\core.dll"
  File "C:\basis\time-windows\Win32\stage\acme_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\acme_windows.dll"
  File "C:\basis\time-windows\Win32\stage\apex_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\apex_windows.dll"
  File "C:\basis\time-windows\Win32\stage\aura_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\aura_windows.dll"
  File "C:\basis\time-windows\Win32\stage\database_sqlite3.dll"
  File "C:\basis\time-windows\Win32\stage\draw2d_gdiplus.dll"
  File "C:\basis\time-windows\Win32\stage\experience_core.dll"
  File "C:\basis\time-windows\Win32\stage\gcom.dll"
  File "C:\basis\time-windows\Win32\stage\imaging_wic.dll"
  File "C:\basis\time-windows\Win32\stage\libcrypto-1_1.dll"
  File "C:\basis\time-windows\Win32\stage\libssl-1_1.dll"
  File "C:\basis\time-windows\Win32\stage\pcre.dll"
  File "C:\basis\time-windows\Win32\stage\node_windows.dll"
  File "C:\basis\time-windows\Win32\stage\sqlite.dll"
  File "C:\basis\time-windows\Win32\stage\zlib.dll"
  File "C:\basis\time-windows\Win32\stage\bzip2.dll"
  File "C:\basis\time-windows\Win32\stage\windowing_win32.dll"
  File "C:\basis\time-windows\Win32\stage\write_text_win32.dll"
  File "C:\basis\time-windows\Win32\stage\app_core_build.dll"
  File "C:\basis\time-windows\Win32\stage\app_core_build.exe"
  File "C:\Program Files\Microsoft Visual Studio\2022\Thumbnail\VC\Redist\MSVC\v143\vc_redist.x86.exe"
  
${If} ${Runningx64}
	ReadRegStr $1 HKLM "SOFTWARE\Wow6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x86" "Installed"
	StrCmp $1 1 installed_redist
${Else}
	ReadRegStr $1 HKLM "SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x86" "Installed"
	StrCmp $1 1 installed_redist
${EndIf}

  ;not installed, so run the installer
  ExecWait  '"$INSTDIR\time\stage\Win32\vc_redist.x86.exe" /install /passive /norestart'

installed_redist:

  ;we are done
  ExecWait '"$INSTDIR\time\stage\Win32\app_core_build.exe" : install' $0
  
  ; Write the installation path into the registry
  WriteRegStr HKLM "SOFTWARE\ca2\app-core\hellomultiverse" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "DisplayName" "composite"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
  CreateShortCut "$DESKTOP\app.lnk" "$INSTDIR\time\stage\Win32\app_core_build.exe" ""

  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\composite"
  CreateShortcut "$SMPROGRAMS\composite\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\composite\app.lnk" "$INSTDIR\time\stage\Win32\app_core_build.exe" "" "$INSTDIR\time\stage\Win32\app_core_build.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_build"
  DeleteRegKey HKLM "SOFTWARE\ca2\app-core\hellomultiverse"

  ; Remove files and uninstaller
  Delete "$INSTDIR\app_core_build.nsi"
  Delete "$INSTDIR\uninstall.exe"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\app_core_build\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\app_core_build"
  RMDir /r "$INSTDIR/time"
  RMDir "$INSTDIR"

SectionEnd
