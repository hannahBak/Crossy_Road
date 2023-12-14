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

Objectload Tree_Load;
GLint Tree = Tree_Load.loadObj("tree.obj");

Objectload Floor1_Load;
GLint Floor1 = Floor1_Load.loadObj("floor_r1.obj");


void initTextures() {

    Car_Load.InitTexture("Car_TEX.jpg");
    Bbyongari_Load.InitTexture("Bbyongari_C.jpg");
    SantaChicken_Load.InitTexture("santa_chicken_C.jpg");
    Tree_Load.InitTexture("tree_C.jpg");
    Floor1_Load.InitTexture("floor_r1_C.jpg");
}

GLuint VAO_Car, VBO_Car_VERTEX, VBO_Car_NORMAL, VBO_Car_UV;
GLuint VAO_Bbyongari, VBO_Bbyongari_VERTEX, VBO_Bbyongari_NORMAL, VBO_Bbyongari_UV;
GLuint VAO_SantaChicken, VBO_SantaChicken_VERTEX, VBO_SantaChicken_NORMAL, VBO_SantaChicken_UV;
GLuint VAO_Tree, VBO_Tree_VERTEX, VBO_Tree_NORMAL, VBO_Tree_UV;
GLuint VAO_Floor1, VBO_Floor1_VERTEX, VBO_Floor1_NORMAL, VBO_Floor1_UV;



bool rotateXOn = false;
bool rotateYOn = false;
float rotateX = 0.f;
float rotateY = 0.f;


struct Mycar {
    int direct = 0;
    float size = 0.005;
    float speed = 0.01f;
    float objectPositionX = -0.5f;
    float objectPositionZ;
};

const int numberOfCars = 7;

// 각 차량에 대한 설정
struct CarSettings {
    float speed;
    float objectPositionZ;
    int direct;

} carSettings[numberOfCars] = {
    {0.025, -0.75, 0},   // car0 설정
    {0.02, -0.2, 1},  // car1 설정
    {0.015, -0.1, 0},  // car2 설정
    {0.01, 0.7, 0},  // car3 설정
    {0.035, 0.8, 0},  // car4 설정
    {0.008, 0.9, 0},  // car5 설정
    {0.035, 1.4, 0},  // car6 설정
};

Mycar mycar[10];

//지영
struct TreeSettings {
    float positionX;
    float positionZ;
    float scale;
} treeSettings[] = {
    {0.0f, 0.0f, 0.05f},  // 첫 번째 나무 설정
    {0.2f, 0.2f, 0.05f}  // 두 번째 나무 설정
};

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

    //Tree
    glGenVertexArrays(1, &VAO_Tree);
    glBindVertexArray(VAO_Tree);
    //vertex
    glGenBuffers(1, &VBO_Tree_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Tree_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outvertex.size() * sizeof(glm::vec3), &Tree_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Tree_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Tree_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outnormal.size() * sizeof(glm::vec3), &Tree_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Tree_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Tree_UV);
    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outuv.size() * sizeof(glm::vec2), &Tree_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);



    // floor_1
    glGenVertexArrays(1, &VAO_Floor1);
    glBindVertexArray(VAO_Floor1);
    //vertex
    glGenBuffers(1, &VBO_Floor1_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor1_VERTEX);
    glBufferData(GL_ARRAY_BUFFER, Floor1_Load.outvertex.size() * sizeof(glm::vec3), &Floor1_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //normal
    glGenBuffers(1, &VBO_Floor1_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor1_NORMAL);
    glBufferData(GL_ARRAY_BUFFER, Floor1_Load.outnormal.size() * sizeof(glm::vec3), &Floor1_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    //uv
    glGenBuffers(1, &VBO_Floor1_UV);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Floor1_UV);
    glBufferData(GL_ARRAY_BUFFER, Floor1_Load.outuv.size() * sizeof(glm::vec2), &Floor1_Load.outuv[0], GL_STATIC_DRAW);
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

bool isGameOver = false; // Global variable to track game state

int windowWidth = 800;
int windowHeight = 800;

void drawGameOverScreen() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // Load and display the image
    int width, height, channels;
    unsigned char* image = stbi_load("title.jpg", &width, &height, &channels, STBI_rgb);
    if (!image) {
        fprintf(stderr, "Error loading image\n");
    
        return;
    }

    // Generate and bind texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    // Draw a textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-100.0f, -100.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(100.0f, -100.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(100.0f, 100.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-100.0f, 100.0f);
    glEnd();


    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable texture mapping
    glDisable(GL_TEXTURE_2D);

    // Swap buffers to display the rendered image
    glutSwapBuffers();
}

bool checkCollision(const glm::vec3& min1, const glm::vec3& max1, const glm::vec3& min2, const glm::vec3& max2) {
    return (min1.x <= max2.x && max1.x >= min2.x) &&
        (min1.y <= max2.y && max1.y >= min2.y) &&
        (min1.z <= max2.z && max1.z >= min2.z);
}

float moveforward = 1.6f;
float moveRight = 0.0f;

GLvoid drawScene()
{
    shaderID.use();
    glBindVertexArray(VAO_Car);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

   
    if (isGameOver) {
        drawGameOverScreen();
    }
    else {


    //조명
        shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
        shaderID.setVec3("lightColor", 3.f, 3.f, 3.f);

        //투영 변환
        glm::mat4 pTransform = glm::mat4(1.0f);
        pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
        shaderID.setMat4("projectionTransform", pTransform);


        glm::mat4 vTransform = glm::mat4(1.0f);
        glm::vec3 cameraPos = glm::vec3(moveRight, 0.2f, moveforward + 0.2);
        glm::vec3 cameraDirection = glm::vec3(moveRight, 0.0f, moveforward - 0.2);
        glm::vec3 cameraUp = glm::vec3(0.0f, 2.0f, 0.0f);
        vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
        shaderID.setMat4("viewTransform", vTransform);
        shaderID.setVec3("viewPos", 0, 0, 0);

        // 병아리의 충돌 박스
        glm::vec3 bbyongariMin = glm::vec3(moveRight - 0.03f, -0.05f, moveforward - 0.03f);
        glm::vec3 bbyongariMax = glm::vec3(moveRight + 0.03f, 0.05f, moveforward + 0.03f);

        // 산타치킨의 충돌 박스
        glm::vec3 santaChickenMin = glm::vec3(0.1f - 0.03f, -0.05f, -1.0f - 0.03f);
        glm::vec3 santaChickenMax = glm::vec3(0.1f + 0.03f, 0.05f, -1.0f + 0.03f);

        // 병아리와 산타치킨의 충돌 체크
        if (checkCollision(bbyongariMin, bbyongariMax, santaChickenMin, santaChickenMax)) {
            std::cout << "Collision detected with mom" << std::endl;
            // 여기에 충돌 처리 로직을 추가할 수 있습니다.
        }

        // car0
        for (int i = 0; i < numberOfCars; ++i) {
            // 차량 설정 적용
            mycar[i].direct = carSettings[i].direct;
            mycar[i].speed = carSettings[i].speed;
            mycar[i].objectPositionZ = carSettings[i].objectPositionZ;

            // 텍스처와 VAO 바인딩
            glBindTexture(GL_TEXTURE_2D, Car_Load.texture);
            glBindVertexArray(VAO_Car);

            // 차량 변환
            glm::mat4 carTransform = glm::mat4(1.0f);
            carTransform = glm::translate(carTransform, glm::vec3(-mycar[i].objectPositionX, 0.0f, mycar[i].objectPositionZ));
            carTransform = glm::rotate(carTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
            carTransform = glm::scale(carTransform, glm::vec3(mycar[i].size, mycar[i].size, mycar[i].size));
            carTransform = glm::rotate(carTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
            carTransform = glm::rotate(carTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));

            // 셰이더 설정 및 렌더링
            shaderID.setMat4("modelTransform", carTransform);
            shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
            glDrawArrays(GL_TRIANGLES, 0, Car);


            glm::vec3 carMin = glm::vec3(-mycar[i].objectPositionX - 0.05f, -0.05f, mycar[i].objectPositionZ - 0.01f);
            glm::vec3 carMax = glm::vec3(-mycar[i].objectPositionX + 0.05f, 0.05f, mycar[i].objectPositionZ + 0.01f);

            // Get the bounding box for bbyongari
            glm::vec3 bbyongariMin = glm::vec3(-0.02f, 0.0f, moveforward - 0.05f);
            glm::vec3 bbyongariMax = glm::vec3(0.02f, 0.05f, moveforward + 0.05f);


            // Check for collision between the current car[i] and bbyongari
            if (checkCollision(carMin, carMax, bbyongariMin, bbyongariMax)) {
                // Collision occurred, handle it as needed
                // For example, stop the car or perform some action
                std::cout << "Collision detected with car " << i << "!\n";
                mycar[i].speed = 0.0f;
                isGameOver = true;
            }
            if (mycar[i].direct == 0)
            {
                mycar[i].objectPositionX += mycar[i].speed;
                if (mycar[i].objectPositionX > 0.5)
                {
                    mycar[i].objectPositionX = -1.0;

                }
            }

            else
            {
                mycar[i].objectPositionX -= mycar[i].speed;
                if (mycar[i].objectPositionX < -0.5)
                {
                    mycar[i].objectPositionX = 1.0;

                }
            }

        }

        // 병아리
        glBindTexture(GL_TEXTURE_2D, Bbyongari_Load.texture);
        glBindVertexArray(VAO_Bbyongari);
        glm::mat4 BbyongariTransform = glm::mat4(1.0f);
        BbyongariTransform = glm::translate(BbyongariTransform, glm::vec3(moveRight, 0.0f, moveforward));  // Translate object
        BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(-90.0f), glm::vec3(0, 1, 0));
        BbyongariTransform = glm::scale(BbyongariTransform, glm::vec3(0.05f, 0.05f, 0.05f));
        BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
        BbyongariTransform = glm::rotate(BbyongariTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
        shaderID.setMat4("modelTransform", BbyongariTransform);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Bbyongari);

        // 산타치킨
        glBindTexture(GL_TEXTURE_2D, SantaChicken_Load.texture);
        glBindVertexArray(VAO_SantaChicken);
        glm::mat4 SantaChickenTransform = glm::mat4(1.0f);
        SantaChickenTransform = glm::translate(SantaChickenTransform, glm::vec3(0.1f, 0.0f, -1.0f));  // Translate object
        SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
        SantaChickenTransform = glm::scale(SantaChickenTransform, glm::vec3(0.05f, 0.05f, 0.05f));
        SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
        SantaChickenTransform = glm::rotate(SantaChickenTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
        shaderID.setMat4("modelTransform", SantaChickenTransform);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, SantaChicken);

        //지영
        for (int i = 0; i < sizeof(treeSettings) / sizeof(TreeSettings); ++i) {
            // 텍스처와 VAO 바인딩
            glBindTexture(GL_TEXTURE_2D, Tree_Load.texture);
            glBindVertexArray(VAO_Tree);

            // 나무 변환
            glm::mat4 treeTransform = glm::mat4(1.0f);
            treeTransform = glm::translate(treeTransform, glm::vec3(treeSettings[i].positionX, 0.0f, treeSettings[i].positionZ));
            treeTransform = glm::scale(treeTransform, glm::vec3(treeSettings[i].scale, treeSettings[i].scale, treeSettings[i].scale));
            treeTransform = glm::rotate(treeTransform, glm::radians(90.0f), glm::vec3(0, 1, 0));
            treeTransform = glm::rotate(treeTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
            treeTransform = glm::rotate(treeTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));

            // 셰이더 설정 및 렌더링
            shaderID.setMat4("modelTransform", treeTransform);
            shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
            glDrawArrays(GL_TRIANGLES, 0, Tree);
        }

        // 바닥
        glBindTexture(GL_TEXTURE_2D, Floor1_Load.texture);
        glBindVertexArray(VAO_Floor1);
        glm::mat4 FloorTransform = glm::mat4(1.0f);
        FloorTransform = glm::translate(FloorTransform, glm::vec3(0.0f, -0.1f, 0.0f));  // Translate object
        FloorTransform = glm::rotate(FloorTransform, glm::radians(00.0f), glm::vec3(0, 1, 0));
        FloorTransform = glm::scale(FloorTransform, glm::vec3(0.005f, 0.004f, 0.005f));
        FloorTransform = glm::rotate(FloorTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
        FloorTransform = glm::rotate(FloorTransform, glm::radians(rotateY), glm::vec3(0, 1, 0));
        shaderID.setMat4("modelTransform", FloorTransform);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Floor1);

        glutSwapBuffers();
    }
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        // Reset the game state
        isGameOver = false;

        // Reset car positions
        for (int i = 0; i < numberOfCars; ++i) {
            mycar[i].objectPositionX = -0.5f;
            mycar[i].objectPositionZ = carSettings[i].objectPositionZ;
            mycar[i].speed = carSettings[i].speed;
        }

        // Reset player position
        moveforward = 1.6f;
        moveRight = 0.0f;
        break;
    case 'p':
        
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
        moveRight -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        moveRight += 0.1;

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