#include "../lib/test/libtest.h"

#include "../lib/json/json.h"

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

void test_Match_json() {
    Club club1;
    Club club2;
    Match match(club1, club2);
    JsonDict * match_dict = new JsonDict(match);
    Match match2(match_dict);
    delete match_dict;
}

#define TESTVEC {T(test_Match_getGrid), \
                 T(test_Match_json) \
}

TEST();
