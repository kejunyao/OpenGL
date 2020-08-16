/**
 * $类描述$
 *
 * @author kejunyao
 * @since 2020年08月03日
 */
#include "EglThread.h"

EglThread::EglThread() {
    pthread_mutex_init(&threadMutex, NULL);
    pthread_cond_init(&threadCond, NULL);
}

EglThread::~EglThread() {
    pthread_mutex_destroy(&threadMutex);
    pthread_cond_destroy(&threadCond);
}

void *eglThreadImpl(void *context) {
    EglThread *eglThread = static_cast<EglThread *>(context);
    if (eglThread == 0) {
        return 0;
    }
    EglHelper *eglHelper = new EglHelper();
    eglHelper->initEgl(eglThread->nativeWindow);
    eglThread->isExit = false;
    while (!eglThread->isExit) {
        if (eglThread->isCreate) {
            if (eglThread->DEBUG) {
                LOGD("EglThread#eglThreadImpl, surfaceCreate");
            }
            // TODO
            eglThread->isCreate = false;
            if (eglThread->onSurfaceCreateCallback != NULL) {
                eglThread->onSurfaceCreateCallback(eglThread->onSurfaceCreateCallbackCtx);
            }
        }
        if (eglThread->isChange) {
            if (eglThread->DEBUG) {
                LOGD("EglThread#eglThreadImpl, surfaceChange");
            }
            eglThread->isChange = false;
            // glViewport(0, 0, eglThread->surfaceWidth, eglThread->surfaceHeight);
            eglThread->isStart = true;
            if (eglThread->onSurfaceChangeCallback != NULL) {
                eglThread->onSurfaceChangeCallback(
                        eglThread->surfaceWidth,
                        eglThread->surfaceHeight,
                        eglThread->onSurfaceChangeCallbackCtx
                        );
            }
        }
        if (eglThread->DEBUG) {
            LOGD("EglThread#eglThreadImpl, draw");
        }
        if (eglThread->isStart) {
            // glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);
            if (eglThread->onSurfaceDrawCallback != NULL) {
                eglThread->onSurfaceDrawCallback(eglThread->onSurfaceDrawCallbackCtx);
            }
            eglHelper->swapBuffers();
        }
        if (eglThread->isAutoReader) {
            usleep(1000000 / 60);
            LOGD("自动渲染....")
        } else{
            pthread_mutex_lock(&eglThread->threadMutex);
            pthread_cond_wait(&eglThread->threadCond, &eglThread->threadMutex);
            pthread_mutex_unlock(&eglThread->threadMutex);
            LOGD("手动渲染....")
        }
    }
    delete eglHelper;
    return 0;
}

void EglThread::onSurfaceCreate(EGLNativeWindowType windowType) {
    if (eglThread == -1) {
        isCreate = true;
        nativeWindow = windowType;
        pthread_create(&eglThread, NULL, eglThreadImpl, this);
    }
}

void EglThread::onSurfaceChange(int width, int height) {
    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
}

void EglThread::setOnSurfaceCreateCallback(EglThread::OnSurfaceCreateCallback callback, void *ctx) {
    onSurfaceCreateCallback = callback;
    onSurfaceCreateCallbackCtx = ctx;
}

void EglThread::setOnSurfaceChangeCallback(EglThread::OnSurfaceChangeCallback callback, void *ctx) {
    onSurfaceChangeCallback = callback;
    onSurfaceChangeCallbackCtx = ctx;
}

void EglThread::setOnSurfaceDrawCallback(EglThread::OnSurfaceDrawCallback callback, void *ctx) {
    onSurfaceDrawCallback = callback;
    onSurfaceDrawCallbackCtx = ctx;
}

void EglThread::setAutoRender(bool isAuto) {
    isAutoReader = isAuto;
}

void EglThread::notifyRender() {
    pthread_mutex_lock(&threadMutex);
    pthread_cond_signal(&threadCond);
    pthread_mutex_unlock(&threadMutex);
}
