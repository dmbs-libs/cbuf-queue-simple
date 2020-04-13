/* 
 *  MIT License
 *  
 *  Copyright (c) 2019 Sergey V. DUDANOV
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "cbuf.h"

void
cbuf_init(cbuf_t *const cbuf, const uint8_t cbuf_size)
{
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->is_full = 0;
    cbuf->mask = cbuf_size - 1;
}

uint8_t
cbuf_is_full(const cbuf_t *const cbuf)
{
    return cbuf->is_full;
}

uint8_t
cbuf_put(cbuf_t *const cbuf)
{
    const uint8_t head_old = cbuf->head;
    const uint8_t head_new = (head_old + 1) & cbuf->mask;
    const uint8_t tail = cbuf->tail;

    cbuf->head = head_new;

    // is already full? just overwrite oldest element.
    if (cbuf->is_full)
    {
        cbuf->tail = (tail + 1) & cbuf->mask;
    }
    
    // cbuf is become full? set flag.
    else if (head_new == tail)
    {
        cbuf->is_full = 1;
    }

    return head_old;
}

uint8_t
cbuf_is_available(const cbuf_t *const cbuf)
{
    return (cbuf->head ^ cbuf->tail) | cbuf->is_full;
}

uint8_t
cbuf_get(cbuf_t *const cbuf)
{
    const uint8_t tail = cbuf->tail;

    cbuf->tail = (tail + 1) & cbuf->mask;
    cbuf->is_full = 0;

    return tail;
}
