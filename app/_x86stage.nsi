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
InstallDir "$PROGRAMFILES\app_app"

; The file to write
OutFile "A:\\Dropbox\\stage\\app_app ${MyTIMESTAMP}.exe"


; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\ca2\app\app" "Install_Dir"

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
Section "tranquillum_composite (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  ;SetOutPath "$PROFILE\School Composite Example"
  
  ; Put file there
  ;File /r "C:\Users\camilo\School Composite Template\"
  
  ; Set output path to the installation directory.
  ;SetOutPath "$INSTDIR\app\appmatter\main"
  
  ; Put file there
  ;File /r "C:\fraser\app\appmatter\main\"
  
  ; Set output path to the installation directory.
  ;SetOutPath "$INSTDIR\tranquillum\appmatter\composite"
  
  ; Put file there
  ;File /r "C:\fraser\tranquillum\appmatter\composite\"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\time\stage\Win32"
  
  ; Put file there
  File "C:\basis\time-windows\Win32\stage\acme.dll"
  File "C:\basis\time-windows\Win32\stage\apex.dll"
  File "C:\basis\time-windows\Win32\stage\aqua.dll"
  File "C:\basis\time-windows\Win32\stage\aura.dll"
  File "C:\basis\time-windows\Win32\stage\acme_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\acme_windows.dll"
  File "C:\basis\time-windows\Win32\stage\apex_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\apex_windows.dll"
  File "C:\basis\time-windows\Win32\stage\aura_windows_common.dll"
  File "C:\basis\time-windows\Win32\stage\aura_windows.dll"
  File "C:\basis\time-windows\Win32\stage\draw2d_gdiplus.dll"
  File "C:\basis\time-windows\Win32\stage\libcrypto-1_1.dll"
  File "C:\basis\time-windows\Win32\stage\libssl-1_1.dll"
  File "C:\basis\time-windows\Win32\stage\pcre.dll"
  File "C:\basis\time-windows\Win32\stage\node_windows.dll"
  File "C:\basis\time-windows\Win32\stage\zlib.dll"
  File "C:\basis\time-windows\Win32\stage\windowing_win32.dll"
  File "C:\basis\time-windows\Win32\stage\app_app.exe"
  File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\v142\vc_redist.x86.exe"
  
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
  ExecWait '"$INSTDIR\time\stage\Win32\app_app.exe" : install' $0
  
  ; Write the installation path into the registry
  WriteRegStr HKLM "SOFTWARE\ca2\app\app" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_app" "DisplayName" "composite"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_app" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_app" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_app" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
  CreateShortCut "$DESKTOP\composite.lnk" "$INSTDIR\time\stage\Win32\app_app.exe" ""

  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\composite"
  CreateShortcut "$SMPROGRAMS\composite\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\composite\app.lnk" "$INSTDIR\time\x86\stage\app_app.exe" "" "$INSTDIR\time\stage\Win32\app_app.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_app"
  DeleteRegKey HKLM "SOFTWARE\ca2\app\app"

  ; Remove files and uninstaller
  Delete "$INSTDIR\app_app.nsi"
  Delete "$INSTDIR\uninstall.exe"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\app_app\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\app_app"
  RMDir /r "$INSTDIR/time"
  RMDir "$INSTDIR"

SectionEnd
