#ifndef FIFO_H
#define FIFO_H

// tasks:
//  - pop retorna true or false se conseguiu concluir a operação, e o valor vai para um buffer.
//  - no constructor é definido o tamanho do buffer. A library vai ter o ponteiro pronto, mas vai ter que alocar a memória necessária.
//  - função peekPosition(). Retorna o valor que está em determinada posição do buffer.
//  - push() pode sobrescrever o valor mais antigo. Nesse caso o head tem que se mover.
//  - definir o tamanho do buffer no constructor

#define BUFFER_SIZE 6

#include <Arduino.h>

template <typename fifo_data>

class FIFO
{
public:
    //constructor:
    FIFO();

    void push(fifo_data data);
    bool pop(fifo_data *);
    void clear();
    bool isEmpty();
    bool isFull();

    fifo_data peekPosition(int _pos);
    fifo_data peek();

private:
    uint16_t head = 0;
    uint16_t tail = 0;
    uint16_t length = 0;
    fifo_data buffer[BUFFER_SIZE];

    void indexAdd(uint16_t *index);
};

#endif