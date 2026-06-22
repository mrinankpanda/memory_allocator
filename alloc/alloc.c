#include "alloc.h"

static char memspace[1024 * 1024 * 1024];

header *findblock_(header *hdr, word allocation, word n) {
    bool okay;
    void *mem;
    header *hdr_;
    word n_; 
    
    if ((n+allocation) > maxWords-2) reterr(errNoMem);
    okay = false; 
    
    okay = (!(hdr->w)) ? true :  
    ((!(hdr->allocated)) && (hdr->w >= allocation)) ? true :
    false;

    if (okay) return hdr;
    else {
        mem = (void *)hdr + (hdr->w * 4) + 4; 
        hdr_ = $h mem; 
        n_ = n + hdr->w; 

        return findblock_(hdr_, allocation, n_); 
    }

    reterr(errUnknown); 
}

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

    words = (!(bytes % 4)) ? bytes/4 : (bytes/4);
        
    hdr = findBlock(words);
    if (!hdr) return $v 0;
    if (words > maxWords) reterr(errNoMem); 

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
    header *hdr;
    int8 *p;

    p = alloc(7);
    printf("Allocated 0x%x\n", $i p); 

    hdr = findBlock(500);
    if (!hdr) {
        printf("Error %d\n", errno);
        return -1; 
    }

    printf("Memspace = 0x%x\n", $i memspace);
    printf("Block = 0x%x\n", $i hdr); 

    return 0; 
}