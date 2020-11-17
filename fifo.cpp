#include "fifo.h"

template <typename fifo_data>
FIFO<fifo_data>::FIFO()
{
    clear();
}

template <typename fifo_data>
void FIFO<fifo_data>::clear()
{
    memset(buffer, 0, sizeof(buffer));
    length = 0;
    head = 0;
    tail = 0;
}

template <typename fifo_data>
fifo_data FIFO<fifo_data>::peekPosition(int _pos)
{
    // 0 é a próxima posição a sair do buffer (first in)
    int cp = head;
    for (int i = 0; i <= _pos; i++)
    {
        cp--;
        if (cp < 0)
        {
            cp = BUFFER_SIZE - 1;
        }
    }
    return buffer[cp];
}

template <typename fifo_data>
fifo_data FIFO<fifo_data>::peek()
{
    return buffer[head];
}

template <typename fifo_data>
bool FIFO<fifo_data>::isEmpty()
{
    return (length == 0);
}

template <typename fifo_data>
bool FIFO<fifo_data>::isFull()
{
    return (length == BUFFER_SIZE);
}

template <typename fifo_data>
void FIFO<fifo_data>::indexAdd(uint16_t *index)
{
    *index = *index + 1;
    if (*index >= BUFFER_SIZE)
    {
        *index = 0;
    }
}

template <typename fifo_data>
void FIFO<fifo_data>::push(fifo_data data)
{
    buffer[tail] = data;
    indexAdd(&tail);
    if (isFull())
    {
        indexAdd(&head);
    }
    else
    {
        length++;
    }
}

template <typename fifo_data>
bool FIFO<fifo_data>::pop(fifo_data *_buffer)
{
    if (isEmpty() == false)
    {
        length--;
        *_buffer = buffer[head];
        buffer[head] = 0;
        indexAdd(&head);
        return true;
    }
    return false;
}