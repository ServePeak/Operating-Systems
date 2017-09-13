// Jia Sen Wu
// jw3675 | N17190076
// CS 3224-B

#include "types.h" // Define standard data type
#include "user.h" // Declare common functions

// Realloc specifically for character pointers
char * realloc(char * ptr, int old_size, int new_size) {
  char * new = malloc(new_size);
  memmove(new, ptr, old_size);
  free(ptr); // No memory leaks please
  return new;
}

// Tail works by reading buffer into a larger buffer of characters, which 
// dynamically allocates until the entire file is read. Then it parses for
// number of last lines wanted.
void tail(int file, int lines) {
  char buf[512];
  char * store = (char*) malloc(0); // Initialize store buffer to 0
  int store_size = 0;

  int fchar;
  
  while((fchar = read(file, buf, sizeof(buf))) > 0) { // Buffer by buffer
    store = realloc(store, store_size, store_size+fchar);
    memmove(store+store_size, buf, fchar); // Move reading buffer into new area
    store_size += fchar;
  }

  // Read the file backwards to save time (Doesn't change Big O)
  int line_count = 0;
  int i = store_size-1;

  for(; i >= 0; --i) {
    if(store[i] == '\n')
      line_count++;
    if(line_count == lines+1) { // Reading backwards starts with an extra line
      i++; // Don't read the new line or there'll be a blank space
      break;
    }
  }
  for(; i < store_size; ++i)
    printf(1, "%c", store[i]);
}

// argc is number of words inputted in terminal
// argv is the array of the words themselves
int main(int argc, char *argv[]) {
  int file;

  
  if(argc == 1) { // Can argc even be 0 with this kind of function?
    tail(0, 10);
    exit(); // Break but exits the function
  }

  // Reads a certain number of lines for a single file
  if(argc == 3 && argv[1][0] == '-') {
    if((file = open(argv[2], 0)) < 0) {
      printf(1, "%s: '%s' does not exist\n", argv[0], argv[2]);
    } else {
      // Remove the dash
      char num[strlen(argv[1])-1];
      for(int i = 0; i < strlen(argv[1])-1; i++)
        num[i] = argv[1][i+1];

      tail(file, atoi(num));
    }
    close(file);
    exit();
  }

  // Maybe you want to tail multiple files. i = 0 to start after tail command
  for(int i = 1; i < argc; i++) { 
    if((file = open(argv[i], 0)) < 0) {
      printf(1, "%s: '%s' does not exist\n", argv[0], argv[i]);
    } else {
      tail(file, 10);
    }
    close(file);
  }

  exit();
}
