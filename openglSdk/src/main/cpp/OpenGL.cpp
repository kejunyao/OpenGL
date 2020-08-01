//
// Created by kejunyao on 2020/7/30.
//

#include <jni.h>
#include <string>
#include "AndroidLog.h"

extern "C" JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_OpenGL_print(JNIEnv* env, jobject thiz, jstring msg) {
    LOGD("ssssssssssss")
}