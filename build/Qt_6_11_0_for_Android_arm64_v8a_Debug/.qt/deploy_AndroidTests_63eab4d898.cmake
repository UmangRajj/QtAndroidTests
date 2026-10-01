include("D:/QT_Projects/AndroidTests/build/Qt_6_11_0_for_Android_arm64_v8a_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/AndroidTests-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")
_qt_internal_show_skip_runtime_deploy_message("shared Qt libs, cross-compiled, non-bundle app"
    EXTRA_MESSAGE "Executable targets have to be app bundles to use this command on Apple platforms."
)