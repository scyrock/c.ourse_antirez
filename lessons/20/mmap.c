#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void){
    int fd = open("mmap.c", O_RDONLY);
    printf("The file descriptor is: %d\n", fd);

    /* mmap() creates a new mapping in the virtual address space of the
     * calling process. The function has as arguments:
     * - The desired starting address for the new mapping. > If NULL the kernel
     *   chooses the address
     * - The length of the mapping. > 100 bytes (arbitrary)
     * - The desired memory protection of the mapping. > PROT_READ Pages may be read.
     * - Any other flag. > MAP_SHARED so the mapping is visible to other processes.
     * - The file descriptor. > fd
     * - The offset. > 0
     * The function returns the address of the mapping.  */
    void *mem = mmap(NULL, 100,PROT_READ,MAP_SHARED,fd,0);
    printf("The map address is: %p\n", mem);
    printf("%c", ((char*)mem)[0]);

    /* The file is now mapped in the memory, and can be handled as a pointer. */
    char *s = mem;      // declare pointer type

    for(int i=0; i<24; i++){
        printf("s[%d] - %c\n", i,s[i]);
    }

    /* Using mmap may speed up read and write processes, allowing to handle the file
     * in a flexible way without requiring many system calls to read and write on it.*/
    return 0;
}
