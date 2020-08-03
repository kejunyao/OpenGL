package com.kejunyao.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * $类描述$
 *
 * @author kejunyao
 * @since 2020年08月01日
 */
public class NativeSurfaceView extends SurfaceView {

    private final SurfaceHolder.Callback mSurfaceCallback = new SurfaceHolder.Callback() {

        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            if (mNativeOpenGL != null) {
                mNativeOpenGL.surfaceCreated(holder.getSurface());
            }

        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            if (mNativeOpenGL != null) {
                mNativeOpenGL.surfaceChange(width, height);
            }
        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {

        }
    };

    public NativeSurfaceView(Context context) {
        this(context, null);
    }

    public NativeSurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public NativeSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    public NativeSurfaceView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        this(context, attrs, defStyleAttr);
    }

    private void init() {
        getHolder().addCallback(mSurfaceCallback);
    }

    private NativeOpenGL mNativeOpenGL;
    public void setNativeOpenGL(NativeOpenGL nativeOpenGL) {
        mNativeOpenGL = nativeOpenGL;
    }
}
