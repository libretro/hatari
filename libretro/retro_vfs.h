#ifndef RETRO_VFS_H__
#define RETRO_VFS_H__

#include "libretro.h"
#include <stdbool.h>
#include <stdint.h>

void retro_vfs_init(retro_environment_t environ_cb);
bool is_retro_vfs_available(void);

bool retro_vfs_file_exists(const char *path);
int64_t retro_vfs_file_size(const char *path);
int retro_vfs_remove(const char *path);
int retro_vfs_rename(const char *old_path, const char *new_path);

typedef struct retro_vfs_file_wrapper RFILE;

RFILE *retro_vfs_fopen(const char *path, unsigned mode, unsigned hints);
int retro_vfs_fclose(RFILE *stream);
int64_t retro_vfs_fread(RFILE *stream, void *s, uint64_t len);
size_t retro_vfs_fread_full(void *buf, size_t size, size_t n, RFILE *f);
int64_t retro_vfs_fwrite(RFILE *stream, const void *s, uint64_t len);
int64_t retro_vfs_fseek(RFILE *stream, int64_t offset, int seek_position);
int64_t retro_vfs_ftell(RFILE *stream);
int retro_vfs_fflush(RFILE *stream);
char *retro_vfs_fgets(RFILE *stream, char *s, int size);

typedef struct retro_vfs_dir_wrapper RDIR;

RDIR *retro_vfs_opendir(const char *dir, bool include_hidden);
bool retro_vfs_readdir(RDIR *dirstream);
const char *retro_vfs_dirent_get_name(RDIR *dirstream);
bool retro_vfs_dirent_is_dir(RDIR *dirstream);
bool retro_vfs_dir_exists(const char *path);
bool retro_vfs_closedir(RDIR *dirstream);

#endif /* RETRO_VFS_H__ */
