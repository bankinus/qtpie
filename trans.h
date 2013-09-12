#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <inttypes.h>

#define T_XBEGIN_STARTED (~0u) //
#define T_XABORT_EXPLICIT (1 << 0) //Set if abort caused by XABORT instruction.
#define T_XABORT_RETRY (1 << 1) //If set, the transaction may succeed on a retry. This bit is always clear if bit 0 is set.
#define T_XABORT_CONFLICT (1 << 2) //Set if another logical processor conflicted with a memory address that was part of the transaction that aborted.
#define T_XABORT_CAPACITY (1 << 3) //Set if an internal buffer overflowed.
#define T_XABORT_DEBUG (1 << 4) //Set if a debug breakpoint was hit.
#define T_XABORT_NESTED (1 << 5) //Set if an abort occurred during execution of a nested transaction.
#define T_XABORT_CODE(x) (((x) >> 24) & 0xff) //XABORT argument (only valid if bit '0' set, otherwise reserved).

#define XBEGIN(label) asm volatile goto(".byte 0xc7,0xf8 ; .long %l0-1f\n1:" ::: "eax", "memory" : label)
#define XEND()    asm volatile(".byte 0x0f,0x01,0xd5" ::"a"(T_XBEGIN_STARTED) : "memory" )
#define XFAIL(label) label: asm volatile("" ::: "eax")
#define XFAIL_STATUS(label, status) label: asm volatile("" : "=a" (status):: "memory")


#define XTCON(x, y) x##y
#define TCONCAT(x, y) XTCON(x, y)

// use this like:
//
// int status;
// TRANSACTION(status,
//     <transactional code>
// );
//
// check status
#define TRANSACTION(status, ...) XBEGIN(TCONCAT(TRANS_LABEL_, __LINE__)); __VA_ARGS__ XEND(); XFAIL_STATUS(TCONCAT(TRANS_LABEL_, __LINE__), status);

#endif
