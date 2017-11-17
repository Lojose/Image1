#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Global.h"
#include "Frame.h"
#include "Image.h"

Frame frame;
int main(int argc, char * argv[]) { 
	const char *cmd1 =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-i apple_raw.png "
		"-f rawvideo "
		"-pix_fmt yuv420p -";

	const char * cmd2 =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

#ifdef _WIN32
	FILE * pipein =  _popen(cmd1, "rb");
	FILE * pipeout = _popen(cmd2, "wb");
#else
	FILE * pipein = popen(cmd1, "rb");
	File * pipout = popen (cmd2, "wb")

#endif
	if (pipeout == 0) {
		std::cout << "error: " << strerror(errno) << std::endl;
		return 1;
	}

	byte *snapshot1;
	snapshot1 = new byte[W *H *3];
	fread(snapshot1, 1, W * H * 3, pipein);
	
	Image img1(100, 100, 0, 0, snapshot1);
	img1.setVelocity(1, 1);
	img1.setSnap(snapshot1); 
	img1.Imgload(snapshot1); 
	img1.write(pipeout); 
	/*
	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double dt = i / frames_per_second;
		if (dt > 1.0 / 60.0) {  
			img1.update(dt);
			img1.draw_();

			frame.write(pipeout);
			frame.clear();
		}
	}
	*/

	fflush(pipeout);
	fflush(pipein); 
#ifdef _WIN32
	_pclose(pipeout);
	_pclose(pipein); 
#else
	pclose(pipe);
#endif
	//std::cout << "num_frames: " << num_frames << std::endl;
	std::cout << "Done." << std::endl;
	return 0;
}

	


