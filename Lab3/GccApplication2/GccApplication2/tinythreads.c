#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)();   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;
long interrupts = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    //Set compare match
    PORTB = PORTB | (1 << PB5);
    PORTB = PORTB | (1 << PB7);
    
    //Set timer enabler
    TIMSK1 = (1 << OCIE1A);
    
    //Set pre-scaling factor and CTC
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    //8 000 000 / 1024 /1000 * 50 * 100 (Target Time)
    OCR1A = 10;//390.625*10;
    
    //Set timer
	TCNT1 = 0;

    EIMSK = EIMSK | (1<<PCINT15);
    PCMSK1 = PCMSK1 | (1<<PCINT15);

    initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        p->next = q;
        *queue = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    //lock(&MTX2);
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        //unlock(&MTX2);
        current->function(current->arg);
        DISABLE();
        //lock(&MTX2);

        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(current, &readyQ);

    dispatch(newp);
    ENABLE();
}

void lock(mutex *m) {
    DISABLE();
    if (m->locked == 0) {
        m->locked = 1;
    }
    else {
        //Add current thread to wait queue
        enqueue(current, &(m->waitQ));

        //And go to next thread
        dispatch(dequeue(&readyQ));
    }
    ENABLE();
}

void unlock(mutex *m) {
    DISABLE();
    if (m->waitQ == NULL) {
        m->locked = 0;
    }
    else {
        // Add current thread to ready queue
        enqueue(current, &readyQ);
        
        //And continue with any waiting threads
        dispatch(dequeue(&m->waitQ));
    }
    ENABLE();
}

/*
void yield (){
    enqueue(current, &readyQ);
    dispatch(dequeue(readyQ));
}
*/
