
# clTerm

### clTerm, API based protable serial terminal utility.

![Version:1.0](https://img.shields.io/badge/Version-1.0-green)
![In Development](https://img.shields.io/badge/Status-In%20Development-orange.svg)
![IDE:CCStudio](https://img.shields.io/badge/IDE-CCStudio-red)
![Protocol:UART](https://img.shields.io/badge/Protocol-UART%20serial-blue)
![Terminal:Putty](https://img.shields.io/badge/Teminal-puTTY-blue)


![License:MIT](https://img.shields.io/github/license/adimalla/MQTT-3.1-C?label=License)
<br/>
<br/>

<img src="https://github.com/adimalla/clTerm/blob/master/screenshots/Selection_328.jpg" width="700" height="500" title="CLI">
<br/>

## Description
**_clTerm_** is an easy to port API based serial terminal utility which allows,users to add standard C like "command line arguments" based functions, or commands to their application. This utility is implemented via callback, which allows portability across any micro-controller that supports serial protocols.

Goal of this utlity to give users a framework to add commands to their application without modifying every section of the code responsible for branching to user defined functions specially when there is a need of adding more functionalities, therefore making the firmware very modular. At the same tim eth utlity focuses on portablity, it is not dependednt on memory mapped peripherals or modules needed for accessing serial protocols. The user defined or vendor defined peripheral APIs can simply be linked to this utlity though API operations structure provided in this ulity, which consists of minimal open, byte operations like (read_char and print_char) and close.

Additionally it is a good academic excercise for leanring how to add command line 'shell' like terminal to application, and learning string operations, linked lists and callbacks.
<br/>

## Features

##### Current:-
* Read and Write API for reading from and writing to serial terminal
* Operations functions to link external character(byte) read and write functions to API, making it portable.
* Allowing user to add command line arrgument based commands to their applications, upto 255 commands.
* Clean API and exception handler for easy debugging and error reporting.
* Both Static and Dynamic allocation of API objects as per availaiblity of features.

##### Future Version:-
* Interrupt support.
* Linked List based command table for efficient resource management.
* String operation based utilities.

<br/>

## Porting and Instalation
Clone repository to the destination directory, include CLTERM_API into include files for the IDE, exclude or remove Examples test code if building a new application.

puTTY terminal is recommended for application development and testing with this utility.
<br/>

## Usage

##### The API consists of four basic structures :-

<pre>
1. API operations structure : Used for linking external basic serial operations to the API.

2. Console handle structure : Main handle object used by all API methods / functions.

3. Command table structure  : Stores the list of user defined commands, used for 
                              accessing the commands

4. API methods/functions    : API functions which are responsible for getting user input, executing 
                              user commands along with exception handling functions.
</pre>

##### API Initialization and Configuration :-

<pre>
1. Link console API operations structure with function wrappers.
   It is initilaized by linking the user or vendor provided serial API functions to the function, 
   pointers present in the structure below. This can be done by creating simple wrapper functions, 
   to match the parameters and return type of the functions. Shown below.
</pre>

~~~~
/* Call back functions  */
typedef struct _console_operations
{
    uint8_t (*open)(uint32_t baudrate);                   
    uint8_t (*print_char)(char data);                     
    char    (*read_char)(void);                           
    int8_t  (*write)(const char *buffer, int16_t length);  
    int8_t  (*read)(char *read_buffer, int16_t length);    

}console_ops_t;
~~~~

</br>

`uint8_t (*open)(uint32_t baudrate);` </br>
Initialize serial hardware, (must return 0 for error, 1 for success), link serial init function with this call,
which can get baudrate or serial speed as parameter or empty/dummy baudrate value if user serial init configures,
fixed baudrate or speed internally.

`uint8_t (*print_char)(char data);` </br>
Writes character / byte data to serial ineterface or hardware, link user or vendor char (byte) write function to this,
call.

`char(*read_char)(void);` </br>
Reads character / byte data from serial interface, link user or vendor function which performs the same operation to this,
call.

</br>

**Create Wrapper Functions :-**

~~~~
Example : for uint8_t (*open)(uint32_t baud_rate)

uint8_t simple_open(uint32_t baud_rate)
{     
  // User;s own serial initialization function
  your_uart0_init(void);
  
  // Must return 1 to indicate success.
  return 1;
}

OR

uint8_t serial_open(uint32_t baud_rate)
{
  // User's own serial initialization function
  your_uart0_init(GPIOA, UART0, baud_rate);     
  
  // Must return 1 to indicate success.
  return 1;
}

Example : for uint8_t (*print_char)(char data) and char (*read_char)(void)

uint8_t my_print_char(char data)
{
    putcUart0(data);

    return 0;
}

char my_read_char(void)
{
  return getcUart0();
}

~~~~

</br>

**Link Wrapper functions to API operations structure :-**
~~~~~
console_ops_t serial_ops =
{

 .open       = serial_open,
 .print_char = my_print_char,
 .read_char  = my_read_char,

};
~~~~~

</br>

<pre>
2. Console handle structure:
   Call console initialization function and pass reference to API operations object created above. 
   Choose static or dynamic allocation (if heap region configured).if static allocation is selected, 
   then input buffer(serial buffer) size is taken from cl_term_config.h defines
   
   <i>Caution!: Static allocation only creates one instance per application, more than 1 instance,
                will be over written.</i>
</pre>
~~~~~
Example: (choosing static allocation)

/* Define baud-rate / serial speed */
#define BAUDRATE 115200

/* Initialize serial buffer */
char *buffer[40] = {0};

/* Initialize serial handle */
cl_term_t *console;

console = console_open(&serial_ops, BAUDRATE, buffer, CONSOLE_STATIC);

if(!console)
  assert(error);

~~~~~

</br>

<pre>
3. Command table structure and adding user defined functions
   clTerm utility provides user to add custom commands which are maintained in console,
   command table structure.Create command_table object though create_commad_list(...) API,
   it takes console handle object as parameter and table size.if console object is statically, 
   allocated then table size value is redundant and will use size value from cl_term_config.h.
</pre>

~~~~~
/* Command List Table */
typedef struct _command_table
{
    uint8_t command_table_size;              /*!< Table Size              */
    char    command_name[CMD_NAME_SIZE];     /*!< Command Name            */
    int     (*func)(int argc, char **argv);  /*!< Linked function pointer */

}command_table_t;
~~~~~

</br>

**Create Command Table List**
~~~~~
Example :-

command_table_t *command_list;

command_list = create_command_list(console, MAX_TABLE_SIZE);

if(!commmand_list)
  assert(error);
~~~~~

## Contributors and Maintainers
Aditya Mall (UTA MSEE)
</br>
email: aditya.mall1990@gmail.com.
