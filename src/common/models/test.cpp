#include "../lib/test/libtest.h"

#include "Match.h"
#include "Club.h"

using namespace std;

void test_Match_getGrid() {
    Club club1;
    Club club2;
    Match match(club1, club2);
    Case grid[WIDTH][LENGTH];
    match.getGrid(grid);
    ASSERT_NOT_NULL(grid, "Grid is null");
}

#define TESTVEC {T(test_Match_getGrid), \
}

TEST();
