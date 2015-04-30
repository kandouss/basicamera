typedef struct buffer {
	void *start;
	size_t length;
} buffer;


void init_buffer(buffer*,size_t);
void kill_buffer(buffer*);
void yuy2_to_rgb(buffer*,buffer*);

#define CLEAR(x) memset(&(x), 0, sizeof(x))
