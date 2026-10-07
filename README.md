# Page Replacement Simulator (FIFO and OPT)

An operating systems project by Nathan Chiamsachang and Trey Rajsombath.

The program reads a page reference string from a text file, simulates a page replacement algorithm on it, prints the frame table, and reports the total number of page faults. It supports two algorithms:

- **FIFO** (first in, first out): replaces the page that has been in memory the longest.
- **OPT** (optimal): replaces the page that will not be used for the longest time in the future.

The simulator is written twice, once in C++ (`Source.cpp`) and once in Python (`page_replacement.py`), so the two can be compared on the same inputs.

## Input format

Each input file is one line of comma-separated values:

```
<algorithm>,<number of frames>,<page>,<page>,<page>,...
```

- `<algorithm>` is `F` for FIFO or `O` for OPT.
- `<number of frames>` is how many frames of memory are available.
- The remaining numbers are the page reference string.

For example, `FIFO.txt` contains:

```
F,4,2,3,2,1,5,2,4,5,3,2,5,2
```

This means FIFO with 4 frames and the reference string `2 3 2 1 5 2 4 5 3 2 5 2`.

A line can hold up to 100 numbers.

## How to run

Both versions ask for the input file name when they start. Run them from the repository folder so the sample files can be found.

### C++

Open `testing os.sln` in Visual Studio 2022 and press **Ctrl+F5**, or build from a Developer Command Prompt:

```
msbuild "testing os.sln" /p:Configuration=Release /p:Platform=x64
"x64\Release\testing os.exe"
```

### Python

Requires Python 3. No extra packages are needed.

```
python page_replacement.py
```

## Sample output

Running either version with `FIFO.txt`:

```
Enter the input file name: FIFO.txt

=== FIFO Page Replacement ===
Number of frames: 4

Reference String:       2       3       2       1       5       2       4       5       3       2       5       2
----------------------------------------------------------------------------------------------------
Frame 1:                2       2               2       2               4                       4
Frame 2:                        3               3       3               3                       2
Frame 3:                                        1       1               1                       1
Frame 4:                                                5               5                       5

Total page faults: 6
```

Each column is one step of the reference string. A column is filled in only when that step caused a page fault; a blank column means the page was already in memory.

## Test results

The four sample files were run through both versions.

| Input file  | Algorithm | Frames | Reference string                | Page faults (C++) | Page faults (Python) |
|-------------|-----------|--------|---------------------------------|-------------------|----------------------|
| `FIFO.txt`  | FIFO      | 4      | `2 3 2 1 5 2 4 5 3 2 5 2`       | 6                 | 6                    |
| `FIFO1.txt` | FIFO      | 4      | `1 2 3 4 1 2 5 1 2 3 4 5`       | 10                | 10                   |
| `OPT.txt`   | OPT       | 3      | `1 2 1 3 1 4 1 5 1 6 1 7 1 8`   | 8                 | 8                    |
| `OPT1.txt`  | OPT       | 4      | `1 2 3 4 1 2 5 1 2 3 4 5`       | 6                 | 6                    |

The full output of the C++ and Python versions, including the frame tables, is identical for every file.

### FIFO compared with OPT

`FIFO1.txt` and `OPT1.txt` use the same reference string and the same 4 frames, so they compare the two algorithms directly: FIFO takes 10 page faults and OPT takes 6. OPT is the lower bound, since it uses knowledge of future references that a real operating system does not have.

### C++ compared with Python

| Version | Average time per run |
|---------|----------------------|
| C++     | about 0.11 seconds   |
| Python  | about 0.58 seconds   |

These are averages over 50 runs of `OPT.txt` on Windows 11, measured from launching the program to its exit. The inputs are very small, so nearly all of this time is the program starting up (for Python, loading the interpreter) rather than the algorithm itself.

## Files

| File                  | Purpose                                  |
|-----------------------|------------------------------------------|
| `Source.cpp`          | C++ version of the simulator             |
| `page_replacement.py` | Python version of the simulator          |
| `testing os.sln`      | Visual Studio solution for the C++ build |
| `FIFO.txt`, `FIFO1.txt` | Sample FIFO inputs                     |
| `OPT.txt`, `OPT1.txt`   | Sample OPT inputs                      |
