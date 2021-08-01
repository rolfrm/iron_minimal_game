#include<iron/full.h>
#include<iron/time.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <math.h>
typedef struct{
  int value;

}wave_element;

typedef struct{
  bool * collapsed;
  wave_element * values;
  int width, height;
}wavestate;


int get_elem(wavestate * wave, int x, int y){
  if(x > wave->width || y > wave->height || x <0 || y < 0) return -1;
								
  int index = x + wave->width * y;
  if(!wave->collapsed[index])  return -1;
  
  return wave->values[index].value;
}

bool wave_prop(wavestate * wave, int x, int y, f32 * prop, int * select){
  int index = x + wave->width * y;
  if(wave->collapsed[index]){
	 return false;
  }
  // checker pattern:
  f32 b = 0;
  f32 w = 0;
  int right = get_elem(wave, x + 1, y);
  if(right == 0)
	 w += 1.0;
  else if(right == 1)
	 b += 1.0;
  int left = get_elem(wave, x - 1, y);
  if(left == 0)
	 w += 1.0;
  else if(left == 1)
	 b += 1.0;
  int up = get_elem(wave, x, y + 1);
  int down = get_elem(wave, x, y - 1);
  if(up == 0)
	 w += 1.0;
  else if (up == 1)
	 b += 1.0;
  if(down == 0)
	 w += 1.0;
  else if (down == 1)
	 b += 1.0;
	 	 
  *prop = MAX(w, b);
  if(select){
	 if(w < b)
		*select = 0;
	 else if(w > b)
		*select = 1;
	 else
		*select = random() % 2; // select random instead.	 
  }
  return true;
}

void printWaveState(wavestate * ws){
  for(int j = 0; j < ws->height; j++){
		for(int i = 0; i < ws->width; i++){
			 int v = get_elem(ws, i, j);
			 if( v == -1){
				printf("  ");
			 }else{
				printf("%i ", v);
			 }
		  }
		printf("\n");
  }
}

void wave_collapse(wavestate * ws){
  while(true){
	 int i2 = 0,j2 = 0;
	 f32 maxProp = 0.0;
	 int selected = -1;
	 bool any = false;
	 int samecount = 1;
	 for(int i = 0; i < ws->width; i++){
		for(int j = 0; j < ws->height; j++){
		  f32 prop = 0.0f;
		  int select = -1;
	 
		  if(wave_prop(ws, i, j, &prop, &select)){
			 any = true;
			 if(prop > maxProp || (prop == maxProp &&  (random() % samecount) == 0)){
				if(prop > maxProp){
				  samecount = 1;
				}else{
				  samecount += 1;
				}
				
				maxProp = prop;
				i2 = i;
				j2 = j;
				selected = select;
			 }
		  }
		}
	 }
	 if(!any)
		break;
	 int index = i2 + ws->width * j2;
	 ws->collapsed[index] = true;
	 ws->values[index].value = selected;
	 printWaveState(ws);
	 printf("\n");
	 iron_usleep(100000);
  }
}

int main(int argc, char ** argv){
  int s = 32;
  wavestate ws = {
						.collapsed = calloc(sizeof(bool) * s * s, 1),
						.values = malloc(sizeof(wave_element) * s * s),
						.width = s,
						.height = s
  };
  
  //ws.values[16 * s + 16].value = 1;
  //ws.collapsed[16 * s + 16] = true;
  wave_collapse(&ws);
  
  /*
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
  */
  return 0;
}
