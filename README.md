# NWEN241 Assignment One

This assignment was designed to test our application of the basic conceptual knowledge of C fundamentals to solve practical programming tasks. All of the code was completed in editor.c, with the complementary files in the folder acting as test cases. 

The first task was to insert a char into a char array at a certain position. This was done using the function: 
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos);

The second task was to implement the function: int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset); This function deletes a char at a certain location in an array and moves the remaining chars accordingly. 

Task three involved the function: int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset); This will replace the first occurrence of the string str with replacement.

For task four, we had to implement a function with the prototype void editor_view(int rows, int cols,
char viewing_buffer[rows][cols], const char editing_buffer[], int editing_buflen, int wrap); This function will copy the contents of the editing_buffer to the viewing_buffer for display to the user.
