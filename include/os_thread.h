#ifndef _OS_THREAD_H_
#define _OS_THREAD_H_

typedef s32 OSId;
typedef s32 OSPri;

typedef struct {
} OSThread;

extern void   osCreateThread(OSThread *, OSId, void (*)(void *), void *, void *, OSPri);
extern void   osStartThread(OSThread *);

#endif /* !_OS_THREAD_H_ */
