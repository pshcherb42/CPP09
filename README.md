## 3 compact programs in C++ 

## Exploring how STL and algoritms behave in real-world data processing

A set of small programs focused on data processing using STL containers.
The goal is to pick the most efficient algorithm for each specific exercise.
It includes performance-comparison scripts, some parsing logic, and the use of various algorithms.

![Containers](./resources/container.jpeg)


## Exercise 00: Bitcoin Exchange

## A tiny C++98 tool that reads real Bitcoin prices and tells you how much your old transactions would be worth today.

This data-processing mini-project loads historical Bitcoin prices, parses user input, validates it, and finds the closest matching price in the dataset.

Here is the data that we are going to feed out program with:
![data](./resources/data.gif)

The input file containing values that we need to convert and dates:
![input](./resources/input_file.png)

The program in action:

![ex00](./resources/ex00.gif)

I built it because it’s a great project to show how to choose the right container (map, vector, etc.), how to organize data in memory, and how to work with large files without losing performance.


## Exercise 01: Reverse Polish Notation

## A simple RPN expression evaluator

This program takes a raw expression, validates its format, and computes the result. The goal is to experiment with the container choice. Finaly, I chose stack-based approach. Why? Because RPN is literally designed for stacks: every number gets pushed, every operator pops the last two values, applies the operation, and pushes the result back. 

The program in action:

![ex01](./resources/ex01.gif)



















EX02 Comming soon...
