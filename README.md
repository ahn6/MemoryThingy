// Author: Aaron Nguyen 301254559 
// Date: March 30 2017 
// Memory Allocation

This specific source code written in C++ is compiled in Visual Studios 2015 in Windows 10.

Some assumptions for the source code
1) Through the allocator, we can track the number of allocations and decide if there is a memory leak based on the number of deallocation & allocation
2) Tests will be run one at a time

Limitations of memory allocator

1) The memory leak detection is very limited, we will indicate to users if there is a memory leak
2) The purposed template is built around vectors as vectors have the ability to deal with an allocation object
   std::vector / template < class T, class Alloc = allocator<T> > class vector; // generic template
   SOURCE: http://www.cplusplus.com/reference/vector/vector/
3) We can track the number of allocations
   
