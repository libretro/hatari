#include "retro_vfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if !defined(_WIN32) || defined(_XBOX)
#include <dirent.h>
#define HAVE_POSIX_DIRENT 1
#endif

static struct retro_vfs_interface *file_cb = NULL;

void retro_vfs_init(retro_environment_t environ_cb)
{
   // already initialized
   if (is_retro_vfs_available())
      return;

   struct retro_vfs_interface_info vfs_iface_info;

   file_cb = NULL;

   if (!environ_cb)
      return;

   // we use v4 to support > 2GB hard disk images
   vfs_iface_info.required_interface_version = 4;
   vfs_iface_info.iface = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &vfs_iface_info))
      file_cb = vfs_iface_info.iface;
}

bool is_retro_vfs_available(void)
{
   return file_cb != NULL;
}

/* ------------------------------------------------------------------ */
/* Stat / exists / size                                                 */
/* ------------------------------------------------------------------ */

bool retro_vfs_file_exists(const char *path)
{
   if (!path || !*path)
      return false;

   if (file_cb && file_cb->stat_64)
   {
      int64_t size  = 0;
      int flags = file_cb->stat_64(path, &size);

#ifdef DEBUG
      fprintf(stderr,
         "retro_vfs_file_exists checking: %s flags=0x%x size=%d valid=%d dir=%d\n",
         path, flags, size, !!(flags & RETRO_VFS_STAT_IS_VALID),
         !!(flags & RETRO_VFS_STAT_IS_DIRECTORY));
      fflush(stderr);
#endif

      return (flags & RETRO_VFS_STAT_IS_VALID) &&
             !(flags & RETRO_VFS_STAT_IS_DIRECTORY);
   }

   {
      FILE *f = fopen(path, "rb");
      if (!f)
         return false;
      fclose(f);
      return true;
   }
}

int64_t retro_vfs_file_size(const char *path)
{
   if (!path || !*path)
      return -1;

   if (file_cb && file_cb->stat_64)
   {
      int64_t size  = 0;
      int flags = file_cb->stat_64(path, &size);
      if (flags & RETRO_VFS_STAT_IS_VALID)
         return (int64_t)size;
      return -1;
   }

   {
      struct stat st;
      if (stat(path, &st) == 0)
         return (int64_t)st.st_size;
      return -1;
   }
}

int retro_vfs_remove(const char *path)
{
   if (file_cb && file_cb->remove)
      return file_cb->remove(path);
   return remove(path);
}

int retro_vfs_rename(const char *old_path, const char *new_path)
{
   if (file_cb && file_cb->rename)
      return file_cb->rename(old_path, new_path);
   return rename(old_path, new_path);
}

/* ------------------------------------------------------------------ */
/* File I/O                                                              */
/* ------------------------------------------------------------------ */

struct retro_vfs_file_wrapper
{
   bool use_vfs;
   union
   {
      struct retro_vfs_file_handle *vfs;
      FILE                         *stdio;
   } handle;
};

RFILE *retro_vfs_fopen(const char *path, unsigned mode, unsigned hints)
{
   RFILE *rf = (RFILE *)calloc(1, sizeof(*rf));

   if (!rf)
      return NULL;

   if (file_cb && file_cb->open)
   {
      rf->use_vfs = true;
      rf->handle.vfs = file_cb->open(path, mode, hints);

      if (!rf->handle.vfs)
      {
         free(rf);
         return NULL;
      }
      return rf;
   }

   {
      const char *stdio_mode = "rb";

      if (mode & RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING)
         stdio_mode = "r+b";
      else if (mode & RETRO_VFS_FILE_ACCESS_WRITE)
         stdio_mode = "wb";

      rf->use_vfs = false;
      rf->handle.stdio = fopen(path, stdio_mode);

      if (!rf->handle.stdio)
      {
         free(rf);
         return NULL;
      }
      return rf;
   }
}

int retro_vfs_fclose(RFILE *stream)
{
   int ret;

   if (!stream)
      return -1;

   ret = stream->use_vfs ? file_cb->close(stream->handle.vfs)
                         : fclose(stream->handle.stdio);

   free(stream);
   return ret;
}

int64_t retro_vfs_fread(RFILE *stream, void *s, uint64_t len)
{
   if (!stream)
      return -1;

   if (stream->use_vfs)
      return file_cb->read(stream->handle.vfs, s, len);

   return (int64_t)fread(s, 1, (size_t)len, stream->handle.stdio);
}

size_t retro_vfs_fread_full(void *buf, size_t size, size_t n, RFILE *f)
{
   size_t total = size * n;
   size_t done = 0;
   uint8_t *p = (uint8_t *)buf;

   while (done < total)
   {
      int64_t r = retro_vfs_fread(f, p + done, total - done);
      if (r <= 0)
         break;
      done += (size_t)r;
   }
   return (size == 0) ? 0 : (done / size);
}

int64_t retro_vfs_fwrite(RFILE *stream, const void *s, uint64_t len)
{
   if (!stream)
      return -1;

   if (stream->use_vfs)
      return file_cb->write(stream->handle.vfs, s, len);

   return (int64_t)fwrite(s, 1, (size_t)len, stream->handle.stdio);
}

int64_t retro_vfs_fseek(RFILE *stream, int64_t offset, int seek_position)
{
   if (!stream)
      return -1;

   if (stream->use_vfs)
      return file_cb->seek(stream->handle.vfs, offset, seek_position);

   if (fseek(stream->handle.stdio, (long)offset, seek_position) != 0)
      return -1;
   return 0;
}

int64_t retro_vfs_ftell(RFILE *stream)
{
   if (!stream)
      return -1;

   if (stream->use_vfs)
      return file_cb->tell(stream->handle.vfs);

   return (int64_t)ftell(stream->handle.stdio);
}

int retro_vfs_fflush(RFILE *stream)
{
   if (!stream)
      return -1;

   if (stream->use_vfs)
      return file_cb->flush ? file_cb->flush(stream->handle.vfs) : 0;

   return fflush(stream->handle.stdio);
}

char *retro_vfs_fgets(RFILE *stream, char *s, int size)
{
   int i;

   if (!stream || !s || size <= 0)
      return NULL;

   if (!stream->use_vfs)
      return fgets(s, size, stream->handle.stdio);

   for (i = 0; i < size - 1; i++)
   {
      char    c;
      int64_t nread = file_cb->read(stream->handle.vfs, &c, 1);

      if (nread <= 0)
      {
         if (i == 0)
            return NULL;
         break;
      }

      s[i] = c;

      if (c == '\n')
      {
         i++;
         break;
      }
   }

   s[i] = '\0';
   return s;
}

/* ------------------------------------------------------------------ */
/* Directory listing                                                    */
/* ------------------------------------------------------------------ */

struct retro_vfs_dir_wrapper
{
   bool use_vfs;
   union
   {
      struct retro_vfs_dir_handle *vfs;
#ifdef HAVE_POSIX_DIRENT
      DIR *posix;
#else
      void *posix;
#endif
   } handle;
#ifdef HAVE_POSIX_DIRENT
   struct dirent *cur;
#endif
};

RDIR *retro_vfs_opendir(const char *dir, bool include_hidden)
{
   RDIR *rd;

   if (file_cb && file_cb->opendir)
   {
      struct retro_vfs_dir_handle *h = file_cb->opendir(dir, include_hidden);
      if (!h)
         return NULL;

      rd = (RDIR *)calloc(1, sizeof(*rd));
      if (!rd)
      {
         file_cb->closedir(h);
         return NULL;
      }
      rd->use_vfs    = true;
      rd->handle.vfs = h;
      return rd;
   }

#ifdef HAVE_POSIX_DIRENT
   {
      DIR *d = opendir(dir);
      if (!d)
         return NULL;

      rd = (RDIR *)calloc(1, sizeof(*rd));
      if (!rd)
      {
         closedir(d);
         return NULL;
      }
      rd->use_vfs      = false;
      rd->handle.posix = d;
      return rd;
   }
#else
   (void)dir;
   (void)include_hidden;
   return NULL;
#endif
}

bool retro_vfs_readdir(RDIR *dirstream)
{
   if (!dirstream)
      return false;

   if (dirstream->use_vfs)
      return file_cb->readdir(dirstream->handle.vfs);

#ifdef HAVE_POSIX_DIRENT
   dirstream->cur = readdir(dirstream->handle.posix);
   return dirstream->cur != NULL;
#else
   return false;
#endif
}

const char *retro_vfs_dirent_get_name(RDIR *dirstream)
{
   if (!dirstream)
      return NULL;

   if (dirstream->use_vfs)
      return file_cb->dirent_get_name(dirstream->handle.vfs);

#ifdef HAVE_POSIX_DIRENT
   return dirstream->cur ? dirstream->cur->d_name : NULL;
#else
   return NULL;
#endif
}

bool retro_vfs_dirent_is_dir(RDIR *dirstream)
{
   if (!dirstream)
      return false;

   if (dirstream->use_vfs)
      return file_cb->dirent_is_dir(dirstream->handle.vfs);
}

bool retro_vfs_dir_exists(const char *path)
{
   if (!path || !*path)
      return false;

   if (file_cb && file_cb->stat_64)
   {
      int64_t size  = 0;
      int     flags = file_cb->stat_64(path, &size);
      return (flags & RETRO_VFS_STAT_IS_VALID) &&
             (flags & RETRO_VFS_STAT_IS_DIRECTORY);
   }

   {
      struct stat st;
      return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
   }
}

bool retro_vfs_closedir(RDIR *dirstream)
{
   bool ret;

   if (!dirstream)
      return false;

   if (dirstream->use_vfs)
      ret = file_cb->closedir(dirstream->handle.vfs);
   else
#ifdef HAVE_POSIX_DIRENT
      ret = (closedir(dirstream->handle.posix) == 0);
#else
      ret = false;
#endif

   free(dirstream);
   return ret;
}
