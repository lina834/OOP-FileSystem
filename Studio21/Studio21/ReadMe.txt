Studio 21 ReadMe.txt 

2. 
virtual destructors are important in the base class because
for the ConcreteCommands, they will have their own private member
variables. Thus, when an object is being destructed, we want to fully 
clean up the correct variables
 
3.
the command prompt is flexible and reusable because 
it only references the interface (the base class) for each object. Thus,
if you want to reuse the command prompt for any newly derived classes,
you don't need to worry about specific implementation because of dynamic allocation.

>>yes<<, it can be easily configured, as it doesn't call any specific functions on the 
derived objects. 

4.
