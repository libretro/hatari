/* Copyright (C) 2018 
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdarg.h>
#include "libretro.h"
#include "retro_disk_control.h"
#include "retro_strings.h"
#include "retro_utils.h"
#include "file/file_path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string/stdstring.h>

/*#include <sys/types.h> 
#include <sys/stat.h> 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>*/

static void fallback_log(enum retro_log_level level, const char* fmt, ...);
static retro_log_printf_t log_cb = fallback_log;

static void fallback_log(enum retro_log_level level, const char* fmt, ...)
{
	va_list va;

	(void)level;

	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}

#define COMMENT "#"
#define M3U_SPECIAL_COMMAND "#COMMAND:"

// Return the directory name of filename 'filename'.
static char* dirname_int(const char* filename)
{
	if (filename == NULL)
		return NULL;

	// Find last separator
	char* right = find_last_slash(filename);
	if (right)
		return strleft(filename, right - filename);

	// Not found
	return NULL;
}

static char* m3u_search_file(const char* basedir, const char* dskName)
{
	// If basedir was provided
	if (basedir != NULL && !path_is_absolute(dskName))
	{
		// Join basedir and dskName
		char* dskPath = path_join_dup(basedir, dskName);

		// Verify if this item is a relative filename (append it to the m3u path)
		if (file_exists(dskPath))
		{
			// Return
			return dskPath;
		}
		free(dskPath);
	}

	// Verify if this item is an absolute pathname (or the file is in working dir)
	if (file_exists(dskName))
	{
		// Copy and return
		return strdup(dskName);
	}

	// File not found
	return NULL;
}

void dc_reset(dc_storage* dc)
{
	unsigned i;

	// Verify
	if (dc == NULL)
		return;

	// Clean the command
	if (dc->command)
	{
		free(dc->command);
		dc->command = NULL;
	}

	// Clean the struct
	for (i = 0; i < dc->count; i++)
	{
		free(dc->files[i]);
		dc->files[i] = NULL;
		free(dc->names[i]);
		dc->names[i] = NULL;

		dc->types[i] = DC_IMAGE_TYPE_NONE;
	}

	dc->unit = DC_IMAGE_TYPE_NONE;
	dc->count = 0;
	dc->index = 0;
	dc->index_prev = 0;
	dc->eject_state = true;
	dc->replace = false;
}

dc_storage* dc_create(void)
{
	int i;

	// Initialize the struct
	dc_storage* dc = NULL;

	if ((dc = (dc_storage*)malloc(sizeof(dc_storage))) != NULL)
	{
		dc->unit = DC_IMAGE_TYPE_NONE;
		dc->count = 0;
		dc->index = 0;
		dc->eject_state = true;
		dc->replace = false;
		dc->command = NULL;
		for (i = 0; i < DC_MAX_SIZE; i++)
		{
			dc->files[i] = NULL;
			dc->names[i] = NULL;
			dc->types[i] = DC_IMAGE_TYPE_NONE;
		}
	}

	return dc;
}

bool dc_add_file_int(dc_storage* dc, char* filename, char* name)
{
	/* Verify */
	if (dc == NULL)
		return false;

	if (!filename || (*filename == '\0'))
		return false;

	/* If max size is not exceeded */
	if (dc->count < DC_MAX_SIZE)
	{
		/* Add the file */
		dc->count++;
		dc->files[dc->count - 1] = strdup(filename);
		dc->names[dc->count - 1] = !string_is_empty(name) ? strdup(name) : NULL;
		dc->types[dc->count - 1] = dc_get_image_type(filename);

		log_cb(RETRO_LOG_INFO, ">>> dc added int %s - [%s]\n", filename, name);
		return true;
	}

	return false;
}

bool dc_add_file(dc_storage* dc, const char* filename)
{
	unsigned index = 0;

	/* Verify */
	if (dc == NULL || !filename || (*filename == '\0'))
		return false;

	/* Dupecheck */
	for (index = 0; index < dc->count; index++)
	{
		if (!strcmp(dc->files[index], filename))
		{
			log_cb(RETRO_LOG_INFO,"File '%s' ignored as duplicate!\n", filename);
			return true;
		}
	}

	// Get 'name' - just the filename without extension
	char name[512];
	name[0] = '\0';
	fill_pathname(name, path_basename(filename), "", sizeof(name));

	if (!dc_add_file_int(dc, strdup(filename), strdup(name)))
		return false;

	// if dc unit-type is none, get type from first image
	if (dc->unit == DC_IMAGE_TYPE_NONE)
	{
		if (dc_get_image_type(dc->files[0]) == DC_IMAGE_TYPE_TAPE)
			dc->unit = DC_IMAGE_TYPE_TAPE;
		else if (dc_get_image_type(dc->files[0]) == DC_IMAGE_TYPE_FLOPPY)
			dc->unit = DC_IMAGE_TYPE_FLOPPY;
		else if (dc_get_image_type(dc->files[0]) == DC_IMAGE_TYPE_MEM)
			dc->unit = DC_IMAGE_TYPE_MEM;
		else
			dc->unit = DC_IMAGE_TYPE_FLOPPY;
	}

	log_cb(RETRO_LOG_INFO,">>> dc added %s - [%s] [unit %i]\n", filename, name, dc->unit);
	return true;
}

bool dc_remove_file(dc_storage* dc, int index)
{
	if (dc == NULL)
		return false;

	if (index < 0 || index >= dc->count)
		return false;

	// "If ptr is a null pointer, no action occurs"
	free(dc->files[index]);
	dc->files[index] = NULL;
	free(dc->names[index]);
	dc->names[index] = NULL;
	dc->types[index] = DC_IMAGE_TYPE_NONE;

	// Shift all entries after index one slot up
	if (index != dc->count - 1)
	{
		memmove(dc->files + index, dc->files + index + 1, (dc->count - 1 - index) * sizeof(dc->files[0]));
		memmove(dc->names + index, dc->names + index + 1, (dc->count - 1 - index) * sizeof(dc->names[0]));
	}
	dc->count--;

	// Reset fliplist unit after removing last entry
	if (dc->count == 0)
	{
		dc->unit = DC_IMAGE_TYPE_NONE;
	}

	return true;
}

int dc_replace_file(dc_storage* dc, int index, const char* filename)
{
	if (dc == NULL)
		return false;

	if (index < 0 || index >= dc->count)
		return false;

	// "If ptr is a null pointer, no action occurs"
	free(dc->files[index]);
	dc->files[index] = NULL;
	free(dc->names[index]);
	dc->names[index] = NULL;
	dc->types[index] = DC_IMAGE_TYPE_NONE;

	if (filename == NULL)
	{
		dc_remove_file(dc, index);
	}
	else
	{
		dc->replace = false;

		char full_path_replace[RETRO_PATH_MAX] = { 0 };
		strncpy(full_path_replace, (char*)filename, sizeof(full_path_replace));

		/* ZIP/M3U not implemented internally */
		if (
			strendswith(full_path_replace, "m3u") ||
			strendswith(full_path_replace, "zip") ||
			strendswith(full_path_replace, "7z")
			)
		{
			log_cb(RETRO_LOG_INFO,">>> dc replace %s unsupported type.\n", filename);
			return false;
		}
		/* Single append */
		else
		{
			// Get 'name' - just the filename without extension
			char name[512];
			name[0] = '\0';
			fill_pathname(name, path_basename(filename), "", sizeof(name));

			/* Dupecheck */
			for (unsigned i = 0; i < dc->count - 1; i++)
			{
				if (!strcmp(dc->files[i], full_path_replace))
				{
					dc_remove_file(dc, index);
					return 2;	// 2 = duplicate found
				}
			}

			dc->files[index] = strdup(filename);
			dc->names[index] = !string_is_empty(name) ? strdup(name) : NULL;
			dc->types[index] = dc_get_image_type(filename);

			log_cb(RETRO_LOG_INFO,">>> dc replace %s - %s [%u].\n", filename, name , dc->types[index] );
		}
	}

	return true;
}


void dc_parse_m3u(dc_storage* dc, const char* m3u_file)
{
	// Verify
	if (dc == NULL)
		return;

	if (m3u_file == NULL)
		return;

	FILE* fp = NULL;

	// Try to open the file
	if ((fp = fopen(m3u_file, "r")) == NULL)
		return;

	// Reset
	dc_reset(dc);

	// Get the m3u base dir for resolving relative path
	char* basedir = dirname_int(m3u_file);

	// Disk control interface 'name' for the following file
	char* image_name = NULL;

	// Read the lines while there is line to read and we have enough space
	char buffer[2048];
	while ((dc->count <= DC_MAX_SIZE) && (fgets(buffer, sizeof(buffer), fp) != NULL))
	{
		char* string = trimwhitespace(buffer);

		// If it's a m3u special key or a file
		if (strstartswith(string, M3U_SPECIAL_COMMAND))
		{
			dc->command = strright(string, strlen(string) - strlen(M3U_SPECIAL_COMMAND));
		}
		else if (!strstartswith(string, COMMENT))
		{
			// Search the file (absolute, relative to m3u)
			char* filename;
			if ((filename = m3u_search_file(basedir, string)) != NULL)
			{

				char tmp[512];
				tmp[0] = '\0';

				fill_pathname(tmp, path_basename(filename), "", sizeof(tmp));
				image_name = strdup(tmp);

				// Add the file to the struct
				dc_add_file_int(dc, filename, image_name);
				image_name = NULL;
			}

		}
	}

	// If basedir was provided
	if (basedir != NULL)
		free(basedir);

	// Close the file
	fclose(fp);

	if (dc->count != 0)
	{
		if (dc_get_image_type(dc->files[0]) == DC_IMAGE_TYPE_TAPE)
			dc->unit = DC_IMAGE_TYPE_TAPE;
		else if (dc_get_image_type(dc->files[0]) == DC_IMAGE_TYPE_FLOPPY)
			dc->unit = DC_IMAGE_TYPE_FLOPPY;
		else
			dc->unit = DC_IMAGE_TYPE_FLOPPY;

		log_cb(RETRO_LOG_INFO,">>> dc (m3u) unit type: %i\n", dc->unit);
	}
}

void dc_free(dc_storage* dc)
{
	// Clean the struct
	dc_reset(dc);
	free(dc);
	dc = NULL;
	return;
}

enum dc_image_type dc_get_image_type(const char* filename)
{
	// Missing file
	if (!filename || (*filename == '\0'))
		return DC_IMAGE_TYPE_NONE;

	// Floppy image
	if (strendswith(filename, "st") ||
		strendswith(filename, "msa") ||
		strendswith(filename, "stx") ||
		strendswith(filename, "dim") ||
		strendswith(filename, "ipf"))
		return DC_IMAGE_TYPE_FLOPPY;

	// Place holder for other images types
	//if (strendswith(filename, "cas"))
	//	return DC_IMAGE_TYPE_TAPE;

	// Fallback
	return DC_IMAGE_TYPE_UNKNOWN;
}
