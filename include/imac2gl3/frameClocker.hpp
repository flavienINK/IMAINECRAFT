#ifndef FRAMECLOCKER_H
#define FRAMECLOCKER_H

#include <time.h>

static const int FRAMES_PER_SECOND = 30;
static const int MIN_LOOP_TIME = 1000000000 / FRAMES_PER_SECOND;

namespace imac2gl3 {
	class FrameClocker {
		private:
			timespec start;
			timespec end;
			timespec diff;
			timespec delay;
			
		public:
			FrameClocker(){clock_gettime(CLOCK_REALTIME, &start);};
			~FrameClocker(){clock_gettime(CLOCK_REALTIME, &end); diff.tv_nsec = end.tv_nsec - start.tv_nsec; if(diff.tv_nsec < MIN_LOOP_TIME){ delay.tv_nsec = MIN_LOOP_TIME - diff.tv_nsec ; delay.tv_sec = 0; nanosleep(&delay, NULL);} }

		
	};
}

#endif
