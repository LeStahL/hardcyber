/* Hardcyber - PC-64k-Intro by Team210 at Deadline 2k19
 * Copyright (C) 2019 DaDummy <c.anselm@paindevs.com>
 * Copyright (C) 2019 Alexander Kraus <nr4@z10.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define DEBUG

#ifdef WIN32
#	define WIN32_LEAN_AND_MEAN
#	define VC_EXTRALEAN
#	include <windows.h>
#   include <Windowsx.h>
#	include <commctrl.h>
#	include <mmsystem.h>
#	include <Mmreg.h>
#   include <vfw.h>
#endif

#include <GL/gl.h>
#include <glext.h>

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>

double t_now = 0.,
       t_start = 0.;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

// TODO: remove below
void debug(int shader_handle)
{
    printf("    Debugging shader with handle %d.\n", shader_handle);
    int compile_status = 0;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        printf("    FAILED.\n");
        GLint len;
        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &len);
        printf("    Log length: %d\n", len);
        GLchar *CompileLog = (GLchar*)malloc(len*sizeof(GLchar));
        glGetShaderInfoLog(shader_handle, len, NULL, CompileLog);
        printf("    Error messages:\n%s\n", CompileLog);
        free(CompileLog);
    }
    else
        printf("    Shader compilation successful.\n");
}

void debugp(int program)
{
    printf("    Debugging program with handle %d.\n", program);
    int compile_status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        printf("    FAILED.\n");
        GLint len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
        printf("    Log length: %d\n", len);
        GLchar *CompileLog = (GLchar*)malloc(len*sizeof(GLchar));
        glGetProgramInfoLog(program, len, NULL, CompileLog);
        printf("    Error messages:\n%s\n", CompileLog);
        free(CompileLog);
    }
    else
        printf("    Program linking successful.\n");
}
#else // DEBUG
#define printf(a)
#endif //DEBUG

HDC hdc;
HGLRC glrc;
int w = 1920,
    h = 1080;

void quad()
{
    glBegin(GL_QUADS);
    glVertex3f(-1,-1,0);
    glVertex3f(-1,1,0);
    glVertex3f(1,1,0);
    glVertex3f(1,-1,0);
    glEnd();
    glFlush();
}

int flip_buffers()
{
    SwapBuffers(hdc);

    MSG msg = { 0 };
    while ( PeekMessageA( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
        if ( msg.message == WM_QUIT ) {
            return FALSE;
        }
        TranslateMessage( &msg );
        DispatchMessageA( &msg );
    }

    return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        switch(wParam)
        {
        case VK_ESCAPE:
            ExitProcess(0);
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        ExitProcess(0);
        break;

    default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Pure opengl drawing code, essentially cross-platform
void draw()
{
//     glActiveTexture(GL_TEXTURE1);
//     glBindTexture(GL_TEXTURE_2D, font_texture_handle);

    quad();
//     glBindTexture(GL_TEXTURE_2D, 0);
}

int WINAPI demo(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // Display demo window
    CHAR WindowClass[]  = "Team210 Demo Window";

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = &WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowClass;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
                    0,                                                          // Optional window styles.
                    WindowClass,                                                // Window class
                    ":: Team210 :: GO - MAKE A DEMO ::",                                 // Window text
                    WS_POPUP | WS_VISIBLE,                                      // Window style
                    0,
                    0,
                    w,
                    h,                     // Size and position

                    NULL,                                                       // Parent window
                    NULL,                                                       // Menu
                    hInstance,                                                  // Instance handle
                    0                                                           // Additional application data
                );

    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = w;
    dm.dmPelsHeight = h;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

    // Show it
    ShowWindow(hwnd, TRUE);
    UpdateWindow(hwnd);

    // Create OpenGL context
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    hdc = GetDC(hwnd);

    int  pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);

    glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
    glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
    glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
    glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
    glUniform1f = (PFNGLUNIFORM1FPROC) wglGetProcAddress("glUniform1f");
    glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");

    ShowCursor(FALSE);

    // Load shader
    FILE *f = fopen("fconv.frag", "rt");
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    char *source = (char*)malloc(len+1);
    fseek(f, 0, SEEK_SET);
    fread(source, 1, len, f);
    source[len-1] = 0;

    int shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_handle, 1, &source, NULL);
    glCompileShader(shader_handle);
    debug(shader_handle);

    int program_handle = glCreateProgram();
    glAttachShader(program_handle, shader_handle);
    glLinkProgram(program_handle);
    debugp(program_handle);

    glUseProgram(program_handle);
    int iDataLocation = glGetUniformLocation(program_handle, "iData"),
        iDataWidthLocation = glGetUniformLocation(program_handle, "iDataWidth");

    // Setup input
#define data_width 10

    int idata_texture_handle;
    unsigned short odata[data_width*data_width],
             idata[data_width*data_width];

    for(int i=0; i<data_width*data_width; ++i)
    {
        idata[i] = i % 2;
        odata[i] = 0;
        printf("%hu", idata[i]);
    }
    printf("\n");

    glGenTextures(1, &idata_texture_handle);
    glBindTexture(GL_TEXTURE_2D, idata_texture_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, data_width, data_width, 0, GL_RED, GL_UNSIGNED_SHORT, idata);

    // Setup output
    int output_framebuffer;
    glGenFramebuffers(1, &output_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, output_framebuffer);

    int odata_texture_handle;
    glGenTextures(1, &odata_texture_handle);
    glBindTexture(GL_TEXTURE_2D, odata_texture_handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, data_width, data_width, 0, GL_RED, GL_UNSIGNED_SHORT, odata);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, odata_texture_handle, 0);

    // Main loop
    glViewport(0,0,data_width,data_width);

    glUniform1i(iDataLocation, 0);
    glUniform1i(iDataWidthLocation, data_width);

    glBindTexture(GL_TEXTURE_2D, idata_texture_handle);
    glActiveTexture(GL_TEXTURE0);

    draw();
    
    glBindTexture(GL_TEXTURE_2D, odata_texture_handle);
    
    glReadPixels(0,0,data_width, data_width, GL_RED, GL_UNSIGNED_SHORT, odata);
    glFlush();
    
    for(int i=0; i<data_width*data_width; ++i)
    {
        printf("%d: %hu -> %hu\n", i, idata[i], odata[i]);
    }
    
    return 0;
}
