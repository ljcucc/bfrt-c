#include <stdio.h>
#include <stdlib.h>

#define MEM_LEN 3000

struct memorys {
  uint8_t* list;
  unsigned pointer;
};

struct memorys mem;

void initMemory(){
  mem.list = malloc(MEM_LEN* ( sizeof (uint8_t)) ); // alloc new memory
  mem.pointer = 0;
}

long fsize(FILE* f){
  long size;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  
  return size;
}

void readout(char* codes, FILE* file){
  char c;
  while((c = getc(file)) != EOF)
    codes[ftell(file)-1] = c;

  printf("%s\n", codes);
}

void changeValue(uint8_t value){
  mem.list[mem.pointer]+=value;
}

void changePointer(unsigned int value){
  mem.pointer += value;
}

long execute(char* codes, unsigned int index, long limit){
  while(index < limit){
    char cur = codes[index++];

    switch(cur){
      case '+':
        changeValue(1);
        break;
      case '-':
        changeValue(-1);
        break;
      case '<':
        changePointer(-1);
        break;
      case '>':
        changePointer(1);
        break;
      case '[':
        {
          long result = index;

          while(result < limit && mem.list[mem.pointer] != 0){
            result = execute(codes, index, limit);
            // printf("end of a loop \n");
          }
          index = result;
          // printf("exit a loop %c\n", codes[index]);
        }
        break;
      case ']':
        return index;
        break;
      case ',':
        break;
      case '.':
        // printf("value is %d\n", mem.list[mem.pointer]);
        putchar(mem.list[mem.pointer]);
        break;
    }
  }

  printf("end of scope %u\n", index);

  return index;
}

int main(int argc, char** argv){

  printf("reading file...\n");

  FILE* script = fopen(argv[1], "r");

  if(!script){
    printf("file is not exist!\n");
    return 1;
  }

  long size = fsize(script);
  char* codes = (char*) malloc(size * sizeof(char));
  printf("size: %ld\n", sizeof(codes)/sizeof(char));
  printf("size: %ld\n", sizeof(codes)/sizeof(char));

  readout(codes, script);
  initMemory();
  execute(codes, 0, size);

  return 0;
}
