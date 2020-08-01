//
// Created by kejunyao on 2020/8/1.
//

#ifndef OPENGL_EGLHELPER_H
#define OPENGL_EGLHELPER_H

#include <EGL/egl.h>

class EglHelper {

    private:
        EGLDisplay eglDisplay;
        EGLContext eglContext;
        EGLConfig eglConfig;
        EGLSurface eglSurface;

    public:
        EglHelper();
        ~EglHelper();

        int initEgl(EGLNativeWindowType win);
        int swapBuffers();
        void destroy();

};


#endif //OPENGL_EGLHELPER_H
