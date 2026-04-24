# Cornell Notes

## Topic: Zigzag Conversion  

## Date: 24/04/2026

---

### Cue Column (Questions, Keywords, or Prompts)

- What is the zigzag conversion pattern?
- How is the cycle length calculated?
- How are characters placed in each row?

---

### Notes Section (Main Notes)

#### Core Idea
- The zigzag pattern repeats every:
```c
cycle = 2 * numRows - 2
```
- Instead of building a 2D matrix, we:
  - Iterate row by row
  - Pick indices using math

##### Row-wise Index Pattern
- For each row r:
  - **Vertical elements**:
```c
for (int j = r; j < len; j += cycle)
```
##### Diagonal elements (only for middle rows)
```c
diag = j + cycle - 2*r
```
  - Condition:
```c
if (r != 0 && r != numRows - 1 && diag < len)
```
##### Why Diagonal Only Applies to Middle Rows
- **Middle rows:**
  - Appear twice per cycle:
    - once going down
    - once going up (diagonal)
- So we need:
    - vertical index
    - diagonal index
- **Top row `(r = 0)`**
  - Only appears once per cycle
  - No diagonal elements
```c
diag = j + cycle
```
  - This equals the next vertical element
-> causes duplicate
- **Bottom row `(r = numRows - 1)`**
  - Also appears once per cycle
  - No diagonal elements
```c
diag = j
```
  -> same index → duplicate

##### Full Optimal Solution:
```c
char* convert(char* s, int numRows) {
    if (numRows == 1) return s;

    int len = strlen(s);
    char* result = (char*) malloc(len + 1);
    int pos = 0;

    int cycle = 2 * numRows - 2;

    for (int r = 0; r < numRows; r++) {
        for (int j = r; j < len; j += cycle) {
            result[pos++] = s[j];

            int diag = j + cycle - 2*r;
            if (r != 0 && r != numRows - 1 && diag < len) {
                result[pos++] = s[diag];
            }
        }
    }

    result[pos] = '\0';
    return result;
}
```

#### Why result[pos] = '\0' is Safe
- We allocate:
```c
char* result = (char*) malloc(len + 1);
```
- The `+1` ensures there is space for the null terminator `\0`.
- **Memory layout:**
```
[result[0] ... result[len-1]] → characters
[result[len]]                → '\0'
```

- **Key invariant:**
```c
pos == len
```
- Because:
- Each character is inserted exactly once
- No duplicates
- No missing elements

---

### Summary Section (Summary of Notes)

[Insert a brief summary of the key ideas and takeaways]
