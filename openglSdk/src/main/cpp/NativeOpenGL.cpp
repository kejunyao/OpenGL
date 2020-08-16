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

void onSurfaceCreateCallback(void *ctx) {
    LOGD("onSurfaceCreateCallback.")
    EglThread *thread = static_cast<EglThread *>(ctx);
}

void onSurfaceChangeCallback(int width, int height, void *ctx) {
    LOGD("onSurfaceChangeCallback.")
    EglThread *thread = static_cast<EglThread *>(ctx);
    glViewport(0, 0, width, height);

}

void onSurfaceDrawCallback(void *ctx) {
    LOGD("onSurfaceDrawCallback.")
    EglThread *thread = static_cast<EglThread *>(ctx);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1surfaceCreated(JNIEnv *env, jobject instance, jobject surface) {
    LOGD("surfaceCreated, instance: ", instance, ", surface: ", surface);
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EglThread();
    eglThread->setOnSurfaceCreateCallback(onSurfaceCreateCallback, eglThread);
    eglThread->setOnSurfaceChangeCallback(onSurfaceChangeCallback, eglThread);
    eglThread->setOnSurfaceDrawCallback(onSurfaceDrawCallback, eglThread);
    eglThread->onSurfaceCreate(nativeWindow);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1surfaceChange(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (eglThread != NULL) {
        eglThread->onSurfaceChange(width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kejunyao_opengl_NativeOpenGL__1setAutoRender(JNIEnv *env, jobject thiz, jboolean b) {
    if (eglThread != NULL) {
        bool isAutoReader = eglThread->isAutoReader;
        eglThread->setAutoRender(b);
        if (!isAutoReader) {
            eglThread->notifyRender();
        }
    }
}