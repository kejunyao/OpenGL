package com.kejunyao.opengl.sample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.kejunyao.opengl.NativeOpenGL;
import com.kejunyao.opengl.NativeSurfaceView;

public class MainActivity extends AppCompatActivity {

    private NativeSurfaceView mNativeSurfaceView;
    private NativeOpenGL mNativeOpenGL;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mNativeSurfaceView = findViewById(R.id.surface_view);
        mNativeOpenGL = new NativeOpenGL();
        mNativeSurfaceView.setNativeOpenGL(mNativeOpenGL);

        findViewById(R.id.switch_render).setOnClickListener(new View.OnClickListener() {
            boolean isAuto = true;
            @Override
            public void onClick(View v) {
                isAuto = !isAuto;
                mNativeOpenGL.setAutoRender(isAuto);
            }
        });
    }
}