/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2024 BS(SE)
 * Shape of each piece is represented by rows in the array.
 * TIP: Name the array what is already been coded to avoid any unwanted errors.
 */
 const int BLOCKS[7][4][2] = {//Array for falling pieces
        // I-block
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        // O-block
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        // L-block
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
        // J-block
        {{0, 1}, {1, 1}, {2, 1}, {0, 0}},
        // S-block
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        // Z-block
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        // T-block
        {{1, 0}, {0, 1}, {1, 1}, {2, 1}}
    };
 const int SHADOW[7][4][2] = {//Array for shadow of falling pieces
     // I-block
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
     // O-block
     {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
     // L-block
     {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
     // J-block
     {{0, 1}, {1, 1}, {2, 1}, {0, 0}},
     // S-block
     {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
     // Z-block
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     // T-block
     {{1, 0}, {0, 1}, {1, 1}, {2, 1}}
 };