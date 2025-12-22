//
// Created by camilo on 2025-12-20 23:40:10 <3ThomasBorregaardSørensen!!
//
#include "framework.h"

#include <X11/Xlib.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <glad/glad.h>

#include <chrono>
#include <cmath>
#include <iostream>

static const char* vs_src = R"(#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 mvp;
void main() {
    gl_Position = mvp * vec4(aPos, 1.0);
}
)";

static const char* fs_src = R"(#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.7, 0.7, 0.2, 1.0);
}
)";

GLuint compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    return s;
}

GLuint createProgram() {
    GLuint vs = compile(GL_VERTEX_SHADER, vs_src);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fs_src);
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}

void mat4_rotate_y(float* m, float a) {
    float c = cosf(a), s = sinf(a);
    m[0]=c;  m[1]=0; m[2]=s;  m[3]=0;
    m[4]=0;  m[5]=1; m[6]=0;  m[7]=0;
    m[8]=-s; m[9]=0; m[10]=c; m[11]=0;
    m[12]=0; m[13]=0; m[14]=-5; m[15]=1;
}
void mat4_perspective(float* m, float fov_rad, float aspect, float zn, float zf)
{
    float f = 1.0f / tanf(fov_rad * 0.5f);

    memset(m, 0, 16 * sizeof(float));

    m[0]  = f / aspect;
    m[5]  = f;
    m[10] = (zf + zn) / (zn - zf);
    m[11] = -1.0f;
    m[14] = (2.0f * zf * zn) / (zn - zf);
}


void mat4_model(float* m, float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    m[0]= c;  m[4]=0; m[8]= s;  m[12]=0;
    m[1]= 0;  m[5]=1; m[9]= 0;  m[13]=0;
    m[2]=-s;  m[6]=0; m[10]=c;  m[14]=-5.0f;
    m[3]= 0;  m[7]=0; m[11]=0;  m[15]=1;
}


void mat4_mul(float* out, const float* a, const float* b)
{
    float r[16];

    for (int c = 0; c < 4; ++c)
        for (int r0 = 0; r0 < 4; ++r0)
            r[c*4 + r0] =
                a[0*4 + r0] * b[c*4 + 0] +
                a[1*4 + r0] * b[c*4 + 1] +
                a[2*4 + r0] * b[c*4 + 2] +
                a[3*4 + r0] * b[c*4 + 3];

    memcpy(out, r, sizeof(r));
}


int rotating_cube() {
    Display* dpy = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(dpy);

    XSetWindowAttributes swa{};
    swa.event_mask = ExposureMask | KeyPressMask;
    Window win = XCreateWindow(dpy, root, 0, 0, 800, 600, 0,
                               CopyFromParent, InputOutput,
                               CopyFromParent, CWEventMask, &swa);
    XMapWindow(dpy, win);

    EGLDisplay egl_dpy = eglGetDisplay(dpy);
    eglInitialize(egl_dpy, nullptr, nullptr);

    EGLint cfg_attr[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
    };

    EGLConfig cfg;
    EGLint num;
    eglChooseConfig(egl_dpy, cfg_attr, &cfg, 1, &num);

    eglBindAPI(EGL_OPENGL_API);

    EGLContext ctx = eglCreateContext(egl_dpy, cfg, EGL_NO_CONTEXT, nullptr);
    EGLSurface surf = eglCreateWindowSurface(egl_dpy, cfg, win, nullptr);
    eglMakeCurrent(egl_dpy, surf, surf, ctx);

    //gladLoadGL(gladLoaderLoadGL);

    gladLoadGL();

    GLuint prog = createProgram();

    float cube[] = {
        // back
        -1,-1,-1,  1,-1,-1,  1, 1,-1,
        1, 1,-1, -1, 1,-1, -1,-1,-1,

        // front
        -1,-1, 1,  1,-1, 1,  1, 1, 1,
        1, 1, 1, -1, 1, 1, -1,-1, 1,

        // left
        -1, 1, 1, -1, 1,-1, -1,-1,-1,
        -1,-1,-1, -1,-1, 1, -1, 1, 1,

        // right
         1, 1, 1,  1, 1,-1,  1,-1,-1,
         1,-1,-1,  1,-1, 1,  1, 1, 1,

        // bottom
        -1,-1,-1,  1,-1,-1,  1,-1, 1,
         1,-1, 1, -1,-1, 1, -1,-1,-1,

        // top
        -1, 1,-1,  1, 1,-1,  1, 1, 1,
         1, 1, 1, -1, 1, 1, -1, 1,-1
    };


    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    auto start = std::chrono::steady_clock::now();

    while (true) {
        while (XPending(dpy)) {
            XEvent e;
            XNextEvent(dpy, &e);
            if (e.type == KeyPress) return 0;
        }

        auto now = std::chrono::steady_clock::now();
        float t = std::chrono::duration<float>(now - start).count();

        // 1 rotation every 15 seconds
        float angle = (t / 15.0f) * 2.0f * 3.1415926f;

        float mvp[16];
        //mat4_rotate_y(mvp, angle);
        float model[16];
        float proj[16];
        //float mvp[16];
        float tmp[16];

        float aspect = 800.0f / 600.0f;

        mat4_model(model, angle);
        mat4_perspective(proj, 60.0f * 3.1415926f / 180.0f, aspect, 0.1f, 100.0f);

        // MVP = proj * model
        mat4_mul(tmp, proj, model);
        memcpy(mvp, tmp, sizeof(mvp));

        glViewport(0, 0, 800, 600);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2,0.6,1,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);
        glUniformMatrix4fv(glGetUniformLocation(prog, "mvp"),
                           1, false, mvp);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        eglSwapBuffers(egl_dpy, surf);
    }
}
