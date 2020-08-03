/**
 * $类描述$
 *
 * @author kejunyao
 * @since 2020年08月03日
 */
#include "EglThread.h"

EglThread::EglThread() {
}

EglThread::~EglThread() {
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
        }
        if (eglThread->isChange) {
            if (eglThread->DEBUG) {
                LOGD("EglThread#eglThreadImpl, surfaceChange");
            }
            eglThread->isChange = false;
            glViewport(0, 0, 720, 1280);
            eglThread->isStart = true;
        }
        if (eglThread->DEBUG) {
            LOGD("EglThread#eglThreadImpl, draw");
        }
        if (eglThread->isStart) {
            glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            eglHelper->swapBuffers();
        }
        usleep(1000000 / 60);
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
