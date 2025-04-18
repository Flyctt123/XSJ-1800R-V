#############################################################################
# Makefile for building: XSJ1800RV
# Generated by qmake (3.1) (Qt 5.12.9)
# Project:  XSJ1800RV.pro
# Template: app
# Command: E:\QT5.12.9\5.12.9\mingw73_64\bin\qmake.exe -o Makefile XSJ1800RV.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
#############################################################################

MAKEFILE      = Makefile

EQ            = =

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = E:\QT5.12.9\5.12.9\mingw73_64\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL      = E:\QT5.12.9\5.12.9\mingw73_64\bin\qmake.exe -install qinstall
QINSTALL_PROGRAM = E:\QT5.12.9\5.12.9\mingw73_64\bin\qmake.exe -install qinstall -exe
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		debug \
		release


debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: XSJ1800RV.pro E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/win32-g++/qmake.conf E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/spec_pre.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/qdevice.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/device_config.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/sanitize.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/gcc-base.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/g++-base.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/angle.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/windows_vulkan_sdk.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/windows-vulkan.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/g++-win32.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/qconfig.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3danimation.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3danimation_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dcore.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dcore_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dextras.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dextras_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dinput.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dinput_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dlogic.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dlogic_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquick.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquick_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickanimation.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickanimation_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickextras.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickextras_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickinput.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickinput_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickrender.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickrender_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickscene2d.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickscene2d_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3drender.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3drender_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axbase.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axbase_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axcontainer.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axcontainer_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axserver.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axserver_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bluetooth.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_charts.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_charts_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_concurrent.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_core.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_core_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_datavisualization.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_datavisualization_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_dbus.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_dbus_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designer.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designer_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_edid_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_egl_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_fb_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gamepad.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gamepad_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gui.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gui_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_help.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_help_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_location.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_location_private.pri \
		../qtmqtt/build-qtmqtt-Desktop_Qt_5_12_9_MinGW_64_bit-Release/mkspecs/modules-inst/qt_lib_mqtt.pri \
		../qtmqtt/build-qtmqtt-Desktop_Qt_5_12_9_MinGW_64_bit-Release/mkspecs/modules-inst/qt_lib_mqtt_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_mqtt.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimedia.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_network.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_network_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_networkauth.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_networkauth_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_nfc.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_nfc_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_opengl.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_opengl_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_openglextensions.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioning.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioning_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioningquick.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioningquick_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_printsupport.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_purchasing.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_purchasing_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qml.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qml_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmldebug_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmltest.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quick.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quick_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickcontrols2.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickcontrols2_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickshapes_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quicktemplates2.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quicktemplates2_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickwidgets.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_remoteobjects.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_remoteobjects_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_repparser.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_repparser_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_script.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_script_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scripttools.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scxml.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scxml_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sensors.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sensors_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialbus.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialbus_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialport.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialport_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sql.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sql_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_svg.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_svg_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_testlib.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_testlib_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_texttospeech.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_texttospeech_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_theme_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uiplugin.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uitools.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uitools_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_virtualkeyboard.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_virtualkeyboard_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_webchannel.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_webchannel_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_websockets.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_websockets_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_widgets.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_widgets_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_windowsuiautomation_support_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_winextras.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_winextras_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xml.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xml_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt_functions.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt_config.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/win32-g++/qmake.conf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/spec_post.prf \
		.qmake.stash \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exclusive_builds.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/toolchain.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/default_pre.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/default_pre.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/resolve_config.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exclusive_builds_post.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/default_post.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qml_debug.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/precompile_header.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/warn_on.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/resources.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/moc.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/opengl.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/uic.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qmake_use.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/file_copies.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/windows.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/testcase_targets.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exceptions.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/yacc.prf \
		E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/lex.prf \
		XSJ1800RV.pro \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Charts.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Widgets.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Gui.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5WebSockets.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Network.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5SerialPort.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Sql.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Core.prl \
		E:/QT5.12.9/5.12.9/mingw73_64/lib/qtmain.prl
	$(QMAKE) -o Makefile XSJ1800RV.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/spec_pre.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/qdevice.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/device_config.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/sanitize.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/gcc-base.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/g++-base.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/angle.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/windows_vulkan_sdk.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/windows-vulkan.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/common/g++-win32.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/qconfig.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3danimation.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3danimation_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dcore.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dcore_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dextras.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dextras_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dinput.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dinput_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dlogic.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dlogic_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquick.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquick_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickanimation.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickanimation_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickextras.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickextras_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickinput.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickinput_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickrender.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickrender_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickscene2d.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3dquickscene2d_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3drender.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_3drender_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_accessibility_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axbase.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axbase_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axcontainer.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axcontainer_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axserver.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_axserver_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bluetooth.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bluetooth_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_bootstrap_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_charts.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_charts_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_concurrent.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_concurrent_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_core.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_core_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_datavisualization.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_datavisualization_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_dbus.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_dbus_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designer.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designer_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_designercomponents_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_edid_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_egl_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_fb_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gamepad.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gamepad_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gui.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_gui_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_help.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_help_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_location.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_location_private.pri:
../qtmqtt/build-qtmqtt-Desktop_Qt_5_12_9_MinGW_64_bit-Release/mkspecs/modules-inst/qt_lib_mqtt.pri:
../qtmqtt/build-qtmqtt-Desktop_Qt_5_12_9_MinGW_64_bit-Release/mkspecs/modules-inst/qt_lib_mqtt_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_mqtt.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimedia.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimedia_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimediawidgets.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_network.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_network_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_networkauth.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_networkauth_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_nfc.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_nfc_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_opengl.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_opengl_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_openglextensions.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_openglextensions_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_packetprotocol_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioning.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioning_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioningquick.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_positioningquick_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_printsupport.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_printsupport_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_purchasing.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_purchasing_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qml.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qml_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmldebug_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmldevtools_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmltest.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qmltest_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quick.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quick_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickcontrols2.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickcontrols2_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickparticles_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickshapes_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quicktemplates2.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quicktemplates2_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickwidgets.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_quickwidgets_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_remoteobjects.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_remoteobjects_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_repparser.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_repparser_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_script.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_script_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scripttools.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scripttools_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scxml.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_scxml_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sensors.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sensors_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialbus.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialbus_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialport.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_serialport_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sql.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_sql_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_svg.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_svg_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_testlib.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_testlib_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_texttospeech.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_texttospeech_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_theme_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uiplugin.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uitools.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_uitools_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_virtualkeyboard.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_virtualkeyboard_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_vulkan_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_webchannel.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_webchannel_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_websockets.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_websockets_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_widgets.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_widgets_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_windowsuiautomation_support_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_winextras.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_winextras_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xml.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xml_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xmlpatterns.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt_functions.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt_config.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/win32-g++/qmake.conf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/spec_post.prf:
.qmake.stash:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exclusive_builds.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/toolchain.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/default_pre.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/default_pre.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/resolve_config.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exclusive_builds_post.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/default_post.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qml_debug.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/precompile_header.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/warn_on.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qt.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/resources.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/moc.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/opengl.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/uic.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/qmake_use.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/file_copies.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/win32/windows.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/testcase_targets.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/exceptions.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/yacc.prf:
E:/QT5.12.9/5.12.9/mingw73_64/mkspecs/features/lex.prf:
XSJ1800RV.pro:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Charts.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Widgets.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Gui.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5WebSockets.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Network.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5SerialPort.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Sql.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/Qt5Core.prl:
E:/QT5.12.9/5.12.9/mingw73_64/lib/qtmain.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile XSJ1800RV.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"

qmake_all: FORCE

make_first: debug-make_first release-make_first  FORCE
all: debug-all release-all  FORCE
clean: debug-clean release-clean  FORCE
distclean: debug-distclean release-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash

debug-mocclean:
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean:
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables:
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables:
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables

check: first

benchmark: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
