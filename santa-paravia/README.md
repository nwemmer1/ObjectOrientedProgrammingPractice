# Santa Paravia
Nathan Wemmer
OOP-001

## Objective:

The goal is to rise up in your city state by managing and taking over different city states and continue until you reach the much sought
after, King or Queen status.

## Main abstractions

Mostly everything is in one big struct called "Player". It is not broken down into different structs yet, but if that was my goal, then I
would break it up into 1 main group called City State Info, having two subgroups classifying them more, making it easier to navigate
and then the elements of the further classification in that subgroup.
* City State Info
  * People/Information
    * Player Information
    * Citizens
    * Military
  * Operations/Actions
    * Food
    * City State Upgrades
    * Taxation
    * Laws
    * Currency


(The above things are separated because one has to do with people/information and the other has to do with more operations and things that happen
in the game that help you advance or fall back depending on the actions selected and problems generated.)

There cannot me more than six people playing the game at once, and must have at least one player to start. Every kind of user inputted 
information is put into a cstring array with respect to what the inputted. Everything for the most part is named clearly and easy to figure
out and navigate through for understanding. Mostly everything is an int except for user inputted names, the titles and prices (which are floats
and chars respectively).

* Male and female titles are separated, which one is used is chosen at the beginning when selecting gender.

* Almost every function passes a structed named player except for few exceptions.

* The Random() function, which doesn't take in the Player data struct, takes parameter 'Hi" and returns a random integer between 0 and
'Hi'.

* InitializePlayer void function sets everything to a default number like the titles, prices, bool expressions.

* The buy/sell functions take player info and ask for user input on how much of something they want to buy or sell and changes the users info
accordingly.

* There are validation functions like CheckNewTitle().

* The taxes seem really complicated; there are a bunch of different 1-letter variables in the taxes/duties.

* PrintInstructions(void) function tells the rules in a weird way, as if you were actually roleplaying. (Which I get, because it is
a role-playing game after all.)

* PlayGame() is responsible for starting everything up with function calls to every main function and branches off from there.


## Comments/Questions


* The ImDead() function is kind of weirdly names and is confusing, would like to change that to something like PlayerDeath().

* I have never seen \t in anything before and have never used it, what is that? -Looked up, found it to be the horintal tab. (I also 
found a wholelist of what I learned to be called Escape Sequences. These are used to represent certain character and text operations.)

* Why was there ever a reason to put everything in one giant struct?

* Wasn't this ever found to be confusing and seemingly run-on?

* What is the advantage of using printf over cout? What is the memory cost?
* -cout is typesafe,couldn't really find a more 

* When being redone, could add lots of flags.

* I'm still kind of confused on how the game difficulty works?

## Updates-Release 1
* I have since moved from my original idea of separating it how I above stated, and started to do it a different way, stated later below.

* I have 2 different versions of this that I am currently working on. I have the original file that is supposedly in C, that I am changing a lot of things in and making sure that I can do certain things with certain functions/objects such as moving around class items. And I have also created the separate empty files that I will start adding and changing things that will be final or I have found to work.

* I have changed the makeshift boolean type into a real bool data type and it works correctly, took out something that had to do with an enum? I looked it up and found little info but I fooled around with some things and I went through every aspect and made sure what I changed was right.

* I changed the random number generator so something that uses way less code, easier to read and understand. I read the old number generator and I couldn't grasp what exactly was going on until it was literally spelled out for me on a website I found. Just uses int RanNum=rand() % Hi +1; This eliminates the need for the type conversion that happened in the old return statement.

* Altered the code that used printf, found it to be more useful and clearer to understand and is used more in C++. Using the modulus and the escape sequences really threw me off and takes longer to read if it's not what you look at everyday. I changed it in several places, used in the PrintInstructions() function and changed everything in 'int main()' to use cout and cin (clearer and more with the times of C++ opposed to C). 
*Why would you have the user input a string, and then immediately change the data type in the next line?
*What was the reasoning behind the Random(Hi) function? Why did it have so many lines and accomplish what I did, but with 4x as much code? Was the rand() % not a thing in C?

* I have multiple files that I felt that when created, it makes it easier to at least see what can go into each class. Resources, player, treasury, grains, labels(name of each player as they rise through the ranks to win the game and become king, etc. 






