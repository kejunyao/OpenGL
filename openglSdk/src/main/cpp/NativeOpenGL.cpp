//
// Created by kejunyao on 2020/7/30.
//

#include <jni.h>
#include <string>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <egl/EglHelper.h>
#include <egl/EglThread.h>

#include "AndroidLog.h"

EglThread *eglThread = NULL;
ANativeWindow *nativeWindow = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1surfaceCreated(JNIEnv *env, jobject instance, jobject surface) {
    LOGD("surfaceCreated, instance: ", instance, ", surface: ", surface);
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EglThread();
    eglThread->onSurfaceCreate(nativeWindow);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1surfaceChange(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (eglThread != NULL) {
        eglThread->onSurfaceChange(width, height);
    }
}