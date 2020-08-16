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
        typedef void(*OnSurfaceCreateCallback)(void *);
        typedef void(*OnSurfaceChangeCallback)(int width, int height, void *);
        typedef void(*OnSurfaceDrawCallback)(void *);

        const bool DEBUG = true;
        pthread_t eglThread = -1;
        ANativeWindow *nativeWindow = NULL;

        bool isCreate = false;
        bool isChange = false;
        bool isExit = false;
        bool isStart = false;

        int surfaceWidth  = 0;
        int surfaceHeight = 0;

        bool isAutoReader = true;
        pthread_cond_t threadCond;
        pthread_mutex_t  threadMutex;

    public:
        EglThread();
        ~EglThread();

        void onSurfaceCreate(EGLNativeWindowType windowType);

        void onSurfaceChange(int width, int height);

        void setAutoRender(bool isAuto);

        void notifyRender();

        OnSurfaceCreateCallback onSurfaceCreateCallback;
        void *onSurfaceCreateCallbackCtx;
        void setOnSurfaceCreateCallback(OnSurfaceCreateCallback callback, void *ctx);

        OnSurfaceChangeCallback onSurfaceChangeCallback;
        void *onSurfaceChangeCallbackCtx;
        void setOnSurfaceChangeCallback(OnSurfaceChangeCallback callback, void *ctx);

        OnSurfaceDrawCallback onSurfaceDrawCallback;
        void *onSurfaceDrawCallbackCtx;
        void setOnSurfaceDrawCallback(OnSurfaceDrawCallback callback, void *ctx);
};


#endif //OPENGL_EGLTHREAD_H
