 #include <cmath>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
// Camera position and environment dimensions
GLfloat cameraPositionX = 0.0f;
GLfloat cameraPositionY = 5.0f;
GLfloat cameraPositionZ = -110.0f;
GLfloat environmentWidth = 100.0f;
GLuint texture;

GLuint LoadTexture(const char* filename);

// Rotation angle for the scene
GLfloat rotationAngle = 0.0f;

// Object bounding boxes
struct BoundingBox {
    GLfloat minX, maxX;
    GLfloat minY, maxY;
    GLfloat minZ, maxZ;
};

BoundingBox houseBox = { -14.0f, -6.0f, 0.0f, 6.0f, -1.0f, 1.0f };
BoundingBox coupleBox = { 3.0f, 7.0f, -5.0f, -1.0f, 3.0f, 7.0f };
BoundingBox treeBox = { 9.0f, 11.0f, 0.0f, 5.0f, -11.0f, -9.0f };
BoundingBox poolBox = { 0.0f, 10.0f, -3.0f, -2.0f, -10.0f, 0.0f };

// Function to check collision with bounding boxes
bool CheckCollision(GLfloat x, GLfloat y, GLfloat z) {
    BoundingBox boxes[] = { houseBox, coupleBox, treeBox, poolBox };
    for (int i = 0; i < 4; ++i) {
        if (x > boxes[i].minX && x < boxes[i].maxX &&
            y > boxes[i].minY && y < boxes[i].maxY &&
            z > boxes[i].minZ && z < boxes[i].maxZ) {
            return true;
        }
    }
    return false;
}

// Function to draw a tree
void DrawTree()
{
    // Brown trunk
    glColor3f(0.4f, 0.2f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.0f);
    glScalef(1.0f, 5.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Green leaves
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
}

// Function to draw a house using quads
 

void DrawHouse() {
    glEnable(GL_TEXTURE_2D);
    texture = LoadTexture("b1.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);

    glScalef(4, 6, 2);

    // Front face
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, 0.0f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 5.0f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 5.0f, 2.5f);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(-2.5f, 0.0f, -2.5f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(2.5f, 0.0f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 5.0f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 5.0f, -2.5f);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(-2.5f, 0.0f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    
    
    
    glVertex3f(-2.5f, 5.0f, 2.5f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(-2.5f, 5.0f, -2.5f);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(2.5f, 0.0f, -2.5f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(2.5f, 0.0f, 2.5f);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(2.5f, 5.0f, 2.5f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(2.5f, 5.0f, -2.5f);
    glEnd();

    // Roof of the house (quad to cover the entire roof)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(-2.5f, 5.0f, -2.5f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(2.5f, 5.0f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    
    glVertex3f(2.5f, 5.0f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 5.0f, 2.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


// Function to draw a cylinder
void DrawCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks)
{
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    gluCylinder(quadric, radius, radius, height, slices, stacks);

    gluDeleteQuadric(quadric);
}

// Function to draw a couple (movable)
void DrawCouple(GLfloat posX, GLfloat posZ)
{

    // Draw body (sphere)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glPushMatrix();
    glTranslatef(posX, -3.0f, posZ);
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();

    // Draw limbs (cylinders)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color

    // Draw limbs for the first person
    glPushMatrix();
    glTranslatef(posX - 1.5f, -3.5f, posZ);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(0.2f, 3.0f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX + 1.5f, -3.5f, posZ);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(0.2f, 3.0f, 20, 20);
    glPopMatrix();

    // Draw limbs for the second person
    glPushMatrix();
    glTranslatef(posX - 1.5f, -3.5f, posZ + 2.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(0.2f, 3.0f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posX + 1.5f, -3.5f, posZ + 2.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawCylinder(0.2f, 3.0f, 20, 20);
    glPopMatrix();
}

// Function to draw a swimming pool
void DrawSwimmingPool()
{
    // Water surface
    glColor3f(0.0f, 0.5f, 1.0f); // Blue color
    glTranslatef(0, 2, -25);
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, -4.0f, -30.0f); // Left corner position
    glVertex3f(-10.0f, -4.0f, -30.0f); // Right corner position
    glVertex3f(-10.0f, -4.0f, -70.0f);
    glVertex3f(-50.0f, -4.0f, -70.0f);
    glEnd();

         // Pool walls
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, -5.0f, -30.0f); // Left corner position
    glVertex3f(-10.0f, -5.0f, -30.0f); // Right corner position
    glVertex3f(-10.0f, -5.0f, -70.0f);
    glVertex3f(-50.0f, -5.0f, -70.0f);
    glEnd();

    // Pool bottom
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray color
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, -5.0f, -30.0f); // Left corner position
    glVertex3f(-10.0f, -5.0f, -30.0f); // Right corner position
    glVertex3f(-10.0f, -5.0f, -70.0f);
    glVertex3f(-50.0f, -5.0f, -70.0f);
    glEnd();

    // Surrounding line (boundary)
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_LINE_LOOP);
    glVertex3f(-50.0f, -4.99f, -30.0f); // Left bottom
    glVertex3f(-10.0f, -4.99f, -30.0f); // Right bottom
    glVertex3f(-10.0f, -4.99f, -70.0f); // Right top
    glVertex3f(-50.0f, -4.99f, -70.0f); // Left top
    glEnd();
}

// Function to draw a car
 
GLuint wheelTexture;

void DrawCar() {
    glEnable(GL_TEXTURE_2D);

    // Load and bind the car body texture
     texture = LoadTexture("carbody.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);

    // Car body
   // glColor3f(1.0f, 1.0f, 1.0f); // White color to allow texture color to show
    glPushMatrix();
    glScalef(3.0f, 1.0f, 1.0f);

    // Draw car body using quads with texture coordinates
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Left face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(1.0f, 1.0f, -1.0f);
    glDisable(GL_TEXTURE_2D);
    // Top face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glPopMatrix();

    // Load and bind the wheel texture
    texture = LoadTexture("wheel.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);

    // Wheels
    glColor3f(1.0f, 1.0f, 1.0f); // White color to allow texture color to show

    // Draw each wheel with texture coordinates
    glPushMatrix();
    glTranslatef(-1.5f, -0.5f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i += 30) {
        float theta = i * 3.14 / 180.0f;
        float nextTheta = (i + 30) * 3.14 / 180.0f;
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.0f);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.1f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.1f);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -0.5f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i += 30) {
        float theta = i * 3.14 / 180.0f;
        float nextTheta = (i + 30) * 3.14 / 180.0f;
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.1f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.1f);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, -0.5f, -1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i += 30) {
        float theta = i * 3.14 / 180.0f;
        float nextTheta = (i + 30) * 3.14 / 180.0f;
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.1f);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.1f);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -0.5f, -1.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i += 30) {
        float theta = i * 3.14 / 180.0f;
        float nextTheta = (i + 30) * 3.14 / 180.0f;
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f * cos(nextTheta), 0.5f * sin(nextTheta), 0.1f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.5f * cos(theta), 0.5f * sin(theta), 0.1f);
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}


// Function to draw the scene
void display()
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 800.0f / 600.0f, 1.0f, 200.0f);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,  // Camera position
        cameraPositionX, 0.0f, 0.0f,                      // Look at point
        0.0f, 1.0f, 0.0f);                                 // Up vector

    // Rotate the scene around Y-axis
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // Draw ground
    glColor3f(0.1f, 0.6f, 0.1f); // Green color
    glBegin(GL_QUADS);
    glVertex3f(-environmentWidth, -4.0f, -environmentWidth);
    glVertex3f(environmentWidth, -4.0f, -environmentWidth);
    glVertex3f(environmentWidth, -4.0f, environmentWidth);
    glVertex3f(-environmentWidth, -4.0f, environmentWidth);
    glEnd();

    // Draw road
    glColor3f(0.3f, 0.3f, 0.3f); // Gray color
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -3.99f, -environmentWidth);
    glVertex3f(10.0f, -3.99f, -environmentWidth);
    glVertex3f(10.0f, -3.99f, environmentWidth);
    glVertex3f(-10.0f, -3.99f, environmentWidth);
    glEnd();

    // Draw lane markings (stipple lines) along z-axis
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF); // Stipple pattern for dashed lines

    glBegin(GL_LINES);
    float lineSpacing = 2.0f; // Spacing between each line
    float zPosition = -environmentWidth;

    while (zPosition <= environmentWidth)
    {
        glVertex3f(-2.0f, -3.98f, zPosition);
        glVertex3f(2.0f, -3.98f, zPosition);
        zPosition += lineSpacing;
    }

    glEnd();
    glDisable(GL_LINE_STIPPLE);

    // Draw houses
    glColor3f(1.0f, 0.5f, 0.0f); // Orange color

    // House 1
    glPushMatrix();
    glTranslatef(-50.0f, -4.0f, 30.0f);
    DrawHouse();
    glPopMatrix();

    // House 2
    glPushMatrix();
    glTranslatef(50.0f, -4.0f, -10.0f);
    DrawHouse();
    glPopMatrix();

    // House 3
    glPushMatrix();
    glTranslatef(-35.0f, -4.0f, -40.0f);
    DrawHouse();
    glPopMatrix();

    // House 4
    glPushMatrix();
    glTranslatef(25.0f, -4.0f, 20.0f);
    DrawHouse();
    glPopMatrix();

         // House 5
    glPushMatrix();
    glTranslatef(60.0f, -4.0f, 25.0f);
    DrawHouse();
    glPopMatrix();

    // Draw trees
    glColor3f(0.4f, 0.2f, 0.0f); // Brown color

    // Tree 1 (farther from road)
    glPushMatrix();
    glTranslatef(-40.0f, -1.5f, -50.0f); // Adjusted z-position
    DrawTree();                          // Draw the tree
    glPopMatrix();

    // Tree 2 (farther from road)
    glPushMatrix();
    glTranslatef(20.0f, -1.5f, 10.0f); // Adjusted z-position
    DrawTree();                         // Draw the tree
    glPopMatrix();

    // Tree 3 (farther from road and to the left)
    glPushMatrix();
    glTranslatef(-30.0f, -1.5f, 30.0f); // Adjusted z-position and left translation
    DrawTree();                         // Draw the tree
    glPopMatrix();

    // Tree 4 (farther from road)
    glPushMatrix();
    glTranslatef(20.0f, -1.5f, -20.0f); // Adjusted z-position
    DrawTree();                         // Draw the tree
    glPopMatrix();

    // Tree 5 (farther from road)
    glPushMatrix();
    glTranslatef(10.0f, -1.5f, -40.0f); // Adjusted z-position
    DrawTree();                         // Draw the tree
    glPopMatrix();

    // Draw couples
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the bodies
    DrawCouple(-20.0f, -30.0f); // Draw first couple
    DrawCouple(30.0f, 10.0f);   // Draw second couple

    // Draw swimming pool
    DrawSwimmingPool();

    // Draw sun
    glPushMatrix();
    glColor3f(1.0f, 0.75f, 0.5f);
    glTranslatef(30.0f, 35.0f, -30.0f);
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();

    // Draw cars
    glColor3f(1,1,1); // Gray color

    // Car 1
    glPushMatrix();
    glTranslatef(-5.0f, -3.98f, -20.0f); // Adjusted position
    DrawCar();
    glPopMatrix();

    // Car 2
    glPushMatrix();
    glTranslatef(5.0f, -3.98f, -40.0f); // Adjusted position
    DrawCar();
    glPopMatrix();

    // Car 3
    glPushMatrix();
    glTranslatef(-5.0f, -3.98f, -60.0f); // Adjusted position
    DrawCar();
    glPopMatrix();


    glutSwapBuffers();
}

// Function to handle special keys
void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (cameraPositionX > -environmentWidth)
            cameraPositionX -= 1.0f;
        break;
    case GLUT_KEY_RIGHT:
        if (cameraPositionX < environmentWidth)
            cameraPositionX += 1.0f;
        break;
    case GLUT_KEY_UP:
        if (cameraPositionZ > -environmentWidth)
            cameraPositionZ -= 1.0f;
        break;
    case GLUT_KEY_DOWN:
        if (cameraPositionZ < environmentWidth)
            cameraPositionZ += 1.0f;
        break;
    }
    glutPostRedisplay();
}

// Function to handle keyboard keys
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r': // Rotate scene right
        rotationAngle += 5.0f;
        break;
    case 'R': // Rotate scene left
        rotationAngle -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

// Function to initialize OpenGL settings
void Init()
{
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); // Light blue background color
    glEnable(GL_DEPTH_TEST);
}




// Function to load BMP file 
GLuint LoadTexture(const char* filename)
{
    int width, height;
    unsigned char* data;

#pragma warning(disable : 4996).
    FILE* file;
    file = fopen(filename, "rb");

    if (file == NULL) return 0;
    width = 512;
    height = 512;
    data = (unsigned char*)malloc(width * height * 3);
    //int size = fseek(file,);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}




// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Our Villege");

    Init();

    glutDisplayFunc(display);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
    return 0;
}