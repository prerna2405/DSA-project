#include <iostream>
using namespace std;
int input_grid[9][9] =
        {
              {6, 0, 0, 0, 0, 0, 0, 3, 8},
					{0, 8, 0, 0, 7, 0, 0, 9, 0},
					{0, 0, 0, 1, 0, 0, 0, 0, 0},
					{5, 0, 0, 6, 0, 0, 7, 0, 0},
					{4, 0, 0, 5, 0, 3, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 2, 0, 1, 0, 0},
					{0, 3, 0, 0, 0, 8, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
struct Playing_grid
{
        int number;
        bool fixed;
}grid[9][9];
void load_input(){
        for (int i = 0; i < 9; i++){
                for (int j = 0; j < 9; j++){
                        if (input_grid[i][j] == 0){
                                grid[i][j].fixed = false;
                                grid[i][j].number = 0;
                        }
                        else{
                                grid[i][j].fixed = true;
                                grid[i][j].number = input_grid[i][j];
                        }
                }
        }
}
void print_grid() {
        for (int i = 0; i < 9; i++)
        {
                for (int j = 0; j < 9; j++)
                {
                        cout << grid[i][j].number << " ";
                }
                cout << endl;
        }
}
bool check_row(int row, int column){
        for (int i = 0; i < 9; i++){
                if (i != column){
                        if (grid[row][i].number == grid[row][column].number ){
                                return false;
                        }
                }
        }
        return true;
}
bool check_column(int row, int column){
        for (int i = 0; i < 9; i++){
                if (i != row){
                        if (grid[i][column].number == grid[row][column].number){
                                return false;
                        }
                }
        }
        return true;
}
bool check_square(int row, int column){
        int vsquare = row/3;
        int hsquare = column/3;
        for (int i = vsquare * 3; i < (vsquare*3 + 3); i++){
                for (int j = hsquare * 3; j < (hsquare*3 + 3); j++) {
                        if (i != row || j != column) {
                                if (grid[ row ][ column ].number == grid[i][j].number) {
                                        return false;
                                }
                        }
                }
        }
        return true;
}
bool solve(int row, int column){
        while (grid[row][column].fixed == true){
                column++;
                if(column > 8) {
                        column = 0;
                        row++;
                }
                if(row > 8) {
                        return true; 
                }
        }
        for (int n = 1; n < 10; n++){
                int try_row, try_column;
                grid[row][column].number = n;
                if ( check_column(row, column) && check_row(row, column) && check_square(row, column)){
                        try_column = column + 1;
                        try_row = row;
                        if(try_column > 8) {
                                try_column = 0;
                                try_row++;
                        }
                        if(try_row > 8) {
                                return true;
                        }
                        if(solve(try_row, try_column)) {
                                return true;
                        }
                } else {
                       cout<<n<<"didn't work at"<<column<<","<<row<<endl;
                }
        }
        grid[row][column].number = 0;
        return false;
}
int main(){
        load_input();
        print_grid();
        if(solve(0,0)){
                cout<<"solved!"<<endl;
        } else {
                cout<<"didn't work!"<<endl;
        }
        cout << endl;
        print_grid();
        return 0;
}
