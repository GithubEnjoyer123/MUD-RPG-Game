##Readme

This program showcases a simple MUD like rpg game. The dungeon is generated randomly through a graph algorithm, and checked recursively. We also use a stack to keep track of users choices dependent on the number of paths available in a given corridor. 

To play the game, you will select a name and a class. You will then be given the general backstory of your situation. When at a corridor you will be given the move forward option. When that is taken away, you’re in combat and must finish before you can proceed. If you reach a dead end the boss will catch up to you and you must defeat it. However, you also may find the exit before the boss reaches you. Since there is no map however, this is quite difficult.

Note: error checking is currently not very tight. Please do not deviate from the options given, as I have not fully checked everything yet.

To run this programL

0. Make sure you have the g++ compiler installed. Find your system [here](https://www.mingw-w64.org/downloads/)
1. Compile the main, dungeon, and character files
```g++ .\main.cpp .\dungeon.cpp .\character.cpp -o Game```
2. Execute the game
```.\a.exe```

#Algorithm Analysis

The main part of the program uses a binary tree with a simple graph algorithm to traverse it. Things are generated randomly. Traversing the tree will give us a time complexity of O(logn), with a worst case of O(n). For this particular program however, we are constantly deleting nodes to make it more efficient for our game. This makes it closer to O(n) time as we reach the end and delete more nodes, however our O(n) at the end will be more efficient than our O(logn) when we first generated our tree.

For our stack, we are generally accessing it through O(1) time. This is because often times we will only have 1 path (depending on the difficulty). On multiple paths, it will be O(n).

While not part of the game, I left a function in that showcased the entire tree printed our recursively, to see what numbers were being generated by my rand function. Traversing the tree in this way would also give us a O(logn) time complexity, as we are ignoring indices with a dedicated value assigned to them (in this case a -1).

Lessons learned: Learned a lot more about memory management, and feel like I got super comfortably with at least basic binary tree traversal. In the future I believe using more recursion can make the code more efficient and not have to traverse the tree as often.

#Example:

Below are sample inputs. My outputs are recorded in the folder as screenshots 1-3

Harry the Wizard
3
y
2
5
3
n
3
n
5
4
3
n
3
n
5
1
3
n
3
n
5
1
3
n
3
n
5
2
y
y
2
y



