#pragma once

const float SPEED_UP = 1.0f;

// Screen
constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 800;
constexpr int SCREEN_BORDER = 100;

// Bird
const float BIRD_WIDTH = 50;
const float BIRD_HEIGHT = 50;
const float GRAVITY = 0.12f;
const float JUMP_FORCE = -4.0f;
const float BIRD_POSITION_X = 100;
const float BIRD_POSITION_Y = 300;

// Pipe
const float PIPE_SPEED = 3.0f;
const float PIPE_SPACING = 300.0f;
const float PIPE_WIDTH = 80.0f;

const float PIPE_GAP = 300.0f;

//Timers

const float PIPE_SPAWN_INTERVAL = 2.0f / SPEED_UP;
const float AI_DECISION_INTERVAL = 0.25f / SPEED_UP;

//TRAINING VOLUME
const int NR_EPISODES = 1000000;
const int MAX_STEPS = 1000000;

//AI REWARDS
const float DEATH_REWARD = -1000;
const float ALIVE_REWARD = 5;
const float PASSED_PIPE_REWARD = 700;

//PIXEL GROUPS
const int PIXEL_GROUP = 100;
const int PIXEL_VERTICAL_GROUP = 60;
const int PIXEL_HORIZONTAL_GROUP = 80;

//AI VALUES
const float DECAY_RATE = 0.995f;
const float ALPHA = 0.15f;
const float EPSILON = 1.0f;
const float GAMMA = 0.98f;

//BENCHMARKS - at what episodes should the program save a file with the alpha, gamma, epsilon and qTable
const int benchmarks[] = {
  10, 100, 250, 500, 1000, 2000, 3000, 5000, 7500, 10000, 20000, 30000, 40000, 50000,
  75000, 100000
};