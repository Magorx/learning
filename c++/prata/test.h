#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include <cstdint>


class Creature {
  private:
    std::string name;
    int32_t hp;
    int32_t min_atk, max_atk;
  public:
    Creature();
    Creature(std::string name, int32_t hp, int32_t min_atk, int32_t max_atk);
    ~Creature();
    void attack(Creature defender);
    std::string get_stats();
}