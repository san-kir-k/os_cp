#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Seabattle {
    const int MSIZE = 10;

    const int BATTLESHIP_C = 1;
    const int CRUISER_C = 2;
    const int DESTROYER_C = 3;
    const int BOAT_C = 4;

    enum class cell_type {
        battleship, 
        cruiser, 
        destroyer, 
        boat, 
        none,
        dead,
        shooted,
        missed
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
            const std::vector<std::vector<int>>& _chose_matrix(int len, direction dir) {
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
            bool _is_available(direction dir, int len, int row, int col) {
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
            void _update(std::vector<std::vector<int>>& av_map, direction dir, int len, int row, int col) {
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
            std::vector<std::vector<int>> _gen_available_map() {
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
        public:
            Battlefield():  battleship_v_slots(0), cruisers_v_slots(0),
                            destroyers_v_slots(0), boats_v_slots(0),
                            battleship_h_slots(0), cruisers_h_slots(0),
                            destroyers_h_slots(0), boats_h_slots(0) {
                _map = std::vector<std::vector<int>>(MSIZE, std::vector<int> (MSIZE, 0));
            };
            ~Battlefield() = default;
            void gen_map() {
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
            std::vector<std::vector<int>> get_map() {
                return _map;
            }
            void get_map_c(int** field) {
                for (int i = 0; i < MSIZE; ++i) {
                    for (int j = 0; j < MSIZE; ++j) {
                        field[i][j] = _map[i][j];
                    }
                }
            }
    };

    class Action {
        private:
            std::vector<std::vector<int>> _map;
            struct cell_stats {
                int health;
                std::vector<std::pair<int, int>> coords;
                cell_type type;
                direction dir;
            };
            std::vector<std::vector<cell_stats>> _stats_map;
            void _death_update(int row, int col, int len) {
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
                    if (area_r < MSIZE && area_c > MSIZE) {
                        _stats_map[area_r][area_c].type = cell_type::missed;
                    }
                    area_r = _stats_map[row][col].coords[0].first - 1;
                    for (int i = 0; i < len + 2; ++i) {
                        area_c = _stats_map[row][col].coords[0].second - 1 + i;
                        if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c > MSIZE) {
                            _stats_map[area_r][area_c].type = cell_type::missed;
                        }
                    }
                    area_r = _stats_map[row][col].coords[0].first + 1;
                    for (int i = 0; i < len + 2; ++i) {
                        area_c = _stats_map[row][col].coords[0].second - 1 + i;
                        if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c > MSIZE) {
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
                    if (area_r < MSIZE && area_c > MSIZE) {
                        _stats_map[area_r][area_c].type = cell_type::missed;
                    }
                    area_c = _stats_map[row][col].coords[0].second - 1;
                    for (int i = 0; i < len + 2; ++i) {
                        area_r = _stats_map[row][col].coords[0].first - 1 + i;
                        if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c > MSIZE) {
                            _stats_map[area_r][area_c].type = cell_type::missed;
                        }
                    }
                    area_c = _stats_map[row][col].coords[0].second + 1;
                    for (int i = 0; i < len + 2; ++i) {
                        area_r = _stats_map[row][col].coords[0].first - 1 + i;
                        if (area_r >= 0 && area_c >= 0 && area_r < MSIZE && area_c > MSIZE) {
                            _stats_map[area_r][area_c].type = cell_type::missed;
                        }
                    }
                }
            }
            void _shoot_update(int row, int col) {
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
        public:
            Action() = default;
            Action(int** field) {
                _map = std::vector<std::vector<int>>(MSIZE, std::vector<int> (MSIZE, 0));
                _stats_map = std::vector<std::vector<cell_stats>>(MSIZE, std::vector<cell_stats> (MSIZE));
                for (int i = 0; i < MSIZE; ++i) {
                    for (int j = 0; j < MSIZE; ++j) {
                        _map[i][j] = field[i][j];
                        if (_map[i][j] == 0) {
                            _stats_map[i][j].health = 0;
                            _stats_map[i][j].type = cell_type::none;
                            _stats_map[i][j].dir = direction::none;
                        } else if (_map[i][j] == 1) {
                            _stats_map[i][j].health = 1;
                            _stats_map[i][j].type = cell_type::boat;
                            _stats_map[i][j].dir = direction::none;
                        } else if (_map[i][j] == 2) {
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
                        if (_stats_map[i][j].type != cell_type::none && _stats_map[i][j].coords.size() != 0) {
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
            ~Action() = default;
            void shoot(int row, int col) {
                if (row >= MSIZE || col >= MSIZE || row < 0|| col < 0) {
                    return;
                }
                if (_stats_map[row][col].type == cell_type::none) {
                    _stats_map[row][col].type = cell_type::missed;
                } 
                if (_stats_map[row][col].type == cell_type::boat ||
                    _stats_map[row][col].type == cell_type::destroyer ||
                    _stats_map[row][col].type == cell_type::cruiser ||
                    _stats_map[row][col].type == cell_type::battleship) {
                    _shoot_update(row, col);
                }
            }
    };
}
