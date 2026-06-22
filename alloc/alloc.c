#include "alloc.h"
#include "birchutils.h"

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

void show_(header *hdr) {
    header *p;
    void *mem; 
    int32 n; 

    for (p=hdr; p->w; mem=$v p + ((p->w+1)*4), p=mem, n++) {
        printf("Alloc %d = %d %s words\n", n, p->w, (p->allocated) ? "allocated" : "free"); 
    }

    return;
}

int main(int argc, char *argv[]) {
    int8 *p;
    int8 *p2;
    int8 *p3;

    p = alloc(7);
    printf("Allocated 0x%x\n", $i p); 

    p = alloc(7);
    p2 = alloc(2000);
    p3 = alloc(1);

    show();

    return 0; 
}