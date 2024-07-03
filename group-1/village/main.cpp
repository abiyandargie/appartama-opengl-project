#include <cmath>
#include <GL/glut.h>

// Movement variables
float moveC = 0.0f;
float moveCar1 = 0.0f;
float moveCar2 = 0.0f;
float moveSun = 0.0f;
float speed = 0.02f;

// Camera position and orientation
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 30.0f;
float cameraAngle = 0.0f; // Y-axis rotation angle
float cameraRotationSpeed = 1.0f;

// Light position
float lightPosition[] = { 10.0f, 20.0f, 10.0f, 1.0f };

void DrawSun() {
    glColor3f(1.0f, 0.647f, 0.0f); // Orange color for the sun
    glPushMatrix();
    glTranslatef(15.0f + moveSun, 10.0f, -5.0f);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
}

void DrawClouds() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(moveC, 0.0f, 0.0f);
    for (float i = 0; i <= 20; i += 5) {
        glPushMatrix();
        glTranslatef(i, 7.0, 0);
        glutSolidSphere(0.7, 250, 250);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i + 1.0, 7.0, 0);
        glutSolidSphere(0.7, 250, 250);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i + 2.0, 7.0, 0);
        glutSolidSphere(0.7, 250, 250);
        glPopMatrix();
    }
    glPopMatrix();
}

void DrawGround() {
    glColor3f(0.098f, 0.502f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-12.0f, -12.0f, -10.0f);
    glVertex3f(38.0f, -12.0f, -10.0f);
    glVertex3f(38.0f, -12.0f, 10.0f);
    glVertex3f(-12.0f, -12.0f, 10.0f);
    glEnd();
}

void DrawRoad() {
    glColor3f(0.412f, 0.412f, 0.412f);
    glBegin(GL_QUADS);
    glVertex3f(-12.0f, -12.0f, 0.0f);
    glVertex3f(38.0f, -12.0f, 0.0f);
    glVertex3f(38.0f, -17.0f, 0.0f);
    glVertex3f(-12.0f, -17.0f, 0.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    for (float i = -12.0f; i < 38.0f; i += 3.0f) {
        glBegin(GL_QUADS);
        glVertex3f(i, -14.5f, 0.01f);
        glVertex3f(i + 2.0f, -14.5f, 0.01f);
        glVertex3f(i + 2.0f, -14.0f, 0.01f);
        glVertex3f(i, -14.0f, 0.01f);
        glEnd();
    }
}

void DrawCar(float moveCar, float x, float y, float z, float angle) {
    glPushMatrix();
    glTranslatef(x + moveCar, y, z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Car body
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Car roof
    glColor3f(0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex3f(-0.4f, 0.5f, 0.4f);
    glVertex3f(0.4f, 0.5f, 0.4f);
    glVertex3f(0.4f, 0.7f, 0.4f);
    glVertex3f(-0.4f, 0.7f, 0.4f);
    glVertex3f(-0.4f, 0.5f, -0.4f);
    glVertex3f(0.4f, 0.5f, -0.4f);
    glVertex3f(0.4f, 0.7f, -0.4f);
    glVertex3f(-0.4f, 0.7f, -0.4f);
    glEnd();

    // Car wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.3f, -0.5f, 0.5f);
    glVertex3f(-0.1f, -0.5f, 0.5f);
    glVertex3f(-0.1f, -0.7f, 0.5f);
    glVertex3f(-0.3f, -0.7f, 0.5f);
    glVertex3f(0.3f, -0.5f, 0.5f);
    glVertex3f(0.1f, -0.5f, 0.5f);
    glVertex3f(0.1f, -0.7f, 0.5f);
    glVertex3f(0.3f, -0.7f, 0.5f);
    glEnd();

    glPopMatrix();
}

void DrawHouse(float x, float y, float z) {
    // House base
    glColor3f(0.82f, 0.41f, 0.12f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    // Roof
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    glEnd();

    glPopMatrix();
}

void DrawTree(float x, float y, float z) {
    glColor3f(0.133f, 0.545f, 0.133f); // Dark green color for tree
    glPushMatrix();
    glTranslatef(x, y, z);

    // Tree trunk
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, -1.0f, 0.0f);
    glVertex3f(0.2f, -1.0f, 0.0f);
    glVertex3f(0.2f, 1.0f, 0.0f);
    glVertex3f(-0.2f, 1.0f, 0.0f);
    glEnd();

    // Tree leaves
    glColor3f(0.0f, 0.392f, 0.0f); // Green color for leaves
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0, 50, 50);

    glPopMatrix();
}

void DrawJungle() {
    // Draw trees at different positions
    DrawTree(-18.0f, -10.0f, 0.0f);
    DrawTree(-15.0f, -11.0f, 0.0f);
    DrawTree(-10.0f, -12.0f, 0.0f);
    DrawTree(-5.0f, -10.5f, 0.0f);
    DrawTree(5.0f, -11.5f, 0.0f);
    DrawTree(10.0f, -12.0f, 0.0f);
    DrawTree(15.0f, -10.0f, 0.0f);
    DrawTree(18.0f, -11.0f, 0.0f);
}

void DrawAllComponents() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Light position setup
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    DrawSun();
    DrawClouds();
    DrawGround();
    DrawRoad();

    DrawCar(moveCar1, 0.0f, -14.5f, 0.0f, 0.0f);
    DrawCar(-moveCar2, 0.0f, -16.5f, 0.0f, 180.0f);

    DrawHouse(-6.0f, -7.0f, 0.0f);
    DrawHouse(10.0f, -7.0f, 0.0f);

    DrawJungle(); // Draw the jungle background

    glutSwapBuffers();
}

void Timer(int value) {
    moveC += speed;
    if (moveC > 38) {
        moveC = -12;
    }

    moveCar1 += speed * 2;
    if (moveCar1 > 38) {
        moveCar1 = -12;
    }

    moveCar2 += speed * 2;
    if (moveCar2 > 38) {
        moveCar2 = -12;
    }

    moveSun += speed / 2;
    if (moveSun > 20) {
        moveSun = -12;
    }

    glutPostRedisplay();
    glutTimerFunc(33, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraZ -= cos(cameraAngle * 3.14159 / 180.0f);
        cameraX -= sin(cameraAngle * 3.14159 / 180.0f);
        break;
    case 's':
        cameraZ += cos(cameraAngle * 3.14159 / 180.0f);
        cameraX += sin(cameraAngle * 3.14159 / 180.0f);
        break;
    case 'a':
        cameraAngle -= cameraRotationSpeed;
        break;
    case 'd':
        cameraAngle += cameraRotationSpeed;
        break;
    }
    glutPostRedisplay();
}

void Initialize() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Light blue background color

    glEnable(GL_DEPTH_TEST);

    // Lighting setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_COLOR_MATERIAL);

    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("3D Scenery");

    Initialize();

    glutDisplayFunc(DrawAllComponents);
    glutTimerFunc(0, Timer, 0);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
    return 0;
}
