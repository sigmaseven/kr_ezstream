#include <krad_mkv_demux.h>

#include "splice.h"

int splice_init(kr_mkv_t *temp, kr_mkv_t *mkv, playlist_t *playlist)
{
	temp = kr_mkv_open_file(playlist->entries[0]);
	int result = kr_mkv_add_video_track(mkv, VP8, 30, 1,
			       		    temp->tracks[VIDEO_TRACK].width,
			       		    temp->tracks[VIDEO_TRACK].height);
	if(result < 0)
	{
		return result;
	}

	kr_mkv_destroy(&temp);
	return 0;
}

void splice(kr_mkv_t *input, kr_mkv_t *output)
{
	int bytes_read;
	int keyframe;
	uint32_t track;
	uint64_t timecode;
	uint8_t *buffer;
	uint8_t flags;

	buffer = (uint8_t *)malloc(10000000);

	while((bytes_read = kr_mkv_read_packet(input, &track, &timecode, &flags, buffer)) > 0)
	{
		if(flags == 0x80)
		{
			keyframe = 1;
		}
		else
		{
			keyframe = 0;
		}

		if(track == VIDEO_TRACK)
		{
			kr_mkv_add_video(output, VIDEO_TRACK, buffer, bytes_read, keyframe);
		}
	}
	free(buffer);
}
