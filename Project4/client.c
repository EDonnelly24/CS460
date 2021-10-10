#include "client.h"
#include "threadpool.h"

/* ******************************************************* */
/* main()                                                  */
/* ******************************************************* */
pthread_mutex_t lock;
struct sockaddr_in client_address
int main() {
    
    // task counter, also serves as argument to 3A+1 algorithm
    int task_counter;
    
    // create threadpool with THREADS_IN_POOL threads
    threadpool pool = threadpool_create();

    
    for (task_counter=1; task_counter<=NUMBER_TASKS; task_counter++)
    {
        // in each loop, execute three_a_plus_one_wrapper in a thread from the pool
        threadpool_add_task(pool, task_copy_arguments, three_a_plus_one_wrapper, (void*)&task_counter);
    }

    // lame way to wait for everybody to get done
    // in a network server, this is not needed as the main thread keeps accepting connections
    sleep(8);
    
    exit(EXIT_SUCCESS);
}

int three_a_plus_one_rec(int input)
{
    int counter = 0;
    int current = input;

    while (current != 1)
    {
        counter++;
        if (current % 2) {
            current = (current*3) + 1;
        }
        else {
            current >>= 1;
        }
    }
    return counter;
}

/* ******************************************************* */
/* three_a_plus_one_wrapper()                              */
/* ******************************************************* */
void three_a_plus_one_wrapper(void *number_ptr)
{
    int number = *((int*)number_ptr);
    
    printf("\nthread ID %p ----> %d: %d", pthread_self(), number, three_a_plus_one_rec(number));
}


/* ******************************************************* */
/* prepare arguments for thread function                   */
/* ******************************************************* */
void *task_copy_arguments(void *args_in)
{
    void *args_out;
    
    args_out = malloc(sizeof(int));
    *((int*)args_out) = *((int*)args_in);
    
    return args_out;
}