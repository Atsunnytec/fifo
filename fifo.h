#ifndef FIFO_H
#define FIFO_H

// tasks:
//  - pop retorna true or false se conseguiu concluir a operação, e o valor vai para um buffer.


#define BUFFER_SIZE 3

template <typename fifo_data>

class FIFO
{
public:
    //constructor:
    FIFO()
    {
        clear();
    }

    void push(fifo_data data);

    fifo_data pop();

    void clear()
    {
        memset(buffer, 0, sizeof(buffer));
        length = 0;
        head = 0;
        tail = 0;
    }

    fifo_data peek()
    {
        return buffer[head];
    }

    bool isEmpty()
    {
        return (length == 0);
    }

private:
    uint16_t head = 0;
    uint16_t tail = 0;
    uint16_t length = 0;
    fifo_data buffer[BUFFER_SIZE];

    void indexAdd(uint16_t *index)
    {
        *index = *index + 1;
        if (*index >= BUFFER_SIZE)
        {
            *index = 0;
        }
    }
};

template <typename fifo_data>
void FIFO<fifo_data>::push(fifo_data data)
{
    buffer[tail] = data;
    indexAdd(&tail);
    length++;
}

template <typename fifo_data>
fifo_data FIFO<fifo_data>::pop()
{
    fifo_data cp;
    if (isEmpty() == false)
    {
        length--;
        cp = buffer[head];
        buffer[head] = 0;
        indexAdd(&head);
    }
    return cp;
}

#endif