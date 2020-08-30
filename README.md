# Rz_rbuf
# Introduction
rz_rbuf is a simple ring buffer used for bare metal MCU system.

# Dependancy
C standard library
* stdio.h
* stdlib.h

# How to use
1. call rz_rbuf_create()
2. use API to control buffer

* Refer to test.c for examples
* User has to prepare enough heap size

# APIs

```
struct rz_rbuf* rz_rbuf_create(int size);
void rz_rbuf_delete(struct rz_rbuf* buf);

int rz_rbuf_push(struct rz_rbuf *buf, unsigned char value);
int rz_rbuf_pop(struct rz_rbuf *buf, unsigned char *value);
int rz_rbuf_get_count(struct rz_rbuf *buf);
void rz_rbuf_clear(struct rz_rbuf *buf);

int rz_rbuf_head_offset(struct rz_rbuf *buf, int offset);
```

# Todo
1. add doxygen style comment

