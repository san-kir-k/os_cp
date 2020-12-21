#include "game_engine.hpp"

namespace Seabattle {
    const int MSIZE = 10;

    const int BATTLESHIP_C = 1;
    const int CRUISER_C = 2;
    const int DESTROYER_C = 3;
    const int BOAT_C = 4;

    const int BATTLESHIP = 4;
    const int CRUISER = 3;
    const int DESTROYER = 2;
    const int BOAT = 1;
    const int NONE = 0;
    const int DEAD = -1;
    const int SHOOTED = -2;
    const int MISSED = -3;

    const std::vector<std::vector<int> > v1_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0}};
    const std::vector<std::vector<int> > h1_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0}};
    const std::vector<std::vector<int> > v2_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0}};
    const std::vector<std::vector<int> > h2_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0}};
    const std::vector<std::vector<int> > v3_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0}};
    const std::vector<std::vector<int> > h3_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0}};
    const std::vector<std::vector<int> > v4_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0}};
    const std::vector<std::vector<int> > h4_matrix =
    {{aa, aa, aa, ~v4, ~v4, ~v4, ~v4, ~v4, ~v4},
     {aa, aa, aa, ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3), ~(v4 | v3)},
     {aa, aa, aa, ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2), ~(v4| v3| v2)},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0, 0},
     {~h4, ~(h4 | h3), ~(h4| h3| h2), 0, 0, 0, 0, 0, 0}};
    
    const std::vector<std::vector<int>>& Battlefield::_chose_matrix(int len, direction dir) {
        if (dir == direction::left) {
            if (len == 1) {
                return h1_matrix;
            } else if (len == 2) {
                return h2_matrix;
            } else if (len == 3) {
                return h3_matrix;
            } else {
                return h4_matrix;
            }
        } else {
            if (len == 1) {
                return v1_matrix;
            } else if (len == 2) {
                return v2_matrix;
            } else if (len == 3) {
                return v3_matrix;
            } else {
                return v4_matrix;
            }
        }
    }
    bool Battlefield::_is_available(direction dir, int len, int row, int col) {
        int available_count = 0;
        if (dir == direction::left) {
            for (int i = col; i < MSIZE; ++i) {
                available_count++;
            }
        } else {
            for (int i = row; i < MSIZE; ++i) {
                available_count++;
            }
        }
        return available_count >= len;
    }
    void Battlefield::_update(std::vector<std::vector<int>>& av_map, direction dir, int len, int row, int col) {
        std::vector<std::vector<int> > matrix = _chose_matrix(len, dir);
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if ((row + i - 4 >= 0) && (row + i - 4 < MSIZE) && (col + j - 4 >= 0) && (col + j - 4 < MSIZE)) {
                    av_map[row + i - 4][col + j - 4] = (av_map[row + i - 4][col + j - 4] & matrix[i][j]);
                    if (((~matrix[i][j]) & h1) != 0) {
                        boats_h_slots--;
                    }
                    if (((~matrix[i][j]) & h2) != 0) {
                        destroyers_h_slots--;
                    }
                    if (((~matrix[i][j]) & h3) != 0) {
                        cruisers_h_slots--;
                    }
                    if (((~matrix[i][j]) & h4) != 0) {
                        battleship_h_slots--;
                    }
                    if (((~matrix[i][j]) & v1) != 0) {
                        boats_v_slots--;
                    }
                    if (((~matrix[i][j]) & v2) != 0) {
                        destroyers_v_slots--;
                    }
                    if (((~matrix[i][j]) & v3) != 0) {
                        cruisers_v_slots--;
                    }
                    if (((~matrix[i][j]) & v4) != 0) {
                        battleship_v_slots--;
                    }
                }
            }
        }
    }
    std::vector<std::vector<int>> Battlefield::_gen_available_map() {
        std::vector<std::vector<int>> av_map(MSIZE, std::vector<int> (MSIZE, 0));
        for (int i = 0; i < MSIZE; ++i) {
            for (int j = 0; j < MSIZE; ++j) {
                for (int len = 1; len <= 4; ++len) {
                    if (_is_available(direction::left, len, i, j)) {
                        if (len == 1) {
                            av_map[i][j] = av_map[i][j] | h1;
                            boats_h_slots++;
                        } else if (len == 2) {
                            av_map[i][j] = av_map[i][j] | h2;
                            destroyers_h_slots++;
                        } else if (len == 3) {
                            av_map[i][j] = av_map[i][j] | h3;
                            cruisers_h_slots++;
                        } else {
                            av_map[i][j] = av_map[i][j] | h4;
                            battleship_h_slots++;
                        }
                    }
                    if (_is_available(direction::down, len, i, j)) {
                        if (len == 1) {
                            av_map[i][j] = av_map[i][j] | v1;
                            boats_v_slots++;
                        } else if (len == 2) {
                            av_map[i][j] = av_map[i][j] | v2;
                            destroyers_v_slots++;
                        } else if (len == 3) {
                            av_map[i][j] = av_map[i][j] | v3;
                            cruisers_v_slots++;
                        } else {
                            av_map[i][j] = av_map[i][j] | v4;
                            battleship_v_slots++;
                        }
                    }
                }
            }
        }
        return av_map;
    }
    Battlefield::Battlefield():  battleship_v_slots(0), cruisers_v_slots(0),
                    destroyers_v_slots(0), boats_v_slots(0),
                    battleship_h_slots(0), cruisers_h_slots(0),
                    destroyers_h_slots(0), boats_h_slots(0) {
        _map = std::vector<std::vector<int>>(MSIZE, std::vector<int> (MSIZE, 0));
    };
    void Battlefield::gen_map() {
        srand(time(0));
        std::vector<std::vector<int> > av_map = _gen_available_map();
        for (int i = 0; i < BATTLESHIP_C; ++i) {
            int dir = rand() % 2;
            int pos;
            if (dir == 0) {
                pos = rand() % battleship_v_slots;
            } else {
                pos = rand() % battleship_h_slots;
            }
            int row; 
            int col;
            for (int j = 0; j < av_map.size(); ++j) {
                for (int k = 0; k < av_map[j].size(); ++k) {
                    if (dir == 0) {
                        if ((av_map[j][k] & v4) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::down, 4, row, col);
                            }
                            pos--;
                        }
                    } else {
                        if ((av_map[j][k] & h4) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::left, 4, row, col);
                            }
                            pos--;
                        }
                    }
                }
            }               
            if (dir == 0) {
                for (int j = row; j < row + 4; ++j) {
                    _map[j][col] = 4;
                }
            } else {
                for (int j = col; j < col + 4; ++j) {
                    _map[row][j] = 4;
                }
            }
        }
        for (int i = 0; i < CRUISER_C; ++i) {
            int dir = rand() % 2;
            int pos;
            if (dir == 0) {
                pos = rand() % cruisers_v_slots;
            } else {
                pos = rand() % cruisers_h_slots;
            }
            int row; 
            int col;
            for (int j = 0; j < av_map.size(); ++j) {
                for (int k = 0; k < av_map[j].size(); ++k) {
                    if (dir == 0) {
                        if ((av_map[j][k] & v3) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::down, 3, row, col);
                            }
                            pos--;
                        }
                    } else {
                        if ((av_map[j][k] & h3) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::left, 3, row, col);
                            }
                            pos--;
                        }
                    }
                }
            }
            if (dir == 0) {
                for (int j = row; j < row + 3; ++j) {
                    _map[j][col] = 3;
                }
            } else {
                for (int j = col; j < col + 3; ++j) {
                    _map[row][j] = 3;
                }
            }
        }
        for (int i = 0; i < DESTROYER_C; ++i) {
            int dir = rand() % 2;
            int pos;
            if (dir == 0) {
                pos = rand() % destroyers_v_slots;
            } else {
                pos = rand() % destroyers_h_slots;
            }
            int row; 
            int col;
            for (int j = 0; j < av_map.size(); ++j) {
                for (int k = 0; k < av_map[j].size(); ++k) {
                    if (dir == 0) {
                        if ((av_map[j][k] & v2) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::down, 2, row, col);
                            }
                            pos--;
                        }
                    } else {
                        if ((av_map[j][k] & h2) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::left, 2, row, col);
                            }
                            pos--;
                        }
                    }
                }
            }
            if (dir == 0) {
                for (int j = row; j < row + 2; ++j) {
                    _map[j][col] = 2;
                }
            } else {
                for (int j = col; j < col + 2; ++j) {
                    _map[row][j] = 2;
                }
            }
        }
        for (int i = 0; i < BOAT_C; ++i) {
            int dir = rand() % 2;
            int pos;
            if (dir == 0) {
                pos = rand() % boats_v_slots;
            } else {
                pos = rand() % boats_h_slots;
            }
            int row; 
            int col;
            for (int j = 0; j < av_map.size(); ++j) {
                for (int k = 0; k < av_map[j].size(); ++k) {
                    if (dir == 0) {
                        if ((av_map[j][k] & v1) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::down, 1, row, col);
                            }
                            pos--;
                        }
                    } else {
                        if ((av_map[j][k] & h1) != 0) {
                            if (pos == 0) {
                                row = j;
                                col = k;
                                _update(av_map, direction::left, 1, row, col);
                            }
                            pos--;
                        }
                    }
                }
            }
            if (dir == 0) {
                for (int j = row; j < row + 1; ++j) {
                    _map[j][col] = 1;
                }
            } else {
                for (int j = col; j < col + 1; ++j) {
                    _map[row][j] = 1;
                }
            }
        }
    }
    std::vector<std::vector<int>> Battlefield::get_map() {
        return _map;
    }
    void Battlefield::get_map_c(int** field) {
        for (int i = 0; i < MSIZE; ++i) {
            for (int j = 0; j < MSIZE; ++j) {
                field[i][j] = _map[i][j];
            }
        }
    }

    void Action::_map_update() {
        for (int i = 0; i < MSIZE; ++i) {
            for (int j = 0; j < MSIZE; ++j) {
                if (_stats_map[i][j].type == cell_type::none) {
                    _map[i][j] = NONE;
                }
                if (_stats_map[i][j].type == cell_type::battleship) {
                    _map[i][j] = BATTLESHIP;
                }
                if (_stats_map[i][j].type == cell_type::cruiser) {
                    _map[i][j] = CRUISER;
                }
                if (_stats_map[i][j].type == cell_type::destroyer) {
                    _map[i][j] = DESTROYER;
                }
                if (_stats_map[i][j].type == cell_type::boat) {
                    _map[i][j] = BOAT;
                }
                if (_stats_map[i][j].type == cell_type::dead) {
                    _map[i][j] = DEAD;
                }
                if (_stats_map[i][j].type == cell_type::shooted) {
                    _map[i][j] = SHOOTED;
                }
                if (_stats_map[i][j].type == cell_type::missed) {
                    _map[i][j] = MISSED;
                }
            }
        }
    }
    void Action::_death_update(int row, int col, int len) {
        for (auto p: _stats_map[row][col].coords) {
            _stats_map[p.first][p.second].type = cell_type::dead;
        }
        if (_stats_map[row][col].dir == direction::left) {
            int area_r = _stats_map[row][col].coords[0].first;
            int area_c = _stats_map[row][col].coords[0].second - 1;
            if (area_r >= 0 && area_c >= 0) {
                _stats_map[area_r][area_c].type = cell_type::missed;
            }
            area_r = _stats_map[row][col].coords[len - 1].first;
            area_c = _stats_map[row][col].coords[len - 1].second + 1;
            if (area_r < MSIZE && area_c < MSIZE) {
                _stats_map[area_r][area_c].type = cell_type::missed;
            }
            area_r = _stats_map[row][col].coords[0].first - 1;
            for (int i = 0; i < len + 2; ++i) {
                area_c = _stats_map[row][col].coords[0].second - 1 + i;
                if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c < MSIZE) {
                    _stats_map[area_r][area_c].type = cell_type::missed;
                }
            }
            area_r = _stats_map[row][col].coords[0].first + 1;
            for (int i = 0; i < len + 2; ++i) {
                area_c = _stats_map[row][col].coords[0].second - 1 + i;
                if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c < MSIZE) {
                    _stats_map[area_r][area_c].type = cell_type::missed;
                }
            }
        } else {
            int area_r = _stats_map[row][col].coords[0].first - 1;
            int area_c = _stats_map[row][col].coords[0].second;
            if (area_r >= 0 && area_c >= 0) {
                _stats_map[area_r][area_c].type = cell_type::missed;
            }
            area_r = _stats_map[row][col].coords[len - 1].first + 1;
            area_c = _stats_map[row][col].coords[len - 1].second;
            if (area_r < MSIZE && area_c < MSIZE) {
                _stats_map[area_r][area_c].type = cell_type::missed;
            }
            area_c = _stats_map[row][col].coords[0].second - 1;
            for (int i = 0; i < len + 2; ++i) {
                area_r = _stats_map[row][col].coords[0].first - 1 + i;
                if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c < MSIZE) {
                    _stats_map[area_r][area_c].type = cell_type::missed;
                }
            }
            area_c = _stats_map[row][col].coords[0].second + 1;
            for (int i = 0; i < len + 2; ++i) {
                area_r = _stats_map[row][col].coords[0].first - 1 + i;
                if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c < MSIZE) {
                    _stats_map[area_r][area_c].type = cell_type::missed;
                }
            }
        }
    }
    void Action::_shoot_update(int row, int col) {
        for (auto p: _stats_map[row][col].coords) {
            _stats_map[p.first][p.second].health--;
        }
        int len = 0;
        if (_stats_map[row][col].type == cell_type::boat) {
            len = 1;
        } else if (_stats_map[row][col].type == cell_type::destroyer) {
            len = 2;
        } else if (_stats_map[row][col].type == cell_type::cruiser) {
            len = 3;
        } else {
            len = 4;
        }
        _stats_map[row][col].type = cell_type::shooted;
        if (_stats_map[row][col].health == 0) {
            _death_update(row, col, len);
        }
    }
    Action::Action(int** field) {
        _count_of_alive = 0;
        _map = field;
        _stats_map = std::vector<std::vector<cell_stats>>(MSIZE, std::vector<cell_stats> (MSIZE));
        for (int i = 0; i < MSIZE; ++i) {
            for (int j = 0; j < MSIZE; ++j) {
                _map[i][j] = field[i][j];
                if (_map[i][j] == 0) {
                    _stats_map[i][j].health = 0;
                    _stats_map[i][j].type = cell_type::none;
                    _stats_map[i][j].dir = direction::none;
                } else if (_map[i][j] == 1) {
                    _count_of_alive++;
                    _stats_map[i][j].health = 1;
                    _stats_map[i][j].type = cell_type::boat;
                    _stats_map[i][j].dir = direction::none;
                } else if (_map[i][j] == 2) {
                    _count_of_alive++;
                    _stats_map[i][j].health = 2;
                    _stats_map[i][j].type = cell_type::destroyer;
                    if ((i + 1 < MSIZE && _map[i + 1][j] == 2) ||
                        (i - 1 >= 0 && _map[i - 1][j] == 2)) {
                        _stats_map[i][j].dir = direction::down;
                    } else if ((j + 1 < MSIZE && _map[i][j + 1] == 2) ||
                                (j - 1 >= 0 && _map[i][j - 1] == 2)) {
                        _stats_map[i][j].dir = direction::left;
                    }
                } else if (_map[i][j] == 3) {
                    _count_of_alive++;
                    _stats_map[i][j].health = 3;
                    _stats_map[i][j].type = cell_type::cruiser;
                    if ((i + 1 < MSIZE && _map[i + 1][j] == 3) ||
                        (i - 1 >= 0 && _map[i - 1][j] == 3)) {
                        _stats_map[i][j].dir = direction::down;
                    } else if ((j + 1 < MSIZE && _map[i][j + 1] == 3) ||
                                (j - 1 >= 0 && _map[i][j - 1] == 3)) {
                        _stats_map[i][j].dir = direction::left;
                    }
                } else {
                    _count_of_alive++;
                    _stats_map[i][j].health = 4;
                    _stats_map[i][j].type = cell_type::battleship;
                    if ((i + 1 < MSIZE && _map[i + 1][j] == 4) ||
                        (i - 1 >= 0 && _map[i - 1][j] == 4)) {
                        _stats_map[i][j].dir = direction::down;
                    } else if ((j + 1 < MSIZE && _map[i][j + 1] == 4) ||
                                (j - 1 >= 0 && _map[i][j - 1] == 4)) {
                        _stats_map[i][j].dir = direction::left;
                    }
                }
            }
        }
        for (int i = 0; i < MSIZE; ++i) {
            for (int j = 0; j < MSIZE; ++j) {
                if (_stats_map[i][j].type != cell_type::none && _stats_map[i][j].coords.size() == 0) {
                    if (_stats_map[i][j].dir == direction::left) {
                        int k = j;
                        std::vector<std::pair<int, int>> tmp_coords;
                        while ((k < MSIZE) && (k < (j + _stats_map[i][j].health))) {
                            tmp_coords.push_back({i, k});
                            k++;
                        }
                        k = j;
                        while ((k < MSIZE) && (k < (j + _stats_map[i][j].health))) {
                            _stats_map[i][k].coords = tmp_coords;
                            k++;
                        }
                    } else {
                        int k = i;
                        std::vector<std::pair<int, int>> tmp_coords;
                        while ((k < MSIZE) && (k < (i + _stats_map[i][j].health))) {
                            tmp_coords.push_back({k, j});
                            k++;
                        }
                        k = i;
                        while ((k < MSIZE) && (k < (i + _stats_map[i][j].health))) {
                            _stats_map[k][j].coords = tmp_coords;
                            k++;
                        }                                
                    }
                }
            }
        }
    }
    void Action::shoot(int row, int col) {
        if (row >= MSIZE || col >= MSIZE || row < 0|| col < 0) {
            return;
        }
        if (_stats_map[row][col].type == cell_type::none) {
            _stats_map[row][col].type = cell_type::missed;
            _map_update();
        } 
        if (_stats_map[row][col].type == cell_type::boat ||
            _stats_map[row][col].type == cell_type::destroyer ||
            _stats_map[row][col].type == cell_type::cruiser ||
            _stats_map[row][col].type == cell_type::battleship) {
            _count_of_alive--;
            _shoot_update(row, col);
            _map_update();
        }
    }
    bool Action::is_gameover() {
        return _count_of_alive == 0;
    }
}
