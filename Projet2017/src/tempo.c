#include "SDL.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>

#include "timer.h"


sigset_t mask , vide;
// Return number of elapsed µsec since... a long time ago
static unsigned long get_time (void)
{
  struct timeval tv;

  gettimeofday (&tv ,NULL);

  // Only count seconds since beginning of 2016 (not jan 1st, 1970)
  tv.tv_sec -= 3600UL * 24 * 365 * 46;

  return tv.tv_sec * 1000000UL + tv.tv_usec;
}

#ifdef PADAWAN

void handler(){
  printf("Thread courant : %p \n", pthread_self());
}

void *infiniteLoop(void *p){

  while(1){
  //  kill(pthread_self(),SIGALRM);
    sigsuspend(&vide);
  }
}
// timer_init returns 1 if timers are fully implemented, 0 otherwise
int timer_init (void)
{
  int nbThreads = 2;
  pthread_t t[nbThreads];



  struct sigaction s;
  s.sa_flags = 0;
  sigemptyset(&s.sa_mask);
  s.sa_handler = handler;
  sigaction(SIGALRM,&s,NULL);

  sigemptyset(&vide);
  sigemptyset(&mask);
  sigaddset(&mask,SIGALRM);

  // Creaation du démon
  for (int i = 0; i < nbThreads; i++) {
    pthread_create(t,NULL,infiniteLoop,NULL);
  }


  for (int i = 0; i < nbThreads; i++) {
    pthread_join(t[i],NULL);
  }

  return 0; // Implementation not ready
}

timer_id_t timer_set (Uint32 delay, void *param)
{
  // TODO

  return (timer_id_t) NULL;
}

int timer_cancel (timer_id_t timer_id)
{
  // TODO

  return 0; // failure
}

#endif
