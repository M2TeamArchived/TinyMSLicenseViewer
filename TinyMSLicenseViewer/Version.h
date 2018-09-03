/******************************************************************************
Project: TinyMSLicenseViewer
Description: TinyMSLicenseViewer Version Definition
File Name: Version.h
License: The MIT License
******************************************************************************/

#ifndef PROJECT_VER
#define PROJECT_VER

#define PROJECT_VER_MAJOR 1
#define PROJECT_VER_MINOR 3
#define PROJECT_VER_BUILD 1809
#define PROJECT_VER_REV 3
#endif

#ifndef PROJECT_VER_FMT_COMMA
#define PROJECT_VER_FMT_COMMA PROJECT_VER_MAJOR,PROJECT_VER_MINOR,PROJECT_VER_BUILD,PROJECT_VER_REV
#endif

#ifndef PROJECT_VER_FMT_DOT
#define PROJECT_VER_FMT_DOT PROJECT_VER_MAJOR.PROJECT_VER_MINOR.PROJECT_VER_BUILD.PROJECT_VER_REV
#endif


#ifndef MACRO_TO_STRING
#define _MACRO_TO_STRING(arg) L#arg
#define MACRO_TO_STRING(arg) _MACRO_TO_STRING(arg)
#endif

#ifndef PROJECT_VERSION
#define PROJECT_VERSION PROJECT_VER_FMT_COMMA
#endif

#ifndef _PROJECT_VERSION_STRING_
#define _PROJECT_VERSION_STRING_ MACRO_TO_STRING(PROJECT_VER_FMT_DOT)
#endif

#ifndef PROJECT_VERSION_STRING
#ifdef PROJECT_CI_BUILD
#define PROJECT_VERSION_STRING _PROJECT_VERSION_STRING_ L" " PROJECT_CI_BUILD
#else
#define PROJECT_VERSION_STRING _PROJECT_VERSION_STRING_
#endif
#endif
