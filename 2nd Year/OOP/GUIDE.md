
# OOP Guidelines for Uttam Sir’s Class

---

## Rule 1 — No static arrays
**Don’t write:**
```cpp
int arr[] = {1,2,3};
````

**Always use dynamic memory:**

```cpp
int* arr = new int[5];
arr[0] = 1;
arr[1] = 6;
```
Refer to a1q16.cpp for more examples
-----

## Rule 2 — Use const whenever possible

Sir expects max usage of `const` in:

  * parameters
  * return types
  * member functions

-----

## Rule 3 — Use char\* for strings

Instead of `string`, declare and allocate manually:

```cpp
char* title = new char[50];
```

-----

## Rule 4 — Know your code

  * If you write it, **understand it**.
  * Sir checks concepts, not typing speed.

-----

## Rule 5 — Design matters more than implementation

Sir expects good class design:

  * Use proper constructors
  * Think of missing functions
  * Justify why each function exists

**Example:**
Even if the question doesn't ask, he may expect functions like:
`setReal()`, `setImag()`, etc.

-----

## Summary

Follow these **5 rules** and your OOP design will easily meet Sir’s expectations.

```

Would you like me to generate a sample C++ class code that follows all these rules (using `char*`, `const`, and dynamic memory)?
```

Remeber to listen to sir .He is very knowledgible and u will know a lot from him trust me.Don't argue with him unless you want to fail.
He never told us to complete all the question but always stressed on doing 1 prog per day if it need but create a 100% good code.
 
**Author :**  Ankit Roy, IT 28