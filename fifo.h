#ifndef FIFO_H
#define FIFO_H

// tasks:
//  - pop retorna true or false se conseguiu concluir a operação, e o valor vai para um buffer.
//  - no constructor é definido o tamanho do buffer. A library vai ter o ponteiro pronto, mas vai ter que alocar a memória necessária.
//  - função peekPosition(). Retorna o valor que está em determinada posição do buffer.
//  - push() pode sobrescrever o valor mais antigo. Nesse caso o head tem que se mover.
//  - definir o tamanho do buffer no constructor

#define DEFAULT_NUMBER_OF_ELEMENTS 6

#include <Arduino.h>

template <typename fifo_data>

class FIFO
{
public:
    //constructor:
    FIFO(uint16_t);

    void push(fifo_data data);
    bool pop();
    void clear();
    bool isEmpty();
    bool isFull();

    fifo_data peekPosition(int _pos);
    fifo_data peek();

    int32_t count = 0; // count está pública para ser utilizada nas ihms sunnytec
                // to do: tentar entregar o endereço da variavel count ao invés de deixar ela pública.
private:
    uint16_t maximumNumberOfItems = DEFAULT_NUMBER_OF_ELEMENTS;
    uint16_t head = 0;
    uint16_t tail = 0;
    fifo_data *buffer;

    void indexAdd(uint16_t *index);
};


template <typename fifo_data>
FIFO<fifo_data>::FIFO(uint16_t _maximumNumberOfItems)
{
    maximumNumberOfItems = _maximumNumberOfItems;
    buffer = (fifo_data*)malloc(maximumNumberOfItems*sizeof(fifo_data));
    clear();
}

template <typename fifo_data>
void FIFO<fifo_data>::clear()
{
    memset(buffer, 0, maximumNumberOfItems*sizeof(fifo_data));
    count = 0;
    head = 0;
    tail = 0;
}

template <typename fifo_data>
fifo_data FIFO<fifo_data>::peekPosition(int _pos)
{
    // 0 é a próxima posição a sair do buffer (first in)
    int cp = head;
    for (int i = 0; i < _pos; i++)
    {
        cp--;
        if (cp < 0)
        {
            cp = maximumNumberOfItems - 1;
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
    return (count == 0);
}

template <typename fifo_data>
bool FIFO<fifo_data>::isFull()
{
    return (count == maximumNumberOfItems);
}

template <typename fifo_data>
void FIFO<fifo_data>::indexAdd(uint16_t *index)
{
    *index = *index + 1;
    if (*index >= maximumNumberOfItems)
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
        indexAdd(&head); // sobrescreve último elemento
        // to do: retornar erro ao invés de sobrescrever, e deixar as duas opções disponíveis.
    }
    else
    {
        count++;
    }
}

template <typename fifo_data>
bool FIFO<fifo_data>::pop()
{
    if (isEmpty() == false)
    {
        count--;
        // buffer[head] = 0;
        indexAdd(&head);
        return true;
    }
    return false;
}

#endif