# Flappy Bird Q-learning AI in C++ and SFML

This project implements a Flappy Bird game AI using Q-learning, a popular reinforcement learning algorithm. The AI learns to play Flappy Bird from scratch, gradually improving its gameplay by interacting with the environment and updating its Q-values based on the rewards and penalties it receives.

In the constants.hpp you have the game and AI parameters

The AI reached a score of 55 in a couple of hours of running (aprox 10000 episodes), if you have any ideas to make it better, contact me at dorufloare@yahoo.com

PS: I will maybie implement a deep-qlearning aproach in the future

In main.cpp you can uncomment a line

```
//ai.loadFromFile(FILENAME); 
```

and add your ai values that are saved by the program, in text files, at the episodes specified in the benchmarks array in constants.hpp, to resume your training

The reinforcement algorithm is written from scratch into the QLearingAI class
