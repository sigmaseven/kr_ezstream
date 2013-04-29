#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <limits.h>
#include <stdint.h>

#define MAX_ENTRIES 1000000
#define MAX_FILENAME 255

typedef struct playlist_struct playlist_t;

struct playlist_struct
{
	uint32_t entry_count;
	uint32_t current_entry;
	char *entry;
	char *entries[MAX_ENTRIES];
};

playlist_t *playlist_init(char *filepath);
uint32_t playlist_count(playlist_t *playlist);
void playlist_sanitize_entry(char *filename);
void playlist_next(playlist_t *playlist);
char *playlist_current_video(playlist_t *playlist);

#endif
