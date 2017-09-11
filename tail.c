// Jia Sen Wu
// jw3675 | N17190076
// CS 3224-B

#include "types.h" // Define standard data type
#include "user.h" // Declare common functions

void tail(int file) {
  printf(1, "This is supposed to read the file\n");
}

// argc is number of words inputted in terminal
// argv is the array of the words themselves
int main(int argc, char *argv[]) {
  int file;

  if(argc == 1) { // Can argc even be 0 with this kind of function?
    printf(1, "Tail is the only existing thing\n");
    tail(0);
    exit(); // Basically break
  }

  // Maybe you want to tail multiple files. i = 0 to start after tail command
  for(int i = 1; i < argc; i++){ 
    if((file = open(argv[i], 0)) < 0){
      printf(1, "%s: '%s' does not exist\n", argv[0], argv[i]);
    } else {
      tail(file);
    }
    close(file);
  }

  exit();
}
