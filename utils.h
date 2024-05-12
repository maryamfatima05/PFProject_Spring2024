/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR SPRING 2024 BS(SE)
 * This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * TIP: After completing your project, you can make changes for aesthetics.
 * */

//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "PF-Project, Spring-2024";
int level = 1;
bool levelUpdated = false;
int linesCleared = 0;
int movesUsed = 0;
int score = 0;
//---Height and Width of the Actual Interactive Game---//
const int blockSize = 5;
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10
const int CELL = 8;
const int SCREEN = 4;
//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece and shadows---//
int point_1[4][2], point_2[4][2], point_3[4][2];

//---Check Uncertain Conditions---//
bool anamoly(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=M)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
    return 1;
};
bool anamoly_shadow() {
    for (int i = 0; i < 4; i++) {
        // If any point of the falling piece reaches the bottom of the grid
        // or there's a filled cell below it, return true indicating an obstacle
        if (point_3[i][1] >= M - 1 || gameGrid[point_3[i][1] + 1][point_3[i][0]] == 1) {
            return true;
        }
    }
    // If no obstacles are found, return false
    return false;
};
