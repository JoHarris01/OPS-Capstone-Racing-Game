// maps.h
// Game maps and map handling - Owned by Teammate A (Maps/Characters)

#pragma once

// Map 1
char map1_row1[] = "S # # # # E  ";
char map1_row2[] = "  # #      # ";

// Map 2 (harder)
char map2_row1[] = "S ## ##  # E ";
char map2_row2[] = " #  ## ##   ";

// Current map data
extern char* currentRow1;
extern char* currentRow2;
extern int selectedMap;
extern int offset;

// Load the selected map
void loadSelectedMap() {
  if (selectedMap == 0) {
    currentRow1 = map1_row1;
    currentRow2 = map1_row2;
  } else {
    currentRow1 = map2_row1;
    currentRow2 = map2_row2;
  }
}

// Simple function to get a character from the map at a position
char getMapTile(int row, int position) {
  if (row == 0) {
    return currentRow1[position % strlen(currentRow1)];
  } else {
    return currentRow2[position % strlen(currentRow2)];
  }
}
