# Page Replacement Simulator (FIFO and OPT)

An operating systems project by [Nathan Chiamsachang](https://github.com/nchiamsachang) and [Trey Rajsombath](https://github.com/TreyRajsombath), written in C++.

The program reads a page reference string from a text file, simulates a page replacement algorithm on it, prints the frame table, and reports the total number of page faults. It supports two algorithms:

- **FIFO** (first in, first out): replaces the page that has been in memory the longest.
- **OPT** (optimal): replaces the page that will not be used for the longest time in the future.

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

Open `testing os.sln` in Visual Studio 2022 and press **Ctrl+F5**, or build from a Developer Command Prompt:

```
msbuild "testing os.sln" /p:Configuration=Release /p:Platform=x64
"x64\Release\testing os.exe"
```

The program asks for the input file name when it starts. Run it from the repository folder so the sample files can be found.

## Sample output

Running the program with `FIFO.txt`:

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

| Input file  | Algorithm | Frames | Reference string                | Page faults |
|-------------|-----------|--------|---------------------------------|-------------|
| `FIFO.txt`  | FIFO      | 4      | `2 3 2 1 5 2 4 5 3 2 5 2`       | 6           |
| `FIFO1.txt` | FIFO      | 4      | `1 2 3 4 1 2 5 1 2 3 4 5`       | 10          |
| `OPT.txt`   | OPT       | 3      | `1 2 1 3 1 4 1 5 1 6 1 7 1 8`   | 8           |
| `OPT1.txt`  | OPT       | 4      | `1 2 3 4 1 2 5 1 2 3 4 5`       | 6           |

`FIFO1.txt` and `OPT1.txt` use the same reference string and the same 4 frames, so they compare the two algorithms directly: FIFO takes 10 page faults and OPT takes 6. OPT is the lower bound, since it uses knowledge of future references that a real operating system does not have.

## Files

| File                    | Purpose                        |
|-------------------------|--------------------------------|
| `Source.cpp`            | The simulator                  |
| `testing os.sln`        | Visual Studio solution         |
| `FIFO.txt`, `FIFO1.txt` | Sample FIFO inputs             |
| `OPT.txt`, `OPT1.txt`   | Sample OPT inputs              |
