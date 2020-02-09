
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
**_clTerm_** is an easy to port minimal API based serial terminal utility which adds a 'shell' like interface to the application and allows users to add standard C like "command line arguments" based functions, or commands to their application. This utility is implemented via callbacks, which allows portability across any micro-controller that supports serial protocols.

Goal of this utlity to give users a shell like interface and a framework to add commands to their application without modifying every section of the code that is responsible for branching to user defined functions specially when there is a need of adding more functions, therefore making the application very modular. At the same time the utlity focuses on portablity, it is not dependednt on memory mapped peripherals or modules needed for accessing serial protocols. The user defined or vendor defined peripheral APIs can simply be linked to this utlity though the provided API operations structure, which consists of minimal operations like open, byte operations like (read_char and print_char) and close.

Additionally it is a good academic excercise for learning how to add command line 'shell' like terminal to applications, learning string operations, linked lists and callbacks.
<br/>

## Features

##### Current:-
* Command line arrgument based functions can be added to the applications, upto 255 commands.
* Read and Write API for, reading from and writing to serial terminal.
* Portable API through call back operations.
* Clean API and exception handler for easy debugging and error reporting.
* Both Static and Dynamic allocation of API objects as per availaiblity of memory regions.
* Minimal code space, under 1000 lines code.

##### Future Version:-
* Interrupt support.
* Linked List based command table for efficient resource management.
* String operation based utilities.

<br/>

## Porting and Instalation
**For New Application** </br>
Clone repository to the destination directory, include CLTERM_API into include files for the IDE, exclude or remove Examples test code.

**Example Test Code** </br>
Clone repository to the destination directory, include CLTERM_API and required board examples into the project directory.

puTTY terminal is recommended for application development and testing with this utility.
<br/>

## Usage

##### The API consists of four basic structures :-

<pre>
1. API operations structure : Used for linking external basic serial operations to the API.

2. Console handle structure : Main handle object used by all API methods / functions.

3. Command table structure  : Stores the list of user defined commands, used for 
                              accessing the commands.

4. API methods/functions    : API functions which are responsible for getting user input, executing 
                              user commands along with exception handling functions.
</pre>

</br>

##### API Initialization and Configuration :-

1. Link console API operations structure with function wrappers.
This is initialized by linking user defined or vendor provided serial API functions to the callback functions present in the API operations structure shown below. Linkning can be done by creating simple wrapper functions to match the parameters and return type of call back functions.

</br>

~~~~
/* Call back functions  */
typedef struct _console_operations
{
    uint8_t (*open)(uint32_t baudrate);                   
    uint8_t (*print_char)(char data);                     
    char    (*read_char)(void);                           
    int8_t  (*write)(const char *buffer, int16_t length);  /* Not used */
    int8_t  (*read)(char *read_buffer, int16_t length);    /* Not used */

}console_ops_t;
~~~~

</br>

`uint8_t (*open)(uint32_t baudrate);` </br>
Initializes serial hardware, (must return 0 for error, 1 for success), link serial init function with this call,
which expects baudrate or serial speed as parameter or empty/dummy baudrate value if user serial init configures,
fixed baudrate or speed internally.

`uint8_t (*print_char)(char data);` </br>
Writes character / byte data to serial ineterface or hardware, link user or vendor char (byte) write function to this,
call.

`char(*read_char)(void);` </br>
Reads character / byte data from serial interface, link user or vendor function ,which performs the same operation, to this,
call.
</br>

**Create Wrapper Functions :-**

~~~~
Example : for uint8_t (*open)(uint32_t baud_rate)

uint8_t simple_open(uint32_t baud_rate)
{     
  /* User's serial initialization function */
  /* Configures baud rate internally */
  your_uart0_init(void);
  
  /* Must return 1 to indicate success */
  return 1;
}

OR

uint8_t serial_open(uint32_t baud_rate)
{
  /* User's serial initialization function */
  your_uart0_init(GPIOA, UART0, baud_rate);     
  
  /* Must return 1 to indicate success */
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

2. Console handle structure:
Call console initialization function and pass reference to API operations object created above. Choose static or dynamic allocation (if heap region configured).if static allocation is selected, then input buffer(serial buffer) size is taken from cl_term_config.h defines.
   
<i>Caution!: Static allocation only creates one instance per application, more than 1 instance, will be over written.</i>

</br>

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

3. clTerm utility provides user to add custom commands which are maintained in console command table structure. Create command_table object though create_commad_list(...) API which takes console handle object as parameter and table size.
if console object is statically allocated then table size value is redundant and will use size value from cl_term_config.h.

</br>

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

**Create Command Table List and Add command **
~~~~~
Example :-

/* User defined test command to print all arguments entered by user */
int test1(int argc, char **argv)
{

    int index = 0;
    int count = 0;

    count = argc;

    console_print(console, "test command \n");

    for(index = 1; index < count; index++)
    {
        console_print(console, argv[index]);

        console_print(console, "\n");
    }

    return 0;
}

/* Define command table object */
command_table_t *command_list;

command_list = create_command_list(console, MAX_TABLE_SIZE);

add_command(command_list, "test1", test1);

if(!commmand_list)
  assert(error);
  
~~~~~

</br>

4. The console API commands are executed by calling the console_begin(...) followed by calling the console_get_string(...) to get user input and finally calling the console_exec_command(...) to execute the correct command entered by the user.
Console_begin(..) function takes console handle object and command table object as parameters.
if there are no previous exceptions with command table API functions console_begin executes successfully, or returns exception to console handle which can be handled by catch_exception(...) function.

</br>

**Call Console API functions**
~~~~~
Example :-

console_begin(console, command_list);


/* Call console_get_string(...), takes two parameters, object to console,
 * handle and max input buffer size.
 */
console_get_string(console, MAX_INPUT_SIZE);


/* Call console_exec_command(...), takes console object, command table object,
 * and user input buffer as parameters. This call is dependent upon successful,
 * execution of console_begin(..) function otherwise exception is generated.
 */
console_exec_command(console, command_list, buffer);

~~~~~

</br>

5. Exception handling functions are provided to throw and catch exceptions produced by the console API methods. Exception, handling functions are dependent on console handle and throw exceptions internally to the console handle which can be caught by the catch_exception(...) function or viewed as symbols in a live debug view.

</br>

<pre>
throw_exception(...), console handle object and exception type as, parameters.

List of exceptions values can be viewed in cl_term.h file.

catch_exception(...), console handle object and exception state as parameters.
if exception state = EXCEPTION_HOLD_STATE, then catch exception function will block, 
the state of the program and report the exception to the terminal.
</pre>

</br>

**Call Exception Handling functions**
~~~~~
Example :-

int8_t exception;

exception |= add_command(command_list, "test1", test1);

throw_exception(myConsole, (console_exceptions_t)exception);

catch_exception(myConsole, EXCEPTION_HOLD_STATE);
~~~~~

</br>

## Contributions
Aditya Mall (UTA MSEE)
</br>
email: aditya.mall1990@gmail.com.
