#include <stdio.h>
#include <assert.h>
#include "rz_rbuf.h"

int main(int argc, char *argv[]) {
    struct rz_rbuf *buf;
    int size;

    char s[100];
    char *p = s;
    int rc;
    int cnt;
    unsigned char v;

    size = 5;
    for (int m=0; m<100; m++) {
        *p++ = m;
    }
    
    buf =  rz_rbuf_create(size);
    assert(buf != 0);
    printf("start = %p\n", buf->start);
    printf("end = %p\n", buf->end);
    printf("head = %p\n", buf->head);
    printf("tail = %p\n", buf->tail);
    printf("count = %d\n", buf->count);
    assert(buf->end - buf->start == size);
    assert(buf->start == buf->head);
    assert(buf->start == buf->tail);

    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 0); 

    //push to full
    rc = rz_rbuf_push(buf, s[0]);
    assert(rc == 0); 
    rc = rz_rbuf_push(buf, s[1]);
    assert(rc == 0); 
    rc = rz_rbuf_push(buf, s[2]);
    assert(rc == 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 3); 
    rc = rz_rbuf_push(buf, s[3]);
    assert(rc == 0); 
    rc = rz_rbuf_push(buf, s[4]);
    assert(rc == 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 5); 
    rc = rz_rbuf_push(buf, s[5]);
    assert(rc != 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 5); 

    //pop 2
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 0); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 1); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 3); 

    //push 3
    rc = rz_rbuf_push(buf, s[5]);
    assert(rc == 0); 
    rc = rz_rbuf_push(buf, s[6]);
    assert(rc == 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 5); 
    rc = rz_rbuf_push(buf, s[7]);
    assert(rc != 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 5); 

    //pop to empty
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 2); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 3); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 4); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 5); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc == 0); 
    assert(v == 6); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 0); 
    rc = rz_rbuf_pop(buf, &v); 
    assert(rc != 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 0); 

    //push 2
    rc = rz_rbuf_push(buf, s[7]);
    assert(rc == 0);
    rc = rz_rbuf_push(buf, s[8]);
    assert(rc == 0); 
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 2); 

    //==== rz_rbuf_clear
    //clear
    rz_rbuf_clear(buf);
    cnt = rz_rbuf_get_count(buf);
    assert(cnt == 0); 

    //push to 2
    rc = rz_rbuf_push(buf, s[0]);
    rc = rz_rbuf_push(buf, s[1]);

    //==== rz_rbuf_head_offset
    //header offset too much
    rc = rz_rbuf_head_offset(buf, 4);
    assert(rc != 0); 
    rc = rz_rbuf_head_offset(buf, 10);
    assert(rc != 0); 

    //push to full
    rc = rz_rbuf_push(buf, s[2]);
    rc = rz_rbuf_push(buf, s[3]);
    rc = rz_rbuf_push(buf, s[4]);

    //header offset  normal
    rc = rz_rbuf_head_offset(buf, 3);
    assert(rc == 0); 


    return 0;
}
