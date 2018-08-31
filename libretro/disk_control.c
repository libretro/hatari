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

#include "disk_control.h"

#include <sys/types.h> 
#include <sys/stat.h> 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMMENT "#"
#define M3U_SPECIAL_COMMAND "#COMMAND:"

#ifdef _WIN32
#define PATH_JOIN_SEPARATOR   		"\\"
// Windows also support the unix path separator
#define PATH_JOIN_SEPARATOR_ALT   	"/"
#else
#define PATH_JOIN_SEPARATOR   		"/"
#endif

// Note: This function returns a pointer to a substring_left of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

// Returns a substring of 'str' that contains the 'len' leftmost characters of 'str'.
char* strleft(char* str, int len)
{
	char* result = calloc(len + 1, sizeof(char));
	strncpy(result, str, len);
	return result;
}

// Returns a substring of 'str' that contains the 'len' rightmost characters of 'str'.
char* strright(char* str, int len)
{
	int pos = strlen(str) - len;
	char* result = calloc(len + 1, sizeof(char));
	strncpy(result, str + pos, len);
	return result;
}

// Returns true if 'str' starts with 'start'
bool strstartswith(const char* str, const char* start)
{
	if (strlen(str) >= strlen(start))
		if(!strncasecmp(str, start, strlen(start)))
			return true;
		
	return false;
}

// Returns true if 'str' ends with 'end'
bool strendswith(const char* str, const char* end)
{
	if (strlen(str) >= strlen(end))
		if(!strcasecmp((char*)&str[strlen(str)-strlen(end)], end))
			return true;
		
	return false;
}

// Return the directory name of filename 'filename'.
char* dirname_int(char* filename)
{
	if (filename == NULL)
		return NULL;
	
	char* right;
	int len = strlen(filename);
	
	if ((right = strrchr(filename, PATH_JOIN_SEPARATOR[0])) != NULL)
		return strleft(filename, len - strlen(right));
	
#ifdef _WIN32
	// Alternative search for windows beceause it also support the UNIX seperator
	if ((right = strrchr(filename, PATH_JOIN_SEPARATOR_ALT[0])) != NULL)
		return strleft(filename, len - strlen(right));
#endif
	
	// Not found
	return NULL;
}

// Verify if file exists
int file_exist(char *filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}

char* path_join(char* basedir, char* filename)
{
	int len = strlen(basedir) + strlen(PATH_JOIN_SEPARATOR) + strlen(filename);
	char* result = calloc(len + 1, sizeof(char));
	sprintf(result, "%s%s%s", basedir, PATH_JOIN_SEPARATOR, filename);
	return result;
}	

char* m3u_search_file(char* basedir, char* dskName)
{
	// Verify if this item is an absolute pathname (or the file is in working dir)
	if (file_exist(dskName))
	{
		// Copy and return
		int len = strlen(dskName);
		char* result = calloc(len + 1, sizeof(char));
		strncpy(result, dskName, len);
		return result;
	}
	
	// If basedir was provided
	if(basedir != NULL)
	{
		// Verify if this item is a relative filename (append it to the m3u path)
		char* dskPath = path_join(basedir, dskName);
		if (file_exist(dskPath))
		{
			// Return
			return dskPath;
		}
		free(dskPath);
	}
	
	// File not found
	return NULL;
}

void dc_reset(dc_storage* dc)
{
	// Verify
	if(dc == NULL)
		return;
	
	// Clean the command
	if(dc->command)
	{
		free(dc->command);
		dc->command = NULL;
	}

	// Clean the struct
	for(unsigned i=0; i < dc->count; i++)
	{
		free(dc->files[i]);
		dc->files[i] = NULL;
	}
	dc->count = 0;
	dc->index = -1;
	dc->eject_state = true;
}

dc_storage* dc_create(void)
{
	// Initialize the struct
	dc_storage* dc = NULL;
	
	if((dc = malloc(sizeof(dc_storage))) != NULL)
	{
		dc->count = 0;
		dc->index = -1;
		dc->eject_state = true;
		dc->command = NULL;
		for(int i = 0; i < DC_MAX_SIZE; i++)
		{
			dc->files[i] = NULL;
		}
	}
	
	return dc;
}

bool dc_add_file_int(dc_storage* dc, char* filename)
{
	// Verify
	if(dc == NULL)
		return false;

	if(filename == NULL)
		return false;

	// If max size is not
	if(dc->count < DC_MAX_SIZE)
	{
		// Add the file
		dc->count++;
		dc->files[dc->count-1] = filename;
		return true;
	}
	
	return false;
}

bool dc_add_file(dc_storage* dc, char* filename)
{
	// Verify
	if(dc == NULL)
		return false;

	if(filename == NULL)
		return false;

	// Copy and return
	int len = strlen(filename);
	char* filename_int = calloc(len + 1, sizeof(char));
	strncpy(filename_int, filename, len);
	return dc_add_file_int(dc, filename_int);
}

void dc_parse_m3u(dc_storage* dc, char* m3u_file)
{
	// Verify
	if(dc == NULL)
		return;
	
	if(m3u_file == NULL)
		return;

	FILE* fp = NULL;

	// Try to open the file
	if ((fp = fopen(m3u_file, "r")) == NULL)
		return;

	// Reset
	dc_reset(dc);
	
	// Get the m3u base dir for resolving relative path
	char* basedir = dirname_int(m3u_file);
	
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
				// Add the file to the struct
				dc_add_file_int(dc, filename);
			}

		}
	}
	
	// If basedir was provided
	if(basedir != NULL)
		free(basedir);

	// Close the file 
	fclose(fp);
}

void dc_free(dc_storage* dc)
{
	// Clean the struct
	dc_reset(dc);
	free(dc);
	dc = NULL;
	return;
}