#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

void *functionCount1();
void *functionCount2();
void *functionAdder();
void *functionMult();

int count = 0, count_add = 0, count_mul = 0;

#define COUNT_DONE 10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

int main(void)
{
	pthread_t thread_1, thread_2, thread_3, thread_4;
	
	pthread_create( &thread_1, NULL, &functionCount1, NULL);
	pthread_create( &thread_2, NULL, &functionCount2, NULL);
	pthread_create( &thread_3, NULL, &functionAdder, NULL);
	pthread_create( &thread_4, NULL, &functionMult, NULL);

	pthread_join( thread_1, NULL );
	pthread_join( thread_2, NULL );
	pthread_join( thread_3, NULL );
	pthread_join( thread_4, NULL );
	
	exit(0);
}

void *functionCount1(void)
{
	for(;;)
	{
		pthread_mutex_lock( &condition_mutex );
		while (count >= COUNT_HALT1 && count <= COUNT_HALT2 )
		{
			pthread_cond_wait( &condition_cond, &condition_mutex );
		}
		
		pthread_mutex_unlock( &condition_mutex );
		
		pthread_mutex_lock( &count_mutex);
		count++;
		
		printf("Counter value functionCount1: %d\n",count);
		pthread_mutex_unlock ( &count_mutex );
		
		if(count >= COUNT_DONE) return(NULL);
	}
}

void *functionCount2(void)
{
	for(;;)
	{
		pthread_mutex_lock( &condition_mutex );
		while (count >= COUNT_HALT1 && count <= COUNT_HALT2 )
		{
			pthread_cond_wait( &condition_cond, &condition_mutex );
		}
		
		pthread_mutex_unlock( &condition_mutex );
		
		pthread_mutex_lock( &count_mutex);
		count++;
		
		printf("Counter value functionCount2: %d\n",count);
		pthread_mutex_unlock ( &count_mutex );
		
		if(count >= COUNT_DONE) return(NULL);
	}
}

void *functionAdder(void)
{
	for(;;)
	{
		pthread_mutex_lock( &condition_mutex );
		if( count < COUNT_HALT1 && count > COUNT_HALT2 )
		{
			pthread_cond_signal( &condition_cond );
		}
		pthread_mutex_unlock( &condition_mutex);
		
		pthread_mutex_lock( &count_mutex);
		count_add = count + 12;
		printf("Count value functionAdder: %d\n", count_add);
		pthread_mutex_unlock( &count_mutex );
		
		if (count >= COUNT_DONE) return NULL;
	}
}

void *functionMult(void)
{
	for(;;)
	{
		pthread_mutex_lock( &condition_mutex );
		if( count < COUNT_HALT1 || count > COUNT_HALT2 )
		{
			pthread_cond_signal( &condition_cond );
		}
		pthread_mutex_unlock( &condition_mutex);
		
		pthread_mutex_lock( &count_mutex);
		count_mul *= 12*count - 9*count;
		printf("Count value functionMult: %d\n", count_mul);
		pthread_mutex_unlock( &count_mutex );
		
		if (count >= COUNT_DONE) return NULL;
	}
}
