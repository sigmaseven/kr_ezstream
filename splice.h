#include "playlist.h"
#define VIDEO_TRACK 1
#define AUDIO_TRACK 2

int splice_init(kr_mkv_t * temp, kr_mkv_t *mkv, playlist_t *playlist);
void splice(kr_mkv_t *input, kr_mkv_t *output);
