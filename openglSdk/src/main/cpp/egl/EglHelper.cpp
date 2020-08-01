//
// Created by kejunyao on 2020/8/1.
//

#include "EglHelper.h"
#include "AndroidLog.h"

EglHelper::EglHelper() {
    eglDisplay = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglContext = EGL_NO_CONTEXT;
    eglConfig = NULL;
}

EglHelper::~EglHelper() {

}

int EglHelper::initEgl(EGLNativeWindowType win) {
    // 1、获取默认显示设备
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOGE("EglHelper#initEgl, eglGetDisplay failure!!");
        return -1;
    }
    // 2、初始化默认显示设备
    EGLint *majors = new EGLint[2];
    EGLBoolean success = eglInitialize(eglDisplay, &majors[0], &majors[1]);
    if (!success) {
        LOGE("EglHelper#initEgl, eglInitialize failure!!");
        return -1;
    }
    // 3、初始显示设备属性
    EGLint attributes[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };
    EGLint numConfig;
    success = eglChooseConfig(eglDisplay, attributes, NULL, 1, &numConfig);
    if (!success) {
        LOGE("EglHelper#initEgl, eglChooseConfig1 failure!!");
        return -1;
    }
    // 4、从系统中获取对应属性的配置
    success = eglChooseConfig(eglDisplay, attributes, &eglConfig, numConfig, &numConfig);
    if (!success) {
        LOGE("EglHelper#initEgl, eglChooseConfig2 failure!!");
        return -1;
    }
    const EGLint attribute_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    // 5、创建EGLContext
    eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, attribute_list);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("EglHelper#initEgl, eglCreateContext failure!!");
        return -1;
    }
    // 6、创建渲染Surface
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, win, NULL);
    if (eglSurface == EGL_NO_DISPLAY) {
        LOGE("EglHelper#initEgl, eglCreateWindowSurface failure!!");
        return -1;
    }
    // 7、
    success = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    if (!success) {
        LOGE("EglHelper#initEgl, eglMakeCurrent failure!!");
        return -1;
    }
    LOGD("EglHelper#initEgl, init success!!");
    return 0;
}

int EglHelper::swapBuffers() {
    if (eglDisplay == EGL_NO_DISPLAY || eglSurface == EGL_NO_SURFACE) {
        return -1;
    }
    if (eglSwapBuffers(eglDisplay, eglSurface)) {
        return 0;
    }
    return -1;
}

void EglHelper::destroy() {
    if (eglDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (eglSurface != EGL_NO_SURFACE) {
            eglDestroySurface(eglDisplay, eglSurface);
            eglSurface = EGL_NO_SURFACE;
        }
        if (eglContext != EGL_NO_CONTEXT) {
            eglDestroyContext(eglDisplay, eglContext);
            eglContext = EGL_NO_CONTEXT;
        }
        eglTerminate(eglDisplay);
        eglDisplay = EGL_NO_DISPLAY;
    }
}
