
%module http

%{

#include <string>
#include <stdexcept>

#include <avhttp.hpp>
#include "javahttp.hpp"

%}

%import "std_except.i"
%import "std_string.i"

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("httpjni");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library libhttpjni.so failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

%include "javahttp.hpp"

