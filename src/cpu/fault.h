#ifndef CPU_FAULT_H
#define CPU_FAULT_H
#include "common/types.h"
#define NO_FAULT ((Fault){ -1, 0 })

typedef struct { 
    int vector;     // vector < 0 means no fault
    u32 error;
} Fault;        

static inline bool faulted(Fault f)   { return f.vector >= 0; }
static inline Fault fault_gp(u32 e)   { return (Fault){ 13, e }; }
static inline Fault fault_np(u32 e)   { return (Fault){ 11, e }; }
static inline Fault fault_ss(u32 e)   { return (Fault){ 12, e }; }

#endif