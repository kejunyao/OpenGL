/**
 * $类描述$
 *
 * @author kejunyao
 * @since 2020年08月03日
 */
#ifndef OPENGL_EGLTHREAD_H
#define OPENGL_EGLTHREAD_H

#include <AndroidLog.h>
#include <pthread.h>
#include <android/native_window.h>
#include <EGL/eglplatform.h>
#include <GLES2/gl2.h>
#include "EglHelper.h"
#include <unistd.h>

class EglThread {
    public:
        const bool DEBUG = true;
        pthread_t eglThread = -1;
        ANativeWindow *nativeWindow = NULL;

        bool isCreate = false;
        bool isChange = false;
        bool isExit = false;
        bool isStart = false;

        int surfaceWidth  = 0;
        int surfaceHeight = 0;

    public:
        EglThread();
        ~EglThread();

        void onSurfaceCreate(EGLNativeWindowType windowType);

        void onSurfaceChange(int width, int height);
};


#endif //OPENGL_EGLTHREAD_H
