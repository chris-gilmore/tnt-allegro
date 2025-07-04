#ifndef _OS_MESSAGE_H_
#define _OS_MESSAGE_H_

typedef void *OSMesg;

typedef struct {
} OSMesgQueue;

#define OS_MESG_NOBLOCK 0
#define OS_MESG_BLOCK   1

extern void   osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32    osRecvMesg(OSMesgQueue *, OSMesg *, s32);

#endif /* !_OS_MESSAGE_H_ */
