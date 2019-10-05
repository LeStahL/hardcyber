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

#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include "engine/renderer.h"
#include "engine/shader.h"
#include "engine/loader.h"
#include "scenes.h"
#include "engine/orchestrator.h"

#include <stddef.h>

#define FALSE (0)
#define TRUE (1)
#define ABS(x) ((x)<0?(-x):(x))
#define sign(x) ((x)<0?-1.:1.)

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


#define clamp(x, minimum, maximum) min(max(x, minimum), maximum)


#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>

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


// Supported resolutions
const int nresolutions = 9;
const char *resolution_names[] = 
{
    // 16:9
    "1920*1080",
    "1600*900",
    "1280*720",
    "960*540",
    // 4:3
    "1600*1200",
    "1280*960",
    "1024*768",
    "800*600",
    "640*480"
};
const int widths[] = 
{
    1920,
    1600,
    1280,
    960,
    1600,
    1280,
    1024,
    800,
    640
};
const int heights[] = 
{
    1080,
    900,
    720,
    540,
    1200,
    960,
    768,
    600,
    480
};

// Supported FSAA entries;
const int nfsaa = 6;
const char *fsaa_names[] =
{
    "1x (None)",
    "4x",
    "9x",
    "16x",
    "25x",
    "36x"
};

const int nbuffersizes = 4;
const char *buffersize_names[] = 
{
    "128x128 px",
    "256x256 px",
    "512x512 px",
    "1024x1024 px"
};

#ifdef MIDI
HMIDIOUT hMidiOut;
#endif

int
#ifdef MIDI
    // MIDI controller values
    fader_0_value,
    fader_1_value,
    fader_2_value,
    fader_3_value,
    fader_4_value,
    fader_5_value,
    fader_6_value,
    fader_7_value,
    
    dial_0_value,
    dial_1_value,
    dial_2_value,
    dial_3_value,
    dial_4_value,
    dial_5_value,
    dial_6_value,
    dial_7_value,
#endif
    
    // SFX
    sfx_program,
    sfx_handle,
    sfx_blockoffset_location,
    sfx_samplerate_location,
    sfx_volumelocation,
    sfx_texs_location,
    sfx_sequence_texture_location,
    sfx_sequence_width_location,

    // Sequence
    sequence_texture_handle,

    // Antialiasing
    fsaa = 36,
    txaa = 1,

	// Text
	font_texture_handle;
    
double mx, my;

// Demo globals
double t
#ifdef MIDI
    ,
    time_dial = 0.,
    time_fine_dial = 0.,
    time_very_fine_dial = 0.,
    fader0 = 0,
    fader1 = 0,
    fader2 = 0,
    fader3 = 0,
    fader4 = 0,
    fader5 = 0,
    fader6 = 0,
    fader7 = 0
#endif
    ;

unsigned int loading = 1, music_loading = 0;
int music_block = 0;
unsigned int snd_framebuffer;
unsigned int start_at_scene = 0;

// Music shader globals
int sample_rate = 44100, channels = 2;
double duration1 = duration; //3 min running time
float *smusic1;
int music1_size;
float texs = 512;
int block_size = 512 * 512,
nblocks1;
unsigned int paused = 0, 
    recording = 0;
char record_filename[1024];

double t_paused;

GLuint first_pass_framebuffer = 0, first_pass_texture;
GLenum error;
#define NSHADERS 4.

float t_load_end = 0.;

void load_demo();
void load_font();
void quad();
void updateBar();
void draw();
void jump_to_scene(unsigned int scene_index);

#include "sequence.h"

#include "sfx.h"
#define SFX_VAR_IVOLUME "iVolume"
#define SFX_VAR_ISAMPLERATE "iSampleRate"
#define SFX_VAR_IBLOCKOFFSET "iBlockOffset"
#define SFX_VAR_ITEXSIZE "iTexSize"
#define SFX_VAR_ISEQUENCE "iSequence"
#define SFX_VAR_ISEQUENCEWIDTH "iSequenceWidth"

#include "font/font.h"

#include "gfx/symbols.h"

#ifdef WIN32
#	include "pal_win32.h"
#else
#	include "pal_linux.h"
#endif

#endif
