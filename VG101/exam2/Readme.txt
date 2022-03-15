ex1:
1:define a structure point->next.
2:use a loop to add the structure,which point its pointer to the first structure before.
3:use pointer to read through a structure until it point to NULL. Then count it.
ex2:
  use << to determine whether it is 0 or 1 in the bit.
ex3:
1:use srand to make sure the random numbers are really random.Use malloc to create a dynamic memory for the sequence.Then use loop to store the
random numbers
2:First, rand a random number k as the point.Then, when i<=k,rand the number and store them in a array a.If the new random number is less than 
the last one, rand again. Then, when i>k, use the last random number as the limit of the next random number.
3:Compare the elements of the array one by one.If one of it is less than the last one, then the k is the last one.Compare the following numbers.
If the following numbers all meet that the last one is greater than the next one, then it is a bitonic,otherwise it is not.
4:Open a file and get the numbers as a string.Count the backspace by reading them one by one. Then use malloc to create a array to store the numbers.
Use fscanf to read the numbers.
5:a:use a loop to read through the array.like:for(i=0;i<n;i++){...}
b:use a loop like above to find the maximun point.If a[i] is the greatest number,then k=i
6.