#include "engine_wrapper.hpp"

void init_action(Seabattle::Action** act, int** field) {
    *act = new Seabattle::Action(field);
}

void deinit_action(Seabattle::Action* act) {
    delete act;
}

void shoot(Seabattle::Action* act, int row, int col) {
    act->shoot(row, col);
}

bool is_gameover(Seabattle::Action* act) {
    return act->is_gameover();
}

void init_battlefield(Seabattle::Battlefield** bf) {
    *bf = new Seabattle::Battlefield();
}

void deinit_battlefield(Seabattle::Battlefield* bf) {
    delete bf;
}

void gen_map(Seabattle::Battlefield* bf) {
    bf->gen_map();
}

void get_map_c(Seabattle::Battlefield* bf, int** field) {
    bf->get_map_c(field);
}

void chose_alive(Seabattle::Action* act, int* row, int* col) {
    act->chose_alive(row, col);
}

bool is_trap(Seabattle::Action* act, int row, int col) {
    return act->is_trap(row, col);
}
