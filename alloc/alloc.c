#include "alloc.h"

static char memspace[1024 * 1024 * 1024];

void *mkalloc(word words, header *hdr) {
    void *ret, *bytesin;
    word wordsin; 

    bytesin = $v(((char*)hdr) - memspace);
    wordsin = (((word)(uintptr_t)bytesin)/4) + 1;

    if (words > (maxWords-wordsin)) {
        reterr(errNoMem); 
    }

    hdr->w = words;
    hdr->allocated = true;
    ret = $v((char*)hdr + sizeof(header));
    
    return ret; 
}

void *alloc(int32 bytes) {
    word words;
    header *hdr;
    void *mem;

    words = (!(bytes % 4)) ? bytes/4 : (bytes/4) + 1;
    
    mem = $v memspace;
    hdr = $h mem; 

    return !(hdr->w) ? ({
        if (words > maxWords) { reterr(errNoMem); }

        mem = mkalloc(words, hdr);
        mem;
    })
    : ({
        $v 0;
    });
}

int main(int argc, char *argv[]) {

    int8 *p;
    p = alloc(7);
    printf("0x%x\n", $i p);

    return 0; 
}