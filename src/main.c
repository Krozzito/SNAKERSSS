#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include "pila.h"
#include <math.h>

#define TABLE_WIDTH 10
#define TABLE_HEIGHT 10

enum Movement
{
    CurrentUP = 1,
    CurrentDown = 2,
    CurrentLeft = 3,
    CurrentRight = 4
};

int table[TABLE_WIDTH][TABLE_HEIGHT] = {0};
int cOriginY = 0, cOriginX = 0;
int FCont = 0;
int actualMovement;
// Comida de la serpiente
int fY, fX;
bool food = false;

Pila body;
void grewSnake()
{
}

void UpdateTeclado()
{
    if (IsKeyPressed(KEY_UP))
        actualMovement = 1;
    if (IsKeyPressed(KEY_DOWN))
        actualMovement = 2;
    if (IsKeyPressed(KEY_LEFT))
        actualMovement = 3;
    if (IsKeyPressed(KEY_RIGHT))
        actualMovement = 4;
}

int gameOver()
{
    while (!WindowShouldClose())
    {

        BeginDrawing();
        DrawText("GAME OVER", 100, 100, 40, RED);
        EndDrawing();
        if (IsKeyPressed(KEY_R))
        {
            return 0;
        }
    }
    CloseWindow();
};

void DrawRotatedTriangle(Vector2 center, float size, float angle, Color color)
{
    // Puntos en coordenadas locales (equilátero)
    Vector2 p1 = {0, -size};
    Vector2 p2 = {-size * 0.866f, size * 0.5f};   // 60° rotado
    Vector2 p3 = {size * 0.866f, size * 0.5f};

    // Rotar cada punto respecto al centro
    float cosA = cosf(angle);
    float sinA = sinf(angle);

    Vector2 rp1 = {
        center.x + p1.x * cosA - p1.y * sinA,
        center.y + p1.x * sinA + p1.y * cosA};

    Vector2 rp2 = {
        center.x + p2.x * cosA - p2.y * sinA,
        center.y + p2.x * sinA + p2.y * cosA};

    Vector2 rp3 = {
        center.x + p3.x * cosA - p3.y * sinA,
        center.y + p3.x * sinA + p3.y * cosA};

    DrawTriangle(rp1, rp2, rp3, color);
}


void currentMovementForce(int currentMovement)
{
    switch (currentMovement)
    {
    case 1:

        if (cOriginY - 1 < 0)
            gameOver();

        if (cOriginY - 1 >= 0)
        {
            actualMovement = 1;

            int prevX = cOriginX;
            int prevY = cOriginY;

            cOriginY--;
            if (table[cOriginY][cOriginX] == 1)
                gameOver();
            if (table[cOriginY][cOriginX] == 2)
            {
                apilar(&body, prevX, prevY);
                FCont++;
                food = false;
            }
            else
            {
                apilar(&body, prevX, prevY);
                ParEnteros p;
                desencolar(&body, &p);
                table[p.y][p.x] = 0;
            }

            table[cOriginY][cOriginX] = 1;
        }
        break;
    case 2:
        if (cOriginY + 1 >= TABLE_HEIGHT)
            gameOver();

        if (cOriginY + 1 < TABLE_HEIGHT)
        {
            actualMovement = 2;

            int prevX = cOriginX;
            int prevY = cOriginY;

            cOriginY++;
            if (table[cOriginY][cOriginX] == 1)
                gameOver();
            if (table[cOriginY][cOriginX] == 2)
            {
                apilar(&body, prevX, prevY);
                FCont++;
                food = false;
            }
            else
            {
                apilar(&body, prevX, prevY);
                ParEnteros p;
                desencolar(&body, &p);
                table[p.y][p.x] = 0;
            }
            table[cOriginY][cOriginX] = 1;
        }

        break;

    case 3:
        if (cOriginX - 1 < 0)
            gameOver();
        if (cOriginX - 1 >= 0)
        {

            actualMovement = 3;

            int prevX = cOriginX;
            int prevY = cOriginY;

            cOriginX--;
            if (table[cOriginY][cOriginX] == 1)
                gameOver();
            if (table[cOriginY][cOriginX] == 2)
            {
                apilar(&body, prevX, prevY);
                FCont++;
                food = false;
            }
            else
            {
                apilar(&body, prevX, prevY);
                ParEnteros p;
                desencolar(&body, &p);
                table[p.y][p.x] = 0;
            }

            table[cOriginY][cOriginX] = 1;
        }

        break;

    case 4:

        if (cOriginX + 1 >= TABLE_WIDTH)
            gameOver();
        if (cOriginX + 1 < TABLE_WIDTH)
        {
            actualMovement = 4;

            int prevX = cOriginX;
            int prevY = cOriginY;

            cOriginX++;
            if (table[cOriginY][cOriginX] == 1)
                gameOver();
            if (table[cOriginY][cOriginX] == 2)
            {
                apilar(&body, prevX, prevY);
                FCont++;
                food = false;
            }
            else
            {
                apilar(&body, prevX, prevY);
                ParEnteros p;
                desencolar(&body, &p);
                table[p.y][p.x] = 0;
            }

            table[cOriginY][cOriginX] = 1;
        }

        break;
    }
}
void startGame(){
    
}
int main(int argc, char const *argv[])
{

    srand(time(NULL));
    const int SCREENWIDTH = 1245;
    const int SCREENHEIGHT = 800;
    const int cellSize = 50;
    // Probando borrar el cuerpo cada 0,5 segundos
    float timerCurrentMovement = 0.0f;
    float timerMovementPermission = 0.0f;

    inicializar(&body);

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "SNAKERSSSSSS");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // Calculos
        float deltatime = GetFrameTime();
        timerCurrentMovement += deltatime;
        timerMovementPermission += deltatime;

        UpdateTeclado();
        if (timerCurrentMovement >= 0.2f)
        {
            currentMovementForce(actualMovement);
            timerCurrentMovement = 0.0f;
        }

        while (!food)
        {
            fX = rand() % 10;
            fY = rand() % 10;

            if (table[fY][fX] != 1)
            {
                table[fY][fX] = 2;
                food = true;
                break;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        // Generacion aleatoria de comida

        // Dibujo
        //  Calcular el tamano y posicion de la tabla total
        float tableWidth = cellSize * TABLE_WIDTH;
        float tableHeight = cellSize * TABLE_HEIGHT;
        float tableX = (SCREENWIDTH - tableWidth) * 0.5f;
        float tableY = (SCREENHEIGHT - tableHeight) * 0.5f;
        DrawRectangleLines(tableX, tableY, tableWidth, tableHeight, GREEN);

        for (int i = 0; i < TABLE_HEIGHT; i++)
        {
            // Dibujar cada celda
            for (int j = 0; j < TABLE_WIDTH; j++)
            {
                // Rectangle cell = {(SCREENWIDTH / 2) + ((j - TABLE_WIDTH / 2) * cellSize), SCREENHEIGHT / 2 + ((i - TABLE_HEIGHT / 2) * cellSize), cellSize, cellSize};

                if((i+j)%2 == 0) DrawRectangle(tableX + j * cellSize, tableY + i * cellSize, cellSize, cellSize, BLUE);
                if((i+j)%2 != 0) DrawRectangle(tableX + j * cellSize, tableY + i * cellSize, cellSize, cellSize, BLACK);
                // Definir el origen de la tabla (punto superior izq), calculado anteriormente
                Rectangle cell = {tableX + j * cellSize, tableY + i * cellSize, cellSize, cellSize};
                DrawRectangleLinesEx(cell, 1, WHITE);
            
                // Dibujar circulo en el centro de los rectangulos
                // if (table[i][j] == 1)
                // {

                //     float centerX = tableX + j * cellSize + cellSize / 2;
                //     float centerY = tableY + i * cellSize + cellSize / 2;
                //     DrawCircle(centerX, centerY, 20, GREEN);
                // }
                if (table[i][j] == 1)
                {
                    float centerX = tableX + j * cellSize + cellSize / 2;
                    float centerY = tableY + i * cellSize + cellSize / 2;

                    if (i == cOriginY && j == cOriginX)
                    {
                        // Es la cabeza → dibujar triángulo con orientación
                        float angle = 0.0f;

                        switch (actualMovement)
                        {
                        case 3:
                            angle = -PI / 2;
                            break; // arriba
                        case 4:
                            angle = PI / 2;
                            break; // abajo
                        case 2:
                            angle = PI;
                            break; // izquierda
                        case 1:
                            angle = 0.0f;
                            break; // derecha
                        }

                        Vector2 center = {centerX, centerY};
                        DrawRotatedTriangle(center, 20, angle, WHITE);
                    }
                    else
                    {
                        // Dibujar cuerpo como círculos
                        DrawCircle(centerX, centerY, 20, YELLOW);
                    }
                }
                // Dibujar comida
                if (table[i][j] == 2)
                {
                    float centerX = tableX + j * cellSize + cellSize / 2;
                    float centerY = tableY + i * cellSize + cellSize / 2;
                    DrawCircle(centerX, centerY, 12, RED);
                }
            }

            // Puntaje en pantalla
            char t[64];
            sprintf(t, "POINTS: %d", FCont);
            DrawText(t, 100, 100, 30, GREEN);
            // Lineas de ejes
            // DrawLine(SCREENWIDTH / 2, 0, SCREENWIDTH / 2, SCREENHEIGHT, RED);
            // DrawLine(0, SCREENHEIGHT / 2, SCREENWIDTH, SCREENHEIGHT / 2, RED);
        }

        EndDrawing();
    };
    CloseWindow();

    return 0;
}
