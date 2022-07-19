#include "editor.h"
#include <stdio.h>
#include <string.h>

/**
  TASK ONE
*/
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos){
    if(pos >= editing_buflen || pos < 0){return 0;}   // invalid position entered

    for(int i = editing_buflen - 1; i > pos; i--){    // moves the chars after pos right by one index
      editing_buffer[i] = editing_buffer[i-1];
    }

    editing_buffer[pos] = to_insert;
    return 1;
}

// -----------------------------------------------------------------------------
/**
  TASK 2:
*/
int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset){
  if(offset >= editing_buflen || offset < 0){return 0;}   // invalid position entered

  int char_deleted = 0;

  for(int i = offset; i < editing_buflen - 1; i++){
    if(editing_buffer[i] == to_delete){
      char_deleted = 1;
      for(int x = i; x < editing_buflen - 1; x++){
        editing_buffer[x] = editing_buffer[x+1];
      }
      editing_buffer[editing_buflen - 1] = '\0';
    }
  }

  return char_deleted;
}



// -----------------------------------------------------------------------------
// Task Three:

/**
  Moves all of the characters after 'offset' to the left one position
*/
void move_left(char editing_buffer[], int editing_buflen, int offset){
  for(int i = offset; i < editing_buflen - 1; i++){
    editing_buffer[i] = editing_buffer[i + 1];
  }
  editing_buffer[editing_buflen - 1] = '\0';
}

/**
  Moves all of the characters after 'offset' to the right one position
*/
void move_right(char editing_buffer[], int editing_buflen, int offset){
  for(int i = editing_buflen - 1; i > offset; i--){
    editing_buffer[i] = editing_buffer[i-1];
  }
}

/**
  TASK THREE
*/
int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset){
  if(strlen(str) == 0){return -1;} // if str is empty
  if(offset >= editing_buflen || offset < 0){return -1;}   // invalid position entered

  int last_index = -1;

  for(int i = offset; i < editing_buflen; i++){
    if(editing_buffer[i] == str[0]){ // if str's first letter is found in array
      int word_found = 1;

      for(int j = i; j < i + strlen(str); j++){
        if(editing_buffer[j] != str[j-i]){
          word_found = 0;
          break;
        }

      }
      if(word_found){
        if(strlen(str) > strlen(replacement)){   // need to move all char after str to the left
          int strlen_diff = strlen(str) - strlen(replacement);
          int shift_index = i + strlen(replacement);
          for(int x = 0; x < strlen_diff; x++){
            move_left(editing_buffer, editing_buflen, shift_index);
          }

        }else if(strlen(str) < strlen(replacement)){    // need to move all char after str to the right
          int strlen_diff = strlen(replacement) - strlen(str);
          int shift_index = i + strlen(str);
          for(int x = 0; x < strlen_diff; x++){
            move_right(editing_buffer, editing_buflen, shift_index);
          }
        }
        for(int y = i; y < i + strlen(replacement); y++){
          editing_buffer[y] = replacement[y-i];
        }
        last_index = i + strlen(replacement) - 1;
        if(last_index > editing_buflen){last_index = editing_buflen-1;}
      }
    }

  }
  return last_index;

}

//------------------------------------------------------------------------------
// TASK FOUR:

/**
  Return the proper new index
*/
int find_new_index(const char editing_buffer[], int curr_index, int editing_buflen){
  int index = curr_index;
  while(editing_buffer[index] != '\n' && index < editing_buflen){
    index++;
  }
  index++;
  printf("new index: %i \n", index);
  return index;
}

/**
  Print the contents of the viewing buffer
*/
void print_vb(int rows, int cols, char vb[rows][cols]){
  for(int row = 0; row < rows; row++){
    for(int col = 0; col < cols; col++){
      printf("%c, ", vb[row][col]);
    }
    printf("\n");
  }
}

/**
  Reset the viewing buffer
*/
void reset_vb(int rows, int cols, char vb[rows][cols])
{
    int i, j;

    for(i=0; i<rows; i++)
        for(j=0; j<cols; j++)
            vb[i][j] = '\0';
}

/**
  TASK FOUR
*/
void editor_view(int rows, int cols, char viewing_buffer[rows][cols], const char editing_buffer[], int editing_buflen, int wrap){
  reset_vb(rows, cols, viewing_buffer);
  int index = 0;
  char previous_char;
  if(wrap != 0){
    for(int row = 0; row < rows; row++){
      for(int col = 0; col < cols; col++){
        if(previous_char == '\n'){col = 0;}
        if(index >= editing_buflen){continue;}
        else if(editing_buffer[index] == '\n' ){
          previous_char = '\n';
          index++;
          row++;
        }else if(col == cols -1){
          continue;
        }else{
          viewing_buffer[row][col] = editing_buffer[index];
          previous_char = editing_buffer[index];
          index++;
        }

      }
    }


  }else{ // NEED TO FIX!!!
    for(int row = 0; row < rows; row++){
      for(int col = 0; col < cols; col++){
        if(previous_char == '\n'){col = 0;}
        if(index >= editing_buflen){continue;}
        else if(editing_buffer[index] == '\n'){
            previous_char = '\n';
            index++;
            row++;
        }else if(col == cols - 1){
          index = find_new_index(editing_buffer, index, editing_buflen);
          previous_char = '\0';
          //viewing_buffer[row][col] = '\0';
        }else{
          viewing_buffer[row][col] = editing_buffer[index];
          previous_char = editing_buffer[index];
          index++;
        }
      }
    }
  }
 }
