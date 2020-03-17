#ifndef FIFO_H
#define FIFO_H

// tasks:
//  - pop retorna true or false se conseguiu concluir a operação, e o valor vai para um buffer.
//  - no constructor é definido o tamanho do buffer. A library vai ter o ponteiro pronto, mas vai ter que alocar a memória necessária.
//  - função peekPosition(). Retorna o valor que está em determinada posição do buffer.
//  - push() pode sobrescrever o valor mais antigo. Nesse caso o head tem que se mover.

#define BUFFER_SIZE 6

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

    bool pop(fifo_data *);

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

#endif