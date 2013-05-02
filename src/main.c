#include <stdio.h>
#include <unistd.h>

#include <krad_mkv_demux.h>

#include "playlist.h"
#include "splice.h"

int main()
{
	kr_mkv_t *mkv_output;
	kr_mkv_t *mkv_input;
	kr_mkv_t *settings;

	krad_system_init();
//	krad_system_log_on("derp.log");
	playlist_t *playlist = playlist_init("test.txt");

	mkv_output = kr_mkv_create_stream(argv[1], atoi(argv[2]), argv[3], argv[4]);

	if(splice_init(settings, mkv_output, playlist) < 0)
	{
		perror("splice_init");
	}

	printf("resolution: %d x %d\n", mkv_output->tracks[VIDEO_TRACK].width,
					mkv_output->tracks[VIDEO_TRACK].height);

	uint32_t i;
	while(1)
	{
		playlist->current_entry = 0;
		for(i = 0; i < playlist_count(playlist); i++)
		{
			if(playlist_current_video(playlist) > 0)
			{
				printf("playing: %s\n", playlist_current_video(playlist));
				mkv_input = kr_mkv_open_file(playlist_current_video(playlist));

				if(!mkv_input)
				{
					perror(playlist_current_video(playlist));
				}

				splice(mkv_input, mkv_output);

				kr_mkv_destroy(&mkv_input);
				playlist_next(playlist);
			}
		}
	}

	kr_mkv_destroy(&mkv_output);
	playlist_destroy(playlist);

	return(0);
}
