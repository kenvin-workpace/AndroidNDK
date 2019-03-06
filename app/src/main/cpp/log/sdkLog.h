//
// Created by Kevin on 2018/5/3.
//
#ifndef ANDROIDNDK_SDKLOG_H
#define ANDROIDNDK_SDKLOG_H "=JNI LOG="
#endif

#include <android/log.h>

#define SDKLOG_DEBUG(...) __android_log_print(ANDROID_LOG_DEBUG, ANDROIDNDK_SDKLOG_H, __VA_ARGS__)
