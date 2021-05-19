# A Curious Number Machine
### Chapter 9 of the book "The Lady, or the Tiger?" by Raymond M. Smullyan

In this chapter, Inspector Craig visits his friend McCulloch who shows
him an interesting computer that he has built.  The following excerpts
are from the book.

*"What does it do?" asked Craig.*

*"Well," replied McCulloch, "you put a number into the machine, and
after a while a number comes out of the machine."*

*"The same number or a different one?" asked Craig.*

*"That depends on what number you put in."*

*"I see," replied Craig.*

*"Now," continued McCulloch, "the machine doesn't accept all
numbers--only some. Those which the machine accepts, I call acceptable
numbers."*

*"That sounds like perfectly logical terminology," said Craig, "but I
would like to know which numbers are acceptable and which are not. Is
there a definite law concerning this? Also, is there a definite law
concerning what number comes out once you have decided what acceptable
number to put in?"*

*"No," replied McCulloch, "deciding to put the number in is not enough;
you have actually to put the number in. "*

*"Oh, well, of course !" said Craig. " I meant to ask whether once the
number has been put in, if it is definitely determined what number
comes out."*

*"Of course it is," replied McCulloch. "My machine is not a random
device ! It operates according to strictly deterministic laws.*

*"Let me explain the rules," he continued. "To begin with, by a number
I mean a positive whole number; my present machine doesn't handle
negative numbers or fractions. A number N is written in the usual way
as a string of the digits 0,1,2,3,4,5,6, 7,8,9. However, the only
numbers my machine handles are those in which 0 does not occur; for
example, numbers like 23 or 5492, but not numbers like 502 
or 3250607. Given two numbers N,M-now by NM I don't mean N times M! By
NM I mean the number obtained by first writing the digits of N in the
order in which they occur, and then following it by the digits of M;
so, for example, if N is the number 53 and M is the number 728, by NM
I mean the number 53728. Or if N is 4 and M is 39, by NM I mean 439·"*

*"What a curious operation on numbers! " exclaimed Craig in surprise.*

*"I know," replied McCulloch, "but this is the operation the machine
understands best. Anyway, let me explain to you the rules of
operation. I say that a number X produces a number Y, meaning that X
is acceptable and that when X is put into the machine, Y is the number
that comes out. The first rule is as follows:*

*"Rule 1. : For any number X, the number 2X (that is, 2 followed by X,
not 2 times Xl) is acceptable, and 2X produces X.
"For example, 253 produces 53; 27482 produces 7482; 23985 produces
3985, and so forth. In other words, if I put a number 2X into the
machine, the machine erases the 2 at the beginning and what is
left-the X--comes out."*

*"That's easy enough to understand," replied Craig. "What are the other
rules?"*

*"There is only one more rule," replied McCulloch, "but first let me
tell you this: For any number X, the number X2X plays a particularly
prominent role; I call the number X2X the associate of the number
X. So, for example, the associate of 7 is 727; the associate of 594 is
5942594- Now, here is the other rule:*

*"Rule 2 : For any numbers X and Y, if X produces Y, then 3X produces
the associate of Y.*

*"For example, 27 produces 7, by Rule 1 ; therefore 327 produces the
associate of 7, which is 727. Thus 327 produces 727. Again, 2586
produces 586; hence 32586 produces the associate of 586, which is
5862586."*

This is a C Program that codes up the rules of this machine.

**Compiling and Running the program**
```
gcc -O2 -o two-three  two-three.c
./two-three | less
```
