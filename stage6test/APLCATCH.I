# 1 "aplcatch.c" 1
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 1 "aplcatch.c" 2
# 1 "./raster.h" 1
# 1 "./types.h" 1
# 20 "./types.h"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 4 "./raster.h" 2
# 11 "./raster.h"
void plot_basket_64(UINT32 *base, int x, int y,
                        const UINT32 bitmap[16 ][2], unsigned int height);

void plot_apple_32(UINT32 *base, UINT16 x, int y,
                        const UINT32 *bitmap, unsigned int height);

void clear_screen(UINT32 *base);

void plot_vertical_line(UINT16 *base, int x, int n, int m);

void plot_pixel(UINT16 *base, int x, int y);

void plot_char(UINT16 *base, int x, int y,
                        const UINT16 *bitmap, unsigned int height);

void clear_basket(UINT32 *base, int x, int y,
                        unsigned int width, unsigned int height);

void clear_apple(UINT32 *base, int x, int y,
                        unsigned int width, unsigned int height);

void clear_char(UINT16 *base, int x, int y, unsigned int height);
# 2 "aplcatch.c" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
# 3 "./bitmaps.h" 2
# 11 "./bitmaps.h"
extern UINT32 apple_bitmap[32 ];
extern UINT32 basket_bitmap[16 ][2];
extern UINT16 num_maps[10][32];
extern UINT16 letterA_bitmap[32];
extern UINT16 letterB_bitmap[32];
extern UINT16 letterC_bitmap[32];
extern UINT16 letterD_bitmap[32];
extern UINT16 letterE_bitmap[32];
extern UINT16 letterF_bitmap[32];
extern UINT16 letterG_bitmap[32];
extern UINT16 letterH_bitmap[32];
extern UINT16 letterI_bitmap[32];
extern UINT16 letterJ_bitmap[32];
extern UINT16 letterK_bitmap[32];
extern UINT16 letterL_bitmap[32];
extern UINT16 letterM_bitmap[32];
extern UINT16 letterN_bitmap[32];
extern UINT16 letterO_bitmap[32];
extern UINT16 letterP_bitmap[32];
extern UINT16 letterQ_bitmap[32];
extern UINT16 letterR_bitmap[32];
extern UINT16 letterS_bitmap[32];
extern UINT16 letterT_bitmap[32];
extern UINT16 letterU_bitmap[32];
extern UINT16 letterV_bitmap[32];
extern UINT16 letterW_bitmap[32];
extern UINT16 letterX_bitmap[32];
extern UINT16 letterY_bitmap[32];
extern UINT16 letterZ_bitmap[32];
extern UINT16 apostrophe_bitmap[32];
# 3 "aplcatch.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 5 "./model.h" 2
# 1 "./RASTER.H" 1
# 6 "./model.h" 2
# 1 "C:/c68/include/stdlib.h" 1
# 18 "C:/c68/include/stdlib.h"
typedef unsigned long  size_t;




typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 7 "./model.h" 2
# 1 "C:/c68/include/time.h" 1
# 26 "C:/c68/include/time.h"
typedef long 		time_t;
# 34 "C:/c68/include/time.h"
typedef unsigned long	clock_t;

struct tm
{
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};



struct timeval {
	long	tv_sec;
	long	tv_usec;
};

struct timezone {
	int	tz_minuteswest;
	int	tz_dsttime;
};


 clock_t	clock	 (void) ;
 double		difftime (time_t, time_t) ;
 time_t		mktime	 (const struct tm *) ;
 time_t		time	 (time_t *) ;
 char * 	asctime	 (const struct tm *) ;
 char *		ctime	 (const time_t *) ;
 struct tm *	gmtime   (const time_t *) ;
 struct tm *	localtime (const time_t *) ;
 unsigned long  strftime (	char *s, size_t maxsize, const char *format, const struct tm *timeptr) ;



 void		tzset	(void) ;


 clock_t	_clock	 (void) ;
 int	gettimeofday (struct timeval *, struct timezone *) ;
 int	settimeofday (struct timeval *, struct timezone *) ;



typedef unsigned long  fd_set;


 int	select	(int, fd_set *, fd_set *, fd_set *,					struct timeval *) ;
# 8 "./model.h" 2
# 15 "./model.h"
typedef struct
{
    UINT16 x;
    int y;
    UINT32 width;
    UINT32 height;
}apple;

typedef struct
{
    UINT16 x, y;
    int delta_x;
    UINT32 width;
    UINT32 height;
    UINT32 (*bitmap)[2];
} basket;

typedef struct {
    UINT16 digit1_x, digit1_y;
    UINT16 digit2_x, digit2_y;
    UINT32 height;
    int value;
} score;

typedef struct {
    UINT16 digit1_x, digit1_y;
    UINT16 digit2_x, digit2_y;
    UINT32 height;
    int value;
} timer_round;

typedef struct {
    UINT16 x, y;
    UINT32 height;
    int value;
} timer_start;

typedef struct {

    UINT16 start_x;
    UINT16 start_y;
    UINT16 spacing;
    char *text;
} message;

typedef struct {
    apple apples[5 ];
    basket b;
    score curr_score;
    timer_round rt;
    timer_start st;
} model;



model *init_model();


basket init_basket();
void move_basket(basket *b, int direction);
void set_basket(basket *b, UINT16 set_x);


apple generate_apple(UINT16 col);
void move_apple(apple *this_apple);
void set_apple(apple *a, int x, int y);


score init_score();
void reset_score(score *score);
void set_score(score *score, int x);


timer_round init_round_timer();
void set_round_timer(timer_round *t, int x);

timer_start init_start_timer();
void set_start_timer(timer_start *st, int x);
# 4 "aplcatch.c" 2
# 1 "./events.h" 1
# 1 "./types.h" 1
# 3 "./events.h" 2
# 1 "./RASTER.H" 1
# 4 "./events.h" 2
# 1 "./model.h" 1
# 5 "./events.h" 2
# 1 "./renderer.h" 1
# 1 "./types.h" 1
# 3 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 4 "./renderer.h" 2
# 1 "./model.h" 1
# 5 "./renderer.h" 2
# 1 "./events.h" 1
# 6 "./renderer.h" 2
# 1 "./input.h" 1
# 1 "./model.h" 1
# 3 "./input.h" 2
# 11 "./input.h"
typedef enum {
    BASKET_MOVE_NONE,
    BASKET_MOVE_LEFT,
    BASKET_MOVE_RIGHT
} BasketAction;


void input_init();


int check_input();


char get_input();


void process_input(char input, int *quit);


void move_basket_based_on_input(basket *b);


BasketAction get_basket_action();
# 7 "./renderer.h" 2
# 1 "./RASTER.H" 1
# 8 "./renderer.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 9 "./renderer.h" 2
# 18 "./renderer.h"
void render_apple(UINT32 *base, apple *a, int op);

void render_basket(UINT32 *base, basket *b, int op);

void render_score(UINT16 *base, score *score);

void render_round_timer(UINT16 *base, timer_round *rt);

void render_start_timer(UINT16 *base, timer_start *st);


void display_message(message *msg);
void clear_message(message *msg);
const UINT16 *get_bitmap_for_char(char c);

void render_borders(UINT16 *base);

void master_render(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt);

void render_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt, timer_start *st);

void initialize_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt);

void update_model(UINT32 *base32, UINT16 *base16, apple *a,
        basket *b, score *score, timer_round *rt);

void render_objects(UINT32 *buffer, model *curr_model, int a_collision);
# 6 "./events.h" 2
# 14 "./events.h"
int check_basket_collision(basket *b, int direction);

int check_apple_collision(basket *b, apple *a);

void reset_apple_position(apple *a);

void increment_score(score *curr_score);

void decrement_round_timer(UINT16 *base, timer_round *t);

int is_start_time_up(timer_start *t);
# 5 "aplcatch.c" 2
# 1 "./types.h" 1
# 6 "aplcatch.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 7 "aplcatch.c" 2
# 1 "./renderer.h" 1
# 8 "aplcatch.c" 2
# 1 "./driver.h" 1
# 9 "aplcatch.c" 2
# 1 "./input.h" 1
# 10 "aplcatch.c" 2
# 20 "aplcatch.c"
UINT8 back_buffer_array[32260];


UINT32* allocate_back_buffer() {
    UINT8 *temp = back_buffer_array;


    temp = (UINT8*)(((UINT32)temp + 255) & ~255);

    return (UINT32*)temp;
}


UINT32* flip_buffers(UINT32 **front_buffer, UINT32 **back_buffer) {

    UINT32 *temp = *front_buffer;
    *front_buffer = *back_buffer;
    *back_buffer = temp;


    return *front_buffer;
}


unsigned long get_time() {
    unsigned long *timer_address = (unsigned long *)0x462;
    unsigned long time;


    unsigned long old_sr = _trap_1_wl((short)0x20,(long)(0)) ;
    time = *timer_address;
    _trap_1_wl((short)0x20,(long)(old_sr)) ;

    return time;
}

int main() {
    int quit = 0;
    unsigned long timeThen, timeNow, start_time;
    int tickCounter = 0;
    UINT32 *FB32 = (void*)_trap_14_w((short)0x2) ;
    UINT16 *FB16 = (UINT16*) (void*)_trap_14_w((short)0x2) ;
    char input;
    UINT32 *front_buffer = (UINT32 *)(void*)_trap_14_w((short)0x2) ;
    UINT32 *back_buffer = allocate_back_buffer();
    UINT32 *original_buffer = (UINT32 *)(void*)_trap_14_w((short)0x2) ;
    UINT32 *curr_buffer = back_buffer;



    model *curr_model = init_model();
    timeThen = get_time();

    input_init();


    clear_screen(front_buffer);
    clear_screen(back_buffer);

    render_borders((UINT16 *)front_buffer);
    render_borders((UINT16 *)back_buffer);




    initialize_model(curr_buffer, (UINT16*) curr_buffer, &(curr_model->apples[0]),
                 &(curr_model->b), &(curr_model->curr_score),
                 &(curr_model->rt));



    while (!quit && curr_model->rt.value > 0) {
        if (check_input()) {
            input = get_input();

            if (input == 'q' || input == 'Q') {
                quit = 1;
            } else {
                process_input(input, &quit);
            }
        }

        timeNow = get_time();
        if (timeNow != timeThen) {
            int b_collision = check_basket_collision(&(curr_model->b), 0);
            int a_collision = check_apple_collision(&(curr_model->b), &(curr_model->apples[0]));
            tickCounter++;


            if (tickCounter >= 70) {
                decrement_round_timer((UINT16*) curr_buffer, &(curr_model->rt));
                tickCounter = 0;
            }


            (void)_trap_14_w((short)0x25) ;
            (void)_trap_14_wllw((short)0x5,(long)(-1),(long)(long)curr_buffer,(short)(-1)) ;
# 124 "aplcatch.c"
            curr_buffer = flip_buffers(&front_buffer, &back_buffer);


            update_model(curr_buffer, (UINT16*) curr_buffer, &(curr_model->apples[0]),
                 &(curr_model->b), &(curr_model->curr_score),
                 &(curr_model->rt));

            timeThen = timeNow;
        }
    }

    (void)_trap_14_wllw((short)0x5,(long)(-1),(long)(long)original_buffer,(short)(-1)) ;
    return 0;
}
