
#include "WordSearchSolver.hpp"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {}
// check if the word location is in specified direction and if so input it in
// the char vector
WordLocation WordSearchSolver::CheckHorizontal(
    const std::string& word, std::vector<CharPositions> char_position) {
  WordLocation w = WordLocation{};
  if (word.length() > puzzle_width_) return w;
  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = 0; j < puzzle_width_ - word.length() + 1; j++) {
      for (size_t z = 0; z < word.length(); z++) {
        if (puzzle_[i][j + z] != word[z]) {
          char_position.clear();
        } else {
          CharPositions ch = {word[z], i, j + z};
          char_position.push_back(ch);
          if (char_position.size() == word.length()) {
            w = {word, char_position};
            return w;
          }
        }
      }
    }
  }
  return w;
}

WordLocation WordSearchSolver::CheckVertical(
    const std::string& word, std::vector<CharPositions> char_position) {
  WordLocation w = WordLocation{};
  if (word.length() > puzzle_height_) return w;
  for (size_t j = 0; j < puzzle_width_; j++) {
    for (size_t i = 0; i < puzzle_height_ - word.length() + 1; i++) {
      for (size_t z = 0; z < word.length(); z++) {
        if (puzzle_[i + z][j] != word[z]) {
          char_position.clear();
        } else {
          CharPositions ch = {word[z], i + z, j};
          char_position.push_back(ch);
          if (char_position.size() == word.length()) {
            w = {word, char_position};
            return w;
          }
        }
      }
    }
  }
  return w;
}

WordLocation WordSearchSolver::CheckLeft(
    const std::string& word, std::vector<CharPositions> char_position) {
  WordLocation w = WordLocation{};
  size_t x = word.length() - 1;
  if (word.length() > puzzle_width_ || word.length() > puzzle_height_) return w;
  for (size_t i = 0; i < puzzle_height_ - word.length() + 1; i++) {
    for (size_t j = x; j < puzzle_width_; j++) {
      for (size_t z = 0; z < word.length(); z++) {
        if (puzzle_[i + z][j - z] != word[z]) {
          char_position.clear();
        } else {
          CharPositions ch = {word[z], i + z, j - z};
          char_position.push_back(ch);
          if (char_position.size() == word.length()) {
            w = {word, char_position};
            return w;
          }
        }
      }
    }
  }
  return w;
}

WordLocation WordSearchSolver::CheckRight(
    const std::string& word, std::vector<CharPositions> char_position) {
  WordLocation w = WordLocation{};
  size_t x = word.length();
  if (word.length() > puzzle_width_ || word.length() > puzzle_height_) return w;
  for (size_t i = 0; i < puzzle_height_ - x + 1; i++) {
    for (size_t j = 0; j < puzzle_width_ - x + 1; j++) {
      for (size_t z = 0; z < word.length(); z++) {
        if (puzzle_[i + z][j + z] != word[z]) {
          char_position.clear();
        } else {
          CharPositions ch = {word[z], i + z, j + z};
          char_position.push_back(ch);
          if (char_position.size() == word.length()) {
            w = {word, char_position};
            return w;
          }
        }
      }
    }
  }
  return w;
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  std::vector<CharPositions> char_position;
  WordLocation w = WordLocation{};
  if (direction == CheckDirection::kHorizontal &&
      CheckHorizontal(word, char_position).word != w.word) {
    return CheckHorizontal(word, char_position);
  }
  if (direction == CheckDirection::kVertical &&
      CheckVertical(word, char_position).word != w.word) {
    return CheckVertical(word, char_position);
  }
  if (direction == CheckDirection::kLeftDiag &&
      CheckLeft(word, char_position).word != w.word) {
    return CheckLeft(word, char_position);
  }
  if (direction == CheckDirection::kRightDiag &&
      CheckRight(word, char_position).word != w.word) {
    return CheckRight(word, char_position);
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation w = WordLocation{};
  if (FindWord(word, CheckDirection::kHorizontal).word != w.word)
    return FindWord(word, CheckDirection::kHorizontal);
  if (FindWord(word, CheckDirection::kVertical).word != w.word)
    return FindWord(word, CheckDirection::kVertical);
  if (FindWord(word, CheckDirection::kLeftDiag).word != w.word)
    return FindWord(word, CheckDirection::kLeftDiag);
  if (FindWord(word, CheckDirection::kRightDiag).word != w.word)
    return FindWord(word, CheckDirection::kRightDiag);
  return WordLocation{};
}