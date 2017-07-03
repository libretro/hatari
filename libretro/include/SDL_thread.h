//FIXME RETRO HACK REDONE ALL THIS CRAPPY
//SDLTHREAD

// only because we need 
/*
HSDL_sem
HSDL_Thread
HSDL_SemWait
HSDL_CreateSemaphore
HSDL_CreateThread
HSDL_KillThread
HSDL_DestroySemaphore
HSDL_SemPost
*/
//in rs232.c

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern long GetTicks(void);

#define HSDL_KillThread(X)

#define ERR_MAX_STRLEN	128
#define ERR_MAX_ARGS	5
#define SDLCALL
#define HSDL_zero(x)	memset(&(x), 0, sizeof((x)))
#define HSDL_malloc	malloc
#define HSDL_MUTEX_TIMEDOUT	1
#define HSDL_MUTEX_MAXWAIT	(~(Uint32)0)
#define HSDL_SetError printf
#define HSDL_free free

typedef struct HSDL_error
{    
    int error;
    char key[ERR_MAX_STRLEN];
    int argc;
    union
    {
        void *value_ptr;
        int value_i;
        double value_f;
        char buf[ERR_MAX_STRLEN];
    } args[ERR_MAX_ARGS];
} HSDL_error;


#ifdef __CELLOS_LV2__

#include <pthread.h>
#include <semaphore.h>


struct HSDL_semaphore
{
    sem_t sem;
};
struct HSDL_semaphore;
typedef struct HSDL_semaphore HSDL_sem;

/* Create a counting semaphore */
HSDL_sem *
HSDL_CreateSemaphore(Uint32 initial_value)
{
	HSDL_sem *sem = (HSDL_sem *) HSDL_malloc(sizeof(HSDL_sem));
	if ( sem ) {
		if ( sem_init(&sem->sem, 0, initial_value) < 0 ) {
			HSDL_SetError("sem_init() failed");
			HSDL_free(sem);
			sem = NULL;
		}
	} else {
		//HSDL_OutOfMemory();
	}
	return sem;
}

void HSDL_DestroySemaphore(HSDL_sem *sem)
{
	if ( sem ) {
		sem_destroy(&sem->sem);
		HSDL_free(sem);
	}
}

int HSDL_SemTryWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}
	retval = HSDL_MUTEX_TIMEDOUT;
	if ( sem_trywait(&sem->sem) == 0 ) {
		retval = 0;
	}
	return retval;
}

int HSDL_SemWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	while ( ((retval = sem_wait(&sem->sem)) == -1) && (errno == EINTR) ) {}
	if ( retval < 0 ) {
		HSDL_SetError("sem_wait() failed");
	}
	return retval;
}

int HSDL_SemWaitTimeout(HSDL_sem *sem, Uint32 timeout)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	/* Try the easy cases first */
	if ( timeout == 0 ) {
		return HSDL_SemTryWait(sem);
	}
	if ( timeout == HSDL_MUTEX_MAXWAIT ) {
		return HSDL_SemWait(sem);
	}

	/* Ack!  We have to busy wait... */
	/* FIXME: Use sem_timedwait()? */
	timeout += HSDL_GetTicks();
	do {
		retval = HSDL_SemTryWait(sem);
		if ( retval == 0 ) {
			break;
		}
		HSDL_Delay(1);
	} while ( HSDL_GetTicks() < timeout );

	return retval;
}


Uint32 HSDL_SemValue(HSDL_sem *sem)
{
	int ret = 0;
	if ( sem ) {
		sem_getvalue(&sem->sem, &ret);
		if ( ret < 0 ) {
			ret = 0;
		}
	}
	return (Uint32)ret;
}

int HSDL_SemPost(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	retval = sem_post(&sem->sem);
	if ( retval < 0 ) {
		HSDL_SetError("sem_post() failed");
	}
	return retval;
}

typedef unsigned long HSDL_threadID;

struct HSDL_mutex
{
    int recursive;
    HSDL_threadID owner;
    HSDL_sem *sem;
};

typedef struct HSDL_mutex HSDL_mutex;
extern HSDL_mutex *HSDL_CreateMutex(void);

/* WARNING:  This may not work for systems with 64-bit pid_t */
Uint32 HSDL_ThreadID(void)
{
	return((Uint32)((size_t)pthread_self()));
}

/* Create a mutex */
HSDL_mutex *
HSDL_CreateMutex(void)
{
    HSDL_mutex *mutex;

    /* Allocate mutex memory */
    mutex = (HSDL_mutex *) HSDL_malloc(sizeof(*mutex));
    if (mutex) {
        /* Create the mutex semaphore, with initial value 1 */
        mutex->sem = HSDL_CreateSemaphore(1);
        mutex->recursive = 0;
        mutex->owner = 0;
        if (!mutex->sem) {
            free(mutex);
            mutex = NULL;
        }
    } else {
        //HSDL_OutOfMemory();
    }
    return mutex;
}

/* Free the mutex */
void
HSDL_DestroyMutex(HSDL_mutex * mutex)
{
    if (mutex) {
        if (mutex->sem) {
            HSDL_DestroySemaphore(mutex->sem);
        }
        free(mutex);
    }
}


/* Lock the semaphore */
int
HSDL_mutexP(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    HSDL_threadID this_thread;

    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    this_thread = HSDL_ThreadID();
    if (mutex->owner == this_thread) {
        ++mutex->recursive;
    } else {
        /* The order of operations is important.
           We set the locking thread id after we obtain the lock
           so unlocks from other threads will fail.
         */
        HSDL_SemWait(mutex->sem);
        mutex->owner = this_thread;
        mutex->recursive = 0;
    }

    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

/* Unlock the mutex */
int
HSDL_mutexV(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    /* If we don't own the mutex, we can't unlock it */
    if (HSDL_ThreadID() != mutex->owner) {
        //HSDL_SetError("mutex not owned by this thread");
        return -1;
    }

    if (mutex->recursive) {
        --mutex->recursive;
    } else {
        /* The order of operations is important.
           First reset the owner so another thread doesn't lock
           the mutex and set the ownership before we reset it,
           then release the lock semaphore.
         */
        mutex->owner = 0;
        HSDL_SemPost(mutex->sem);
    }
    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

typedef struct HSDL_Thread HSDL_Thread;
//typedef unsigned long HSDL_threadID;

typedef enum {
    HSDL_THREAD_PRIORITY_LOW,
    HSDL_THREAD_PRIORITY_NORMAL,
    HSDL_THREAD_PRIORITY_HIGH
} HSDL_ThreadPriority;

typedef int (SDLCALL * HSDL_ThreadFunction) (void *data);

//typedef sys_ppu_thread_t SYS_ThreadHandle;
typedef pthread_t SYS_ThreadHandle;
/* This is the system-independent thread info structure */
struct HSDL_Thread
{
    HSDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    HSDL_error errbuf;
    void *data;
};


/* Arguments and callback to setup and run the user thread function */
typedef struct {
        int (SDLCALL *func)(void *);
        void *data;
        HSDL_Thread *info;
        HSDL_sem *wait;
} thread_args;

void HSDL_SYS_SetupThread(void)
{
        int i;

#ifdef PTHREAD_CANCEL_ASYNCHRONOUS
        /* Allow ourselves to be asynchronously cancelled */
        { int oldstate;
                pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldstate);
        }
#endif
}

void
HSDL_RunThread(void *data)
{
    thread_args *args;
    int (SDLCALL * userfunc) (void *);
    void *userdata;
    int *statusloc;

    /* Perform any system-dependent setup
       - this function cannot fail, and cannot use HSDL_SetError()
     */
    HSDL_SYS_SetupThread();

    /* Get the thread id */
    args = (thread_args *) data;
    args->info->threadid = HSDL_ThreadID();

    /* Figure out what function to run */
    userfunc = args->func;
    userdata = args->data;
    statusloc = &args->info->status;

    /* Wake up the parent thread */
    HSDL_SemPost(args->wait);

    /* Run the function */
    *statusloc = userfunc(userdata);
}

static void *RunThread(void *data)
{
        HSDL_RunThread(data);
        pthread_exit((void*)0);
        return((void *)0);              /* Prevent compiler warning */
}

int HSDL_SYS_CreateThread(HSDL_Thread *thread, void *args)
{
        pthread_attr_t type;

        /* Set the thread attributes */
        if ( pthread_attr_init(&type) != 0 ) {
                HSDL_SetError("Couldn't initialize pthread attributes");
                return(-1);
        }
        pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);

        /* Create the thread and go! */
        if ( pthread_create(&thread->handle, &type, RunThread, args) != 0 ) {
                HSDL_SetError("Not enough resources to create thread");
                return(-1);
        }

#ifdef __RISCOS__
        if (riscos_using_threads == 0) {
                riscos_using_threads = 1;
                riscos_main_thread = HSDL_ThreadID();
        }
#endif

        return(0);
}




void HSDL_SYS_WaitThread(HSDL_Thread *thread)
{
        pthread_join(thread->handle, 0);
}

void HSDL_SYS_KillThread(HSDL_Thread *thread)
{

}

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/
static int HSDL_maxthreads = 0;
static int HSDL_numthreads = 0;
static HSDL_Thread **HSDL_Threads = NULL;
static HSDL_mutex *thread_lock = NULL;

static int
HSDL_ThreadsInit(void)
{
    int retval;

    retval = 0;
    thread_lock = HSDL_CreateMutex();
    if (thread_lock == NULL) {
        retval = -1;
    }
    return (retval);
}
/* Routines for manipulating the thread list */
static void
HSDL_AddThread(HSDL_Thread * thread)
{
    /* WARNING:
       If the very first threads are created simultaneously, then
       there could be a race condition causing memory corruption.
       In practice, this isn't a problem because by definition there
       is only one thread running the first time this is called.
     */
    if (!thread_lock) {
        if (HSDL_ThreadsInit() < 0) {
            return;
        }
    }
    HSDL_mutexP(thread_lock);

    /* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
    printf("Adding thread (%d already - %d max)\n",
           HSDL_numthreads, HSDL_maxthreads);
#endif
    if (HSDL_numthreads == HSDL_maxthreads) {
        HSDL_Thread **threads;
        threads = (HSDL_Thread **) realloc(HSDL_Threads,
                                              (HSDL_maxthreads +
                                               ARRAY_CHUNKSIZE) *
                                              (sizeof *threads));
        if (threads == NULL) {
            //HSDL_OutOfMemory();
            goto done;
        }
        HSDL_maxthreads += ARRAY_CHUNKSIZE;
        HSDL_Threads = threads;
    }
    HSDL_Threads[HSDL_numthreads++] = thread;
  done:
    HSDL_mutexV(thread_lock);
}

static void
HSDL_DelThread(HSDL_Thread * thread)
{
    int i;

    if (!thread_lock) {
        return;
    }
    HSDL_mutexP(thread_lock);
    for (i = 0; i < HSDL_numthreads; ++i) {
        if (thread == HSDL_Threads[i]) {
            break;
        }
    }
    if (i < HSDL_numthreads) {
        if (--HSDL_numthreads > 0) {
            while (i < HSDL_numthreads) {
                HSDL_Threads[i] = HSDL_Threads[i + 1];
                ++i;
            }
        } else {
            HSDL_maxthreads = 0;
            /*HSDL_*/free(HSDL_Threads);
            HSDL_Threads = NULL;
        }
#ifdef DEBUG_THREADS
        printf("Deleting thread (%d left - %d max)\n",
               HSDL_numthreads, HSDL_maxthreads);
#endif
    }
    HSDL_mutexV(thread_lock);

}

#define DECLSPEC

#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
#undef HSDL_CreateThread
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data,
                 pfnHSDL_CurrentBeginThread pfnBeginThread,
                 pfnHSDL_CurrentEndThread pfnEndThread)
#else
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data)
#endif
{
    HSDL_Thread *thread;
    thread_args *args;
    int ret;

    /* Allocate memory for the thread info structure */
    thread = (HSDL_Thread *) malloc(sizeof(*thread));
    if (thread == NULL) {
        //HSDL_OutOfMemory();
        return (NULL);
    }
    memset(thread, 0, (sizeof *thread));
    thread->status = -1;

    /* Set up the arguments for the thread */
    args = (thread_args *) HSDL_malloc(sizeof(*args));
    if (args == NULL) {
        //HSDL_OutOfMemory();
        free(thread);
        return (NULL);
    }
    args->func = fn;
    args->data = data;
    args->info = thread;
    args->wait = HSDL_CreateSemaphore(0);
    if (args->wait == NULL) {
        free(thread);
        free(args);
        return (NULL);
    }

    /* Add the thread to the list of available threads */
    HSDL_AddThread(thread);

    /* Create the thread and go! */
#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
    ret = HSDL_SYS_CreateThread(thread, args, pfnBeginThread, pfnEndThread);
#else
    ret = HSDL_SYS_CreateThread(thread, args);
#endif
    if (ret >= 0) {
        /* Wait for the thread function to use arguments */
        HSDL_SemWait(args->wait);
    } else {
        /* Oops, failed.  Gotta free everything */
        HSDL_DelThread(thread);
        free(thread);
        thread = NULL;
    }
    HSDL_DestroySemaphore(args->wait);
    free(args);

    /* Everything is running now */
    return (thread);
}

#elif defined(GEKKO)
#include <sys/errno.h> 
#include <unistd.h>
#include <signal.h>

#include <ogc/semaphore.h>
//WII
#define LWP_PRIO_NORMAL 64

#include <ogc/lwp.h>
#include <ogc/mutex.h>
#include <ogc/cond.h>

typedef lwp_t pthread_t;
typedef void* pthread_attr_t;

typedef mutex_t pthread_mutex_t;
typedef void* pthread_mutexattr_t;

typedef cond_t pthread_cond_t;
typedef void* pthread_condattr_t;

static inline int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg) {
        return LWP_CreateThread(thread, start_routine, arg, NULL, 0, LWP_PRIO_NORMAL);
}
static inline int pthread_join(pthread_t thread, void **value_ptr) {
        return LWP_JoinThread(thread, NULL);
}

static inline int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
        return LWP_MutexInit(mutex, false);
}
static inline int pthread_mutex_destroy(pthread_mutex_t *mutex) {
        return LWP_MutexDestroy(*mutex);
}
static inline int pthread_mutex_lock(pthread_mutex_t *mutex) {
        return LWP_MutexLock(*mutex);
}
static inline int pthread_mutex_trylock(pthread_mutex_t *mutex) {
        return LWP_MutexTryLock(*mutex);
}
static inline int pthread_mutex_unlock(pthread_mutex_t *mutex) {
        return LWP_MutexUnlock(*mutex);
}

static inline int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr) {
        return LWP_CondInit(cond);
}
static inline int pthread_cond_destroy(pthread_cond_t *cond) {
        return LWP_CondDestroy(*cond);
}
static inline int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
        return LWP_CondWait(*cond, *mutex);
}
static inline int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime) {
        return LWP_CondTimedWait(*cond, *mutex, abstime);
}
static inline int pthread_cond_signal(pthread_cond_t *cond) {
        return LWP_CondSignal(*cond);
}
static inline int pthread_cond_broadcast(pthread_cond_t *cond) {
        return LWP_CondBroadcast(*cond);
}

#define sem_wait LWP_SemWait
#define sem_init LWP_SemInit
#define sem_post LWP_SemPost
#define sem_destroy LWP_SemDestroy

//END WII

typedef u32 sem_t;

struct HSDL_semaphore
{
    sem_t sem;
};

struct HSDL_semaphore;
typedef struct HSDL_semaphore HSDL_sem;

/* Create a counting semaphore */
HSDL_sem *
HSDL_CreateSemaphore(Uint32 initial_value)
{
	HSDL_sem *sem = (HSDL_sem *) HSDL_malloc(sizeof(HSDL_sem));
	if ( sem ) {
		if ( sem_init(&sem->sem, 0, initial_value) < 0 ) {
			HSDL_SetError("sem_init() failed");
			HSDL_free(sem);
			sem = NULL;
		}
	} else {
		//HSDL_OutOfMemory();
	}
	return sem;
}

void HSDL_DestroySemaphore(HSDL_sem *sem)
{
	if ( sem ) {
		sem_destroy(sem->sem);
		HSDL_free(sem);
	}
}

int HSDL_SemTryWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}
	retval = HSDL_MUTEX_TIMEDOUT;
	if ( sem_trywait(&sem->sem) == 0 ) {
		retval = 0;
	}
	return retval;
}

int HSDL_SemWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	while ( ((retval = sem_wait(sem->sem)) == -1) && (errno == EINTR) ) {}
	if ( retval < 0 ) {
		HSDL_SetError("sem_wait() failed");
	}
	return retval;
}

int HSDL_SemWaitTimeout(HSDL_sem *sem, Uint32 timeout)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	/* Try the easy cases first */
	if ( timeout == 0 ) {
		return HSDL_SemTryWait(sem);
	}
	if ( timeout == HSDL_MUTEX_MAXWAIT ) {
		return HSDL_SemWait(sem);
	}

	/* Ack!  We have to busy wait... */
	/* FIXME: Use sem_timedwait()? */
	timeout += HSDL_GetTicks();
	do {
		retval = HSDL_SemTryWait(sem);
		if ( retval == 0 ) {
			break;
		}
		HSDL_Delay(1);
	} while ( HSDL_GetTicks() < timeout );

	return retval;
}


Uint32 HSDL_SemValue(HSDL_sem *sem)
{
	int ret = 0;
	if ( sem ) {
		sem_getvalue(&sem->sem, &ret);
		if ( ret < 0 ) {
			ret = 0;
		}
	}
	return (Uint32)ret;
}

int HSDL_SemPost(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	retval = sem_post(sem->sem);
	if ( retval < 0 ) {
		HSDL_SetError("sem_post() failed");
	}
	return retval;
}

typedef struct HSDL_Thread HSDL_Thread;
typedef unsigned long HSDL_threadID;

/* The SDL thread priority
 *
 * Note: On many systems you require special privileges to set high priority.
 */
typedef enum {
    HSDL_THREAD_PRIORITY_LOW,
    HSDL_THREAD_PRIORITY_NORMAL,
    HSDL_THREAD_PRIORITY_HIGH
} HSDL_ThreadPriority;

typedef int (SDLCALL * HSDL_ThreadFunction) (void *data);
//typedef sys_ppu_thread_t SYS_ThreadHandle;
typedef pthread_t SYS_ThreadHandle;

/* This is the system-independent thread info structure */
struct HSDL_Thread
{
    HSDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    HSDL_error errbuf;
    void *data;
};

struct HSDL_mutex
{
    int recursive;
    HSDL_threadID owner;
    HSDL_sem *sem;
};

typedef struct HSDL_mutex HSDL_mutex;
extern HSDL_mutex *HSDL_CreateMutex(void);




/* Create a mutex */
HSDL_mutex *
HSDL_CreateMutex(void)
{
    HSDL_mutex *mutex;

    /* Allocate mutex memory */
    mutex = (HSDL_mutex *) HSDL_malloc(sizeof(*mutex));
    if (mutex) {
        /* Create the mutex semaphore, with initial value 1 */
        mutex->sem = HSDL_CreateSemaphore(1);
        mutex->recursive = 0;
        mutex->owner = 0;
        if (!mutex->sem) {
            free(mutex);
            mutex = NULL;
        }
    } else {
        //HSDL_OutOfMemory();
    }
    return mutex;
}

/* Free the mutex */
void
HSDL_DestroyMutex(HSDL_mutex * mutex)
{
    if (mutex) {
        if (mutex->sem) {
            HSDL_DestroySemaphore(mutex->sem);
        }
        free(mutex);
    }
}

/* WARNING:  This may not work for systems with 64-bit pid_t */
Uint32 HSDL_ThreadID(void)
{
	//return((Uint32)((size_t)pthread_self()));
		return (Uint32) LWP_GetSelf();
}


/* Lock the semaphore */
int
HSDL_mutexP(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    HSDL_threadID this_thread;

    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    this_thread = HSDL_ThreadID();
    if (mutex->owner == this_thread) {
        ++mutex->recursive;
    } else {
        /* The order of operations is important.
           We set the locking thread id after we obtain the lock
           so unlocks from other threads will fail.
         */
        HSDL_SemWait(mutex->sem);
        mutex->owner = this_thread;
        mutex->recursive = 0;
    }

    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

/* Unlock the mutex */
int
HSDL_mutexV(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    /* If we don't own the mutex, we can't unlock it */
    if (HSDL_ThreadID() != mutex->owner) {
        //HSDL_SetError("mutex not owned by this thread");
        return -1;
    }

    if (mutex->recursive) {
        --mutex->recursive;
    } else {
        /* The order of operations is important.
           First reset the owner so another thread doesn't lock
           the mutex and set the ownership before we reset it,
           then release the lock semaphore.
         */
        mutex->owner = 0;
        HSDL_SemPost(mutex->sem);
    }
    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/
static int HSDL_maxthreads = 0;
static int HSDL_numthreads = 0;
static HSDL_Thread **HSDL_Threads = NULL;
static HSDL_mutex *thread_lock = NULL;

static int
HSDL_ThreadsInit(void)
{
    int retval;

    retval = 0;
    thread_lock = HSDL_CreateMutex();
    if (thread_lock == NULL) {
        retval = -1;
    }
    return (retval);
}

/* Routines for manipulating the thread list */
static void
HSDL_AddThread(HSDL_Thread * thread)
{
    /* WARNING:
       If the very first threads are created simultaneously, then
       there could be a race condition causing memory corruption.
       In practice, this isn't a problem because by definition there
       is only one thread running the first time this is called.
     */
    if (!thread_lock) {
        if (HSDL_ThreadsInit() < 0) {
            return;
        }
    }
    HSDL_mutexP(thread_lock);

    /* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
    printf("Adding thread (%d already - %d max)\n",
           HSDL_numthreads, HSDL_maxthreads);
#endif
    if (HSDL_numthreads == HSDL_maxthreads) {
        HSDL_Thread **threads;
        threads = (HSDL_Thread **) realloc(HSDL_Threads,
                                              (HSDL_maxthreads +
                                               ARRAY_CHUNKSIZE) *
                                              (sizeof *threads));
        if (threads == NULL) {
            //HSDL_OutOfMemory();
            goto done;
        }
        HSDL_maxthreads += ARRAY_CHUNKSIZE;
        HSDL_Threads = threads;
    }
    HSDL_Threads[HSDL_numthreads++] = thread;
  done:
    HSDL_mutexV(thread_lock);
}

static void
HSDL_DelThread(HSDL_Thread * thread)
{
    int i;

    if (!thread_lock) {
        return;
    }
    HSDL_mutexP(thread_lock);
    for (i = 0; i < HSDL_numthreads; ++i) {
        if (thread == HSDL_Threads[i]) {
            break;
        }
    }
    if (i < HSDL_numthreads) {
        if (--HSDL_numthreads > 0) {
            while (i < HSDL_numthreads) {
                HSDL_Threads[i] = HSDL_Threads[i + 1];
                ++i;
            }
        } else {
            HSDL_maxthreads = 0;
            /*HSDL_*/free(HSDL_Threads);
            HSDL_Threads = NULL;
        }
#ifdef DEBUG_THREADS
        printf("Deleting thread (%d left - %d max)\n",
               HSDL_numthreads, HSDL_maxthreads);
#endif
    }
    HSDL_mutexV(thread_lock);

}

/* The default (non-thread-safe) global error variable */
static HSDL_error HSDL_global_error;

/* Routine to get the thread-specific error variable */
HSDL_error *
HSDL_GetErrBuf(void)
{
    HSDL_error *errbuf;

    errbuf = &HSDL_global_error;
    if (HSDL_Threads) {
        int i;
        HSDL_threadID this_thread;

        this_thread = HSDL_ThreadID();
        HSDL_mutexP(thread_lock);
        for (i = 0; i < HSDL_numthreads; ++i) {
            if (this_thread == HSDL_Threads[i]->threadid) {
                errbuf = &HSDL_Threads[i]->errbuf;
                break;
            }
        }
        HSDL_mutexV(thread_lock);
    }
    return (errbuf);
}

static int sig_list[] = {
    SIGHUP, SIGINT, SIGQUIT, SIGPIPE, SIGALRM, SIGTERM, SIGWINCH, 0
};

void
HSDL_MaskSignals(sigset_t * omask)
{
    sigset_t mask;
    int i;

    sigemptyset(&mask);
    for (i = 0; sig_list[i]; ++i) {
        sigaddset(&mask, sig_list[i]);
    }
}

void
HSDL_UnmaskSignals(sigset_t * omask)
{

}

/* Arguments and callback to setup and run the user thread function */
typedef struct
{
    int (SDLCALL * func) (void *);
    void *data;
    HSDL_Thread *info;
    HSDL_sem *wait;
} thread_args;

void
HSDL_SYS_SetupThread(void)
{
    /* Mask asynchronous signals for this thread */
    HSDL_MaskSignals(NULL);
}

void
HSDL_RunThread(void *data)
{
    thread_args *args;
    int (SDLCALL * userfunc) (void *);
    void *userdata;
    int *statusloc;

    /* Perform any system-dependent setup
       - this function cannot fail, and cannot use HSDL_SetError()
     */
    HSDL_SYS_SetupThread();

    /* Get the thread id */
    args = (thread_args *) data;
    args->info->threadid = HSDL_ThreadID();

    /* Figure out what function to run */
    userfunc = args->func;
    userdata = args->data;
    statusloc = &args->info->status;

    /* Wake up the parent thread */
    HSDL_SemPost(args->wait);

    /* Run the function */
    *statusloc = userfunc(userdata);
}

static void *
RunThread(void *arg)
{
    HSDL_RunThread(arg);
	return((void *)0);		/* Prevent compiler warning */
}

int HSDL_SYS_CreateThread(HSDL_Thread *thread, void *args)
{
	pthread_attr_t type;

	LWP_CreateThread(&thread->handle, RunThread, args, 0, 0, 80);

	return(0);
}
void HSDL_SYS_WaitThread(HSDL_Thread *thread)
{
	pthread_join(thread->handle, 0);
}

#define DECLSPEC

#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
#undef HSDL_CreateThread
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data,
                 pfnHSDL_CurrentBeginThread pfnBeginThread,
                 pfnHSDL_CurrentEndThread pfnEndThread)
#else
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data)
#endif
{
    HSDL_Thread *thread;
    thread_args *args;
    int ret;

    /* Allocate memory for the thread info structure */
    thread = (HSDL_Thread *) malloc(sizeof(*thread));
    if (thread == NULL) {
        //HSDL_OutOfMemory();
        return (NULL);
    }
    memset(thread, 0, (sizeof *thread));
    thread->status = -1;

    /* Set up the arguments for the thread */
    args = (thread_args *) HSDL_malloc(sizeof(*args));
    if (args == NULL) {
        //HSDL_OutOfMemory();
        free(thread);
        return (NULL);
    }
    args->func = fn;
    args->data = data;
    args->info = thread;
    args->wait = HSDL_CreateSemaphore(0);
    if (args->wait == NULL) {
        free(thread);
        free(args);
        return (NULL);
    }

    /* Add the thread to the list of available threads */
    HSDL_AddThread(thread);

    /* Create the thread and go! */
#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
    ret = HSDL_SYS_CreateThread(thread, args, pfnBeginThread, pfnEndThread);
#else
    ret = HSDL_SYS_CreateThread(thread, args);
#endif
    if (ret >= 0) {
        /* Wait for the thread function to use arguments */
        HSDL_SemWait(args->wait);
    } else {
        /* Oops, failed.  Gotta free everything */
        HSDL_DelThread(thread);
        free(thread);
        thread = NULL;
    }
    HSDL_DestroySemaphore(args->wait);
    free(args);

    /* Everything is running now */
    return (thread);
}

HSDL_threadID
HSDL_GetThreadID(HSDL_Thread * thread)
{
    HSDL_threadID id;

    if (thread) {
        id = thread->threadid;
    } else {
        id = HSDL_ThreadID();
    }
    return id;
}

int
HSDL_SetThreadPriority(HSDL_ThreadPriority priority)
{
    return 0;
}

void
HSDL_WaitThread(HSDL_Thread * thread, int *status)
{
    if (thread) {
        HSDL_SYS_WaitThread(thread);
        if (status) {
            *status = thread->status;
        }
        HSDL_DelThread(thread);
        free(thread);
    }
}

#elif defined WIN32PORT

#include <unistd.h>
#include <windows.h>

struct HSDL_semaphore {
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
	SYNCHHANDLE id;
#else
	HANDLE id;
#endif
	volatile LONG count;
};

struct HSDL_semaphore;
typedef struct HSDL_semaphore HSDL_sem;

/* Create a semaphore */
HSDL_sem *HSDL_CreateSemaphore(Uint32 initial_value)
{
	HSDL_sem *sem;

	/* Allocate sem memory */
	sem = (HSDL_sem *)HSDL_malloc(sizeof(*sem));
	if ( sem ) {
		/* Create the semaphore, with max value 32K */
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
		sem->id = CreateSemaphoreCE(NULL, initial_value, 32*1024, NULL);
#else
		sem->id = CreateSemaphore(NULL, initial_value, 32*1024, NULL);
#endif
		sem->count = (LONG) initial_value;
		if ( ! sem->id ) {
			HSDL_SetError("Couldn't create semaphore");
			HSDL_free(sem);
			sem = NULL;
		}
	} else {
		//HSDL_OutOfMemory();
	}
	return(sem);
}


/* Free the semaphore */
void HSDL_DestroySemaphore(HSDL_sem *sem)
{
	if ( sem ) {
		if ( sem->id ) {
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
			CloseSynchHandle(sem->id);
#else
			CloseHandle(sem->id);
#endif
			sem->id = 0;
		}
		HSDL_free(sem);
	}
}

int HSDL_SemWaitTimeout(HSDL_sem *sem, Uint32 timeout)
{
	int retval;
	DWORD dwMilliseconds;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL sem");
		return -1;
	}

	if ( timeout == HSDL_MUTEX_MAXWAIT ) {
		dwMilliseconds = INFINITE;
	} else {
		dwMilliseconds = (DWORD)timeout;
	}
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
	switch (WaitForSemaphoreCE(sem->id, dwMilliseconds)) {
#else
	switch (WaitForSingleObject(sem->id, dwMilliseconds)) {
#endif
	    case WAIT_OBJECT_0:
		InterlockedDecrement(&sem->count);
		retval = 0;
		break;
	    case WAIT_TIMEOUT:
		retval = HSDL_MUTEX_TIMEDOUT;
		break;
	    default:
		HSDL_SetError("WaitForSingleObject() failed");
		retval = -1;
		break;
	}
	return retval;
}

int HSDL_SemTryWait(HSDL_sem *sem)
{
	return HSDL_SemWaitTimeout(sem, 0);
}

int HSDL_SemWait(HSDL_sem *sem)
{
	return HSDL_SemWaitTimeout(sem, HSDL_MUTEX_MAXWAIT);
}

/* Returns the current count of the semaphore */
Uint32 HSDL_SemValue(HSDL_sem *sem)
{
	if ( ! sem ) {
		HSDL_SetError("Passed a NULL sem");
		return 0;
	}
	return (Uint32) sem->count;
}

int HSDL_SemPost(HSDL_sem *sem)
{
	if ( ! sem ) {
		HSDL_SetError("Passed a NULL sem");
		return -1;
	}
	/* Increase the counter in the first place, because
	 * after a successful release the semaphore may
	 * immediately get destroyed by another thread which
	 * is waiting for this semaphore.
	 */
	InterlockedIncrement(&sem->count);
#if defined(_WIN32_WCE) && (_WIN32_WCE < 300)
	if ( ReleaseSemaphoreCE(sem->id, 1, NULL) == FALSE ) {
#else
	if ( ReleaseSemaphore(sem->id, 1, NULL) == FALSE ) {
#endif
		InterlockedDecrement(&sem->count);	/* restore */
		HSDL_SetError("ReleaseSemaphore() failed");
		return -1;
	}
	return 0;
}
typedef struct HSDL_Thread HSDL_Thread;
typedef unsigned long HSDL_threadID;

/* The SDL thread priority
 *
 * Note: On many systems you require special privileges to set high priority.
 */
typedef enum {
    HSDL_THREAD_PRIORITY_LOW,
    HSDL_THREAD_PRIORITY_NORMAL,
    HSDL_THREAD_PRIORITY_HIGH
} HSDL_ThreadPriority;

typedef int (SDLCALL * HSDL_ThreadFunction) (void *data);
typedef HANDLE SYS_ThreadHandle;

/* This is the system-independent thread info structure */
struct HSDL_Thread
{
    HSDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    HSDL_error errbuf;
    void *data;
};

struct HSDL_mutex {
	HANDLE id;
};

typedef struct HSDL_mutex HSDL_mutex;
extern HSDL_mutex *HSDL_CreateMutex(void);

/* Create a mutex */
HSDL_mutex *HSDL_CreateMutex(void)
{
	HSDL_mutex *mutex;

	/* Allocate mutex memory */
	mutex = (HSDL_mutex *)HSDL_malloc(sizeof(*mutex));
	if ( mutex ) {
		/* Create the mutex, with initial value signaled */
		mutex->id = CreateMutex(NULL, FALSE, NULL);
		if ( ! mutex->id ) {
			HSDL_SetError("Couldn't create mutex");
			HSDL_free(mutex);
			mutex = NULL;
		}
	} else {
		//HSDL_OutOfMemory();
	}
	return(mutex);
}

/* Free the mutex */
void HSDL_DestroyMutex(HSDL_mutex *mutex)
{
	if ( mutex ) {
		if ( mutex->id ) {
			CloseHandle(mutex->id);
			mutex->id = 0;
		}
		HSDL_free(mutex);
	}
}

/* Lock the mutex */
int HSDL_mutexP(HSDL_mutex *mutex)
{
	if ( mutex == NULL ) {
		HSDL_SetError("Passed a NULL mutex");
		return -1;
	}
	if ( WaitForSingleObject(mutex->id, INFINITE) == WAIT_FAILED ) {
		HSDL_SetError("Couldn't wait on mutex");
		return -1;
	}
	return(0);
}

/* Unlock the mutex */
int HSDL_mutexV(HSDL_mutex *mutex)
{
	if ( mutex == NULL ) {
		HSDL_SetError("Passed a NULL mutex");
		return -1;
	}
	if ( ReleaseMutex(mutex->id) == FALSE ) {
		HSDL_SetError("Couldn't release mutex");
		return -1;
	}
	return(0);
}

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/
static int HSDL_maxthreads = 0;
static int HSDL_numthreads = 0;
static HSDL_Thread **HSDL_Threads = NULL;
static HSDL_mutex *thread_lock = NULL;

static int
HSDL_ThreadsInit(void)
{
    int retval;

    retval = 0;
    thread_lock = HSDL_CreateMutex();
    if (thread_lock == NULL) {
        retval = -1;
    }
    return (retval);
}

/* Routines for manipulating the thread list */
static void
HSDL_AddThread(HSDL_Thread * thread)
{
    /* WARNING:
       If the very first threads are created simultaneously, then
       there could be a race condition causing memory corruption.
       In practice, this isn't a problem because by definition there
       is only one thread running the first time this is called.
     */
    if (!thread_lock) {
        if (HSDL_ThreadsInit() < 0) {
            return;
        }
    }
    HSDL_mutexP(thread_lock);

    /* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
    printf("Adding thread (%d already - %d max)\n",
           HSDL_numthreads, HSDL_maxthreads);
#endif
    if (HSDL_numthreads == HSDL_maxthreads) {
        HSDL_Thread **threads;
        threads = (HSDL_Thread **) realloc(HSDL_Threads,
                                              (HSDL_maxthreads +
                                               ARRAY_CHUNKSIZE) *
                                              (sizeof *threads));
        if (threads == NULL) {
            //HSDL_OutOfMemory();
            goto done;
        }
        HSDL_maxthreads += ARRAY_CHUNKSIZE;
        HSDL_Threads = threads;
    }
    HSDL_Threads[HSDL_numthreads++] = thread;
  done:
    HSDL_mutexV(thread_lock);
}

static void
HSDL_DelThread(HSDL_Thread * thread)
{
    int i;

    if (!thread_lock) {
        return;
    }
    HSDL_mutexP(thread_lock);
    for (i = 0; i < HSDL_numthreads; ++i) {
        if (thread == HSDL_Threads[i]) {
            break;
        }
    }
    if (i < HSDL_numthreads) {
        if (--HSDL_numthreads > 0) {
            while (i < HSDL_numthreads) {
                HSDL_Threads[i] = HSDL_Threads[i + 1];
                ++i;
            }
        } else {
            HSDL_maxthreads = 0;
            free(HSDL_Threads);
            HSDL_Threads = NULL;
        }
#ifdef DEBUG_THREADS
        printf("Deleting thread (%d left - %d max)\n",
               HSDL_numthreads, HSDL_maxthreads);
#endif
    }
    HSDL_mutexV(thread_lock);

}
Uint32 HSDL_ThreadID(void)
{
	return((Uint32)GetCurrentThreadId());
}

/* The default (non-thread-safe) global error variable */
static HSDL_error HSDL_global_error;

/* Routine to get the thread-specific error variable */
HSDL_error *
HSDL_GetErrBuf(void)
{
    HSDL_error *errbuf;

    errbuf = &HSDL_global_error;
    if (HSDL_Threads) {
        int i;
        HSDL_threadID this_thread;

        this_thread = HSDL_ThreadID();
        HSDL_mutexP(thread_lock);
        for (i = 0; i < HSDL_numthreads; ++i) {
            if (this_thread == HSDL_Threads[i]->threadid) {
                errbuf = &HSDL_Threads[i]->errbuf;
                break;
            }
        }
        HSDL_mutexV(thread_lock);
    }
    return (errbuf);
}


/* Arguments and callback to setup and run the user thread function */
typedef struct
{
    int (SDLCALL * func) (void *);
    void *data;
    HSDL_Thread *info;
    HSDL_sem *wait;
} thread_args;


void HSDL_SYS_SetupThread(void)
{
	return;
}

void
HSDL_RunThread(void *data)
{
    thread_args *args;
    int (SDLCALL * userfunc) (void *);
    void *userdata;
    int *statusloc;

    /* Perform any system-dependent setup
       - this function cannot fail, and cannot use HSDL_SetError()
     */
    HSDL_SYS_SetupThread();

    /* Get the thread id */
    args = (thread_args *) data;
    args->info->threadid = HSDL_ThreadID();

    /* Figure out what function to run */
    userfunc = args->func;
    userdata = args->data;
    statusloc = &args->info->status;

    /* Wake up the parent thread */
    HSDL_SemPost(args->wait);

    /* Run the function */
    *statusloc = userfunc(userdata);
}
typedef unsigned long (__cdecl *pfnHSDL_CurrentBeginThread) (void *, unsigned,
        unsigned (__stdcall *func)(void *), void *arg, 
        unsigned, unsigned *threadID);
typedef void (__cdecl *pfnHSDL_CurrentEndThread)(unsigned code);


typedef struct ThreadStartParms
{
  void *args;
  pfnHSDL_CurrentEndThread pfnCurrentEndThread;
} tThreadStartParms, *pThreadStartParms;



static DWORD RunThread(void *data)
{
  pThreadStartParms pThreadParms = (pThreadStartParms)data;
  pfnHSDL_CurrentEndThread pfnCurrentEndThread = NULL;

  // Call the thread function!
  HSDL_RunThread(pThreadParms->args);

  // Get the current endthread we have to use!
  if (pThreadParms)
  {
    pfnCurrentEndThread = pThreadParms->pfnCurrentEndThread;
    HSDL_free(pThreadParms);
  }
  // Call endthread!
  if (pfnCurrentEndThread)
    (*pfnCurrentEndThread)(0);
  return(0);
}

static DWORD WINAPI RunThreadViaCreateThread(LPVOID data)
{
  return RunThread(data);
}

static unsigned __stdcall RunThreadViaBeginThreadEx(void *data)
{
  return (unsigned) RunThread(data);
}

int HSDL_SYS_CreateThread(HSDL_Thread *thread, void *args)
{
#ifdef _WIN32_WCE
	pfnHSDL_CurrentBeginThread pfnBeginThread = NULL;
	pfnHSDL_CurrentEndThread pfnEndThread = NULL;
#else
	pfnHSDL_CurrentBeginThread pfnBeginThread = _beginthreadex;
	pfnHSDL_CurrentEndThread pfnEndThread = _endthreadex;
#endif
	pThreadStartParms pThreadParms = (pThreadStartParms)HSDL_malloc(sizeof(tThreadStartParms));
	if (!pThreadParms) {
		//HSDL_OutOfMemory();
		return(-1);
	}

	// Save the function which we will have to call to clear the RTL of calling app!
	pThreadParms->pfnCurrentEndThread = pfnEndThread;
	// Also save the real parameters we have to pass to thread function
	pThreadParms->args = args;

	if (pfnBeginThread) {
		unsigned threadid = 0;
		thread->handle = (SYS_ThreadHandle)
				((size_t) pfnBeginThread(NULL, 0, RunThreadViaBeginThreadEx,
										 pThreadParms, 0, &threadid));
	} else {
		DWORD threadid = 0;
		thread->handle = CreateThread(NULL, 0, RunThreadViaCreateThread, pThreadParms, 0, &threadid);
	}
	if (thread->handle == NULL) {
		HSDL_SetError("Not enough resources to create thread");
		return(-1);
	}
	return(0);
}


void HSDL_SYS_WaitThread(HSDL_Thread *thread)
{
	WaitForSingleObject(thread->handle, INFINITE);
	CloseHandle(thread->handle);
}

#define DECLSPEC

#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
#undef HSDL_CreateThread
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data,
                 pfnHSDL_CurrentBeginThread pfnBeginThread,
                 pfnHSDL_CurrentEndThread pfnEndThread)
#else
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data)
#endif
{
    HSDL_Thread *thread;
    thread_args *args;
    int ret;

    /* Allocate memory for the thread info structure */
    thread = (HSDL_Thread *) /*HSDL_*/malloc(sizeof(*thread));
    if (thread == NULL) {
        //HSDL_OutOfMemory();
        return (NULL);
    }
    memset(thread, 0, (sizeof *thread));
    thread->status = -1;

    /* Set up the arguments for the thread */
    args = (thread_args *) HSDL_malloc(sizeof(*args));
    if (args == NULL) {
        //HSDL_OutOfMemory();
        free(thread);
        return (NULL);
    }
    args->func = fn;
    args->data = data;
    args->info = thread;
    args->wait = HSDL_CreateSemaphore(0);
    if (args->wait == NULL) {
        free(thread);
        free(args);
        return (NULL);
    }

    /* Add the thread to the list of available threads */
    HSDL_AddThread(thread);

    /* Create the thread and go! */
#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
    ret = HSDL_SYS_CreateThread(thread, args, pfnBeginThread, pfnEndThread);
#else
    ret = HSDL_SYS_CreateThread(thread, args);
#endif
    if (ret >= 0) {
        /* Wait for the thread function to use arguments */
        HSDL_SemWait(args->wait);
    } else {
        /* Oops, failed.  Gotta free everything */
        HSDL_DelThread(thread);
        free(thread);
        thread = NULL;
    }
    HSDL_DestroySemaphore(args->wait);
    free(args);

    /* Everything is running now */
    return (thread);
}

HSDL_threadID
HSDL_GetThreadID(HSDL_Thread * thread)
{
    HSDL_threadID id;

    if (thread) {
        id = thread->threadid;
    } else {
        id = HSDL_ThreadID();
    }
    return id;
}

int
HSDL_SetThreadPriority(HSDL_ThreadPriority priority)
{
    return 0;
}

void
HSDL_WaitThread(HSDL_Thread * thread, int *status)
{
    if (thread) {
        HSDL_SYS_WaitThread(thread);
        if (status) {
            *status = thread->status;
        }
        HSDL_DelThread(thread);
        free(thread);
    }
}

#else //pthread

#include <sys/errno.h> 
#include <unistd.h>
#include <signal.h>

#include <pthread.h>
#include <semaphore.h>

struct HSDL_semaphore
{
    sem_t sem;
};

struct HSDL_semaphore;
typedef struct HSDL_semaphore HSDL_sem;

/* Create a counting semaphore */
HSDL_sem *
HSDL_CreateSemaphore(Uint32 initial_value)
{
	HSDL_sem *sem = (HSDL_sem *) HSDL_malloc(sizeof(HSDL_sem));
	if ( sem ) {
		if ( sem_init(&sem->sem, 0, initial_value) < 0 ) {
			HSDL_SetError("sem_init() failed");
			HSDL_free(sem);
			sem = NULL;
		}
	} else {
		//HSDL_OutOfMemory();
	}
	return sem;
}

void HSDL_DestroySemaphore(HSDL_sem *sem)
{
	if ( sem ) {
		sem_destroy(&sem->sem);
		HSDL_free(sem);
	}
}

int HSDL_SemTryWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}
	retval = HSDL_MUTEX_TIMEDOUT;
	if ( sem_trywait(&sem->sem) == 0 ) {
		retval = 0;
	}
	return retval;
}

int HSDL_SemWait(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	while ( ((retval = sem_wait(&sem->sem)) == -1) && (errno == EINTR) ) {}
	if ( retval < 0 ) {
		HSDL_SetError("sem_wait() failed");
	}
	return retval;
}

int HSDL_SemWaitTimeout(HSDL_sem *sem, Uint32 timeout)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	/* Try the easy cases first */
	if ( timeout == 0 ) {
		return HSDL_SemTryWait(sem);
	}
	if ( timeout == HSDL_MUTEX_MAXWAIT ) {
		return HSDL_SemWait(sem);
	}

	/* Ack!  We have to busy wait... */
	/* FIXME: Use sem_timedwait()? */
	timeout += HSDL_GetTicks();
	do {
		retval = HSDL_SemTryWait(sem);
		if ( retval == 0 ) {
			break;
		}
		HSDL_Delay(1);
	} while ( HSDL_GetTicks() < timeout );

	return retval;
}


Uint32 HSDL_SemValue(HSDL_sem *sem)
{
	int ret = 0;
	if ( sem ) {
		sem_getvalue(&sem->sem, &ret);
		if ( ret < 0 ) {
			ret = 0;
		}
	}
	return (Uint32)ret;
}

int HSDL_SemPost(HSDL_sem *sem)
{
	int retval;

	if ( ! sem ) {
		HSDL_SetError("Passed a NULL semaphore");
		return -1;
	}

	retval = sem_post(&sem->sem);
	if ( retval < 0 ) {
		HSDL_SetError("sem_post() failed");
	}
	return retval;
}

typedef struct HSDL_Thread HSDL_Thread;
typedef unsigned long HSDL_threadID;

/* The SDL thread priority
 *
 * Note: On many systems you require special privileges to set high priority.
 */
typedef enum {
    HSDL_THREAD_PRIORITY_LOW,
    HSDL_THREAD_PRIORITY_NORMAL,
    HSDL_THREAD_PRIORITY_HIGH
} HSDL_ThreadPriority;

typedef int (SDLCALL * HSDL_ThreadFunction) (void *data);
//typedef sys_ppu_thread_t SYS_ThreadHandle;
typedef pthread_t SYS_ThreadHandle;

/* This is the system-independent thread info structure */
struct HSDL_Thread
{
    HSDL_threadID threadid;
    SYS_ThreadHandle handle;
    int status;
    HSDL_error errbuf;
    void *data;
};

struct HSDL_mutex
{
    int recursive;
    HSDL_threadID owner;
    HSDL_sem *sem;
};

typedef struct HSDL_mutex HSDL_mutex;
extern HSDL_mutex *HSDL_CreateMutex(void);


/* Create a mutex */
HSDL_mutex *
HSDL_CreateMutex(void)
{
    HSDL_mutex *mutex;

    /* Allocate mutex memory */
    mutex = (HSDL_mutex *) HSDL_malloc(sizeof(*mutex));
    if (mutex) {
        /* Create the mutex semaphore, with initial value 1 */
        mutex->sem = HSDL_CreateSemaphore(1);
        mutex->recursive = 0;
        mutex->owner = 0;
        if (!mutex->sem) {
            /*HSDL_*/free(mutex);
            mutex = NULL;
        }
    } else {
        //HSDL_OutOfMemory();
    }
    return mutex;
}

/* Free the mutex */
void
HSDL_DestroyMutex(HSDL_mutex * mutex)
{
    if (mutex) {
        if (mutex->sem) {
            HSDL_DestroySemaphore(mutex->sem);
        }
        free(mutex);
    }
}

/* WARNING:  This may not work for systems with 64-bit pid_t */
Uint32 HSDL_ThreadID(void)
{
	return((Uint32)((size_t)pthread_self()));
}


/* Lock the semaphore */
int
HSDL_mutexP(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    HSDL_threadID this_thread;

    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    this_thread = HSDL_ThreadID();
    if (mutex->owner == this_thread) {
        ++mutex->recursive;
    } else {
        /* The order of operations is important.
           We set the locking thread id after we obtain the lock
           so unlocks from other threads will fail.
         */
        HSDL_SemWait(mutex->sem);
        mutex->owner = this_thread;
        mutex->recursive = 0;
    }

    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

/* Unlock the mutex */
int
HSDL_mutexV(HSDL_mutex * mutex)
{
#if HSDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL) {
        //HSDL_SetError("Passed a NULL mutex");
        return -1;
    }

    /* If we don't own the mutex, we can't unlock it */
    if (HSDL_ThreadID() != mutex->owner) {
        //HSDL_SetError("mutex not owned by this thread");
        return -1;
    }

    if (mutex->recursive) {
        --mutex->recursive;
    } else {
        /* The order of operations is important.
           First reset the owner so another thread doesn't lock
           the mutex and set the ownership before we reset it,
           then release the lock semaphore.
         */
        mutex->owner = 0;
        HSDL_SemPost(mutex->sem);
    }
    return 0;
#endif /* HSDL_THREADS_DISABLED */
}

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/
static int HSDL_maxthreads = 0;
static int HSDL_numthreads = 0;
static HSDL_Thread **HSDL_Threads = NULL;
static HSDL_mutex *thread_lock = NULL;

static int
HSDL_ThreadsInit(void)
{
    int retval;

    retval = 0;
    thread_lock = HSDL_CreateMutex();
    if (thread_lock == NULL) {
        retval = -1;
    }
    return (retval);
}

/* Routines for manipulating the thread list */
static void
HSDL_AddThread(HSDL_Thread * thread)
{
    /* WARNING:
       If the very first threads are created simultaneously, then
       there could be a race condition causing memory corruption.
       In practice, this isn't a problem because by definition there
       is only one thread running the first time this is called.
     */
    if (!thread_lock) {
        if (HSDL_ThreadsInit() < 0) {
            return;
        }
    }
    HSDL_mutexP(thread_lock);

    /* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
    printf("Adding thread (%d already - %d max)\n",
           HSDL_numthreads, HSDL_maxthreads);
#endif
    if (HSDL_numthreads == HSDL_maxthreads) {
        HSDL_Thread **threads;
        threads = (HSDL_Thread **) realloc(HSDL_Threads,
                                              (HSDL_maxthreads +
                                               ARRAY_CHUNKSIZE) *
                                              (sizeof *threads));
        if (threads == NULL) {
            //HSDL_OutOfMemory();
            goto done;
        }
        HSDL_maxthreads += ARRAY_CHUNKSIZE;
        HSDL_Threads = threads;
    }
    HSDL_Threads[HSDL_numthreads++] = thread;
  done:
    HSDL_mutexV(thread_lock);
}

static void
HSDL_DelThread(HSDL_Thread * thread)
{
    int i;

    if (!thread_lock) {
        return;
    }
    HSDL_mutexP(thread_lock);
    for (i = 0; i < HSDL_numthreads; ++i) {
        if (thread == HSDL_Threads[i]) {
            break;
        }
    }
    if (i < HSDL_numthreads) {
        if (--HSDL_numthreads > 0) {
            while (i < HSDL_numthreads) {
                HSDL_Threads[i] = HSDL_Threads[i + 1];
                ++i;
            }
        } else {
            HSDL_maxthreads = 0;
            /*HSDL_*/free(HSDL_Threads);
            HSDL_Threads = NULL;
        }
#ifdef DEBUG_THREADS
        printf("Deleting thread (%d left - %d max)\n",
               HSDL_numthreads, HSDL_maxthreads);
#endif
    }
    HSDL_mutexV(thread_lock);

}

/* The default (non-thread-safe) global error variable */
static HSDL_error HSDL_global_error;

/* Routine to get the thread-specific error variable */
HSDL_error *
HSDL_GetErrBuf(void)
{
    HSDL_error *errbuf;

    errbuf = &HSDL_global_error;
    if (HSDL_Threads) {
        int i;
        HSDL_threadID this_thread;

        this_thread = HSDL_ThreadID();
        HSDL_mutexP(thread_lock);
        for (i = 0; i < HSDL_numthreads; ++i) {
            if (this_thread == HSDL_Threads[i]->threadid) {
                errbuf = &HSDL_Threads[i]->errbuf;
                break;
            }
        }
        HSDL_mutexV(thread_lock);
    }
    return (errbuf);
}

static int sig_list[] = {
    SIGHUP, SIGINT, SIGQUIT, SIGPIPE, SIGALRM, SIGTERM, SIGWINCH, 0
};

void
HSDL_MaskSignals(sigset_t * omask)
{
    sigset_t mask;
    int i;

    sigemptyset(&mask);
    for (i = 0; sig_list[i]; ++i) {
        sigaddset(&mask, sig_list[i]);
    }

}

void
HSDL_UnmaskSignals(sigset_t * omask)
{

}

/* Arguments and callback to setup and run the user thread function */
typedef struct
{
    int (SDLCALL * func) (void *);
    void *data;
    HSDL_Thread *info;
    HSDL_sem *wait;
} thread_args;

void
HSDL_SYS_SetupThread(void)
{
    /* Mask asynchronous signals for this thread */
    HSDL_MaskSignals(NULL);
}

void
HSDL_RunThread(void *data)
{
    thread_args *args;
    int (SDLCALL * userfunc) (void *);
    void *userdata;
    int *statusloc;

    /* Perform any system-dependent setup
       - this function cannot fail, and cannot use HSDL_SetError()
     */
    HSDL_SYS_SetupThread();

    /* Get the thread id */
    args = (thread_args *) data;
    args->info->threadid = HSDL_ThreadID();

    /* Figure out what function to run */
    userfunc = args->func;
    userdata = args->data;
    statusloc = &args->info->status;

    /* Wake up the parent thread */
    HSDL_SemPost(args->wait);

    /* Run the function */
    *statusloc = userfunc(userdata);
}

static void *
RunThread(void *arg)
{
    HSDL_RunThread(arg);
    pthread_exit((void*)0);
}

int HSDL_SYS_CreateThread(HSDL_Thread *thread, void *args)
{
	pthread_attr_t type;

	/* Set the thread attributes */
	if ( pthread_attr_init(&type) != 0 ) {
		HSDL_SetError("Couldn't initialize pthread attributes");
		return(-1);
	}
	pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);

	/* Create the thread and go! */
	if ( pthread_create(&thread->handle, &type, RunThread, args) != 0 ) {
		HSDL_SetError("Not enough resources to create thread");
		return(-1);
	}

#ifdef __RISCOS__
	if (riscos_using_threads == 0) {
		riscos_using_threads = 1;
		riscos_main_thread = HSDL_ThreadID();
	}
#endif

	return(0);
}
void HSDL_SYS_WaitThread(HSDL_Thread *thread)
{
	pthread_join(thread->handle, 0);
}

#define DECLSPEC

#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
#undef HSDL_CreateThread
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data,
                 pfnHSDL_CurrentBeginThread pfnBeginThread,
                 pfnHSDL_CurrentEndThread pfnEndThread)
#else
DECLSPEC HSDL_Thread *SDLCALL
HSDL_CreateThread(int (SDLCALL * fn) (void *), void *data)
#endif
{
    HSDL_Thread *thread;
    thread_args *args;
    int ret;

    /* Allocate memory for the thread info structure */
    thread = (HSDL_Thread *) /*HSDL_*/malloc(sizeof(*thread));
    if (thread == NULL) {
        //HSDL_OutOfMemory();
        return (NULL);
    }
    memset(thread, 0, (sizeof *thread));
    thread->status = -1;

    /* Set up the arguments for the thread */
    args = (thread_args *) HSDL_malloc(sizeof(*args));
    if (args == NULL) {       
        free(thread);
        return (NULL);
    }
    args->func = fn;
    args->data = data;
    args->info = thread;
    args->wait = HSDL_CreateSemaphore(0);
    if (args->wait == NULL) {
        free(thread);
        free(args);
        return (NULL);
    }

    /* Add the thread to the list of available threads */
    HSDL_AddThread(thread);

    /* Create the thread and go! */
#ifdef HSDL_PASSED_BEGINTHREAD_ENDTHREAD
    ret = HSDL_SYS_CreateThread(thread, args, pfnBeginThread, pfnEndThread);
#else
    ret = HSDL_SYS_CreateThread(thread, args);
#endif
    if (ret >= 0) {
        /* Wait for the thread function to use arguments */
        HSDL_SemWait(args->wait);
    } else {
        /* Oops, failed.  Gotta free everything */
        HSDL_DelThread(thread);
        free(thread);
        thread = NULL;
    }
    HSDL_DestroySemaphore(args->wait);
    free(args);

    /* Everything is running now */
    return (thread);
}

HSDL_threadID
HSDL_GetThreadID(HSDL_Thread * thread)
{
    HSDL_threadID id;

    if (thread) {
        id = thread->threadid;
    } else {
        id = HSDL_ThreadID();
    }
    return id;
}

int
HSDL_SetThreadPriority(HSDL_ThreadPriority priority)
{
    return 0;
}

void
HSDL_WaitThread(HSDL_Thread * thread, int *status)
{
    if (thread) {
        HSDL_SYS_WaitThread(thread);
        if (status) {
            *status = thread->status;
        }
        HSDL_DelThread(thread);
        free(thread);
    }
}

#endif
