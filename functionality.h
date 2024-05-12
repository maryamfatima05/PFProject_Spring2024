/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR SPRING 2024 BS(SE)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */
void shadows() {//Function to form shadows
    for (int i = 0; i < 4; i++) {
        point_3[i][0] = point_1[i][0];
        point_3[i][1] = point_1[i][1];

    }
    while (!anamoly_shadow) {
        for (int i = 0; i < 4; i++) {
            point_3[i][1] += 1;
        }
    }
    if (anamoly_shadow) {
        for (int i = 0; i < 4; i++) {
            point_3[i][1] -= 1;
        }
    }
}

int updateLevel() {//Function to update level
    if (linesCleared % 5 == 0 && !levelUpdated) {
        level++;
        levelUpdated = true; 
    }
    return level;
}

int calculateLinesCleared() {//Functions to calculate the number of lines cleared
    int lines = 0;
    for (int y = 0; y < M; ++y) {
        bool rowFull = true;
        for (int x = 0; x < N; ++x) {
            if (gameGrid[y][x] != 1) {
                rowFull = false;
                break;
            }
        }
        if (rowFull) {
            lines++;
        }
    }
    if (lines % 10 == 0) {
        updateLevel();
    }
    return lines;
}

int calculateScore(int linesClearedThisMove, int level) {//Function to calculate the scores based on the number of lines cleared in one move
    int score = 0;
    switch (linesClearedThisMove) {
    case 1:
        score += 10 * (level);
        break;
    case 2:
        score += 30 * (level);
        break;
    case 3:
        score += 60 * (level);
        break;
    case 4:
        score += 100 * (level);
        break;
    default:
        break;
    }
    return score;
}

float adjustDelay(float baseDelay) {//Function to set the speed according to the level
    return baseDelay - (level - 1) * 0.1; // Decrease delay by 0.1 second per level
}
int clearFilledLines() {//Function to clear the filled rows and to calculate the score according to that 
    int linesClearedThisMove = 0; 
    for (int y = M - 1; y >= 0; --y) {
        bool rowFull = true;

        for (int x = 0; x < N; ++x) {
            
            if (gameGrid[y][x] == 0) {
                rowFull = false;
                
                
                    
                    break;
                }
            }
        if (rowFull) {
            linesClearedThisMove++;
            for (int i = y; i > 0; --i) {
                for (int x = 0; x < N; ++x) {
                    gameGrid[i][x] = gameGrid[i - 1][x];
                }
            }
            for (int x = 0; x < N; ++x) {
                gameGrid[0][x] = 0;
            }
            ++y;
        }
    }
    linesClearedThisMove += calculateLinesCleared();
    int scoreThisMove = calculateScore(linesClearedThisMove, updateLevel());
    score += scoreThisMove;
    return score;
}

bool gameOver()//Function to track if the game is over
{
    for (int i = 0; i < N; i++)
    {
        if (gameGrid[1][i] != 0)
            return 1;
    }
    return 0;
}

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum) {//Fucntion where the actual game startd
    if (gameOver()) {
        return;
    }
    int score = 0;
    if (timer > delay) {
        for (int i = 0; i < 4; i++) {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1;
        }
            if (!anamoly()) {
                std::cout << "Level: " << level << std::endl;
                movesUsed++;
                std::cout << "Moves: " << movesUsed<<std::endl;
                delay = 0.4;
                int n = rand() % 7; // Random index for selecting a piece from the BLOCKS array
                colorNum =rand() % 8;//Random color generating 
                for (int i = 0; i < 4; i++) {
                    int x = BLOCKS[n][i][0];
                    int y = BLOCKS[n][i][1];
                    point_1[i][0] = x;
                    point_1[i][1] = y;
                }

                for (int i = 0; i < 4; i++) {
                    gameGrid[point_2[i][1]][point_2[i][0]] = 1;
                }
                    clearFilledLines();

                for (int i = 0; i < 4; i++) {
                    point_2[i][0] = -1;
                    point_2[i][1] = -1;
                }
                
                    std::cout << "Score:" << clearFilledLines()<<std::endl;
                    std::cout << "Speed: " << adjustDelay(delay) <<std::endl;            }
            
            timer = 0; // Reset the timer
        }
    }


/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
void rotatePiece(bool& rotate) {//Function to rotte the falling piece
    if (rotate) {
        int centerX = (point_1[0][0] + point_1[1][0] + point_1[2][0] + point_1[3][0]) / 4;
        int centerY = (point_1[0][1] + point_1[1][1] + point_1[2][1] + point_1[3][1]) / 4;

        for (int i = 0; i < 4; i++) {
            int deltaX = point_1[i][0] - centerX;
            int deltaY = point_1[i][1] - centerY;

            int newX = centerX + deltaY;
            int newY = centerY - deltaX;

            if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
                point_1[i][0] = newX;
                point_1[i][1] = newY;
            }
        }

        rotate = false; 
    }
}

void moveLeft(int& delta_x) {//Function to move the piece left
    if (delta_x == -1) {
        
        bool canMoveLeft = true;
        for (int i = 0; i < 4; i++) {
            if (point_1[i][0] <= 0) {
                canMoveLeft = false;
                break;
            }
        }

        if (canMoveLeft) {
            for (int i = 0; i < 4; i++) {
                point_1[i][0]--;
            }
        }
        delta_x = 0; 
    }
}

void moveRight(int& delta_x) {//Function to move the piece right
    if (delta_x == 1) {
        
        bool canMoveRight = true;
        for (int i = 0; i < 4; i++) {
            if (point_1[i][0] >= N - 1) {
                canMoveRight = false;
                break;
            }
        }

        if (canMoveRight) {
            for (int i = 0; i < 4; i++) {
                point_1[i][0]++;
            }
        }

        delta_x = 0; 
    }
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
