//
//  gztools.cpp
//  Efficient Compression Tool
//
//  Created by Felix Hanau on 08.05.15.
//  Copyright (c) 2015 Felix Hanau. All rights reserved.
//

#include "gztools.h"
#include "zlib/zlib.h"
#include "leanify/zip.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

void ungz(const char * Infile, const char * Outfile){
    gzFile r = gzopen(Infile, "rb");
    if (!r){
        return;
    }
    FILE * stream = fopen (Outfile, "wb");
    if (!stream){
        return;
    }
    char buf [8192];
    int bytes;
    do {
        bytes = gzread(r, &buf, 8192);
        fwrite(buf, 1, bytes, stream);
    }
    while (!gzeof(r));
    gzclose_r(r);
    fclose(stream);
}

int IsGzip(const char * Infile){
    FILE * stream = fopen (Infile, "rb");
    if (!stream){
        return 2;
    }
    char buf [2];
    if (fread(&buf, 1, 2, stream) != 2){
        return 2;
    }
    fclose(stream);
    if (buf[0] == 31 && buf[1] == -117){
        return 1;
    }
    return 0;
}

int IsZIP(const char * Infile){
  FILE * stream = fopen (Infile, "rb");
  if (!stream){
    return -1;
  }
  unsigned char buf [4];
  if (fread(&buf, 1, 4, stream) != 4){
    return -1;
  }
  fclose(stream);

  return memcmp(buf, Zip::header_magic, 4) == 0;
}
