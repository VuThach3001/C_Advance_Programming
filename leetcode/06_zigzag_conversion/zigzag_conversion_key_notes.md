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
  - **Diagonal elements** (only for middle rows)
```c
diag = j + cycle - 2*r
```
  - **Condition**:
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
  - This equals the next vertical element
    - causes duplicate
```c
diag = j + cycle
```
- **Bottom row `(r = numRows - 1)`**
  - Also appears once per cycle
  - No diagonal elements
    - same index → duplicate
```c
diag = j
```

##### What “Duplicate” Means
- Duplicate = inserting the same character twice
- Example (row 0):
  - 6 and 12 appear twice → incorrect result
```
Vertical: 0, 6, 12
Diagonal:    6, 12
```

##### Final Rule
```
if (r != 0 && r != numRows - 1)
```

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

#### Time Complexity
- O(n) where n is the length of the input string `s`
- At first glance, it looks like nested loops → O(n²). But that’s misleading.
  - **Key Insight:** Each character is processed once
#### Space Complexity
- O(n) for the output string `result`
- O(1) additional space for variables

---

### Summary Section (Summary of Notes)

- The zigzag conversion can be efficiently implemented by iterating row by row and calculating indices using a cycle length.
- Middle rows have both vertical and diagonal elements, while the top and bottom rows only have vertical elements.
- The algorithm has a time complexity of O(n) and a space complexity of O(n) for the output string, with O(1) additional space for variables.
