#pragma once

#include "game_engine.hpp"

extern "C" void init_action(Seabattle::Action** act, int** field);

extern "C" void deinit_action(Seabattle::Action* act);

extern "C" void shoot(Seabattle::Action* act, int row, int col);

extern "C" bool is_gameover(Seabattle::Action* act);

extern "C" void init_battlefield(Seabattle::Battlefield** bf);

extern "C" void deinit_battlefield(Seabattle::Battlefield* bf);

extern "C" void gen_map(Seabattle::Battlefield* bf);

extern "C" void get_map_c(Seabattle::Battlefield* bf, int** field);

extern "C" void chose_alive(Seabattle::Action* act, int* row, int* col);

extern "C" bool is_trap(Seabattle::Action* act, int row, int col);
