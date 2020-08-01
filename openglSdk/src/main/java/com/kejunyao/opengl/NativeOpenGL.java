package com.kejunyao.opengl;

import android.view.Surface;

/**
 * $类描述$
 *
 * @author kejunyao
 * @since 2020年08月01日
 */
public class NativeOpenGL {

    static {
        System.loadLibrary("NativeOpenGL");
    }

    public void surfaceCreated(Surface surface) {
        _surfaceCreated(surface);
    }

    private native void _surfaceCreated(Surface surface);
}
