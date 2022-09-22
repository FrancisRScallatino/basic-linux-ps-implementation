# week 1
## tasks at hand
* [x] Figure out how to get process file location
* [] read from the entire file (must be able to extract all arguments)
* [] Find the location of each file a particular flag wants you to find
    * [] read it's contents (should be able to do this if second bullet is met, maybe?)

# week 3
## what I did
* 
## bugs

### notes
#### questions
1. Where is the Process UID and how to I compare to the current process UID?
   * located in the status file
   * can also use stat() for each individual process to get it's UID

1. What is meant by "display process information" for option -p
    * same default fields shown by the ps command