# multicore_final

## InputGenerator

**InputGenerator** is a C++ program designed to generate randomized input files for testing purposes. It creates a text file containing a specified number of lines, each formatted according to specific rules involving uppercase letters and random integers. This tool is particularly useful for developers who need to generate test cases for algorithms or data processing applications.

### Features

- **Customizable Line Count:** Specify the number of lines (`N`) to generate.
- **Random Integers Range:** Define the maximum value (`M`) for the random integers.
- **Letter Proportions:** Control the proportions of lines starting with specific uppercase letters (`I`, `R`, `U`, `S`).
- **Flexible Input Methods:** Accepts command-line arguments or interactive input via standard input.
- **Dynamic Filename Generation:** Generates filenames reflecting the parameters used for easy identification.

### Usage

#### Command-Line Arguments

The program accepts the following command-line arguments:

- `-n [positive integer]`: Specifies the number of lines (`N`) to generate.
- `-m [positive integer]`: Sets the maximum value (`M`) for the random integers (range from `0` to `M`).
- `-i [0-100]`: Percentage of lines starting with the letter `I`.
- `-r [0-100]`: Percentage of lines starting with the letter `R`.
- `-u [0-100]`: Percentage of lines starting with the letter `U`.
- `-s [0-100]`: Percentage of lines starting with the letter `S`.

**Note:** The sum of the specified percentages (`-i`, `-r`, `-u`, `-s`) cannot exceed 100. If the total is less than 100, the remaining percentage is distributed equally among the unspecified letters.

#### Interactive Input

If no command-line arguments are provided, the program will prompt you to enter the values for `N` and `M` via standard input.

#### Example Commands

1. **Generate a file with 10 lines, random integers up to 100:**

   ```bash
   ./InputGenerator -n 10 -m 100
   ```

2. **Generate a file where all lines start with `I`:**

   ```bash
   ./InputGenerator -n 10 -m 100 -i 100
   ```

3. **Generate a file with specific letter proportions:**

   ```bash
   ./InputGenerator -n 20 -m 50 -i 25 -r 25 -u 25 -s 25
   ```

4. **Generate a file with partial letter proportions:**

   ```bash
   ./InputGenerator -n 15 -m 80 -i 10 -u 20
   ```

   In this case, lines starting with `I` will make up 10%, `U` will make up 20%, and the remaining 70% will be distributed equally between `R` and `S`.

### Output Format

The program generates a text file named based on the provided parameters. The filename follows this pattern:

```
N{N}M{M}[I{percent_i}][R{percent_r}][U{percent_u}][S{percent_s}].txt
```

- **N{N}**: The total number of lines.
- **M{M}**: The maximum random integer value.
- **I{percent_i}**, **R{percent_r}**, **U{percent_u}**, **S{percent_s}**: Included only if the corresponding percentage parameter is specified.

**Example Filenames:**

- `N10M100.txt`
- `N10M100I100.txt`
- `N15M80I10U20.txt`

#### File Content Structure

- The first line contains the number `N`.
- The next `N` lines follow this format:
  - Each line starts with an uppercase letter (`I`, `R`, `U`, or `S`), followed by one or two integers.
  - If the letter is `I` or `U`, it is followed by two identical integers between `0` and `M`.
  - If the letter is `R` or `S`, it is followed by one integer between `0` and `M`.

**Sample Output File:**

```
6
I 17 17
R 56
U 72 72
S 44
I 19 19
S 32
```

