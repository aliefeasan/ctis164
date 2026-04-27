/**********************************
 CTIS164 - Homework 2
-----------------------------------
NAME SURNAME : Ali Efe Asan
STUDENT ID   : 22402968
SECTION      :
HOMEWORK     : 2
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define TIMER_PERIOD  16
#define TIMER_ON       1
#define D2R 0.01745329252
#define PI  3.14159265358
#define GAME_LEFT    -300
#define GAME_RIGHT    220
#define GAME_TOP      270
#define GAME_BOTTOM  -200
#define BOARD_LEFT    230
#define BOARD_RIGHT   390
#define KEYS_BOTTOM  -270
#define KEYS_TOP     -210
#define ST_WAITING  0
#define ST_PLAYING  1
#define ST_PAUSED   2
#define ST_OVER     3

bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight;


float subY = 0;
float subSpeed = 4.0f;


bool  torpActive = false;
float torpX, torpY;
float torpSpeed = 8.5f;

#define MAX_UFOS 5
struct Ufo {
    bool alive;
    float x, y;
    float spd;
    float radius;
};
Ufo ufos[MAX_UFOS];

int   totalScore = 0;
int   lastPts = 0;
int   totalRockets = 0;
int   burstRockets = 0;
float timeLeft = 30.0f;


int gameState = ST_WAITING;
int spawnDelay[MAX_UFOS];


void circle(int x, int y, int r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 3)
        glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
    glEnd();
}

void circle_wire(int x, int y, int r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 3)
        glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
    glEnd();
}

void drawText(const char* text, float x, float y, void* font) {
    glRasterPos2f(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(font, text[i]);
}

void print(int x, int y, const char* string, void* font) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);
}

void vprint(int x, int y, void* font, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, str[i]);
}

void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);
    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    glPopMatrix();
}



void spawnUfo(int slot) {
    ufos[slot].alive = true;

    ufos[slot].radius = 18 + rand() % 10;


    float laneCenterX = -130.0f + (slot * 70.0f);


    ufos[slot].x = laneCenterX + (rand() % 15 - 7);

    ufos[slot].y = (float)(GAME_BOTTOM + ufos[slot].radius + 2);
    ufos[slot].spd = 1.0f + (rand() % 28) / 10.0f;
    spawnDelay[slot] = 0;
}

void resetGame() {
    totalScore = 0;
    lastPts = 0;
    totalRockets = 0;
    burstRockets = 0;
    timeLeft = 30.0f;
    torpActive = false;
    subY = 0;

    for (int i = 0; i < MAX_UFOS; i++) {
        ufos[i].alive = false;
        spawnDelay[i] = i * 40;
    }
}


void drawSub(float cx, float cy) {
    glColor3f(0.2f, 0.55f, 0.2f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5) {
        float rx = 38 * cos(i * D2R);
        float ry = 17 * sin(i * D2R);
        glVertex2f(cx + rx, cy + ry);
    }
    glEnd();

    glColor3f(0.15f, 0.45f, 0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(cx - 8, cy + 17);
    glVertex2f(cx - 8, cy + 34);
    glVertex2f(cx + 10, cy + 34);
    glVertex2f(cx + 10, cy + 17);
    glEnd();

    glColor3f(0.1f, 0.35f, 0.1f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(cx + 3, cy + 34);
    glVertex2f(cx + 3, cy + 44);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(cx + 3, cy + 44);
    glVertex2f(cx + 13, cy + 44);
    glEnd();
    glLineWidth(1);

    glColor3f(0.5f, 0.4f, 0.1f);
    for (int b = 0; b < 3; b++) {
        float ang = b * 120.0f * D2R;
        glBegin(GL_POLYGON);
        glVertex2f(cx - 38, cy);
        glVertex2f(cx - 38 + 7 * cos(ang), cy + 7 * sin(ang));
        glVertex2f(cx - 38 + 13 * cos(ang + 0.5f), cy + 13 * sin(ang + 0.5f));
        glVertex2f(cx - 38 + 7 * cos(ang + 1.0f), cy + 7 * sin(ang + 1.0f));
        glEnd();
    }

    glColor3f(0.6f, 0.85f, 0.9f);
    circle((int)(cx + 15), (int)cy, 7);
    glColor3f(0.1f, 0.3f, 0.5f);
    circle_wire((int)(cx + 15), (int)cy, 7);

    glColor3f(0.15f, 0.45f, 0.15f);
    glBegin(GL_TRIANGLES);
    glVertex2f(cx + 38, cy + 6);
    glVertex2f(cx + 38, cy - 6);
    glVertex2f(cx + 52, cy);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(cx + 48, cy + 4);
    glVertex2f(cx + 53, cy + 4);
    glVertex2f(cx + 53, cy - 4);
    glVertex2f(cx + 48, cy - 4);
    glEnd();
}

void drawTorpedo(float tx, float ty) {
    glColor3f(0.7f, 0.7f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rx = 10 * cos(i * D2R);
        float ry = 5 * sin(i * D2R);
        glVertex2f(tx + rx, ty + ry);
    }
    glEnd();

    glColor3f(0.9f, 0.3f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(tx + 10, ty + 3);
    glVertex2f(tx + 10, ty - 3);
    glVertex2f(tx + 18, ty);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(tx - 10, ty);
    glVertex2f(tx - 5, ty + 7);
    glVertex2f(tx - 3, ty + 2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(tx - 10, ty);
    glVertex2f(tx - 5, ty - 7);
    glVertex2f(tx - 3, ty - 2);
    glEnd();
}

void drawUfo(float cx, float cy, float r) {
    glColor3f(0.55f, 0.55f, 0.65f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5)
        glVertex2f(cx + r * cos(i * D2R), cy + r * 0.38f * sin(i * D2R));
    glEnd();

    glColor3f(0.3f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 180; i += 5)
        glVertex2f(cx + r * 0.5f * cos(i * D2R), cy + r * 0.55f * sin(i * D2R));
    glEnd();

    glColor3f(0.8f, 0.8f, 0.95f);
    glBegin(GL_POLYGON);
    for (int i = 160; i < 380; i += 5)
        glVertex2f(cx + r * cos(i * D2R), cy + r * 0.2f * sin(i * D2R));
    glEnd();

    float lightColors[3][3] = { {1,0.2f,0.2f},{0.2f,1,0.2f},{1,1,0.2f} };
    for (int k = 0; k < 3; k++) {
        float ang = (k * 120.0f) * D2R;
        glColor3f(lightColors[k][0], lightColors[k][1], lightColors[k][2]);
        circle((int)(cx + r * 0.65f * cos(ang)), (int)(cy - r * 0.18f), 4);
    }

    glColor3f(0.3f, 0.3f, 0.4f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 5)
        glVertex2f(cx + r * cos(i * D2R), cy + r * 0.38f * sin(i * D2R));
    glEnd();
}

void drawGameArea() {
    glBegin(GL_QUADS);
    glColor3f(0.04f, 0.04f, 0.16f);
    glVertex2f(GAME_LEFT, GAME_TOP);
    glVertex2f(GAME_RIGHT, GAME_TOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(GAME_RIGHT, GAME_BOTTOM);
    glVertex2f(GAME_LEFT, GAME_BOTTOM);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.9f);
    int starX[] = { -220,-170,-100,-60,-10, 40, 90,130,180,-240,-130,-80, 20, 70,150,200,-200,-40,110 };
    int starY[] = { 240, 210, 250,230,260,240,220,255,235, 180, 190,170,200,185,195,215, 150,160,145 };
    for (int s = 0; s < 19; s++) {
        glBegin(GL_QUADS);
        glVertex2f(starX[s] - 1.5f, starY[s] - 1.5f);
        glVertex2f(starX[s] + 1.5f, starY[s] - 1.5f);
        glVertex2f(starX[s] + 1.5f, starY[s] + 1.5f);
        glVertex2f(starX[s] - 1.5f, starY[s] + 1.5f);
        glEnd();
    }
}

void drawScoreboard() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(BOARD_LEFT, GAME_TOP);
    glVertex2f(BOARD_RIGHT, GAME_TOP);
    glVertex2f(BOARD_RIGHT, GAME_BOTTOM);
    glVertex2f(BOARD_LEFT, GAME_BOTTOM);
    glEnd();

    int bx = BOARD_LEFT + 12;
    int rowH = 88;
    int topY = 235;

    glColor3f(1.0f, 1.0f, 1.0f);
    vprint(bx, topY, GLUT_BITMAP_HELVETICA_12, "REMAINING");
    vprint(bx, topY - 14, GLUT_BITMAP_HELVETICA_12, "TIME");
    if (timeLeft <= 5.0f && gameState == ST_PLAYING)
        glColor3f(1.0f, 0.15f, 0.15f);
    else
        glColor3f(0.0f, 1.0f, 0.0f);
    vprint(bx + 5, topY - 34, GLUT_BITMAP_HELVETICA_18, "%05.2f", timeLeft);

    glColor3f(1.0f, 1.0f, 1.0f);
    vprint(bx, topY - rowH, GLUT_BITMAP_HELVETICA_12, "TOTAL");
    vprint(bx, topY - rowH - 14, GLUT_BITMAP_HELVETICA_12, "ROCKETS");
    glColor3f(1.0f, 1.0f, 0.0f);
    vprint(bx + 5, topY - rowH - 34, GLUT_BITMAP_HELVETICA_18, "%02d", totalRockets);

    glColor3f(1.0f, 1.0f, 1.0f);
    vprint(bx, topY - 2 * rowH, GLUT_BITMAP_HELVETICA_12, "BURST");
    vprint(bx, topY - 2 * rowH - 14, GLUT_BITMAP_HELVETICA_12, "ROCKETS");
    glColor3f(1.0f, 1.0f, 0.0f);
    vprint(bx + 5, topY - 2 * rowH - 34, GLUT_BITMAP_HELVETICA_18, "%02d", burstRockets);

    glColor3f(1.0f, 1.0f, 1.0f);
    vprint(bx, topY - 3 * rowH, GLUT_BITMAP_HELVETICA_12, "LAST");
    vprint(bx, topY - 3 * rowH - 14, GLUT_BITMAP_HELVETICA_12, "POINTS");
    glColor3f(1.0f, 1.0f, 0.0f);
    vprint(bx + 5, topY - 3 * rowH - 34, GLUT_BITMAP_HELVETICA_18, "%02d", lastPts);

    glColor3f(1.0f, 1.0f, 1.0f);
    vprint(bx, topY - 4 * rowH, GLUT_BITMAP_HELVETICA_12, "TOTAL");
    vprint(bx, topY - 4 * rowH - 14, GLUT_BITMAP_HELVETICA_12, "POINTS");
    glColor3f(1.0f, 0.0f, 0.0f);
    vprint(bx + 5, topY - 4 * rowH - 34, GLUT_BITMAP_HELVETICA_18, "%02d", totalScore);
}

void drawKeysArea() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(GAME_LEFT, KEYS_BOTTOM);
    glVertex2f(BOARD_RIGHT, KEYS_BOTTOM);
    glVertex2f(BOARD_RIGHT, GAME_BOTTOM);
    glVertex2f(GAME_LEFT, GAME_BOTTOM);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    vprint(GAME_LEFT + 10, KEYS_BOTTOM + 38, GLUT_BITMAP_HELVETICA_18, "Press <F1> to start a new game");
}

void drawStatusMsg() {
    if (gameState == ST_PAUSED) {
        glColor3f(1.0f, 0.6f, 0.1f);
        vprint(-75, 10, GLUT_BITMAP_HELVETICA_18, "-- PAUSED --");
    }
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGameArea();
    drawScoreboard();
    drawKeysArea();

    for (int i = 0; i < MAX_UFOS; i++) {
        if (!ufos[i].alive) continue;
        drawUfo(ufos[i].x, ufos[i].y, ufos[i].radius);
    }

    if (torpActive)
        drawTorpedo(torpX, torpY);

    float subDrawX = GAME_LEFT + 65;
    drawSub(subDrawX, subY);

    glColor3f(0.6f, 0.6f, 0.7f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(GAME_LEFT, GAME_BOTTOM);
    glVertex2f(GAME_RIGHT, GAME_BOTTOM);
    glVertex2f(GAME_RIGHT, GAME_TOP);
    glVertex2f(GAME_LEFT, GAME_TOP);
    glEnd();
    glLineWidth(1);

    drawStatusMsg();
    glutSwapBuffers();
}


void onKeyDown(unsigned char key, int x, int y) {
    if (key == 27) {
        if (gameState == ST_PLAYING)
            gameState = ST_PAUSED;
        else if (gameState == ST_PAUSED)
            gameState = ST_PLAYING;
    }
    if (key == ' ' && gameState == ST_PLAYING && !torpActive) {
        float subDrawX = GAME_LEFT + 65;
        torpX = subDrawX + 54;
        torpY = subY;
        torpActive = true;
        totalRockets++;
    }
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
    glutPostRedisplay();
}

void onSpecialKeyDown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    up = true; break;
    case GLUT_KEY_DOWN:  down = true; break;
    case GLUT_KEY_LEFT:  left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    case GLUT_KEY_F1:
        if (gameState == ST_WAITING || gameState == ST_OVER) {
            resetGame();
            gameState = ST_PLAYING;
        }
        else if (gameState == ST_PAUSED || gameState == ST_PLAYING) {
            resetGame();
            gameState = ST_PLAYING;
        }
        break;
    }
    glutPostRedisplay();
}

void onSpecialKeyUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    up = false; break;
    case GLUT_KEY_DOWN:  down = false; break;
    case GLUT_KEY_LEFT:  left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }
    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y) {
    glutPostRedisplay();
}

void onResize(int w, int h) {
    winWidth = w; winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    display();
}

void onMoveDown(int x, int y) { glutPostRedisplay(); }
void onMove(int x, int y) { glutPostRedisplay(); }


#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (gameState != ST_PLAYING) {
        glutPostRedisplay();
        return;
    }

    float dt = TIMER_PERIOD / 1000.0f;
    timeLeft -= dt;
    if (timeLeft <= 0.0f) {
        timeLeft = 0.0f;
        gameState = ST_OVER;
        torpActive = false;
        glutPostRedisplay();
        return;
    }

    float subTopLimit = GAME_TOP - 22;
    float subBottomLimit = GAME_BOTTOM + 22;
    if (up && subY < subTopLimit)    subY += subSpeed;
    if (down && subY > subBottomLimit) subY -= subSpeed;

    if (torpActive) {
        torpX += torpSpeed;

        if (torpX > GAME_RIGHT) {
            torpActive = false;
        }

        for (int i = 0; i < MAX_UFOS; i++) {
            if (!ufos[i].alive) continue;

            float torpTipX = torpX + 18;
            float dx = torpTipX - ufos[i].x;
            float dy = torpY - ufos[i].y;
            float dist = sqrt(dx * dx + dy * dy);

            if (dist <= ufos[i].radius) {
                ufos[i].alive = false;
                burstRockets++;


                float dikeyHizalanma = fabs(dy);
                float oran = dikeyHizalanma / ufos[i].radius;

                int kazanilanPuan = 5; 
                if (oran > 0.2f) kazanilanPuan = 4;
                if (oran > 0.4f) kazanilanPuan = 3;
                if (oran > 0.6f) kazanilanPuan = 2;
                if (oran > 0.8f) kazanilanPuan = 1; 

                lastPts = kazanilanPuan;
                totalScore += kazanilanPuan;

                spawnDelay[i] = 40 + rand() % 60;
            }
        }
    }

    for (int i = 0; i < MAX_UFOS; i++) {
        if (!ufos[i].alive) continue;
        ufos[i].y += ufos[i].spd;

        if (ufos[i].y + ufos[i].radius >= GAME_TOP) {
            ufos[i].alive = false;
            spawnDelay[i] = 30 + rand() % 60;
        }
    }

    for (int i = 0; i < MAX_UFOS; i++) {
        if (ufos[i].alive) continue;
        if (spawnDelay[i] > 0) {
            spawnDelay[i]--;
        }
        else {
            spawnUfo(i);
        }
    }

    glutPostRedisplay();
}
#endif


void Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand((unsigned int)time(NULL));

    for (int i = 0; i < MAX_UFOS; i++) {
        ufos[i].alive = false;
        spawnDelay[i] = i * 35;
    }
}

// ========================================================
//  Main
// ========================================================

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 150);
    glutCreateWindow("CTIS164 HW2 - 2025-2026 SPRING - Ali Efe Asan");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);
    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();
    glutMainLoop();
    return 0;
}