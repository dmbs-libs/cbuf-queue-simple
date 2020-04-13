## cbuf-queue-simple

Simple queue and circular buffer implementation as [DMBS](https://github.com/abcminiuser/dmbs) library.

#### API

`cbuf.h:`

```c
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
```
`queue.h:`

```c
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
```