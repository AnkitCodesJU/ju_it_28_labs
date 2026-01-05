


# DSA Lab Guidelines (Palash Kundu & Dr. Bhaskar Sardar)
### *Author: Ankit Roy, IT 28*

---

## Rule 1 — Always take input from the user
* **No hardcoded values.**
* Every program must use `scanf()` for inputs and print using `printf()`.

---

## Rule 2 — All programs in pure C
* **No C++ features.**
* Stick to standard C functions and headers only.

---

## Rule 3 — Your enemy: The ancient GCC in SSH
You will be coding in a remote SSH terminal with a **prehistoric GCC version**.

**That means:**
* Declare variables at the **top** of the function.
* Do not declare inside loops:
```c
int i;
for(i = 0; i < n; i++)
````

*(C99-style declarations inside for-loops may NOT work.)*

**Modern C features may fail.**
Keep your code old-school and portable.

-----

## Rule 4 — Compiling with math.h

If your program uses math functions:

```bash
gcc prog.c -lm
```

Otherwise:

```bash
gcc prog.c
```

Run it with:

```bash
./a.out
```

-----

## Rule 5 — Chill environment (but don’t get lazy)

  * Nobody will deeply inspect your code...
  * ...but still **prepare for the worst-case viva questions**.
  * Write clean, understandable programs.
  * **Stick to basics.**
  * Don't get caught cheating in class else you and your batch is dead

<!-- end list -->

