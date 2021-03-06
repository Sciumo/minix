#ifndef _INCLUDE_TOOLS_H
#define _INCLUDE_TOOLS_H 1

/* Constants describing the disk */
#define SECTOR_SIZE	512
#define SECTOR_SHIFT	9
#define RATIO(b)	((b)/SECTOR_SIZE)
#define ISO_SECTOR_SIZE	2048
#define ISO_PVD_OFFSET	16
#define HRATIO		(SECTOR_SIZE / HCLICK_SIZE)
#define PARAMSEC	1	/* sector containing boot parameters */
#define DSKBASE		0x1E	/* floppy disk parameter vector */
#define DSKPARSIZE	11	/* there are this many bytes of parameters */
#define ESC		'\33'	/* escape key */
#define HEADERSEG	0x0060	/* place for an array of struct exec's */
#define MINIXSEG	0x0080	/* MINIX loaded here (rounded up to a click) */
#define BOOTSEG		0x07C0	/* bootstraps are loaded here */
#define SIGNATURE	0xAA55	/* proper bootstraps have this signature */
#define SIGNATPOS	510	/* offset within bootblock */
#define FREESEG		0x0800	/* Memory from FREESEG to cseg is free */
#define MSEC_PER_TICK	55	/* 18.2 ticks per second */

/* Scan codes for four different keyboards (from kernel/keyboard.c) */
#define DUTCH_EXT_SCAN	  32	/* 'd' */
#define OLIVETTI_SCAN	  12	/* '=' key on olivetti */
#define STANDARD_SCAN	  13	/* '=' key on IBM */
#define US_EXT_SCAN	  22	/* 'u' */

/* Other */
#define ROOT_INO ((ino_t) 1)	/* Inode nr of root dir. */
#define IM_NAME_MAX       63

/* Variables */
#ifndef EXTERN
#define EXTERN extern
#endif

typedef struct vector {
  u16_t offset;
  u16_t segment;
} vector;

struct image_header {
  char name[IM_NAME_MAX + 1];	/* Null terminated. */
  struct exec process;
};

EXTERN vector rem_part;		/* boot partition table entry */
EXTERN u16_t cseg, dseg;	/* code and data segment of the boot program */
EXTERN u32_t runsize;		/* size of this program */
EXTERN u16_t device;		/* drive being booted from */
EXTERN u16_t heads, sectors;	/* the drive's number of heads and sectors */
extern u16_t eqscancode;	/* Set by peek/getch() if they see a '=' */

/* Sticky attributes */
#define E_SPECIAL	0x01	/* These are known to the program */
#define E_DEV		0x02	/* The value is a device name */
#define E_RESERVED	0x04	/* May not be set by user, e.g. scancode */
#define E_STICKY	0x07	/* Don't go once set */

/* Volatile attributes */
#define E_VAR		0x08	/* Variable */
#define E_FUNCTION	0x10	/* Function definition */

typedef struct environment {
  struct environment *next;
  char flags;
  char *name;			/* name = value */
  char *arg;			/* name(arg) {value} */
  char *value;
  char *defval;			/* Safehouse for default values */
} environment;

/* External variables */
EXTERN environment *env;	/* Lists the environment */
EXTERN int fsok;		/* True if the boot device contains an FS */
EXTERN u32_t lowsec;		/* Offset to the file system on the boot dev */

#if defined(_MINIX) || defined(__minix) || defined(__ACK__)
/* Prototypes */
off_t r_super(void);
void r_stat(Ino_t _inum, struct stat *_stp );
ino_t r_readdir(char *_name );
off_t r_vir2abs(off_t _virblk );
ino_t r_lookup(Ino_t _cwd, char *_path );
#endif

#ifdef _MONHEAD
void readerr(off_t _sec, int _err );
int numprefix(char *_s, char **_ps );
int numeric(char *_s );
dev_t name2dev(char *_name );
int delay(char *_msec );
char *unix_err(int _err );
void init_cache(void);
void invalidate_cache(void);
char *b_value(char *_name );
void raw_copy(int _doff, int _dseg, int _soff, int _sseg, int _count);
void raw_clear(int _off, int _seg, int _count);
void bootstrap(int _device, int _partoff, int _partseg);

long a2l(char *_a );
char *ul2a(u32_t _n );
char *u2a(int _n1 );

/* Functions defined in monhead.s and usable by other files. */
void reset_video(int color);
int dev_geometry(void);
u16_t get_ext_memsize(void);
u16_t get_low_memsize(void);
u16_t get_processor(void);
u32_t get_tick(void);
u16_t get_video(void);
u16_t get_word(int _off, int _seg);
int getchar(void);
void minix(void);
void minix86(int _kcs, int _kds, char *_bpar, int _psize);
void minix386(int _kcs, int _kds, char *_bpar, int _psize);
int peekchar(void);
void put_word(int _off, int _seg, int _word);
int putchar(char _c);
int readsectors(int _off, int _seg, off_t _adr, int _ct);
void reboot(void);
void relocate(void);
int writesectors(int _off, int _seg, off_t _adr, int _ct);
#endif

#endif
