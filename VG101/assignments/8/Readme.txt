Part1:
1.The class:
  In the class,we set the time when the car enters and leaves the parkinglot, the type of the car, the price of the car and the slot of the
car as private.In public,intimein and outtimein are used to input and output the time when the car enters the parkinglot.intimeout and 
outtimeout are used to input and output the time when the car leaves.Constructor is used to input the name and the price ofthe car.Ticket is
used to print the ticket of the car.
2.The main.cpp:
  This parkinglot has two floors.The first floor is intended for small vehicle,and ten can be included.The second floor is for big car,and
only five can be included.
  First,build two array.One contains five "0" and one contains ten "0".They stand for the parkinglot.If the number in the array is 0,it stands
for the empty of the slot.When a car enters the parkinglot and takes up one slot,we change the number into the time that the car enters the
parkinglot.Second,build two functions called loop1 and loop2.They both return an integer.This integer is the time when the car enter the
parkinglot.Meanwhile, both of them have the input of an integer and an pointer pointing to an array.The array is the parkinglot and the integer
is the time that last car entered the parkinglot.
  In the function,we rand a number under the limit of (180-the time when last car entered).Then,plus it with the time that last car entered.
The result is the time that the car enters(called timein in following statement).This helps to make sure when the time that a car enter 
won't be early than the former car.Then rand a number and plus it withthe time when the car enters.The result is the time when the car leaves
(called timeout in the following statement).Then,we compare timein with all the numbers in the array and set k=0.If we found the number in 
the array is less than timein,it means that the slot is empty and we change the number to 0 and change k to 1.When the loop is over,if k=1,
it means that there are at least one empty slot.If k=0,it means that all the numbers in the array is larger than timein,which means there is
no empty slot.Then,we carry out another loop.Search 0 in the array.Once we find 0,the position is the empty slot,and hence,we get the slot.
Then we store the position,change the number to timeout and break immediately.Then what we need to do is to use ticket function to print the
ticket.
  In main function,we use a loop to limit the time.We want to simulate the time in 180min,so we compare the output of the function,which is
also the time that the car enters with 180.If less, keep doing the loop.Else,leave the loop.
Part 2
About the hierarchy diagram:
Figure------Group------UFO---------------
        |     |                          |
        |     |--------Car---------------|(has)
        |     |                          |-----various shapes
        |     |--------Spacecraft--------|
        |     |                          |
        |     |--------Teleport----------
        |
        |
        |---Shape------Triangle
              |
              |--------Rectangle
              |
              |--------semiCircle
              |
              |--------Polygon
              |
              |--------Circle
              |
              |--------Line

          (has)
Parkinglot-----Slot
           |
           |---Group
           |
           |---Car
           |
           |---Line(door)

About the process of parking:
    The door opens and the car enters, then the door will close(maybe a bonus hah). The car will make a smooth arc when turning or reversing. All the requirements in the homework are realized in this program.

About the randomness of the program:
    The parkinglot is designed with 10 slots arranged like this:
         10  9  8  7  6
         
          1  2  3  4  5
    We assume that all the parking objects will park in an empty slot with the smallest number possible.So before the car comes into a slot, the slots whose numbers are smaller than this one will be occupied by random objects(UFO,spacecraft or teleport).
    Besides, after running a couple of times, you may find that the parked objects are usually more than 5. This is because one of the random numbers we set in the main.c happens to be large(actually this probability is large if we consecutively make 3 random numbers).In theory,our algorithm of choosing random numbers of objects can cover all the consequences.  

About the a,b parameter:
    It may be a little confusing to see parameters a and b in the constructors, they are used in the inheritence of initiate the anchor.

About the choice between vector or scalar calculation:
    In most of the basic commands we use vector calculation provided in the homework.But in some few cases we directly act on values of x or y of a vector(for instance in writing the trajectory). In fact, writing in vector or scalar form in these cases is almost the same.

About the length of the function:
    After I wrote the function regarding the movement in the parking process, I found it longer than 50 lines, but I don't think I need to devide it into smaller functions. There are 2 reasons. First, the moving parts in the park are quite a lot so that writing in several functions will be a little bit troublesome. Second, by writing in one function I want to show that their movements are uniform and synchronized.
    Instead,I used comments to divide the different parts in the whole function. I think the result is the same as writing several functions.