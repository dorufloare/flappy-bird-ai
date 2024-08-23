#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <random>

class QLearningAI {
public:
  QLearningAI(float alpha = 0.1, float gamma = 0.99, float epsilon = 1.0);
  int chooseAction(float verticalDist, float horizontalDist);
  void updateQValue(float verticalDist, float horizontalDist, int action, float reward, 
                      float nextVerticalDist, float nextHorizontalDist);

  void saveInFile(std::string filename);
  void loadFromFile(std::string filename);

  float alpha;
  float gamma;
  float epsilon;

private:
  std::string getStateKey(float verticalDist, float horizontalDist);

  std::unordered_map<std::string, std::unordered_map<int,float>> qTable;

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;

  float default_q_value;
  float flap_q_value;
};
