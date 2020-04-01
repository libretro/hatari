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

#include "retro_files.h"

#include <sys/stat.h> 
#include <stdio.h>
#include <string.h>

bool file_exists(const char *path)
{
   FILE *dummy;

   if (!path || !*path)
      return false;

   dummy = fopen(path, "rb");

   if (!dummy)
      return false;

   fclose(dummy);
   return true;
}

void path_join(char* out, const char* basedir, const char* filename)
{
	snprintf(out, RETRO_PATH_MAX, "%s%s%s", basedir, RETRO_PATH_SEPARATOR, filename);
}	

#ifdef VITA
#include <psp2/types.h>
#include <psp2/io/dirent.h>
#include <psp2/kernel/threadmgr.h>

#define rmdir(name) sceIoRmdir(name)


int chdir( const char* path)
{
  return 0;
}

char* getcwd( char* buf, size_t size )
{
  if ( buf != NULL && size >= 2 )
  {
    buf[ 0 ] = '.';
    buf[ 1 ] = 0;
    return buf;
  }

  return NULL;
}
#endif
