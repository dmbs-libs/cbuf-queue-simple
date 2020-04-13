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

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "cbuf.h"

/* 
 * Queue declare macro. Size must be one of these values: 2, 4, 8, 16, 32, 64, 128, 0(eq. 256).
 */
#define QUEUE(name,type,size)       struct name { cbuf_t cbuf; type buffer[size]; } name

/* 
 * Init queue.
 */
#define queue_init(name)            cbuf_init(&name.cbuf, sizeof(name.buffer) / sizeof(name.buffer[0]));

/* 
 * Is queue full? Used by sender. May be omitted if elements may be overwritten.
 */
#define queue_is_full(name)         cbuf_is_full(&name.cbuf)

/* 
 * Putting element into queue. Used by sender.
 * Return: element, that must be immediatly writed after return before reading it by receiver.
 */
#define queue_put(name)             name.buffer + cbuf_put(&name.cbuf)

/* 
 * Is new element available? Must be use by receiver before getting element.
 */
#define queue_is_available(name)    cbuf_is_available(&name.cbuf)

/* 
 * Getting element from queue. Used by receiver. MUST be calling ONLY if new element is available.
 * Return: element, that must be immediatly readed after return before overwriting by sender.
 */
#define queue_get(name)             name.buffer + cbuf_get(&name.cbuf)

#endif
