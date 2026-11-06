#ifndef EMU_CPU_SEG_H
#define EMU_CPU_SEG_H

#define IS_DATA_SEGMENT_DESCRIPTOR(s) (((s >> 43) & 0x3) == 0x2)    // Check if type has type bits 10000
#define IS_CODE_SEGMENT_DESCRIPTOR(s) (((s >> 43) & 0x3) == 0x3)    // Check if type has type bits 11000
#define IS_SYSM_SEGMENT_DESCRIPTOR(s) (!((s >> 44) & 1))            // Check if type has type bits 00000
#define IS_DATA_SEG(s) (s == SEG_REG_ES || s == SEG_REG_DS || s == SEG_REG_FS || s == SEG_REG_GS)

#define DESCRIPTOR_RW(d) (((d) >> 41) & 1)                   // Get descriptor r/w value

// helpers (useful when s == 1)
#define SEG_IS_CODE(c)     ((c)->s && ((c)->type & 8))
#define SEG_IS_DATA(c)     ((c)->s && !((c)->type & 8))
#define SEG_WRITABLE(c)    (SEG_IS_DATA(c) && ((c)->type & 2))
#define SEG_READABLE(c)    (SEG_IS_DATA(c) || ((c)->type & 2))
#define SEG_EXPAND_DOWN(c) (SEG_IS_DATA(c) && ((c)->type & 4))
#define SEG_CONFORMING(c)  (SEG_IS_CODE(c) && ((c)->type & 4))

typedef enum { 
    ACC_READ, 
    ACC_WRITE, 
    ACC_EXEC 
} Access;

#endif
