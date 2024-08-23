#include "QLearningAI.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include "constants.hpp"

QLearningAI::QLearningAI(float alpha, float gamma, float epsilon)
  : alpha(ALPHA), gamma(GAMMA), epsilon(EPSILON), gen(rd()), dis(0.0, 1.0) {

  default_q_value = 0.0; 
  flap_q_value = 0;   
}

std::string QLearningAI::getStateKey(float verticalDist, float horizontalDist) {
  return std::to_string(static_cast<int>(verticalDist)) + "_" + 
         std::to_string(static_cast<int>(horizontalDist));
}

int QLearningAI::chooseAction(float verticalDist, float horizontalDist){
  std::string state = getStateKey(verticalDist, horizontalDist);

  if (qTable.find(state) == qTable.end()) {
    qTable[state][0] = default_q_value; 
    qTable[state][1] = flap_q_value;   
  }

  if (dis(gen) < epsilon) {
    return std::rand() % 2;
  } else {
    return (qTable[state][0] > qTable[state][1]) ? 0 : 1;
  }
}

void QLearningAI::updateQValue(float verticalDist, float horizontalDist, int action, float reward, 
                               float nextVerticalDist, float nextHorizontalDist) {

  std::string state = getStateKey(verticalDist, horizontalDist);
  std::string nextState = getStateKey(nextVerticalDist, nextHorizontalDist);

  if (qTable.find(nextState) == qTable.end()) {
    qTable[nextState][0] = default_q_value;
    qTable[nextState][1] = flap_q_value;
  }

  float maxFutureQ = std::max(qTable[nextState][0], qTable[nextState][1]);
  float currentQ = qTable[state][action];

  qTable[state][action] = currentQ + alpha * (reward + gamma * maxFutureQ - currentQ);
  std::cout << "Updated Q-table: " << state << ' ' << action << ' ' << qTable[state][action] << '\n';
}

void QLearningAI::loadFromFile(std::string filename) {
  std::ifstream fin(filename);

  if (!fin.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }

  qTable.clear();
  fin >> alpha >> gamma >> epsilon;

  if (fin.fail()) {
    std::cerr << "Error reading alpha, gamma, epsilon values." << std::endl;
    return;
  }

  std::string state;
  float value0, value1;

  while (fin >> state >> value0 >> value1) {
    qTable[state][0] = value0;
    qTable[state][1] = value1;
  }

  fin.close();
}


void QLearningAI::saveInFile(std::string filename) {
  std::ofstream fout(filename, std::ios::out | std::ios::trunc);

  fout << alpha << ' ' << gamma << ' ' << epsilon << '\n';

  for (auto it : qTable) {
    fout << it.first << ' ' << it.second[0] << ' ' << it.second[1] << '\n';
  }
  fout.close();
}