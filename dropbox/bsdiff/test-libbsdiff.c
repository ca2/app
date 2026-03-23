
#include <sys/types.h>

#include <bzlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "libbsdiff.h"

main(int argc, char *argv[])
{
	int fd;
	off_t oldsize, newsize, maxpatch, patchsize;
	u_char *old, *new, *patch, *patched;

	if(argc<3) errx(1,"usage: %s oldfile newfile [patchfile]\n",argv[0]);

	if(((fd=open(argv[1],O_RDONLY,0))<0) ||
		((oldsize=lseek(fd,0,SEEK_END))==-1) ||
		((old=malloc(oldsize+1))==NULL) ||
		(lseek(fd,0,SEEK_SET)!=0) ||
		(read(fd,old,oldsize)!=oldsize) ||
		(close(fd)==-1)) err(1,"%s",argv[1]);

	if(((fd=open(argv[2],O_RDONLY,0))<0) ||
		((newsize=lseek(fd,0,SEEK_END))==-1) ||
		((new=malloc(newsize+1))==NULL) ||
		(lseek(fd,0,SEEK_SET)!=0) ||
		(read(fd,new,newsize)!=newsize) ||
		(close(fd)==-1)) err(1,"%s",argv[2]);

	maxpatch = 2 * (oldsize + newsize);
	if(!(patch = malloc(maxpatch)))
		err(1, "malloc failed");
	if(!(patched = malloc(newsize)))
		err(1, "malloc failed");

	printf("Creating patch... ");
	if(!(patchsize = bsdiff(old, oldsize, new, newsize, patch, maxpatch)))
		err(1, "bsdiff failed");

	printf("done. Patch size: %lu bytes\n", patchsize);

	if(argc==4) {
		if(((fd=open(argv[3],O_CREAT|O_TRUNC|O_WRONLY,0666))<0) ||
			(write(fd,patch,patchsize)!=patchsize) || (close(fd)==-1))
			err(1,"%s",argv[3]);
	}

	printf("newsize = %lu, size_of_patched = %lu\n", newsize, size_of_patched(patch));
	if(size_of_patched(patch) != newsize)
		err(1, "size mismatch");

	if(!bspatch(old, oldsize, patch, patchsize, patched))
		err(1, "bspatch failed");

	if(memcmp(new, patched, newsize))
		err(1, "Patch test failed: destination does not equal source");

	printf("Patch test succesful!\n");
	return(0);
}

