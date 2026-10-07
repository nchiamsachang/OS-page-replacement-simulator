#Nathan Chiamsachang
#Trey Rajsombath
# Python version of Source.cpp, kept the same so the two can be compared
import sys


# checks if a page is already in a frame
def is_in_frames(frames, page):
    for f in frames:
        if f == page:
            return True
    return False


# prints the ref string, dashed line, and the table row by row
def print_table(ref, num_frames, history, fault_history):
    # print the ref string across the top
    out = "Reference String:\t"
    for page in ref:
        out += str(page) + "\t"
    print(out)

    # print a dashed line
    print("----" + "--------" * len(ref))

    for row in range(num_frames):
        out = "Frame " + str(row + 1) + ":\t\t"
        for col in range(len(ref)):  # each column is one step
            if not fault_history[col]:  # no fault so print blank
                out += "\t"
            elif history[col][row] == -1:  # frame is empty
                out += "\t"
            else:
                out += str(history[col][row]) + "\t"  # else print the page in frame
        print(out)


# FIFO page replacement algorithm
def fifo(ref, num_frames):
    frames = [-1] * num_frames  # set all frames to empty
    faults = 0  # fault count
    oldest = 0  # track which frame to replace next

    # store each columns frame state for printing row by row
    history = []
    fault_history = []

    for page in ref:  # go through each page in ref string
        if is_in_frames(frames, page):
            fault_history.append(False)
        else:  # page fault
            frames[oldest] = page
            oldest = (oldest + 1) % num_frames  # move to next spot in order
            faults += 1
            fault_history.append(True)

        history.append(frames[:])  # save current frame state

    print_table(ref, num_frames, history, fault_history)
    return faults


# OPT page replacement algorithm
def opt(ref, num_frames):
    frames = [-1] * num_frames  # set all frames to empty
    faults = 0  # fault count
    count = 0

    # store history for printing later
    history = []
    fault_history = []

    for i in range(len(ref)):
        if is_in_frames(frames, ref[i]):
            fault_history.append(False)
        else:  # page fault
            if count < num_frames:  # empty frame available
                frames[count] = ref[i]
                count += 1
            else:  # all frames full, need to replace
                farthest = -1
                replace_index = 0

                for j in range(num_frames):
                    next_use = -1

                    for k in range(i + 1, len(ref)):  # look ahead
                        if frames[j] == ref[k]:
                            next_use = k
                            break

                    if next_use == -1:  # never used again
                        replace_index = j
                        break

                    if next_use > farthest:  # this page is used farther in future
                        farthest = next_use
                        replace_index = j

                frames[replace_index] = ref[i]  # replace chosen frame
            faults += 1
            fault_history.append(True)

        history.append(frames[:])

    print_table(ref, num_frames, history, fault_history)
    return faults


def main():
    print("Enter the input file name: ", end="", flush=True)
    filename = sys.stdin.readline().split()[0]

    try:
        infile = open(filename)
    except OSError:
        print("Error: could not open file " + filename)
        return 1

    line = infile.readline().rstrip("\r\n")
    infile.close()

    algo = line[0]

    # parse the numbers after the first comma
    numbers = []
    pos = 2  # start after the first char and comma

    while pos < len(line):
        num = 0  # build number digit by digit
        found_digit = False

        while pos < len(line) and "0" <= line[pos] <= "9":  # read digit
            num = num * 10 + int(line[pos])
            pos += 1
            found_digit = True

        if found_digit:
            numbers.append(num)

        pos += 1

    num_frames = numbers[0]
    ref = numbers[1:]

    # checks ref string for FIFO
    if algo == "F" or algo == "f":
        print("\n=== FIFO Page Replacement ===")
        print("Number of frames: " + str(num_frames) + "\n")
        faults = fifo(ref, num_frames)
    # check ref string for OPT
    elif algo == "O" or algo == "o":
        print("\n=== OPT Page Replacement ===")
        print("Number of frames: " + str(num_frames) + "\n")
        faults = opt(ref, num_frames)
    # if nothing return
    else:
        print("Unknown algorithm type: " + algo)
        return 1

    # print page fault
    print("\nTotal page faults: " + str(faults))
    return 0


if __name__ == "__main__":
    sys.exit(main())
