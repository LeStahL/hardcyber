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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_types.h"

static const struct OpenGLSettings opengl_settings = {
    CompatibilityProfile, // profile
	DoubleBuffer, // swapChain

    2, // majorVersion
    1, // minorVersion

	0, // useSRGB

	8, // redBits
	8, // greenBits
	8, // blueBits
	8, // alphaBits

	24, // depthBits
	8, // stencilBits

	1, // samples (for Multisampling)
};

#define duration (222.0)

#endif
