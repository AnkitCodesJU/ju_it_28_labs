/***********************************************************************
*
* Name- Ankit Roy, Roll- 002411001028
* Name- Saptarshi Sau, Roll- 002411001031
* Team-Number-05, Section- A1
* Date: 4th November 2026

* Output Description:
*       bench  : table of threads, parallel min, average time, speedup,
*                efficiency and correctness; also writes results.csv and
*                the graph execution_time_plot.svg (open in a browser).
*       join   : STARTED / COMPLETED messages from every worker, the
*                joined local minimums and the correct global minimum.
*       nojoin : shows that main reads the results before the workers
*                finish, so the "global min" is wrong / incomplete.
*
* Compilation command: gcc -O0 -Wall -o A1_05_ASN-6 A1_05_ASN-6.c -lpthread
*       -O2       : optimise the code (realistic timing)
*       -Wall     : enable all common compiler warnings
*       -lpthread : link the POSIX threads library
*
* Execution sequence:
*       ./A1_05_ASN-6 bench 1500000000
*       ./A1_05_ASN-6 join 4 1500000000
*       ./A1_05_ASN-6 nojoin 4 1500000000

* Assignment Details:
*       Find the minimum value in a huge unsigned char array using
*       POSIX threads (pthreads). The array is split into equal segments,
*       each worker thread finds the minimum of its own segment, and the
*       main thread combines (reduces) the local minimums into the global
*       minimum. The program also:
*         - measures execution time for 1, 2, 4, 8 and 16 threads and
*           draws a graph of time / speedup / efficiency (bench mode),
*         - demonstrates the thread lifecycle when main JOINS all
*           workers (join mode), and
*         - demonstrates what happens when main does NOT wait for the
*           workers (nojoin mode).
*
* Input Description: Command-line arguments.
*       ./A1_05_ASN-6 bench  [N] [REPEATS]
*       ./A1_05_ASN-6 join   [T] [N]
*       ./A1_05_ASN-6 nojoin [T] [N]
*       N       = number of array elements (minimum 10^7, default 8 GiB)
*       REPEATS = timing runs per thread count (1..32, default 5)
*       T       = number of worker threads   (1..64, default 4)
*
*
* NOTE: very large N needs a 64-bit compiler (Linux / WSL / MSYS2
*       MinGW-w64) and at least N bytes of free RAM
*       (1500000000 elements = about 1.4 GB).
*
*
***********************************************************************/

#define __USE_MINGW_ANSI_STDIO 1   // Lets old MinGW printf understand %llu (ignored on Linux)

#include <stdio.h>      // Required for printf(), fprintf(), fopen(), perror(), fflush()
#include <stdlib.h>     // Required for malloc(), free(), exit(), atoi(), strtoull()
#include <string.h>     // Required for strcmp() and memcpy()
#include <stdint.h>     // Required for uintptr_t (to pack a value into a pointer)
#include <pthread.h>    // Required for pthread_create(), pthread_join(), pthread_exit() etc.
#include <sys/time.h>   // Required for gettimeofday() used for timing
#ifdef _WIN32           // If compiling on Windows ...
#include <windows.h>    // ... GetSystemInfo() gives the CPU count
#else                   // Otherwise (Linux / macOS) ...
#include <unistd.h>     // ... sysconf() gives the CPU count
#endif                  // End of the platform check

#define DEFAULT_N        8589934592ULL // Default array size: 8 GiB = 8 * 2^30 elements
#define DEFAULT_REPEATS  5             // Default number of timing runs per thread count
#define MAX_THREADS      64            // Upper limit on the number of threads
#define PLANTED_MIN      3             // The known global minimum planted in the array

/* ---------- shared data ---------- */
static unsigned char *arr;             // Pointer to the huge array (shared by all threads)
static size_t         N;               // Number of elements in the array
static int            verbose = 0;     // 1 = print thread lifecycle messages, 0 = silent

// Structure passed to each worker thread
typedef struct {
    int           id;                  // Logical thread number 0..T-1
    size_t        start, end;          // This thread's segment is [start, end)
    unsigned char local_min;           // Local minimum (also stored here for the nojoin demo)
    volatile int  done;                // Set to 1 when the worker finishes (volatile: read by main)
} thread_arg_t;

/* ---------- portability helpers ---------- */
// pthread_t is an integer on Linux but a struct in Windows pthreads-w32,
// so copy its leading bytes into an unsigned long for printing.
static unsigned long tid_to_ulong(pthread_t t)
{
    unsigned long id = 0;                                       // Result starts as 0
    memcpy(&id, &t, sizeof id < sizeof t ? sizeof id : sizeof t); // Copy the smaller of the two sizes
    return id;                                                  // Return the printable thread id
}

// Returns the number of CPUs that are currently online
static long cpu_count(void)
{
#ifdef _WIN32                                  // Windows version
    SYSTEM_INFO si;                            // Structure that receives system information
    GetSystemInfo(&si);                        // Fill it in
    return (long)si.dwNumberOfProcessors;      // Return the number of processors
#else                                          // Linux / macOS version
    return sysconf(_SC_NPROCESSORS_ONLN);      // Ask the OS for the online CPU count
#endif
}

/* ---------- timing helper using gettimeofday() ---------- */
static double now_sec(void)
{
    struct timeval tv;                         // Holds seconds and microseconds
    gettimeofday(&tv, NULL);                   // Read the current wall-clock time
    return tv.tv_sec + tv.tv_usec / 1e6;       // Convert to seconds as a double
}

/* ---------- array initialisation (deterministic pseudo-random) ---------- */
static void init_array(size_t n)
{
    unsigned int seed = 12345;                    // Fixed seed => same array on every run
    for (size_t i = 0; i < n; i++) {              // Visit every element
        seed = seed * 1103515245u + 12345u;       // Simple linear congruential generator (LCG)
        arr[i] = (unsigned char)(10 + (seed >> 16) % 246);   // Value in the range 10..255
    }
    // Plant one known minimum at a deterministic position
    size_t pos = (n / 7) * 5 + 13;                // Position roughly 5/7 of the way through
    arr[pos] = PLANTED_MIN;                       // Store the value 3 there (smaller than all others)
}

/* ---------- sequential reference ---------- */
static unsigned char sequential_min(void)
{
    unsigned char m = 255;                        // Start with the largest possible value
    for (size_t i = 0; i < N; i++)                // Scan the whole array with one thread
        if (arr[i] < m) m = arr[i];               // Keep the smallest value seen so far
    return m;                                     // Return the sequential minimum (used to verify)
}

/* ---------- worker thread ---------- */
static void *worker(void *p)
{
    thread_arg_t *a = (thread_arg_t *)p;          // Convert the generic pointer back to our struct
    pthread_t self = pthread_self();              // Get this thread's own pthread id

    if (verbose)                                  // In demo modes, announce that the thread started
        printf("  [thread %2d | pthread_self=%lu] STARTED  segment [%llu, %llu)\n",
               a->id, tid_to_ulong(self), (unsigned long long)a->start, (unsigned long long)a->end);

    unsigned char m = 255;                        // Local minimum starts at the largest value
    for (size_t i = a->start; i < a->end; i++)    // Scan only this thread's segment
        if (arr[i] < m) m = arr[i];               // Keep the smallest value in the segment

    a->local_min = m;                             // Save the local minimum in the shared struct
    a->done = 1;                                  // Mark this worker as finished

    if (verbose)                                  // In demo modes, announce completion
        printf("  [thread %2d | pthread_self=%lu] COMPLETED local min = %u\n",
               a->id, tid_to_ulong(self), m);

    // Return the local minimum through pthread_exit().
    // The value is packed into the pointer itself (no malloc needed).
    pthread_exit((void *)(uintptr_t)m);
    return NULL;   // Never reached; keeps older compilers quiet
}

/* ---------- split array into ~equal segments ---------- */
static void make_segments(thread_arg_t *args, int T)
{
    size_t chunk = N / T, rem = N % T, pos = 0;   // Base segment size, leftover elements, current position
    for (int t = 0; t < T; t++) {                 // For every thread ...
        size_t len = chunk + ((size_t)t < rem ? 1 : 0);   // First 'rem' threads get one extra element
        args[t].id = t;                           // Thread number
        args[t].start = pos;                      // Segment start index
        args[t].end = pos + len;                  // Segment end index (exclusive)
        args[t].local_min = 255;                  // Not computed yet
        args[t].done = 0;                         // Not finished yet
        pos += len;                               // Next segment starts where this one ends
    }
}

/* ---------- parallel minimum: create, join, reduce ---------- */
static unsigned char parallel_min(int T, double *elapsed)
{
    pthread_t    tid[MAX_THREADS];                // Thread handles
    thread_arg_t args[MAX_THREADS];               // Per-thread arguments
    make_segments(args, T);                       // Divide the array among T threads

    double t0 = now_sec();                        // Start the timer

    for (int t = 0; t < T; t++)                   // Create T worker threads
        if (pthread_create(&tid[t], NULL, worker, &args[t]) != 0) {   // Non-zero means failure
            perror("pthread_create");             // Print the reason
            exit(1);                              // Stop the program
        }

    unsigned char gmin = 255;                     // Global minimum starts at the largest value
    for (int t = 0; t < T; t++) {                 // Wait for every thread in order
        void *ret;                                // Receives the value passed to pthread_exit()
        pthread_join(tid[t], &ret);               // Block until thread t ends and collect its result
        unsigned char lm = (unsigned char)(uintptr_t)ret;   // Unpack the local minimum
        if (verbose)                              // In demo modes, show what was joined
            printf("  main: joined thread %2d -> local min %u\n", t, lm);
        if (lm < gmin) gmin = lm;                 // Global reduction: keep the smallest local min
    }

    *elapsed = now_sec() - t0;                    // Stop the timer and return elapsed time
    return gmin;                                  // Return the global minimum
}

/* ================= graph: pure-C SVG writer ================= */
/* Draws two panels into an SVG file (opens in any web browser):
 *   left : average execution time vs number of threads
 *   right: measured speedup, ideal speedup and parallel efficiency
 * X axis is log2(threads) so 1,2,4,8,16 are evenly spaced.            */

#define PW 460   // Panel plot-area width in pixels
#define PH 300   // Panel plot-area height in pixels

// Log base 2 without libm: halve to [1,2), then ln(m) via atanh series
static double log2d(double x)
{
    if (x <= 0) return 0;                         // log of non-positive values is undefined; return 0
    double r = 0;                                 // Integer part of the result
    while (x >= 2) { x /= 2; r++; }               // Bring x below 2, counting halvings
    while (x < 1)  { x *= 2; r--; }               // Bring x up to at least 1, counting doublings
    double z = (x - 1) / (x + 1), z2 = z * z, term = z, ln = 0;   // Setup for ln(x) = 2*atanh(z)
    for (int k = 1; k < 40; k += 2) { ln += term / k; term *= z2; } // Series z + z^3/3 + z^5/5 + ...
    return r + 2 * ln / 0.69314718055994530942;   // Integer part + ln(x)/ln(2)
}

// Map index -> x pixel, and value -> y pixel, inside a panel whose plot area starts at (ox, oy)
static double px(int i, int n, int ox)            { return ox + (n > 1 ? (double)i * PW / (n - 1) : PW / 2.0); }
static double py(double v, double lo, double hi, int oy) { return oy + PH - (v - lo) / (hi - lo) * PH; }

// Draws the frame, title, x-axis ticks/labels and axis titles of one panel
static void svg_axes(FILE *f, int ox, int oy, const int *th, int n,
                     const char *title, const char *ylabel)
{
    // Rectangle around the plot area
    fprintf(f, "<rect x='%d' y='%d' width='%d' height='%d' fill='none' stroke='#333'/>\n",
            ox, oy, PW, PH);
    // Panel title, centred above the plot
    fprintf(f, "<text x='%d' y='%d' font-size='16' text-anchor='middle' font-weight='bold'>%s</text>\n",
            ox + PW / 2, oy - 15, title);
    for (int i = 0; i < n; i++) {   // x ticks + vertical grid lines
        double x = px(i, n, ox);    // Pixel position of tick i
        fprintf(f, "<line x1='%.1f' y1='%d' x2='%.1f' y2='%d' stroke='#ddd'/>\n", x, oy, x, oy + PH); // Grid line
        fprintf(f, "<text x='%.1f' y='%d' font-size='12' text-anchor='middle'>%d</text>\n",
                x, oy + PH + 18, th[i]);                                                             // Thread count label
    }
    // x-axis title
    fprintf(f, "<text x='%d' y='%d' font-size='13' text-anchor='middle'>Number of threads</text>\n",
            ox + PW / 2, oy + PH + 40);
    // y-axis title, rotated 90 degrees
    fprintf(f, "<text transform='translate(%d,%d) rotate(-90)' font-size='13' text-anchor='middle'>%s</text>\n",
            ox - 55, oy + PH / 2, ylabel);
}

// Draws one data series as a polyline, optionally dashed, with circle or square markers
static void svg_line(FILE *f, const double *ys, int n, int ox, int oy, double lo, double hi,
                     const char *color, int dashed, int square_marker)
{
    // Start the polyline element (dashed if requested)
    fprintf(f, "<polyline fill='none' stroke='%s' stroke-width='2.5'%s points='",
            color, dashed ? " stroke-dasharray='6,4'" : "");
    for (int i = 0; i < n; i++)                                  // Add every point
        fprintf(f, "%.1f,%.1f ", px(i, n, ox), py(ys[i], lo, hi, oy));
    fprintf(f, "'/>\n");                                         // Close the polyline
    if (dashed) return;                                          // Dashed (ideal) line gets no markers
    for (int i = 0; i < n; i++) {                                // Draw a marker at each point
        double x = px(i, n, ox), y = py(ys[i], lo, hi, oy);      // Pixel position of point i
        if (square_marker)                                       // Square marker (efficiency)
            fprintf(f, "<rect x='%.1f' y='%.1f' width='9' height='9' fill='%s'/>\n", x - 4.5, y - 4.5, color);
        else                                                     // Circle marker (time / speedup)
            fprintf(f, "<circle cx='%.1f' cy='%.1f' r='5' fill='%s'/>\n", x, y, color);
    }
}

// Writes the complete two-panel graph to an SVG file
static void write_svg(const char *fname, const int *th, const double *avg,
                      const double *spd, const double *eff, int n)
{
    FILE *f = fopen(fname, "w");                                 // Open the output file
    if (!f) { perror("fopen svg"); return; }                     // Give up if it cannot be opened
    int W = 2 * PW + 260, H = PH + 130;                          // Total image width and height
    // SVG header and white background
    fprintf(f, "<svg xmlns='http://www.w3.org/2000/svg' width='%d' height='%d' "
               "font-family='Arial, sans-serif'>\n<rect width='100%%' height='100%%' fill='white'/>\n", W, H);

    /* ---- left panel: execution time ---- */
    int ox1 = 80, oy = 50;                                       // Top-left corner of the left plot area
    double tmax = 0;                                             // Largest average time
    for (int i = 0; i < n; i++) if (avg[i] > tmax) tmax = avg[i]; // Find it
    tmax *= 1.15;                                                // Add 15% headroom above the top point
    char title[64];                                              // Buffer for the panel title
    snprintf(title, sizeof title, "Execution time vs threads (N = %.0f)", (double)N); // Title with N
    svg_axes(f, ox1, oy, th, n, title, "Average execution time (s)");                // Draw frame and axes
    for (int k = 0; k <= 5; k++) {          // Six y-axis ticks (0 .. tmax)
        double v = tmax * k / 5, y = py(v, 0, tmax, oy);         // Tick value and its pixel position
        fprintf(f, "<line x1='%d' y1='%.1f' x2='%d' y2='%.1f' stroke='#ddd'/>\n", ox1, y, ox1 + PW, y); // Grid line
        fprintf(f, "<text x='%d' y='%.1f' font-size='12' text-anchor='end'>%.3f</text>\n", ox1 - 6, y + 4, v); // Label
    }
    svg_line(f, avg, n, ox1, oy, 0, tmax, "#2a6fdb", 0, 0);      // Plot the average times (blue)
    for (int i = 0; i < n; i++)                                  // Write the time value above each point
        fprintf(f, "<text x='%.1f' y='%.1f' font-size='11' text-anchor='middle'>%.4fs</text>\n",
                px(i, n, ox1), py(avg[i], 0, tmax, oy) - 10, avg[i]);

    /* ---- right panel: speedup (log2 left axis) + efficiency (right axis) ---- */
    int ox2 = ox1 + PW + 140;                                    // Left edge of the right plot area
    double smax = log2d(th[n - 1]);         // Speedup axis runs 1 .. max threads (in log2)
    double lsp[16], lid[16];                                     // log2 of measured and ideal speedup
    for (int i = 0; i < n; i++) {
        lsp[i] = log2d(spd[i]);                                  // Measured speedup on log2 scale
        lid[i] = log2d(th[i]);                                   // Ideal speedup (= threads) on log2 scale
    }
    svg_axes(f, ox2, oy, th, n, "Speedup and parallel efficiency", "Speedup"); // Draw frame and axes
    for (int i = 0; i < n; i++) {           // Left ticks: 1,2,4,8,16
        double y = py(log2d(th[i]), 0, smax, oy);                // Pixel position of the tick
        fprintf(f, "<line x1='%d' y1='%.1f' x2='%d' y2='%.1f' stroke='#ddd'/>\n", ox2, y, ox2 + PW, y); // Grid line
        fprintf(f, "<text x='%d' y='%.1f' font-size='12' text-anchor='end'>%d</text>\n", ox2 - 6, y + 4, th[i]); // Label
    }
    for (int k = 0; k <= 5; k++) {          // Right ticks: efficiency 0.0 .. 1.0
        double v = k * 0.2, y = py(v, 0, 1.1, oy);               // Tick value and pixel position
        fprintf(f, "<text x='%d' y='%.1f' font-size='12' fill='#e07b00'>%.1f</text>\n", ox2 + PW + 6, y + 4, v); // Label
    }
    // Right-axis title (orange, rotated)
    fprintf(f, "<text transform='translate(%d,%d) rotate(90)' font-size='13' text-anchor='middle' fill='#e07b00'>"
               "Parallel efficiency</text>\n", ox2 + PW + 45, oy + PH / 2);
    svg_line(f, lid, n, ox2, oy, 0, smax, "#888", 1, 0);         // Ideal speedup (grey, dashed)
    svg_line(f, lsp, n, ox2, oy, 0, smax, "#2a6fdb", 0, 0);      // Measured speedup (blue, circles)
    svg_line(f, eff, n, ox2, oy, 0, 1.1, "#e07b00", 0, 1);       // Efficiency (orange, squares)

    /* legend */
    int lx = ox2 + PW - 175, ly = oy + PH / 2 - 30;              // Legend box position
    fprintf(f, "<rect x='%d' y='%d' width='165' height='70' fill='white' stroke='#ccc'/>\n", lx, ly); // Legend box
    // Legend entry: measured speedup
    fprintf(f, "<circle cx='%d' cy='%d' r='5' fill='#2a6fdb'/><text x='%d' y='%d' font-size='12'>Measured speedup</text>\n",
            lx + 15, ly + 16, lx + 30, ly + 20);
    // Legend entry: ideal speedup
    fprintf(f, "<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='#888' stroke-width='2.5' stroke-dasharray='6,4'/>"
               "<text x='%d' y='%d' font-size='12'>Ideal speedup</text>\n",
            lx + 5, ly + 36, lx + 25, ly + 36, lx + 30, ly + 40);
    // Legend entry: efficiency
    fprintf(f, "<rect x='%d' y='%d' width='9' height='9' fill='#e07b00'/><text x='%d' y='%d' font-size='12'>Efficiency</text>\n",
            lx + 10, ly + 51, lx + 30, ly + 60);

    fprintf(f, "</svg>\n");                                      // Close the SVG document
    fclose(f);                                                   // Close the file
}

/* ================= MODE 1: benchmark ================= */
static void run_bench(int repeats)
{
    int counts[] = {1, 2, 4, 8, 16};                             // Thread counts to test
    int nc = sizeof(counts) / sizeof(counts[0]);                 // Number of thread counts (5)
    double avg[16], spd[16], eff_arr[16];                        // Average time, speedup, efficiency per count

    double ts = now_sec();                                       // Start timing the sequential version
    unsigned char smin = sequential_min();                       // Correct answer from one thread
    double seq_time = now_sec() - ts;                            // Sequential time

    // Print run information
    printf("Array size N = %llu (%.2f GB), repeats = %d, online CPUs = %ld\n",
           (unsigned long long)N, N / 1073741824.0, repeats, cpu_count());
    printf("Sequential min = %u  (time %.6f s)\n\n", smin, seq_time);
    // Print the table header
    printf("%-8s %-10s %-12s %-10s %-10s %s\n",
           "Threads", "ParMin", "AvgTime(s)", "Speedup", "Effic.", "Correct");

    FILE *csv = fopen("results.csv", "w");                       // Open the CSV results file
    fprintf(csv, "threads,avg_time,speedup,efficiency,runs\n");  // CSV header line

    for (int c = 0; c < nc; c++) {                               // For each thread count
        int T = counts[c];                                       // Current number of threads
        double sum = 0, runs[32];                                // Sum of times and each individual time
        unsigned char pmin = 0;                                  // Parallel minimum result
        for (int r = 0; r < repeats; r++) {                      // Repeat the measurement
            pmin = parallel_min(T, &runs[r]);                    // Run with T threads and record time
            sum += runs[r];                                      // Accumulate the time
        }
        avg[c] = sum / repeats;                                  // Average time for T threads
        double speedup = avg[0] / avg[c];                        // Speedup relative to 1 thread
        double eff = speedup / T;                                // Parallel efficiency = speedup / threads
        spd[c] = speedup;                                        // Store for the graph
        eff_arr[c] = eff;                                        // Store for the graph
        // Print one row of the table; "YES" if the parallel result matches the sequential one
        printf("%-8d %-10u %-12.6f %-10.3f %-10.3f %s\n",
               T, pmin, avg[c], speedup, eff, pmin == smin ? "YES" : "NO");

        fprintf(csv, "%d,%.6f,%.4f,%.4f,", T, avg[c], speedup, eff);   // Write summary columns to CSV
        for (int r = 0; r < repeats; r++)                              // Then every individual run time
            fprintf(csv, "%.6f%s", runs[r], r + 1 < repeats ? ";" : "\n"); // Separated by ';', newline at end
    }
    fclose(csv);                                                 // Close the CSV file
    write_svg("execution_time_plot.svg", counts, avg, spd, eff_arr, nc); // Draw the graph
    printf("\nResults written to results.csv\n");                // Tell the user where results are
    printf("Graph written to execution_time_plot.svg (open it in a web browser)\n");
}

/* ================= MODE 2: join demo ================= */
static void run_join_demo(int T)
{
    verbose = 1;                                                 // Turn on lifecycle messages
    printf("=== JOIN version: main waits for all %d workers ===\n", T);
    printf("main thread pthread_self=%lu\n", tid_to_ulong(pthread_self())); // Print main's thread id
    double el;                                                   // Elapsed time
    unsigned char p = parallel_min(T, &el);                      // Create, join and reduce
    unsigned char s = sequential_min();                          // Sequential answer for checking
    // Compare the parallel and sequential results
    printf("Global min (parallel) = %u, sequential = %u -> %s, time %.6f s\n",
           p, s, p == s ? "CORRECT" : "WRONG", el);
    printf("main: all workers finished, exiting normally.\n");
}

/* ================= MODE 3: no-join demo ================= */
static void run_nojoin_demo(int T)
{
    pthread_t    tid[MAX_THREADS];                               // Thread handles
    static thread_arg_t args[MAX_THREADS];  // static: still valid after this function returns
    verbose = 1;                                                 // Turn on lifecycle messages
    make_segments(args, T);                                      // Divide the array among T threads

    printf("=== NO-JOIN version: main does NOT wait for workers ===\n");
    printf("main thread pthread_self=%lu\n", tid_to_ulong(pthread_self())); // Print main's thread id

    for (int t = 0; t < T; t++) {                                // Create T worker threads
        pthread_create(&tid[t], NULL, worker, &args[t]);         // Start worker t
        pthread_detach(tid[t]);           // Detach it: it will never be joined
    }

    // main immediately "collects" whatever is there right now
    unsigned char gmin = 255;                                    // Global minimum so far
    int finished = 0;                                            // How many workers had finished
    for (int t = 0; t < T; t++) {                                // Look at each worker's struct
        printf("  main: thread %2d done=%d local_min=%u\n",
               t, args[t].done, args[t].local_min);              // Show its current state
        if (args[t].done) { finished++; if (args[t].local_min < gmin) gmin = args[t].local_min; } // Use only finished ones
    }
    // Show that the result is incomplete / wrong
    printf("main: only %d of %d workers had finished; 'global min' = %u (expected %u)\n",
           finished, T, gmin, PLANTED_MIN);
    printf("main: returning from main() now -> process exits, unfinished workers are killed.\n");
    fflush(stdout);                                              // Make sure all output is printed
    // Returning from main calls exit(), terminating all remaining threads
}

/* ================= main ================= */
int main(int argc, char *argv[])
{
    const char *mode = argc > 1 ? argv[1] : "bench";             // Mode from argv[1]; default "bench"
    int  repeats = DEFAULT_REPEATS, T = 4;                       // Default repeats and thread count
    unsigned long long n_req = DEFAULT_N;                        // Default array size

    if (strcmp(mode, "bench") == 0) {                            // bench [N] [REPEATS]
        if (argc > 2) n_req = strtoull(argv[2], NULL, 10);       // Read N
        if (argc > 3) repeats = atoi(argv[3]);                   // Read REPEATS
        if (repeats < 1 || repeats > 32) repeats = DEFAULT_REPEATS; // Keep REPEATS in range
    } else {                                                     // join / nojoin [T] [N]
        if (argc > 2) T = atoi(argv[2]);                         // Read T
        if (argc > 3) n_req = strtoull(argv[3], NULL, 10);       // Read N
        if (T < 1 || T > MAX_THREADS) T = 4;                     // Keep T in range
    }
    if (n_req < 10000000ULL) {                                   // Assignment requires N >= 10^7
        fprintf(stderr, "N must be at least 10^7\n");
        return 1;
    }
    if (n_req > (unsigned long long)SIZE_MAX) {                  // N too large for a 32-bit build
        fprintf(stderr, "N = %llu is too big for this %d-bit program.\n"
                        "Compile with a 64-bit compiler (MSYS2 MinGW-w64 or WSL/Linux).\n",
                n_req, (int)(sizeof(size_t) * 8));
        return 1;
    }
    N = (size_t)n_req;                                           // Store N in the shared variable

    printf("Allocating %.2f GB ...\n", N / 1073741824.0);        // Report allocation size
    fflush(stdout);                                              // Print it before the slow malloc
    arr = malloc(N);                                             // Allocate N bytes (1 byte per element)
    if (!arr) {                                                  // malloc failed: not enough memory
        fprintf(stderr, "malloc failed: not enough free memory for %.2f GB.\n"
                        "Try a smaller size, e.g.  ./A1_05_ASN-6 bench 2000000000\n", N / 1073741824.0);
        return 1;
    }
    printf("Filling array ...\n");                               // Report initialisation
    fflush(stdout);                                              // Print it before the slow fill
    init_array(N);                                               // Fill the array and plant the minimum

    if      (strcmp(mode, "bench")  == 0) run_bench(repeats);    // Mode 1: timing experiment
    else if (strcmp(mode, "join")   == 0) run_join_demo(T);      // Mode 2: join demo
    else if (strcmp(mode, "nojoin") == 0) { run_nojoin_demo(T); return 0; } // Mode 3: exit without joining
    else { fprintf(stderr, "unknown mode %s\n", mode); return 1; }          // Unknown mode

    free(arr);                                                   // Release the array memory
    return 0;                                                    // Successful execution
}
