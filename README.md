Just a basic Arena allocator for Windows.\
I realized you could just use two pointers to make a functional Arena.

A few notes;\
When calling VirtualAlloc, I don't see the point of\
rounding up the requested size to a multiple of 4096 (Page size).\
VirtualAlloc already has to do it, so why do it twice?

Also, no bounds checking.\
Thanks to Virtual Memory, you can reserve an address range\
larger than the amount of RAM you have installed,\
and the OS will happily page to disk and commit memory as\
needed when reading or writing to memory,\
this means you might as well reserve an address range\
far larger than you actually need, as doing so isn't\
actually using any memory, and just alloc as needed.\
So bound checking in this case is kinda useless.\
Not saying you should never do so, but if you're already\
reserving a larger address range than needed then it's\
fine and safe not to.
