/* There will be a finite number of messages.
    We will define them here. */

#include <string.h>
// does this go in a .c file? look up tomorrow.
/// https://stackoverflow.com/questions/228684/how-to-declare-a-structure-in-a-header-that-is-to-be-used-by-multiple-files-in-c
struct message {
    int id;
    char payload[64]; 
};

struct message broken_motor;

broken_motor.id = 0;
strcpy(broken_motor.payload, "please replace the motor");


enum messages {0,1,2,3,4,5};

