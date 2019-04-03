!include "MUI.nsh"

Name "switch"

OutFile "switch_installer.exe"

SetCompressor lzma

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_INSTFILES


!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "Russian"
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
!define MUI_FINISHPAGE_SHOWREADME ""

!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED

!define MUI_FINISHPAGE_SHOWREADME_FUNCTION finishpageaction

!define PACKAGE_DIR "PACKAGE"

!define PRODUCT_NAME "Switch_com"
!define SERVICE_NAME "Switch"

#!define SERVICE_FILE_NAME "utservice.exe"

!define PRODUCT_VERSION "0.2"

!define OS_VERSION "Win32"

Caption "��������� ${PRODUCT_NAME} ${PRODUCT_VERSION}"
Name "switch"
OutFile "${PRODUCT_NAME}-${OS_VERSION}-${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\Switch"


Function .onInit
	SetOutPath "$TEMP"
	File "${PACKAGE_DIR}\gonets.bmp" 
	advsplash::show  1000 600 400 -1  "$TEMP\gonets"
FunctionEnd

Section "���������� ������" SecMain
	SetOutPath "$INSTDIR"
	SectionIn  RO 

	#�������� ������������� �������
	#SimpleSC::ExistsService "${SERVICE_NAME}"
	#Pop $0 ; 
	
	#��������� ��� ���� ������ ����������
	#StrCmp $0 "0" ServiceExist ServiceNotExist
	#ServiceExist:
		#SimpleSC::StopService "${SERVICE_NAME}" 1 30
		#Pop $0 ; 
		#MessageBox MB_OK "��������� ������ utservice"
			
		#������ ������ �� ������ ������
		#SimpleSC::RemoveService "${SERVICE_NAME}"
		#Pop $0 ; 
		#MessageBox MB_OK "�������� ������ ${SERVICE_NAME} $0"
	#ServiceNotExist:
	
	
	IfFileExists "$INSTDIR\switch.exe" 0 NotFiles
		MessageBox MB_OKCANCEL  "������� ����� �� ���������� ����������, �������������� ��������� ������?" IDOK reinstall IDCANCEL Endlabel
	
		reinstall:
			Delete "$INSTDIR\utservice.exe" 
			Delete "$INSTDIR\utmonitor.exe"
			Delete "$INSTDIR\icudt51.dll"
			Delete "$INSTDIR\icuin51.dll"
			Delete "$INSTDIR\icuuc51.dll"
			Delete "$INSTDIR\libEGL.dll"
			Delete "$INSTDIR\libGLESv2.dll"
			Delete "$INSTDIR\Qt5Core.dll"
			Delete "$INSTDIR\Qt5Gui.dll"
			Delete "$INSTDIR\Qt5Network.dll"
			Delete "$INSTDIR\Qt5Widgets.dll"
			Delete "$INSTDIR\Qt5Xml.dll"
			Delete "$SMPROGRAMS\Switch\Switch.lnk"
			Delete "$DESKTOP\COM_SWITCH.lnk"
			Delete "$INSTDIR\Doc\UserGuide.pdf"
			
			Delete "$INSTDIR\libgcc_s_dw2-1.dll"
			Delete "$INSTDIR\libGLESv2.dll"
			Delete "$INSTDIR\libstdc++-6.dll"
			Delete "$INSTDIR\libwinpthread-1.dll"
			Delete "$INSTDIR\Qt5Concurrent.dll"
			Delete "$INSTDIR\2port-icon.ico"
			Delete "$INSTDIR\Qt5SerialPort.dll"
			Delete "$INSTDIR\switch.exe"
			Delete "$INSTDIR\uninst.exe"
	NotFiles:
		
	
	#������� ��� ��� ��� �������	
	#File "${PACKAGE_DIR}\${SERVICE_FILE_NAME}"
	#File "${PACKAGE_DIR}\icudt51.dll"
	#File "${PACKAGE_DIR}\icuin51.dll"
	#File "${PACKAGE_DIR}\icuuc51.dll"
	#File "${PACKAGE_DIR}\libEGL.dll"
	#File "${PACKAGE_DIR}\libGLESv2.dll"
	#File "${PACKAGE_DIR}\Qt5Core.dll"
	#File "${PACKAGE_DIR}\Qt5Gui.dll"
	#File "${PACKAGE_DIR}\Qt5Network.dll"
	#File "${PACKAGE_DIR}\Qt5Widgets.dll"
	#File "${PACKAGE_DIR}\utservice.conf"
	#File "${PACKAGE_DIR}\UTSERVICE_RESTART.BAT"
	#File "${PACKAGE_DIR}\switch.exe"
	#File "${PACKAGE_DIR}\Qt5Xml.dll"
	#SetOutPath "$INSTDIR\platforms"
	#File /r "${PACKAGE_DIR}\platforms\*"
	#SetOutPath "$INSTDIR\Examples"
	#File /r "${PACKAGE_DIR}\Examples\*"
	
	
	File "${PACKAGE_DIR}\libgcc_s_dw2-1.dll"
	File "${PACKAGE_DIR}\libGLESv2.dll"
	File "${PACKAGE_DIR}\libstdc++-6.dll"
	File "${PACKAGE_DIR}\libwinpthread-1.dll"
	File "${PACKAGE_DIR}\Qt5Concurrent.dll"
	File "${PACKAGE_DIR}\Qt5Core.dll"
	File "${PACKAGE_DIR}\Qt5Gui.dll"
	File "${PACKAGE_DIR}\Qt5Network.dll"
	File "${PACKAGE_DIR}\Qt5SerialPort.dll"
	File "${PACKAGE_DIR}\Qt5Widgets.dll"
	File "${PACKAGE_DIR}\switch.exe"
	
	File "${PACKAGE_DIR}\2port-icon.ico"
	SetOutPath "$INSTDIR\bearer"
	File /r  "${PACKAGE_DIR}\bearer"
	
	
	SetOutPath "$INSTDIR\platforms"
	File /r  "${PACKAGE_DIR}\platforms\*"
	
	SetOutPath "$INSTDIR\imageformats"
	File /r  "${PACKAGE_DIR}\imageformats"
	
	SetOutPath "$INSTDIR\Doc"
	File /r  "${PACKAGE_DIR}\UserGuide.pdf"

	SetOutPath "$INSTDIR\iconengines"
	File /r  "${PACKAGE_DIR}\iconengines\*"
	#SimpleSC::InstallService "${SERVICE_NAME}" "${SERVICE_NAME}" "16" "2" "$INSTDIR\${SERVICE_FILE_NAME} --log" "" "" ""
    #Pop $0 
	#StrCmp $0 "0" WellInstall FailInstall
	#WellInstall:
		#MessageBox MB_OK "������ ${SERVICE_NAME} ������� �����������."
	#	Goto NextInstall
	#FailInstall:
	#	MessageBox MB_OK "�� ������� ���������� ������ ${SERVICE_NAME}, ��������� �������� �� ����� ���� ��������� $0"
	#NextInstall:
	
	#SimpleSC::StartService "${SERVICE_NAME}" "" 30
	#Pop $0 ; 
	#StrCmp $0 "0" WellStart UnequalStart
	#WellStart:
		#MessageBox MB_OK "������ ${SERVICE_NAME} ������� ��������"
	#	Goto NextUnequal
	#UnequalStart:
	#	MessageBox MB_OK "�� ������� ��������� ������ ${SERVICE_NAME} $0"
	#NextUnequal:
	
	
	WriteUninstaller "$INSTDIR\uninst.exe" 
	WriteRegStr HKLM SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\MyUtService "DisplayName" "${SERVICE_NAME}"
	WriteRegStr HKLM SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\MyUtService "UninstallString" "$INSTDIR\uninst.exe"
	
	CreateDirectory "$SMPrograms\Switch"

	CreateShortCut "$SMPROGRAMS\$INSTDIR\Switch.lnk" "$INSTDIR\Switch.exe" 
	#CreateShortCut "$SMPROGRAMS\UTSERVICE\������� XML-RPC.lnk" "$INSTDIR\Examples\"
	#CreateShortCut "$SMPROGRAMS\UTSERVICE\���������������� UTSERVICE.lnk" "$INSTDIR\utservice.conf"
	#CreateShortCut "$SMPROGRAMS\UTSERVICE\������ ����������.lnk" "$INSTDIR\utmonitor.exe"
	#CreateShortCut "$SMPROGRAMS\Switch\�������� Switch.lnk" "$INSTDIR\uninst.exe"
	#ShellLink::SetRunAsAdministrator "$SMPROGRAMS\UTSERVICE\������ ����������.lnk" 
	#���� �� ����� ������� ������ ������, ��������� � ��� �����
	Endlabel:
SectionEnd
Section "����� �� ������� �����" SectionX
    SetShellVarContext current
    CreateShortCut "$DESKTOP\COM_SWITCH.lnk" "$INSTDIR\Switch.exe" "" "$INSTDIR\2port-icon.ico" 0
SectionEnd



Section Uninstall 
	
	
	#ExecWait '"sc" stop ${SERVICE_NAME}'
	#ExecWait '"sc" delete ${SERVICE_NAME}' 
	
	#������ ������ �� �������
	#DeleteRegKey HKLM SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\switch_com.exe
	
	#������ ������
	#Delete "$SMPROGRAMS\Switch\�������� UTSERVICE.lnk"
	#Delete "$SMPROGRAMS\UTSERVICE\���������� UTSERVICE.lnk"
	#Delete "$SMPROGRAMS\UTSERVICE\���������������� UTSERVICE.lnk"
	#Delete "$SMPROGRAMS\Switch\��������� UTSERVICE.lnk"
	#Delete "$SMPROGRAMS\Switch\utmonitor.lnk"
	#Delete "$SMPROGRAMS\Switch\������� XML-RPS.lnk"
	#Delete "$SMPROGRAMS\Switch\������ ����������.lnk"
	#Delete "$SMPROGRAMS\Switch\���������������� UTSERVICE.lnk"
	#Delete "$SMPROGRAMS\Switch\������� XML-RPC.lnk"
	#������� dll
	Delete "$INSTDIR\utservice.exe" 
	Delete "$INSTDIR\utmonitor.exe"
	Delete "$INSTDIR\icudt51.dll"
	Delete "$INSTDIR\icuin51.dll"
	Delete "$INSTDIR\icuuc51.dll"
	Delete "$INSTDIR\libEGL.dll"
	Delete "$INSTDIR\libGLESv2.dll"
	Delete "$INSTDIR\Qt5Core.dll"
	Delete "$INSTDIR\Qt5Gui.dll"
	Delete "$INSTDIR\Qt5Network.dll"
	Delete "$INSTDIR\Qt5Widgets.dll"
	Delete "$INSTDIR\Qt5Xml.dll"
	Delete "$SMPROGRAMS\Switch\Switch.lnk"
	Delete "$DESKTOP\COM_SWITCH.lnk"
	Delete "$INSTDIR\Doc\UserGuide.pdf"
	
	Delete "$INSTDIR\libgcc_s_dw2-1.dll"
	Delete "$INSTDIR\libGLESv2.dll"
	Delete "$INSTDIR\libstdc++-6.dll"
	Delete "$INSTDIR\libwinpthread-1.dll"
	Delete "$INSTDIR\Qt5Concurrent.dll"
	Delete "$INSTDIR\2port-icon.ico"
	Delete "$INSTDIR\Qt5SerialPort.dll"
	Delete "$INSTDIR\switch.exe"
	Delete "$INSTDIR\uninst.exe"
	RMDir /r "$INSTDIR\bearer"
	RMDir /r "$INSTDIR\iconengines"
	RMDir /r "$INSTDIR\imageformats"
	RMDir /r "$INSTDIR\platforms"
	RMDir /r "$INSTDIR\Doc"
	RMDir /r "$SMPROGRAMS\Switch"
	RMDir "$INSTDIR"
SectionEnd 







