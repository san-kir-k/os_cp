#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Seabattle {
    enum class cell_type {
        battleship, 
        cruiser, 
        destroyer, 
        boat, 
        none,
        dead,
        shooted,
        missed, 
        trap,
        triggered
    };
    enum bin_flags {
        aa = 0b11111111,
        h4 = 0b10000000,
        v4 = 0b01000000, 
        h3 = 0b00100000, 
        v3 = 0b00010000, 
        h2 = 0b00001000, 
        v2 = 0b00000100, 
        h1 = 0b00000010, 
        v1 = 0b00000001, 
        uu = 0b00000000
    };
    enum class direction {
        none = -1,
        left = 0,
        down = 1
    };

    class Battlefield {
        private:
            std::vector<std::vector<int>> _map;
            int battleship_v_slots;
            int cruisers_v_slots;
            int destroyers_v_slots;
            int boats_v_slots;
            int battleship_h_slots;
            int cruisers_h_slots;
            int destroyers_h_slots;
            int boats_h_slots;
            void _make_traps_form_boats();
            const std::vector<std::vector<int>>& _chose_matrix(int len, direction dir);
            bool _is_available(direction dir, int len, int row, int col);
            void _update(std::vector<std::vector<int>>& av_map, direction dir, int len, int row, int col);
            std::vector<std::vector<int>> _gen_available_map();
        public:
            Battlefield();
            ~Battlefield() = default;
            void gen_map();
            std::vector<std::vector<int>> get_map();
            void get_map_c(int** field);
    };

    class Action {
        private:
            int _count_of_alive;
            int** _map;
            struct cell_stats {
                int health;
                std::vector<std::pair<int, int>> coords;
                cell_type type;
                direction dir;
            };
            std::vector<std::vector<cell_stats>> _stats_map;
            void _map_update();
            void _death_update(int row, int col, int len);
            void _shoot_update(int row, int col);
        public:
            Action() = default;
            Action(int** field);
            ~Action() = default;
            void chose_alive(int* row, int* col);
            bool is_trap(int row, int col);
            void shoot(int row, int col);
            bool is_gameover();
    };
}
