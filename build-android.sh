#! /bin/bash

SELFPATH=`realpath $0`

export ANDROID_NDK=/opt/android-ndk

MY_ANDROID_ROOT=`echo ~/android`

export BOOST_ROOT=${MY_ANDROID_ROOT}/boost_1_59_0/

export BOOST_INCLUDEDIR=${MY_ANDROID_ROOT}/boost_1_59_0/

boostdef=(-DBOOST_COROUTINE_LIBRARIES=${MY_ANDROID_ROOT}/boost_1_59_0/stage/lib/libboost_coroutine.a
	-DBOOST_COROUTINE_LIBRARY_RELEASE=${MY_ANDROID_ROOT}/boost_1_59_0/stage/lib/libboost_coroutine.a
	-DBOOST_COROUTINE_LIBRARY_DEBUG=${MY_ANDROID_ROOT}/boost_1_59_0/stage/lib/libboost_coroutine.a
	-D_boost_COMPILER_VERSION=4.9
)

export CMAKE_MODULE_PATH=${MY_ANDROID_ROOT}
cmake -DBoost_LIBRARY_DIRS=${MY_ANDROID_ROOT}/boost_1_59_0/stage/lib -DBOOST_INCLUDEDIR=${MY_ANDROID_ROOT}/boost_1_59_0/ -DBOOST_ROOT=${MY_ANDROID_ROOT}/boost_1_59_0/ -DSWIG_EXECUTABLE=/usr/bin/swig -DCMAKE_TOOLCHAIN_FILE=~/projects/android-cmake/android.toolchain.cmake -DANDROID_STL=gnustl_static -DANDROID_CMAKE_DIR=${MY_ANDROID_ROOT} \
	-DPROTOBUF_INCLUDE_DIR=${MY_ANDROID_ROOT}/protobuf/include -DPROTOBUF_LIBRARY=${MY_ANDROID_ROOT}/protobuf/lib/libprotobuf.a -DPROTOBUF_PROTOC_EXECUTABLE=/usr/bin/protoc \
	`dirname ${SELFPATH}` -DANDROID_NATIVE_API_LEVEL=14 # -DANDROID_ABI=arm64-v8a -DANDROID_NATIVE_API_LEVEL=21
	# -DANDROID_TOOLCHAIN_NAME=aarch64-linux-android-4.9
