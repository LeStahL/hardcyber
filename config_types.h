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

#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H

enum OpenGLProfile
{
	CoreProfile,
	CompatibilityProfile,
};

enum SwapChain
{
	DoubleBuffer,
	TripleBuffer,
};

struct OpenGLSettings
{
	enum OpenGLProfile profile;
	enum SwapChain swapChain;

	int majorVersion;
	int minorVersion;

	int useSRGB;

	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;

	int depthBits;
	int stencilBits;

	int samples;
};

#endif
