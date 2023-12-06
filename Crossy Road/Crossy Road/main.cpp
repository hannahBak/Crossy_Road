#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 10.f


#include "shader.h"
#include "load_OBJ.h"

Objectload Car_Load;
GLint Car = Car_Load.loadObj("car1.obj");

Objectload Bbyongari_Load;
GLint Bbyongari = Bbyongari_Load.loadObj("bbyongari.obj");

Objectload SantaChicken_Load;
GLint SantaChicken = SantaChicken_Load.loadObj("santa_chicken.obj");



void initTextures() {

    Car_Load.InitTexture("Car_TEX.jpg");
    Bbyongari_Load.InitTexture("Bbyongari_C.jpg");
    SantaChicken_Load.InitTexture("santa_chicken_C.jpg");


}

GLuint VAO_Car, VBO_Car_VERTEX, VBO_Car_NORMAL, VBO_Car_UV;
GLuint VAO_Bbyongari, VBO_Bbyongari_VERTEX, VBO_Bbyongari_NORMAL, VBO_Bbyongari_UV;
GLuint VAO_SantaChicken, VBO_SantaChicken_VERTEX, VBO_SantaChicken_NORMAL, VBO_SantaChicken_UV;


int timer{ 0 };



int dicePyramidToggle = 0;
bool rotateXOn = false;
bool rotateYOn = false;
float rotateX = 0.f;
float rotateY = 0.f;


void InitBuffer() {

    //car
    glGenVertexArrays(1, &VAO_Car);
    glBindVertexArray(VAO_Car);
    //vertex
    glGenBuffers(1, &VBO_Car_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Car_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Car_Load.outvertex.size() * sizeof(glm::vec3), &Car_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Car_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Car_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Car_Load.outnormal.size() * sizeof(glm::vec3), &Car_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Car_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Car_UV);
    glBufferData(GL_ARRAY_BUFFER, Car_Load.outuv.size() * sizeof(glm::vec2), &Car_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //Bbyongari
    glGenVertexArrays(1, &VAO_Bbyongari);
    glBindVertexArray(VAO_Bbyongari);
    //vertex
    glGenBuffers(1, &VBO_Bbyongari_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Bbyongari_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Bbyongari_Load.outvertex.size() * sizeof(glm::vec3), &Bbyongari_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Bbyongari_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Bbyongari_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Bbyongari_Load.outnormal.size() * sizeof(glm::vec3), &Bbyongari_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Bbyongari_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Bbyongari_UV);
    glBufferData(GL_ARRAY_BUFFER, Bbyongari_Load.outuv.size() * sizeof(glm::vec2), &Bbyongari_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    //SantaChicken
    glGenVertexArrays(1, &VAO_SantaChicken);
    glBindVertexArray(VAO_SantaChicken);
    //vertex
    glGenBuffers(1, &VBO_SantaChicken_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_SantaChicken_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, SantaChicken_Load.outvertex.size() * sizeof(glm::vec3), &SantaChicken_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_SantaChicken_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_SantaChicken_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, SantaChicken_Load.outnormal.size() * sizeof(glm::vec3), &SantaChicken_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_SantaChicken_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_SantaChicken_UV);
    glBufferData(GL_ARRAY_BUFFER, SantaChicken_Load.outuv.size() * sizeof(glm::vec2), &SantaChicken_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

   
}


GLvoid drawScene();
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid SpecialKeyBoard(int key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid TimerFunc(int x);

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    InitBuffer();
    initTextures();
    shaderID.makeShader("vertexShaderSource.glsl", "fragmentShaderSource.glsl");
    glutKeyboardFunc(KeyBoard);
    glutSpecialFunc(SpecialKeyBoard);
    glutTimerFunc(10, TimerFunc, 0);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}
float objectPositionX = -0.5f;  // Initial position of the object
float objectSpeed = 0.01f;
float moveforward = 1.0f;

GLvoid drawScene()
{
    shaderID.use();
    glBindVertexArray(VAO_Car);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    //조명
    shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
    shaderID.setVec3("lightColor", 3.f, 3.f, 3.f);

    //투영 변환
    glm::mat4 pTransform = glm::mat4(1.0f);
    pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    shaderID.setMat4("projectionTransform", pTransform);


    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::vec3 cameraPos = glm::vec3(0, 0.2f, moveforward + 0.2);
    glm::vec3 cameraDirection = glm::vec3(0, 0.0f, moveforward - 0.3);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);



    objectPositionX += objectSpeed;

    if (objectPositionX > 0.5)
    {
        objectPositionX = -1.0;
    }
    glBindTexture(GL_TEXTURE_2D, Car_Load.texture);
    glBindVertexArray(VAO_Car);
    glm::mat4 PlayerTransform = glm::mat4(1.0f);
    PlayerTransform = glm::translate(PlayerTransform, glm::vec3(-objectPositionX, 0.0f, 0.0f));  // Translate object
    PlayerTransform = glm::rotate(PlayerTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
    PlayerTransform = glm::scale(PlayerTransform, glm::vec3(0.005f, 0.005f, 0.005f));
    PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
    PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
    shaderID.setMat4("modelTransform", PlayerTransform);
    shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
    glDrawArrays(GL_TRIANGLES, 0, Car);


    glBindTexture(GL_TEXTURE_2D, Bbyongari_Load.texture);
    glBindVertexArray(VAO_Bbyongari);
    glm::mat4 BbyongariTransform = glm::mat4(1.0f);
    BbyongariTransform = glm::translate(BbyongariTransform, glm::vec3(0.0f, 0.0f, moveforward));  // Translate object
    BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    BbyongariTransform = glm::scale(BbyongariTransform, glm::vec3(0.05f, 0.05f, 0.05f));
    BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
    BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
    shaderID.setMat4("modelTransform", BbyongariTransform);
    shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
    glDrawArrays(GL_TRIANGLES, 0, Bbyongari);
    
    
     glBindTexture(GL_TEXTURE_2D, SantaChicken_Load.texture);
    glBindVertexArray(VAO_SantaChicken);
    glm::mat4 SantaChickenTransform = glm::mat4(1.0f);
    SantaChickenTransform = glm::translate(SantaChickenTransform, glm::vec3(0.1f, 0.0f, -1.f));  // Translate object
    SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
    SantaChickenTransform = glm::scale(SantaChickenTransform, glm::vec3(0.05f, 0.05f, 0.05f));
    SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
    SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
    shaderID.setMat4("modelTransform", SantaChickenTransform);
    shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
    glDrawArrays(GL_TRIANGLES, 0, SantaChicken);
    


    glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        dicePyramidToggle = 0;
        break;
    case 'c':
        dicePyramidToggle = 1;
        break;
    case 'x':
        rotateXOn = !rotateXOn;
        break;
    case 'y':
        rotateYOn = !rotateYOn;
        break;
    case 'q':
        exit(-1);
    }
    glutPostRedisplay();
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
    switch (key)
    {
    default:
    case GLUT_KEY_UP:
        moveforward -= 0.1;
        break;
    case GLUT_KEY_DOWN:
        moveforward += 0.1;
        break;
    case GLUT_KEY_LEFT:
       
        break;
    case GLUT_KEY_RIGHT:
      
        break;
    }
    glutPostRedisplay();
}

GLvoid TimerFunc(int x)
{
    switch (x)
    {
    case 0:
        if (rotateXOn) {
            rotateX += 0.5;
        }
        if (rotateYOn) {
            rotateY += 0.5;
        }
        break;
    }
    glutTimerFunc(10, TimerFunc, 0);
    glutPostRedisplay();
}