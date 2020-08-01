package com.kejunyao.opengl.sample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.kejunyao.opengl.OpenGL;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        OpenGL openGL = new OpenGL();
        openGL.println();
    }
}