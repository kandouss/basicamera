typedef struct buffer {
	void *start;
	size_t length;
} buffer;

static char            *dev_name;
static int              fd = -1;
struct buffer          *buffers;
static unsigned int     n_buffers;
static int              out_buf;
static int              force_format;
static int              frame_count = 5;

int open_device(void);
int close_device(void);
buffer get_frame(int);

#define CLEAR(x) memset(&(x), 0, sizeof(x))
