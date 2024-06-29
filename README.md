# Quine-McCluskey Algorithm Implementation

## Overview
This program implements the Quine-McCluskey algorithm to minimize Boolean expressions from given minterms.

## Example Usage

### Input:
```plaintext
Enter the number of bits: 4
Enter the number of MinTerms: 8
Enter MinTerm: 0
Enter MinTerm: 1
Enter MinTerm: 2
Enter MinTerm: 8
Enter MinTerm: 10
Enter MinTerm: 11
Enter MinTerm: 14
Enter MinTerm: 15

Minimized Boolean Expression:
A'B'C' + B'D' + AC

## Flow of the Program

### Input Collection
- Prompt the user to enter the number of bits for the Boolean variables.
- Prompt the user to enter the number of minterms.
- Collect each minterm from the user.

### Initialization
- Initialize necessary data structures:
  - `minTermsBits`: Stores minterms in binary form.
  - `minTermsStr`: Stores minterms as strings.
  - `implicantsBits`: Stores implicants in binary form.
  - `implicants`: Stores implicants as strings.
  - `track`: Tracks implicants in the table.
  - `essentialImplicantsBits`: Stores essential implicants in binary form.
  - `dominatingRowsBits`: Stores dominating rows in binary form.
  - `minTermOccurred`: Map to track occurrence of minterms.

### Conversion Functions
- `ConvertToBits(int minTerm)`: Converts an integer minterm to its binary representation as a string.
- `ConvertToString(int num)`: Converts an integer to its string representation.

### Helper Functions
- `OneBitDifference(string s1, string s2)`: Checks if two binary strings differ by exactly one bit.
- `EditString(string s1, string s2)`: Creates a new string where differing bits between `s1` and `s2` are replaced with '-'.

### Table Construction
- `CreateTable(int start)`: Constructs the prime implicant table:
  - Iteratively compares each pair of minterms to find those differing by a single bit.
  - Generates new minterms by combining pairs and checks for uniqueness using `minTermOccurred`.

### Prime Implicant Table
- `ImplicantTable()`: Populates the prime implicant table:
  - Uses the table generated by `CreateTable()` to mark implicants covering each minterm.

### Finding Essential Implicants
- `FindEssentialImplicants()`: Identifies essential prime implicants:
  - Analyzes the table to find implicants covering only one minterm.
  - Marks these implicants as essential and removes covered minterms from the table.

### Removing Dominating Rows
- `RemoveDominatingRows()`: Eliminates redundant implicants:
  - Identifies and removes implicants dominated by others based on covered minterms.

### Output
- `PrintResult(int numBits)`: Prints the minimized Boolean expression:
  - Converts essential implicants back to Boolean terms and prints the minimized expression.

### Execution
- `main()`: Controls the flow of the program:
  - Reads input, initializes data structures, executes the Quine-McCluskey algorithm, and prints the minimized Boolean expression.
 

