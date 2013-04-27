#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"

playlist_t *playlist_init(char *filepath)
{
	FILE *fp = fopen(filepath, "r");
	char *filename;
	char line[4096];
	playlist_t *playlist;

	if(!fp)
	{
		perror("playlist_init");
		return NULL;
	}

	playlist = (playlist_t *)malloc(sizeof(playlist_t));
	playlist->entry_count = 0;
	playlist->current_entry = 0;

	while((filename = fgets(line, LINE_MAX, fp)) != NULL)
	{
		if(strlen(filename) <= MAX_FILENAME)
		{
			playlist->entries[playlist->entry_count] = (char *)malloc(sizeof(char) * strlen(filename));
			memset(playlist->entries[playlist->entry_count], 0, strlen(filename));
			strncpy(playlist->entries[playlist->entry_count], filename, (strlen(filename)-1));
		}

		playlist->entry_count++;
	}

	fclose(fp);
	return playlist;
}

uint32_t playlist_count(playlist_t *playlist)
{
	return playlist->entry_count;
}

char *playlist_current_video(playlist_t *playlist)
{
	return playlist->entries[playlist->current_entry];
}

void playlist_next(playlist_t *playlist)
{
	playlist->current_entry++;
}

void playlist_destroy(playlist_t *playlist)
{
	int i = 0;

	// Free all of our entries first.
	for(i = 0; i < playlist->entry_count; i++)
	{
		if(playlist->entries[i] != NULL)
		{
			free(playlist->entries[i]);
		}
	}
	// Free the playlist context.
	free(playlist);
}
