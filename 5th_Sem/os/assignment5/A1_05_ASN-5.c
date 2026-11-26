/***********************************************************************
*
* Name- Ankit Roy, Roll- 002411001028
* Name- Saptarshi Sau, Roll- 002411001031
* Team-Number-05, Section- A1
* Date: 14th October 2026
*
* Assignment Details:
* (ii)  Execute a program using /usr/bin/time -v ./program. Record and
*       interpret User time, System time, Elapsed time and Maximum
*       resident set size.
* (iii) Write a C program that allocates a large amount of memory using
*       malloc(). Initialize the allocated memory so that the allocated
*       pages are actually touched. Keep the program running for
*       sufficient time. Compare free -h before and after execution.
*       Also investigate the process using ps and pmap -x <PID>.
*
* Input Description: Two optional command-line arguments.
*       argv[1] = amount of memory to allocate in MB   (default 512)
*       argv[2] = number of seconds to sleep/stay alive (default 60)
* Output Description: Prints the PID, page size, allocation size, result
*       of the CPU work, confirmation that malloc() succeeded and that
*       all pages were touched, then sleeps so the process can be
*       inspected, and finally frees the memory and exits.
*
* Compilation command: gcc -O0 -Wall -o asn5 A1_05_ASN-5.c
*       -O0   : no optimisation, so the CPU loop is not removed and
*               User time is measured correctly
*       -Wall : enable all common compiler warnings
*
* Execution sequence:
*
* PART (ii) - Timing the program
*   Step 1: gcc -O0 -Wall -o asn5 A1_05_ASN-5.c
*   Step 2: /usr/bin/time -v ./asn5 256 2          (Linux)
*           /usr/bin/time -l ./asn5 256 2          (macOS)
*           (256 = MB to allocate, 2 = seconds to sleep)
*   Step 3: Note User time, System time, Elapsed time and
*           Maximum resident set size from the output.
*
* PART (iii) - Inspecting memory usage (use two terminals)
*   Terminal 1:
*   Step 1: free -h                                (Linux, BEFORE)
*           top -l 1 | grep PhysMem                (macOS, BEFORE)
*   Step 2: ./asn5 512 60
*           (note the PID printed by the program)
*   Terminal 2 (while the program is sleeping):
*   Step 3: free -h                                (Linux, DURING)
*           top -l 1 | grep PhysMem                (macOS, DURING)
*   Step 4: ps -o pid,vsz,rss,%mem,cmd -p <PID>    (Linux)
*           ps -o pid,vsz,rss,%mem,command -p <PID> (macOS)
*   Step 5: pmap -x <PID>                          (Linux)
*           vmmap --summary <PID>                  (macOS)
*   Terminal 1 (after "Memory freed, exiting." is printed):
*   Step 6: free -h                                (Linux, AFTER)
*           top -l 1 | grep PhysMem                (macOS, AFTER)
*
* Sample Input and Output generated (on macOS, Apple Silicon):
*
* PART (ii):  /usr/bin/time -l ./asn5 256 2
* PID            : 45546
* Page size      : 16384 bytes
* Allocating     : 256 MB (268435456 bytes)
* CPU work done  : sum = 899999997
* malloc() done  : virtual memory reserved, pages NOT yet resident
* Pages touched  : 16384 pages now resident in RAM
* Sleeping 2 s. ...
* Memory freed, exiting.
*         3.00 real         0.26 user         0.03 sys
*            269811712  maximum resident set size
*                16624  page reclaims
*                    9  page faults
*
* Interpretation:
*   User time    0.26 s : CPU time in user mode (the loop and memset).
*   System time  0.03 s : CPU time in the kernel, mainly servicing page
*                         faults when each page was first touched.
*   Elapsed time 3.00 s : wall-clock time; much larger than user+sys
*                         because the process slept for 2 s.
*   Max RSS  ~257.3 MB  : peak physical RAM; equals the 256 MB block
*                         plus code/libraries, as every page was touched.
*   Page reclaims 16624 : ~one minor fault per 16 KB page
*                         (256 MB / 16 KB = 16384 pages).
*
* PART (iii): ./asn5 512 60
* PhysMem BEFORE : 17G used (2210M wired, 4944M compressor), 555M unused.
* PhysMem DURING : 17G used (2240M wired, 4980M compressor), 217M unused.
* PhysMem AFTER  : 17G used (2512M wired, 4952M compressor), 375M unused.
*
* ps -o pid,vsz,rss,%mem,command -p 45639
*   PID      VSZ    RSS %MEM COMMAND
* 45639 435823040 525632  2.8 ./asn5 512 60
*
* vmmap --summary 45639   (key line)
* REGION TYPE    VIRTUAL  RESIDENT  DIRTY   SWAPPED
* MALLOC_LARGE    512.0M    512.0M  512.0M      0K
* Physical footprint: 513.2M
*
* Interpretation:
*   Free memory dropped while the program ran and recovered after it
*   exited. RSS ~513 MB and a fully resident, dirty 512 MB MALLOC_LARGE
*   region show that malloc() only reserves virtual memory; physical
*   pages are assigned when they are first written (touched).
*
***********************************************************************/

#include <stdio.h>      // Required for printf(), perror() and fflush()
#include <stdlib.h>     // Required for malloc(), free(), strtoul() and atoi()
#include <string.h>     // Required for memset()
#include <unistd.h>     // Required for getpid(), sleep() and sysconf()

int main(int argc, char *argv[]) {
    // Read the memory size (in MB) from the first argument; use 512 MB if none is given.
    size_t mb = (argc > 1) ? strtoul(argv[1], NULL, 10) : 512;

    // Read the sleep duration (in seconds) from the second argument; use 60 s if none is given.
    int seconds = (argc > 2) ? atoi(argv[2]) : 60;

    // Convert megabytes to bytes (1 MB = 1024 * 1024 bytes).
    size_t bytes = mb * 1024UL * 1024UL;

    // Ask the operating system for the size of one memory page (4 KB on most Linux, 16 KB on Apple Silicon).
    long page = sysconf(_SC_PAGESIZE);

    // Print this process's ID so it can be inspected with ps and pmap/vmmap.
    printf("PID            : %d\n", getpid());

    // Print the page size reported by the system.
    printf("Page size      : %ld bytes\n", page);

    // Print how much memory is going to be allocated.
    printf("Allocating     : %zu MB (%zu bytes)\n", mb, bytes);

    // 'volatile' stops the compiler from optimising this variable (and the loop) away.
    volatile unsigned long sum = 0;

    // Pure CPU work with no system calls: this time is counted as USER time.
    for (unsigned long i = 0; i < 300000000UL; i++)
        // Add a small value each iteration to keep the CPU busy.
        sum += i % 7;

    // Print the result so the work is visibly used.
    printf("CPU work done  : sum = %lu\n", sum);

    // Request the memory block. This only reserves VIRTUAL address space; no physical RAM is used yet.
    char *buf = malloc(bytes);

    // If malloc() returns NULL, the allocation failed.
    if (buf == NULL) {
        // Print the reason for the failure.
        perror("malloc");
        // Exit with an error code.
        return 1;
    }

    // Confirm the allocation; at this point RSS has not grown yet.
    printf("malloc() done  : virtual memory reserved, pages NOT yet resident\n");

    // Visit the block one page at a time.
    for (size_t off = 0; off < bytes; off += page)
        // Writing one byte causes a page fault; the kernel then maps a physical frame (counted as SYSTEM time).
        buf[off] = (char)(off & 0xFF);

    // Initialise the entire block so every page is definitely touched and dirty.
    memset(buf, 'A', bytes);

    // Report how many pages are now resident in physical memory.
    printf("Pages touched  : %zu pages now resident in RAM\n", bytes / page);

    // Tell the user the program is about to sleep.
    printf("\nSleeping %d s. In another terminal run:\n", seconds);

    // Suggest the command to check system memory.
    printf("  free -h\n");

    // Suggest the ps command with this process's PID (%% prints a literal % sign).
    printf("  ps -o pid,vsz,rss,%%mem,cmd -p %d\n", getpid());

    // Suggest the pmap command with this process's PID.
    printf("  pmap -x %d\n\n", getpid());

    // Force all buffered output to the terminal before sleeping.
    fflush(stdout);

    // Keep the process alive (holding its memory) so it can be inspected; adds to ELAPSED time only.
    sleep(seconds);

    // Release the memory back to the operating system.
    free(buf);

    // Inform the user that the memory has been freed.
    printf("Memory freed, exiting.\n");

    return 0; // Successful execution
}
