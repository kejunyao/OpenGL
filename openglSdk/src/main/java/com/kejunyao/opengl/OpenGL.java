package com.kejunyao.opengl;

public class OpenGL {

    static {
        System.loadLibrary("OpenGL");
    }

    public void println() {
        print("aaaaa");
    }

    private native void print(String msg);
}
