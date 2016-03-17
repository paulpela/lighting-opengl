#pragma once

void render();
void update();
void mainLoop(int t);
void mouseHandler(int button, int state, int x, int y);
void keyboardHandler(unsigned char key, int x, int y);
void onResize(int x, int y);
void passiveMouseMotion(int x, int y);
