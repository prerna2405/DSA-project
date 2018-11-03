#include <vector>
#include <iostream>
using namespace std;

class Sudoku {
  public:
    Sudoku();
    void Print_Screen();
    void Print_Convert();
    int Solve();
  protected:
    int Is_Row_Valid(int r);
    int Is_Col_Valid(int c);
    int Is_Panel_Valid(int sr, int sc);
    int Recursive_Solve(int r, int c);
    vector <string> Grid;
    vector <int> checker;
};
#include <cstdio>
#include <cstdlib>

Sudoku::Sudoku()
{
  int i, j;
  char c;

  Grid.resize(9);
  checker.resize('9'+1);

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!(cin >> c)) {
        cerr << "Bad Sudoku File -- not enough entries\n";
        exit(1);
      } 
      if (c == '-' || (c >= '0' && c <= '9')) {
        Grid[i].push_back(c);
      } else {
        cerr << "Bad Sudoku File -- entry: " << c << endl;
        exit(1);
      } 
    }
  }
  for (i = 0; i < 9; i++) {
    if (!Is_Row_Valid(i)) {
      cerr << "Bad Sudoku File -- Bad row " << i << endl;
      exit(1);
    }
    if (!Is_Col_Valid(i)) {
      cerr << "Bad Sudoku File -- Bad col " << i << endl;
      exit(1);
    }
  }
  for (i = 0; i < 9; i += 3) {
    for (j = 0; j < 9; j += 3) {
      if (!Is_Panel_Valid(i, j)) {
        cerr << "Bad Sudoku File -- Bad panel starting at row " << i << " col " << j << endl;
        exit(1);
      }
    }
  }
}

void Sudoku::Print_Screen()
{
  int i, j;

  for (i = 0; i < Grid.size(); i++) {
    for (j = 0; j < Grid[i].size(); j++) {
      if (j != 0) printf(" ");
      printf("%c ", Grid[i][j]);
      if (j == 2 || j == 5) printf("  ");
    }
    printf("\n");
    if (i == 2 || i == 5) printf("\n");
  }
}

void Sudoku::Print_Convert()
{
  int PPS = 24;
  int Border = 3;
  int CW = 1;
  int PW = 2;
  int i, j, x, y;

  printf("convert -size %dx%d xc:Black \\\n", PPS*9+Border*2+CW*8+PW*2, PPS*9+Border*2+CW*8+PW*2);
  printf("  -background White -fill Black \\\n");
  x = Border;
  for (i = 0; i < 9; i++) {
    y = Border;
    for (j = 0; j < 9; j++) {
      printf("\\( -size %dx%d -gravity Center label:%c \\)", PPS, PPS, Grid[i][j]);
      printf(" -geometry %dx%d+%d+%d -gravity NorthWest -composite \\\n", PPS, PPS, x, y);
      y += (PPS+CW);
      if (j == 2 || j == 5) y += PW;
    }
    x += (PPS+CW);
    if (i == 2 || i == 5) x += PW;
  }
  printf("  Sudoku.jpg\n");
}

int Sudoku::Solve()
{
  return Recursive_Solve(0, 0);
}

int Sudoku::Is_Row_Valid(int r)
{
  int i;

  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (i = 0; i < 9; i++) {
    if (Grid[r][i] != '-') {
      if (checker[Grid[r][i]]) return 0;
      checker[Grid[r][i]] = 1;
    }
  }
  return 1;
}

int Sudoku::Is_Col_Valid(int c)
{
  int i, j;
    
  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (i = 0; i < 9; i++) {
    if (Grid[i][c] != '-') {
      if (checker[Grid[i][c]]) return 0;
      checker[Grid[i][c]] = 1;
    }
  }
  return 1;
}

int Sudoku::Is_Panel_Valid(int sr, int sc)
{
  int r, c, i;
  for (i = '0'; i <= '9'; i++) checker[i] = 0;

  for (r = sr; r < sr+3; r++) {
    for (c = sc; c < sc+3; c++) {
      if (Grid[r][c] != '-') {
        if (checker[Grid[r][c]]) return 0;
        checker[Grid[r][c]] = 1;
      }
    }
  }
  return 1;
}

int Sudoku::Recursive_Solve(int r, int c)
{
  int i;
  
  /* Skip all non-dash characters */
  while (r < 9 && Grid[r][c] != '-') {
    c++;
    if (c == 9) {
      r++;
      c = 0;
    }
  }

  /* Base case -- we're done */
  if (r == 9) return 1;

  /* Try each value.  If successful, then return true. */
  for (i = '1'; i <= '9'; i++) {
    Grid[r][c] = i;
    if (Is_Row_Valid(r) && 
        Is_Col_Valid(c) && 
        Is_Panel_Valid(r-r%3, c-c%3) &&
        Recursive_Solve(r, c)) {
      return 1;
    }
  }

  /* If unsuccessful, reset the element and return false. */
  
  Grid[r][c] = '-';
  return 0;
}


