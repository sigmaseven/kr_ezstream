#include <stdio.h>
#include <unistd.h>

#include <krad_mkv_demux.h>

#include "playlist.h"

int main()
{
	kr_mkv_t *mkv_output;
	kr_mkv_t *mkv_input;
	kr_mkv_t *settings;

	krad_system_init();
//	krad_system_log_on("derp.log");
	playlist_t *playlist = playlist_init("test.txt");
	mkv_output = kr_mkv_create_file("output.webm");

	if(splice_init(settings, mkv_output, playlist) < 0)
	{
		perror("splice_init");
	}

	printf("resolution: %d x %d\n", mkv_output->tracks[1].width, mkv_output->tracks[1].height);

	uint32_t i;

	for(i = 0; i < playlist_count(playlist); i++)
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
	kr_mkv_destroy(&mkv_output);
	playlist_destroy(playlist);

	return(0);
}
