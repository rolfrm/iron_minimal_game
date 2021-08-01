#include <iron/full.h>
#include <iron/gl.h>
int main(int argc, char ** argv){
  gl_window * w = gl_window_open(200,196);
  gl_window_make_current(w);
  
  while(true){
	 gl_window_make_current(w);
	 gl_window_event events[10];
  	 size_t event_count = gl_get_events(events, array_count(events));
    blit_begin(BLIT_MODE_UNIT);
    blit_rectangle(-1,-1,2,2, 1,1,1,1);
	 blit_rectangle(-0.5,-0.5,1,1, 0,1,1,1);

	 gl_window_poll_events();
    gl_window_swap(w);
    iron_usleep(100000/3);  
  }
  return 0;
}
