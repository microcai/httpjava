cmake_minimum_required(VERSION 3.0)
project(javahttp CXX C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/avhttp/include/)

find_package(SWIG REQUIRED)

find_package(Boost COMPONENTS system thread date_time chrono)

include_directories(${BOOST_INCLUDEDIR})

link_directories(${Boost_LIBRARY_DIRS})

include(${SWIG_USE_FILE})

if (ANDROID)
	set( ANDROID_LOG_LIBRARIES log)
else()
	find_package(JNI REQUIRED)
	include_directories(${JNI_INCLUDE_DIRS})
	link_directories(${JNI_LIBRARIES})

	message(STATUS "jni is " ${JNI_LIBRARIES} )
endif()

set(CMAKE_SWIG_FLAGS -package net.wanin.httpjava)

set_source_files_properties(httpjava.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(streamclient.i PROPERTIES SWIG_FLAGS "-includeall")
swig_add_module(httpjni java httpjava.i javahttp.cpp javahttp.hpp)
swig_link_libraries(httpjni ${ANDROID_LOG_LIBRARIES} ${BOOST_LIBRARIES} boost_system boost_thread boost_filesystem)
set_target_properties(${SWIG_MODULE_httpjni_REAL_NAME} PROPERTIES NO_SONAME OFF)

# windows 上基本上没有 zip 这个命令，还是别弄了，免得失败，对吧？
if(NOT WIN32)
	add_custom_command(TARGET httpjni
		POST_BUILD
		COMMAND zip httpjni.zip *.java libhttpjni.so
		DEPENDS httpjni
		BYPRODUCTS httpjni.zip
		COMMENT "generating zip for distribute to customers"
		USES_TERMINAL)
endif()

