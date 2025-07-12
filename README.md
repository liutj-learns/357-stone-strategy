# 357-stone-strategy
A high school project demonstrating recursion, decision making, and algorithmic strategy in a 357 stone game.

## Project Overview
The 357 Stone Game is a puzzle game derived from Nim. There are three piles with 3, 5, and 7 stones. Two players take turns removing 1 to 3 stones from a single pile. The player who removes the last stone wins.

After repeatedly losing to my cousin, I wondered: Can this game be solved like Nim, with a guaranteed winning strategy? This project was developed to explore that question using recursive algorithms.

## Features
Recursively determines if a given game state is a winning or losing position

Offers interactive gameplay between user and AI

Provides strategy suggestions during the game

Combines C++ backend logic with a simple HTML interface

Implements memoization to optimize recursive calls

## Key Concepts Applied
Recursion and memoization

Game tree traversal

C++ standard input/output handling

Simple web front-end (HTML + JavaScript)

## How It Works
User inputs initial stone counts (e.g. 3 5 7) and whether to play first

Players take turns removing 1–3 stones from a pile

After the third turn, user can input h to get a hint

The program checks whether the current state is winning or losing using a recursive function canWin(a, b, c)

Game ends when all stones are taken; winner is displayed

## Sample Function: `canWin(a, b, c)`
```cpp

bool canWin(int a, int b, int c) {
    string key = makeKey(a, b, c);
    if (memo.count(key)) return memo[key];
    if (a == 0 && b == 0 && c == 0) return memo[key] = false;

    for (int take = 1; take <= 3; ++take) {
        if (a >= take && !canWin(a - take, b, c)) return memo[key] = true;
        if (b >= take && !canWin(a, b - take, c)) return memo[key] = true;
        if (c >= take && !canWin(a, b, c - take)) return memo[key] = true;
    }
    return memo[key] = false;
}
```

## Files Included
- [357clue.cpp](./357clue.cpp) - Main game logic (C++)
- [index.html](./index.html) -Visual interface (HTML + JavaScript)


## Reflections
This was my first time working with C++. I started with zero experience but gradually learned how to use control flow, functions, arrays, and recursion. This project helped me apply concepts like game trees and algorithmic thinking in a creative way. In the future, I hope to expand this into a two-player mode and add randomized AI to increase replayability.

## References
Nim - Wikipedia

Canvas API - MDN

TED-Ed: Can You Solve the Rogue AI Riddle?

ChatGPT (for strategy exploration and code assistance)
