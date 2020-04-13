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

#ifndef _CBUF_H_
#define _CBUF_H_

#include <stdint.h>

/* Circular buffer context structure. */
typedef struct cbuf_t {
    uint8_t head;       // head index
    uint8_t tail;       // tail index
    uint8_t is_full;    // "cbuf is full" flag
    uint8_t mask;       // cbuf_size - 1
} cbuf_t;

/* 
 * Init circular buffer. Size must be one of these values: 2, 4, 8, 16, 32, 64, 128, 0(eq. 256).
 */
void
cbuf_init(cbuf_t *cbuf, uint8_t cbuf_size);

/* 
 * Is buffer full? Used by sender. May be omitted if elements may be overwritten.
 */
uint8_t
cbuf_is_full(const cbuf_t *cbuf);

/* 
 * Putting new element into buffer. Used by sender.
 * Return: index of element, that must be immediatly writed after return before reading it by receiver.
 */
uint8_t
cbuf_put(cbuf_t *cbuf);

/* 
 * Is new element available? Must be use by receiver before getting element.
 */
uint8_t
cbuf_is_available(const cbuf_t *cbuf);

/* 
 * Getting element from buffer. Used by receiver. MUST be calling ONLY if new element is available.
 * Return: index of element, that must be immediatly readed after return before overwriting by sender.
 */
uint8_t
cbuf_get(cbuf_t *cbuf);

#endif
