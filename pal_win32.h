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

#ifndef PAL_WIN32_H
#define PAL_WIN32_H

#include "common.h"

#ifndef MINIFY_64K
// Export symbols that make hybrid graphics systems (laptops) use the dedicated GPU
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#endif

void *malloc(size_t size)
{
	return GlobalAlloc(GMEM_ZEROINIT, size);
}

HWAVEOUT hWaveOut;
WAVEHDR header = { 0, 0, 0, 0, 0, 0, 0, 0 };

HDC hdc;
HGLRC glrc;

#ifdef RECORD
HWND hRecordFilenameEdit, hCaptureWindow, hCaptureDriverComboBox ;
#endif 

double get_sound_playback_time();
void set_sound_playback_time(double time);

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
#ifdef RECORD
                    if(recording) 
                    {
                        capFileSaveAs(hCaptureWindow, record_filename);
                    }
#endif
					ExitProcess(0);
					break;
				case VK_SPACE:
					// pause/unpaused render timer
					paused = !paused;
					if(paused)
						waveOutPause(hWaveOut);
					else
						waveOutRestart(hWaveOut);
					break;
			}
			break;
		case WM_RBUTTONDOWN:
#ifdef RECORD
            if(recording) capFileSaveAs(hCaptureWindow, record_filename);
#endif
			ExitProcess(0);
			break;
//         case WM_MOUSEMOVE:
//             mx = GET_X_LPARAM(lParam);
//             my = GET_Y_LPARAM(lParam);
//             break;

		default:
			break;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_COMMAND:
			UINT id =  LOWORD(wParam);
			HWND hSender = (HWND)lParam;

			switch(id)
			{
				case 5:
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					w = widths[index];
                    h = heights[index];
				}
                break;
				case 6:
					muted = !muted;
					if(muted)
						SendMessage(hSender, BM_SETCHECK, BST_CHECKED, 0);
					else
						SendMessage(hSender, BM_SETCHECK, BST_UNCHECKED, 0);
                break;
				case 7:
#ifdef RECORD
                    GetWindowText(hRecordFilenameEdit, record_filename, 1024);
#endif
					DestroyWindow(hwnd);
					PostQuitMessage(0);
                break;
				case 8: // Full screen Antialiasing
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					fsaa = (index + 1)*(index + 1);
				}
                break;
				case 9: // Texture buffer size
				{
					int index = SendMessage(hSender, CB_GETCURSEL, 0, 0);
					texs = 128;
					for(int i=0; i<index; ++i)
						texs *= 2;
					block_size = texs*texs;
				}
                break;
				case 10:
				{
                    start_at_scene = SendMessage(hSender, CB_GETCURSEL, 0, 0);
				}
				break;
#ifdef RECORDING
                case 11:
                {
                    recording = !recording;
					if(recording)
                    {
						SendMessage(hSender, BM_SETCHECK, BST_CHECKED, 0);
                        EnableWindow(hRecordFilenameEdit, TRUE);
                        EnableWindow(hCaptureDriverComboBox, TRUE);
                    }
                    else
                    {
						SendMessage(hSender, BM_SETCHECK, BST_UNCHECKED, 0);
                        EnableWindow(hRecordFilenameEdit, FALSE);
                        EnableWindow(hCaptureDriverComboBox, FALSE);
                    }
                }
				break;
#endif
			}
			break;

		case WM_CLOSE:
			ExitProcess(0);
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI demo(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	// Display settings selector
	WNDCLASS wca = { 0 };
	wca.lpfnWndProc   = DialogProc;
	wca.hInstance     = hInstance;
	wca.lpszClassName = L"Settings";
	RegisterClass(&wca);
	HWND lwnd = CreateWindowEx(
		0,                              // Optional window styles.
		L"Settings",                     // Window class
		demoname,    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		200, 200, 300, 360,

		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	// Add "Resolution: " text
	HWND hResolutionText = CreateWindow(WC_STATIC, "Resolution: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,15,100,100, lwnd, NULL, hInstance, NULL);

	// Add resolution Combo box
	HWND hResolutionComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 10, 175, 400, lwnd, (HMENU)5, hInstance,
	 NULL);

	// Add items to resolution combo box and select full HD
    for(int i=0; i<nresolutions; ++i)
        SendMessage(hResolutionComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) resolution_names[i]);
	SendMessage(hResolutionComboBox, CB_SETCURSEL, 2, 0);
    w = widths[2];
    h = heights[2];

	// Add mute checkbox
	HWND hMuteCheckbox = CreateWindow(WC_BUTTON, TEXT("Mute"),
					 WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
					 10, 40, 100, 20,
					 lwnd, (HMENU) 6, hInstance, NULL);

	// Add "Antialiasing: " text
	HWND hAntialiasingText = CreateWindow(WC_STATIC, "FSAA: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,65,100,100, lwnd, NULL, hInstance, NULL);

	// Add Fullscreen Antialiasing combo box
	HWND hFSAAComboBox= CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 60, 175, 280, lwnd, (HMENU)8, hInstance,
	 NULL);
    
    // Populate with entries
    for(int i=0; i<nfsaa; ++i)
        SendMessage(hFSAAComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) fsaa_names[i]);
	SendMessage(hFSAAComboBox, CB_SETCURSEL, nfsaa-1, 0);
    fsaa = nfsaa*nfsaa;

	// Add "SFX Buffer: " text
	HWND hTXAAText = CreateWindow(WC_STATIC, "SFX Buffer: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,95,100,100, lwnd, NULL, hInstance, NULL);

	// Add SFX buffer size combo box
	HWND hTXAAComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 90, 175, 280, lwnd, (HMENU)9, hInstance,
	 NULL);

	// Populate with entries
    for(int i=0; i<4; ++i)
        SendMessage(hTXAAComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) buffersize_names[i]);
	SendMessage(hTXAAComboBox, CB_SETCURSEL, 2, 0);

	// Add "Antialiasing: " text
	HWND hSceneText = CreateWindow(WC_STATIC, "Scene: ", WS_VISIBLE | WS_CHILD | SS_LEFT, 10,125,100,100, lwnd, NULL, hInstance, NULL);

	// Add scene selector
	HWND hSceneComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
	 CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	 100, 120, 175, 680, lwnd, (HMENU)10, hInstance,
	 NULL);

    // Populate with entries
    for(int i=0; i<nscenes; ++i)
        SendMessage(hSceneComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) scene_names[i]);
	SendMessage(hSceneComboBox, CB_SETCURSEL, 0, 0);

	// Add start button
	HWND hwndButton = CreateWindow(WC_BUTTON,"Offend!",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,185,225,90,90,lwnd,(HMENU)7,hInstance,NULL);

#ifdef RECORD
    // Add record checkbox
	HWND hRecordCheckbox = CreateWindow(WC_BUTTON, TEXT("Record"),
					 WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
					 10, 150, 89, 20,
					 lwnd, (HMENU) 11, hInstance, NULL);
    
    // Add record filename text field
    hRecordFilenameEdit = CreateWindow(WC_EDIT, TEXT("lightcyber.avi"), WS_VISIBLE | WS_CHILD | WS_BORDER ,100,150 ,175,25,lwnd, (HMENU) 12,NULL,NULL );
    EnableWindow(hRecordFilenameEdit, FALSE);
    
    // Add capture driver selector
	hCaptureDriverComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
        CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        100, 180, 175, 680, lwnd, (HMENU)12, hInstance,
        NULL);
    char capture_device_name[80];
    char capture_device_version[80];

    for(int wIndex = 0; wIndex < 10; wIndex++) 
    {
        if (capGetDriverDescription(
                wIndex, 
                capture_device_name, 
                sizeof (capture_device_name), 
                capture_device_version, 
                sizeof (capture_device_version)
            )) 
        {
            SendMessage(hCaptureDriverComboBox, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) capture_device_name);
        }
    } 
    SendMessage(hCaptureDriverComboBox, CB_SETCURSEL, 0, 0);
    EnableWindow(hCaptureDriverComboBox, FALSE);
#endif
    
	// Show the selector
	ShowWindow(lwnd, TRUE);
	UpdateWindow(lwnd);

	MSG msg = { 0 };
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#if RECORDING
	if(recording)
    {
        // FIXME: add actually selected driver
        SendMessage (hCaptureWindow, WM_CAP_DRIVER_CONNECT, 0, 0L); 
    }
#endif

#ifdef DEBUG
	printf("Rendering Demo with:\nSound ");
    if(muted)printf("muted");
    else printf("playing");
	printf("\nResolution: %d * %d\n", w, h);
	printf("FSAA: %d*\n", fsaa);
    if(recording)printf("recording to %s\n", record_filename);
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
#ifdef RECORD
    if(recording)
    {
        hCaptureWindow = capCreateCaptureWindow(
            WindowClass,
            WS_CHILD | WS_VISIBLE,
            0,
            0,
            w,
            h,
            hwnd,
            0                                                
        );
        capCaptureSequence(hCaptureWindow); 
    }
#endif
    
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

    rInitializeRenderer();

    ShowCursor(FALSE);
    
	load_demo();

    jump_to_scene(start_at_scene);

    // Main loop
    while(flip_buffers())
	{
        t_now = get_sound_playback_time();

		draw();
	}

	return 0;
}

void jump_to_scene(unsigned int scene_index)
{
    if (scene_index < nscenes)
    {
        set_sound_playback_time(start_times[scene_index]);
    }
    else
    {
        printf("Midi scene override failed - index out of bounds: %d", scene_index);
    }
}

void initialize_sound()
{
	hWaveOut = 0;
	int n_bits_per_sample = 16;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, channels, sample_rate, sample_rate*channels*n_bits_per_sample / 8, channels*n_bits_per_sample / 8, n_bits_per_sample, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
}

double get_sound_playback_time()
{
    static MMTIME MMTime = { TIME_SAMPLES, 0};
    waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
    return t_start + ((double)MMTime.u.sample) / 44100.0;
}

void set_sound_playback_time(double time)
{
    waveOutReset(hWaveOut);

    t_start = time;
    int delta = clamp((int)(time * (double)sample_rate), 0, music1_size-1);
    header.lpData = smusic1+delta;
    header.dwBufferLength = 4 * (music1_size-delta);
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
}

#endif
