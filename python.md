## Python

There are three numeric types in Python:

    int
    float
    complex

Variables of numeric types are created when you assign a value to them:
```
x = 1    # int
y = 2.8  # float
z = 1j   # complex
```
* we can get the type of any object using **type()** command
> print(type(x))


If you want to specify the variables you can use type casting
 * int ()
 * float ()
 * string ()
 ___
## string
you can assign string with in " " or ' ' .<br />

|Function|work|examples|
|--------|----|--------|
|strip()|remove blank space from the begining or from the end|a = " Hello, World!"<br /> print(a.strip()) # returns "Hello, World!" |
|len()|gives us the length of the string|print(len(a)) <br /> It will show 13|
|lower()|makes every character into lowercase|print(a.lower()) <br /> hello, world! |
|upper() |makes every charecter into upper class|print(a.upper()) <br /> HELLO, WORLD! |
|replace()| replaces a string with another string:|print(a.replace("H", "J")) <br />Jello, World! |

## some important operator
x=5 <br />


|operator|work|examples|apply it|
|--------|----|--------|--------|
|/=|division|x/=3|1.666667|
|//=|floor division act as GI|x//=3|1|
|\**=| to the power|x\**=3|125|
|&=| and operator <br />In binary form it will check| x&=3|1 <br /> 0101 <br /> 0011 <br /> so answer will be 0001|
|<<=| forward operator <br /> makes every bits forwarded by 3 digit |x<<=3|40|
|>>=| backward operator <br \> makes every bits backward by 3 digit | x>>=3|0|

___
## arrays
There are four collection data types in the Python programming language:

    List is a collection which is ordered and changeable. Allows duplicate members.
    Tuple is a collection which is ordered and unchangeable. Allows duplicate members.
    Set is a collection which is unordered and unindexed. No duplicate members.
    Dictionary is a collection which is unordered, changeable and indexed. No duplicate members.
    
## list    
Python has a set of built-in methods that you can use on **lists**.


|Method| 	Description|
|------|-------------|
|append()|	Adds an element at the end of the list|
|clear()|	Removes all the elements from the list|
|copy()	|Returns a copy of the list|
|count()	|Returns the number of elements with the specified value|
|extend()	|Add the elements of a list (or any iterable), to the end of the current list|
|index()	|Returns the index of the first element with the specified value|
|insert()	|Adds an element at the specified position|
|pop()|	Removes the element at the specified position|
|remove()	|Removes the item with the specified value|
|reverse()|	Reverses the order of the list|
|sort()	|Sorts the list|

## Tuple Methods

Python has two built-in methods that you can use on tuples.


|Method |	Description|
|-------|------------|
|count()| Returns the number of times a specified value occurs in a tuple|
|index()|	Searches the tuple for a specified value and returns the position of where it was found|

## set 
thisset = {"apple", "banana", "cherry"}
Python has a set of built-in methods that you can use on sets.


|Method| 	Description|examples|
|------|-------------|--------|
|add()|	Adds an element to the set|thisset.add("orange") <br /> {'cherry', 'banana', 'apple', 'orange'} |
|clear()|	Removes all the elements from the set|thisset.clear() <br />set() |
|copy()|	Returns a copy of the set|
|difference()|	Returns a set containing the difference between two or more sets|
|difference_update()|	Removes the items in this set that are also included in another, specified set|
|discard()|	Remove the specified item|thisset.discard("banana")<br />{"apple","cherry"}|
|intersection()|	Returns a set, that is the intersection of two other sets|
|intersection_update()|	Removes the items in this set that are not present in other, specified set(s)|
|isdisjoint()|	Returns whether two sets have a intersection or not|
|issubset()|	Returns whether another set contains this set or not|
|issuperset()|	Returns whether this set contains another set or not|
|pop()|	Removes an element from the set|x = thisset.pop()<br />print(x)<br />print(thisset)<br />apple<br />{'cherry', 'banana'}| 
|remove()|	Removes the specified element|thisset.remove("banana")<br />{"apple","cherry"}|
|symmetric_difference()|	Returns a set with the symmetric differences of two sets|
|symmetric_difference_update()|	inserts the symmetric differences from this set and another|
|union()|	Return a set containing the union of sets|
|update()|	Update the set with the union of this set and others|thisset.update(["orange", "mango", "grapes"]) <br />{'orange', 'mango', 'cherry', 'grapes', 'banana', 'apple'} |

## Dictionary Methods

Python has a set of built-in methods that you can use on dictionaries.


|Method 	|Description|
|---------|-----------|
|clear()	|Removes all the elements from the dictionary|
|copy()	|Returns a copy of the dictionary|
|fromkeys()|	Returns a dictionary with the specified keys and values|
|get()	|Returns the value of the specified key|
|items()	|Returns a list containing the a tuple for each key value pair|
|keys()	|Returns a list containing the dictionary's keys|
|pop()	|Removes the element with the specified key|
|popitem()|	Removes the last inserted key-value pair|
|setdefault()|	Returns the value of the specified key. If the key does not exist: insert the key, with the specified value|
|update()	|Updates the dictionary with the specified key-value pairs|
|values()	|Returns a list of all the values in the dictionary|

##  For Loop:
```
for x in range(2, 30, 3):
  print(x)
```
here it  will print like this:
