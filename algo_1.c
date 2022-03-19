#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function(void *ptr);
void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main(void)
{
	int rc1=0, rc2=0;
	pthread_t thread1, thread2, thread3, thread4;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1=0, iret2=0;	

	/* Create independent threads each of which will execute function */

	iret1 = pthread_create(
			&thread1, 
			NULL, 
			print_message_function,
			(void*) message1
			);
	iret2 = pthread_create(
			&thread2,
			NULL,
			print_message_function,
			(void*) message2
			);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	/* Create independent threads each of which will execute functionC */

	if( (rc1=pthread_create( &thread3,NULL,&functionC,NULL)) )
	{
		printf("Thread creation failed: %d\n", rc1);
	}

	
	if( (rc2=pthread_create( &thread4,NULL,&functionC,NULL)) )
	{
		printf("Thread creation failed: %d\n", rc2);

	}

	/* Wait till threads are complete before
	 * main continues. Unless we wait there 
	 * is a risk of execution of exit before
	 * threads have completed.
	 */
	
	
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);

	printf("Thread 1 returns: %d\n", iret1);
	printf("Thread 2 returns: %d\n", iret2);

	exit(0);
}

void *print_message_function(void *ptr)
{
	char *message;
	message = (char *) ptr;
	printf("%s \n", message);
}

void *functionC()
{
	pthread_mutex_lock (&mutex1);
	counter++;
	printf("Counter value: %d\n", counter);
	pthread_mutex_unlock (&mutex1);
}
