/*
 * "streamable kanji code filter and converter"
 * Copyright (c) 1998-2002 HappySize, Inc. All rights reserved.
 *
 * LICENSE NOTICES
 *
 * This file is part of "streamable kanji code filter and converter",
 * which is distributed under the terms of GNU Lesser General Public 
 * License (version 2) as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with "streamable kanji code filter and converter";
 * if not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA  02111-1307  USA
 *
 * The author of this file:
 *
 */
/*
 * The source code included in this files was separated from mbfilter.c
 * by Moriyoshi Koizumi <moriyoshi@php.net> on 20 Dec 2002. The file
 * mbfilter.c is included in this package .
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#include <assert.h>

#include "mbfl_allocators.h"
#include "mbfl_string.h"
#include "mbfl_wchar_device.h"

void mbfl_wchar_device_ctor(mbfl_wchar_device *device)
{
	assert(device != NULL);

	device->buffer = (unsigned int *)0;
	device->length = 0;
	device->pos= 0;
	device->allocsz = MBFL_MEMORY_DEVICE_ALLOC_SIZE;
}

void mbfl_wchar_device_dtor(mbfl_wchar_device *device)
{
	assert(device != NULL);

	if (device->buffer) {
		mbfl_free(device->buffer);
	}
	device->buffer = (unsigned int*)0;
	device->length = 0;
	device->pos = 0;
}

int mbfl_wchar_device_output(int c, void *data)
{
	mbfl_wchar_device *device = (mbfl_wchar_device *)data;

	if (device->pos >= device->length) {
		/* reallocate buffer */
		int newlen;
		unsigned int *tmp;

		newlen = device->length + device->allocsz;
		tmp = (unsigned int *)mbfl_realloc((void *)device->buffer, newlen*sizeof(int));
		if (tmp == NULL) {
			return -1;
		}
		device->length = newlen;
		device->buffer = tmp;
	}

	device->buffer[device->pos++] = c;

	return c;
}

