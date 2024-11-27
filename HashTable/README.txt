HashTable Project - OpenMP Compilation and Execution

Prerequisites:
Ensure you have access to the CIMS machines at NYU.
OpenMP-enabled compiler installed (g++ supporting -fopenmp flag).
Required files and directories are stored locally in /localdirectory.

Steps to Compile and Execute
Step 1: Transfer Files to CIMS
Open your terminal.
Use the following command to securely copy the HashTable directory to the CIMS server:
scp -r /localdirectory/HashTable username@access.cims.nyu.edu:/home/username/

Step 2: SSH into CIMS
Connect to the CIMS server:
ssh username@access.cims.nyu.edu
From the CIMS server, connect to the crunchy1 machine:
ssh username@crunchy1.cims.nyu.edu

Step 3: Navigate to the Project Directory
Change to the HashTable directory:
cd HashTable

Step 4: Compile the Source Code
Compile the input program:
g++ -Wall -std=c++17 -fopenmp -o input input.cpp
Compile the segmented hash table implementation:
g++ -Wall -std=c++17 -fopenmp -o segmented_test ExecutorLinkedListSegmented.cpp
Compile the naive hash table implementation:
g++ -Wall -std=c++17 -fopenmp -o naive_test ExecutorLinkedListNaive.cpp

Step 5: Run the Executables
Execute the naive hash table test:
./naive_test --capacity 10 < input.txt
Execute the segmented hash table test:
./segmented_test --capacity 10 --segmentsize 10 < input.txt

Step 6: Performance Testing
Measure execution time for the naive hash table:
time ./naive_test --capacity 1 < I50000S500000.txt
Measure execution time for the segmented hash table:
time ./segmented_test --capacity 1 --segmentsize 2 < I50000S500000.txt
Notes
Ensure that, as an example: input.txt and I50000S500000.txt are present in the same directory as the compiled executables.
Use appropriate --capacity and --segmentsize values based on your testing requirements.

