/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR SPRING 2024 BS(SE)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include<fstream>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main() {
    srand(time(0));
    RenderWindow window(VideoMode(480, 585), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    
    SoundBuffer buffer1, buffer2, buffer3, buffer4;//Sound effects
    buffer1.loadFromFile("sound/sounds_select.wav");
    buffer2.loadFromFile("sound/movement-swipe-whoosh-3-186577.wav");
    buffer3.loadFromFile("sound/super_mario_dies.wav");
    buffer4.loadFromFile("sound/level-up-2-199574.wav");
    Sound sound1, sound2, sound3, sound4;
    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);
    sound4.setBuffer(buffer4);

    Music music;//Background music
    music.openFromFile("sound/background.wav");
    music.setVolume(40);
    music.setLoop(true);
    music.play();

    obj1.loadFromFile("img/tiles.png");//Images .png
    obj2.loadFromFile("img/tetris.jpg");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadows.png");
    obj5.loadFromFile("img/game over pic.jpg");
    obj6.loadFromFile("img/tetris logo.jpg");
    obj7.loadFromFile("img/see you.png");
    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj4), over(obj5), logo(obj6), bye(obj7);

    Font font, font2;//Fonts
    font.loadFromFile("font/Jaro-Regular-VariableFont_opsz.ttf"); // Adjust font file path as needed
    font2.loadFromFile("font/Autumn in November.ttf");

    int delta_x = 0, colorNum = 1;
    float timer = 0, delay = 0.4;
    bool rotate = 0;
    int cont = 0;//Starts from menu 
    bool end = 0;//Game is over or Game is 
    int highScores[2] = { 0 };//Array for storing highscores
    Clock clock;

        while (window.isOpen()) {
            if (cont == 0) {   //Displaying menu when cont=0
                logo.setPosition(70, 80); //Display Tetris logo
                Text play;//Play button
                play.setFont(font);
                play.setString("Play(P)");
                play.setCharacterSize(24);
                play.setFillColor(Color::White);
                play.setStyle(Text::Bold);
                play.setPosition(150, 300); 

                Text scoreboard;//Highscores button
                scoreboard.setFont(font);
                scoreboard.setString("See Highscores(S)");
                scoreboard.setCharacterSize(24);
                scoreboard.setFillColor(Color::White);
                scoreboard.setStyle(Text::Bold);
                scoreboard.setPosition(150, 360);

                Text help;//Help instructions
                help.setFont(font);
                help.setString("Help(H)");
                help.setCharacterSize(24);
                help.setFillColor(Color::White);
                help.setStyle(Text::Bold);
                help.setPosition(150, 420);

                Text exit;//Exiting the game
                exit.setFont(font);
                exit.setString("Exit(E)");
                exit.setCharacterSize(24);
                exit.setFillColor(Color::White);
                exit.setStyle(Text::Bold);
                exit.setPosition(150, 480);

                window.clear();
                window.draw(background);
                window.draw(logo);
                window.draw(play);
                window.draw(scoreboard);
                window.draw(help);
                window.draw(exit);
                window.display();

                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        return 0; // Exit the program if the window is closed
                    }

                    else if (event.key.code == Keyboard::P && cont != 1) {//play
                        sound1.play();
                        bool scoreInserted = false;
                        for (int i = 0; i < 2; ++i) {//Updating and sorting highscores
                            if (score > highScores[i]) {
                                for (int j = 1; j > i; --j) {
                                    highScores[j] = highScores[j - 1];
                                }
                                highScores[i] = score;
                                scoreInserted = true;
                                break;
                            }
                        }
                        if (scoreInserted) {//Writing highscores to the file highscores.bin
                            std::fstream fs;
                            fs.open("C:\\Users\\admin\\Music\\BS(SE) PF-Project Spring2024\\highscores.bin", std::ios::binary | std::ios::out);
                            if (!fs.is_open()) {
                                std::cout << "Cannot open file";
                            }
                            else {
                                for (int i = 0; i < 2; i++) {
                                    fs.write((char*)&highScores[i], sizeof(highScores[i]));
                                }
                            }
                            fs.close();
                        }
                        //Restoring the initial conditions(starting new game) when play is pressed
                        cont = 1;
                        score = 0;
                        movesUsed = 0;
                        for (int i = 0; i < M; i++) {
                            for (int j = 0; j < N; j++) {
                                gameGrid[i][j] = 0;
                            }
                        }
                        for (int i = 0; i < 4; i++) {
                            if (point_2[i][0] != -1 && point_2[i][1] != -1) {
                                gameGrid[point_2[i][1]][point_2[i][0]] = 0;
                            }
                        }
                        int n = rand() % 7;
                        for (int i = 0; i < 4; i++) {
                            point_1[i][0] = BLOCKS[n][i][0];
                            point_1[i][1] = BLOCKS[n][i][1];
                        }
                    }

                    else if (event.key.code == Keyboard::S) {
                        sound1.play();
                        window.draw(background);
                        // Return to the menu
                        std::fstream fs;
                        fs.open("C:\\Users\\admin\\Music\\BS(SE) PF-Project Spring2024\\highscores.bin", std::ios::binary | std::ios::in);
                        if (!fs.is_open()) {
                            std::cout << "Cannot open file";
                        }
                        else {

                            Text readscore;
                            readscore.setFont(font2);
                            readscore.setString("Highscores");
                            readscore.setCharacterSize(24);
                            readscore.setFillColor(Color::White);
                            readscore.setStyle(Text::Bold);
                            readscore.setPosition(70, 70);

                            for (int i = 0; i < 2; i++) {
                                fs.read((char*)&highScores[i], sizeof(highScores[i]));;//Reading from the file highscores.bin when Scores is clicked

                                Text writescore;
                                writescore.setFont(font2);
                                writescore.setString(std::to_string(highScores[i]));
                                writescore.setCharacterSize(24);
                                writescore.setFillColor(Color::White);
                                writescore.setStyle(Text::Bold);
                                writescore.setPosition(100, 150 + i * 50);

                                window.draw(writescore); 
                            }

                            Text back;
                            back.setFont(font2);
                            back.setString("Back(B)");
                            back.setCharacterSize(24);
                            back.setFillColor(Color::White);
                            back.setStyle(Text::Bold);
                            back.setPosition(100, 150 + 250);
                            
                            window.draw(readscore); 
                            window.draw(back); 
                            window.display();

                            bool highScoresScreenOpen = true;
                            while (highScoresScreenOpen) {
                                Event highScoresEvent;
                                while (window.pollEvent(highScoresEvent)) {
                                    if (highScoresEvent.type == Event::Closed) {
                                        window.close();
                                        return 0;
                                    }
                                    else if (highScoresEvent.key.code == Keyboard::B) {
                                        sound1.play();
                                        highScoresScreenOpen = false;
                                    }
                                }
                            }
                        }
                        fs.close();
                    }
                    
                    else if (event.key.code == Keyboard::E) {
                        sound1.play();//Closing the game when exit pressed
                        end = 1;
                    }

                    else if (event.key.code == Keyboard::H) {
                        sound1.play();//viewing instructions when help is pressed
                        window.draw(background);

                        Text help;
                        help.setFont(font2);
                        help.setString("Help(H)");
                        help.setCharacterSize(24);
                        help.setFillColor(Color::White);
                        help.setStyle(Text::Bold);
                        help.setPosition(70, 50);

                        window.draw(help);

                        Text instructions;
                        instructions.setFont(font); 
                        instructions.setString("Welcome to Tetris! Welcome to Tetris! \nThe objective is to strategically rotate \nand place falling blocks to create complete\n horizontal lines without any gaps. \nUse the arrow keys to move the falling \nblock left or right, \nand the up arrow to rotate it.\n Press the down arrow to \naccelerate its descent. \nOnce a line is complete,\n it will disappear,\n earning you points.\n Be careful not to let the \nblocks reach the top of the screen, \nas this will end the game.\n Press 'B' at any time to return to the menu.\nGood luck and enjoy stacking!"); // Replace "..." with your instructions
                        instructions.setCharacterSize(24);
                        instructions.setFillColor(sf::Color::White);
                        instructions.setStyle(sf::Text::Bold);
                        instructions.setPosition(10, 100); 

                        window.draw(instructions);

                        Text back;
                        back.setFont(font2);
                        back.setString("Back(B)");
                        back.setCharacterSize(24);
                        back.setFillColor(Color::White);
                        back.setStyle(Text::Bold);
                        back.setPosition(50, 150 + 450);
                        
                        window.draw(back);

                        window.display();
                        bool helpScreenOpen = true;
                        while (helpScreenOpen) {
                            Event helpEvent;
                            while (window.pollEvent(helpEvent)) {
                                if (helpEvent.type == Event::Closed) {
                                    window.close();
                                    return 0;
                                }
                                else if (helpEvent.type == Event::KeyPressed && helpEvent.key.code == Keyboard::B) {
                                    sound1.play();
                                    helpScreenOpen = false;
                                }
                            }
                        }
                        
                    }

                }
            }

            if (end) {//If exited the game
                window.clear();
                bye.setPosition(100, 100);
                window.draw(bye);

                Text goodbye;
                goodbye.setFont(font2);
                goodbye.setString("GOODBYE:)");
                goodbye.setCharacterSize(24);
                goodbye.setFillColor(Color::White);
                goodbye.setStyle(Text::Bold);
                goodbye.setPosition(150, 400);

                window.draw(goodbye);

                window.display();
                sleep(seconds(2));
                window.close();
                return 0;
            }

            if (cont == -1) {//If Paused (X) is pressed during the game
                logo.setPosition(70, 80);

                Text restart;//Restart
                restart.setFont(font);
                restart.setString("Replay(R)");
                restart.setCharacterSize(24);
                restart.setFillColor(Color::White);
                restart.setStyle(Text::Bold);
                restart.setPosition(150, 360); 

                Text continuegame;//Continue
                continuegame.setFont(font);
                continuegame.setString("Continue(C)");
                continuegame.setCharacterSize(24);
                continuegame.setFillColor(Color::White);
                continuegame.setStyle(Text::Bold);
                continuegame.setPosition(150, 420);

                window.clear(Color::Black);
                window.draw(background);
                window.draw(logo);
                window.draw(restart);
                window.draw(continuegame);
                window.display();

                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        return 0; // Exit the program if the window is closed
                    }
                    else if (event.key.code == Keyboard::R && (cont == 1 || cont == -1 || cont == 2)) {
                        sound1.play();//To restart the game go back to the main menu
                        cont = 0;
                        clock.restart();
                    }
                    else if (event.key.code == Keyboard::C) {
                        sound1.play();// To continue the game
                        cont = 1;
                    }
                }
            }

            if (cont == 2) {//If the game is over
                over.setPosition(70, 80);

                Text restart;//Restart
                restart.setFont(font);
                restart.setString("Replay(R)");
                restart.setCharacterSize(24);
                restart.setFillColor(Color::White);
                restart.setStyle(Text::Bold);
                restart.setPosition(150, 360);

                Text exit;//Exit
                exit.setFont(font);
                exit.setString("Exit(E)");
                exit.setCharacterSize(24);
                exit.setFillColor(Color::White);
                exit.setStyle(Text::Bold);
                exit.setPosition(150, 420);

                window.clear(Color::Black);
                window.draw(background);
                window.draw(over);
                window.draw(restart);
                window.draw(exit);
                window.display();

                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                        return 0; // Exit the program if the window is closed
                    }
                    else if (event.key.code == Keyboard::R && (cont == 1 || cont == -1 || cont == 2)) {
                        sound1.play();//To restart the game
                        cont = 0;
                        clock.restart();
                    }
                    else if (event.key.code == Keyboard::E) {
                        sound1.play();//To exit the game
                        end = 1;
                    }
                }
            }

            if (cont == 1) {//When the game is in playing state
                float time = clock.getElapsedTime().asSeconds();
                clock.restart();
                timer += time;

                //---Event Listening Part---//
                Event e;
                while (window.pollEvent(e)) {                    //Event is occurring - until the game is in running state
                    if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                        window.close();                            //Opened window disposes
                    if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                        if (e.key.code == Keyboard::Up) {         //Check if the other key pressed is UP key
                            sound2.play();
                            rotate = true;
                        }                                          //Rotation gets on
                        else if (e.key.code == Keyboard::Left) {     //Check if the other key pressed is LEFT key
                            sound2.play();
                            delta_x = -1;
                        }                                           //Change in X-Axis - Negative
                        else if (e.key.code == Keyboard::Right) {    //Check if the other key pressed is RIGHT key
                            sound2.play();
                            delta_x = 1;
                        }                                               //Change in X-Axis - Positive
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {   //Just another way to detect key presses without event listener
                    delay = 0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
                }

                ///////////////////////////////////////////////
                ///*** START CALLING YOUR FUNCTIONS HERE ***///
                
                fallingPiece(timer, delay, colorNum);
                
                while (window.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        window.close();
                        return 0; // Exit the program if the window is closed
                    }

                    else if (e.key.code == Keyboard::X) {//To pause the game
                        sound1.play();
                        cont = -1;
                    }
                }
                
                int lev = updateLevel();
                
                rotatePiece(rotate);

                moveLeft(delta_x);

                moveRight(delta_x);

                shadows();
                if (gameOver()) {
                    sound3.play();
                    cont = 2;
                }

                //Example: fallingPiece() function is called here
                ///*** YOUR CALLING STATEMENTS END HERE ***///
                //////////////////////////////////////////////

                window.clear(Color::Black);
                window.draw(background);
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        if (gameGrid[i][j] == 0)
                            continue;
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        sprite.setPosition(j * 18, i * 18);
                        sprite.move(28, 31); //offset
                        window.draw(sprite);
                    }
                }

                for (int i = 0; i < 4; i++) {
                    sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                    sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                    sprite.move(28, 31);
                    window.draw(sprite);
                }

                Text pause;//Pause text
                pause.setFont(font);
                pause.setString("Pause(X)");
                pause.setCharacterSize(24);
                pause.setFillColor(Color::White);
                pause.setStyle(Text::Bold);
                pause.setPosition(150, 500);

                Text scores;//Scores text
                scores.setFont(font);
                scores.setString("Scores");
                scores.setCharacterSize(24);
                scores.setFillColor(Color::White);
                scores.setStyle(Text::Bold);
                scores.setPosition(230, 200);

                Text moves;//Moves text
                moves.setFont(font);
                moves.setString("Moves");
                moves.setCharacterSize(24);
                moves.setFillColor(Color::White);
                moves.setStyle(Text::Bold);
                moves.setPosition(230, 250);

                Text levels;//Level text
                levels.setFont(font);
                levels.setString("Level");
                levels.setCharacterSize(24);
                levels.setFillColor(Color::White);
                levels.setStyle(Text::Bold);
                levels.setPosition(230, 300);

                Text displayScores;//displaying live scores
                displayScores.setFont(font);
                displayScores.setString(std::to_string(score));
                displayScores.setCharacterSize(24);
                displayScores.setFillColor(Color::White);
                displayScores.setStyle(Text::Bold);
                displayScores.setPosition(340, 200);

                Text displayMoves;//Displaying live moves
                displayMoves.setFont(font);
                displayMoves.setString(std::to_string(movesUsed));
                displayMoves.setCharacterSize(24);
                displayMoves.setFillColor(Color::White);
                displayMoves.setStyle(Text::Bold);
                displayMoves.setPosition(340, 250);

                Text displayLevel;//Displaying live level
                displayLevel.setFont(font);
                displayLevel.setString("Begginer");
                displayLevel.setCharacterSize(24);
                displayLevel.setFillColor(Color::White);
                displayLevel.setStyle(Text::Bold);
                displayLevel.setPosition(340, 300);

                window.draw(pause);
                window.draw(scores);
                window.draw(moves);
                window.draw(levels);
                window.draw(displayScores);
                window.draw(displayMoves);
                window.draw(displayLevel);
                //---The Final on Which Everything is Drawn Over is Loaded---//
                window.draw(frame);
                //---The Window that now Contains the Frame is Displayed---//
                window.display();
            }
        }
    
    return 0;
}
