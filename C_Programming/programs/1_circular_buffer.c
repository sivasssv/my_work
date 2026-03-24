#include <stdio.h>
#include <stdint.h>

/*Structures*/
typedef struct 
{
    uint8_t buffer[256];
    uint8_t head; /* write index */
    uint8_t tail; /* read index  */
}CircularBuffer;

/*Function declarations*/
void cb_init(CircularBuffer *cb);
int cb_write(CircularBuffer *cb, uint8_t data);
int cb_read(CircularBuffer *cb, uint8_t *data);
int cb_is_empty(CircularBuffer *cb);
int cb_is_full(CircularBuffer *cb);



/*Main function*/
int main()
{
    uint8_t read = 0;
    CircularBuffer buff;
    cb_init(&buff);
    if (cb_is_full(&buff) == 1)
    {
        printf("Circular buffer is full\n");
    }


    cb_write(&buff, 9);
    cb_write(&buff, 8);
    cb_write(&buff, 7);
    cb_write(&buff, 6);

    for(uint8_t i = 0; i < 4; i++ )
    {
        cb_read(&buff, &read);
        printf("read out : %d\n", read);
    }


    if (cb_is_empty)
    {
        printf("Circular buffer is empty\n");
    }

    return 0;
}

/*Initialization of Circular Buffer*/
void cb_init(CircularBuffer *cb)
{
    cb->head = 0;
    cb->tail = 0;
}



/*Writing data into Circular buffer*/
int cb_write(CircularBuffer *cb, uint8_t data)
{
    uint8_t next_head = (cb->head + 1) % 256;

    if (next_head == cb->tail)
    {
        return -1;
    }

    cb->buffer[cb->head] = data;
    cb->head = next_head;
    return 0;
}

/*Reading data from Circular buffer*/
int cb_read(CircularBuffer *cb, uint8_t *data)
{
    if(cb->tail == cb->head)
    {
        return -1;
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % 256;
    return 0;
}

/*Checking whether the bufer is empty*/
int cb_is_empty(CircularBuffer *cb)
{
    return (cb->head == cb->tail);    
}

/*Checking whether the buffer is full*/
int cb_is_full(CircularBuffer *cb)
{
    return ((cb-> head + 1) % 256 == cb->tail);
}



