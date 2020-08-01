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

#include "AndroidLog.h"

EglHelper *eglHelper = NULL;
ANativeWindow *nativeWindow = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1surfaceCreated(JNIEnv *env, jobject instance, jobject surface) {
    LOGD("surfaceCreated, instance: ", instance, ", surface: ", surface);
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglHelper = new EglHelper();
    eglHelper->initEgl(nativeWindow);

    glViewport(0, 0, 720, 1280);

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    eglHelper->swapBuffers();
}