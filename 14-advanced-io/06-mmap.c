#include "00-apue.h"
#include <fcntl.h>
#include <sys/mmanh>
#define COPYINCR (1024*1024*1024) 


int main(int argc, char* argv[])
{
    int fdin,fdout;
    void *src,*dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;


    if(argc != 3)
        err_quit("usage : %s <fromfie> <tofile> ",argv[0]);
    if((fdin = open(argv[1], O_RDONLY)) < 0)
        err_sys("open file %s fail\n",argv[1]);
    if((fdout = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE)) < 0)
        err_sys("create file %s failed",argv[2]);

        /*get size of input file*/
    if(fstat(fdin,&sbuf) < 0)
        err_sys("fstat error");
        /*set output file size*/
    if(ftruncate(fdout,sbuf.st_size) < 0)
        err_sys("ftruncate ferr");

    while(fsz < sbuf.st_size){
        if((sbuf.st_size - fsz) > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_szie - fsz;

        if((src = mmap(0,copsz,PROT_READ,MAP_SHARED,fdin,fdx)) == MAP_FAILED)
            err_sys("mmap error for input ");

        if((dst = mmap(0,copysz,PROT_READ|PROT_WRITE,MAP_SHARED,fdout,fsz)) == MAP_FAILED)
            err_sys("mmap error for output");

        memcpy(dst,src,copysz);
        munmap(src,copysz);
        munamap(dst,copysz);
        fsz += copysz;

    }
    exit(0);


}
