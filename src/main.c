#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include "pila.h"

#define TABLE_WIDTH 10
#define TABLE_HEIGHT 10

enum Movement {
    CurrentUP = 1,
    CurrentDown = 2,
    CurrentLeft = 3,
    CurrentRight = 4 
};

int table[TABLE_WIDTH][TABLE_HEIGHT] = {0};
int cOriginY = 0, cOriginX = 0;
int FCont=0;
int actualMovement;
//Comida de la serpiente
int fY, fX;
bool food = false;

Pila body;
void DrawBody(){
    for (int i = 0; i < tamanio(&body) ; i++)
    {
        ParEnteros p;
        desapilar(&body,&p);
        table[p.y][p.x]=1;
    }
}

void UpdateTeclado() {
    if (IsKeyPressed(KEY_DOWN))
    {
        actualMovement=2;
        // if(cOriginY+1 < TABLE_HEIGHT && actualMovement != 2){
        //     actualMovement = 2;
        //     table[cOriginY][cOriginX]= 0;
        //     cOriginY++;
        //     if(table[cOriginY][cOriginX]==2)
        //     {
        //         apilar(&body, cOriginX, cOriginY-1);
            
        //         FCont++;
        //         food=false;
                    
        //     }
        //     table[cOriginY][cOriginX]= 1;
        // }
    } 
    if (IsKeyPressed(KEY_UP)){
        actualMovement=1;
        // if(cOriginY - 1 >= 0 && actualMovement != 1){
        //     actualMovement = 1;
        //     table[cOriginY][cOriginX]= 0;
        //     cOriginY--;
        //     if(table[cOriginY][cOriginX]==2)
        //     {
        //         apilar(&body,cOriginX,cOriginY+1);
        //         FCont++;
        //         food=false;       
        //     }
        //     table[cOriginY][cOriginX]= 1;
        
        // }
    }
    if (IsKeyPressed(KEY_RIGHT)){
        actualMovement=4;
        // if (cOriginX+1 < TABLE_WIDTH && actualMovement != 4)
        // {
        //     actualMovement = 4;
        //     table[cOriginY][cOriginX]= 0;
        //     cOriginX++;
        //     if(table[cOriginY][cOriginX]==2)
        //     {
        //         apilar(&body,cOriginX-1,cOriginY);
        //         FCont++;
        //         food=false;
                    
        //     }
        //     table[cOriginY][cOriginX]= 1;
        // }
        
    }
    if (IsKeyPressed(KEY_LEFT)){
        actualMovement=3;
        // if (cOriginX-1 >= 0 && actualMovement != 3)
        // {
        //     actualMovement = 3;
        //     table[cOriginY][cOriginX]= 0;
        //     cOriginX--;
        //     if(table[cOriginY][cOriginX]==2)
        //     {
        //       apilar(&body,cOriginX+1,cOriginY);  
        //       FCont++;
        //       food=false;
              
                    
        //     }
        //     table[cOriginY][cOriginX]= 1;
        // }
    }

}
void deletebody(int tableY, int tableX, int cellSize){
     for (int i = 0; i < TABLE_HEIGHT; i++)
        {
            // Dibujar cada celda
            for (int j = 0; j < TABLE_WIDTH; j++)
            {
                if(table[i][j]==0){
                    float centerX = tableX + j*cellSize + cellSize / 2;
                    float centerY = tableY + i*cellSize + cellSize / 2;
                    DrawCircle(centerX, centerY, 12, BLACK);
                }
            }
        }
}
void currentMovementForce(int currentMovement)
{
    switch (currentMovement)
    {
        case 1:
        
        if(cOriginY - 1 >= 0){
            actualMovement = 1;
            table[cOriginY][cOriginX]= 0;
            cOriginY--;
            if(table[cOriginY][cOriginX]==2)
            {
                apilar(&body,cOriginX,cOriginY+1);
                FCont++;
                food=false;       
            }
            table[cOriginY][cOriginX]= 1;
        }
        break;
        case 2:
          if(cOriginY+1 < TABLE_HEIGHT){
            actualMovement = 2;
            table[cOriginY][cOriginX]= 0;
            cOriginY++;
            if(table[cOriginY][cOriginX]==2)
            {
                apilar(&body, cOriginX, cOriginY-1);
            
                FCont++;
                food=false;
                    
            }
            table[cOriginY][cOriginX]= 1;
        }

        break;

        case 3:
            if (cOriginX-1 >= 0)
        {
            
            table[cOriginY][cOriginX]= 0;
            cOriginX--;
            if(table[cOriginY][cOriginX]==2)
            {
              apilar(&body,cOriginX+1,cOriginY);  
              FCont++;
              food=false;
              
                    
            }
            table[cOriginY][cOriginX]= 1;
        }
        

        break;

        case 4:
            if (cOriginX+1 < TABLE_WIDTH)
            {
                table[cOriginY][cOriginX]= 0;
                cOriginX++;
                if(table[cOriginY][cOriginX]==2)
                {
                    apilar(&body,cOriginX-1,cOriginY);
                    FCont++;
                    food=false;
                }
                table[cOriginY][cOriginX]= 1;
            }

        break;
    }
}

int main(int argc, char const *argv[])
{
    
    srand (time(NULL));
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
        
        //Calculos
        float deltatime = GetFrameTime();
        timerCurrentMovement += deltatime;
        timerMovementPermission += deltatime;


        

        UpdateTeclado();
        if (timerCurrentMovement >= 0.23f)
        {
            currentMovementForce(actualMovement);
            timerCurrentMovement = 0.0f;
        }
        
        
        

        
        if(!food){
            fX = rand() % 10;
            fY = rand() % 10;

            table[fY][fX] = 2;
            food = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
           // Generacion aleatoria de comida
       
        //Dibujo
        // Calcular el tamano y posicion de la tabla total
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

                // Definir el origen de la tabla (punto superior izq), calculado anteriormente
                Rectangle cell = {tableX + j * cellSize, tableY + i * cellSize, cellSize, cellSize};
                DrawRectangleLinesEx(cell, 1, WHITE);
                
                // Dibujar circulo en el centro de los rectangulos
                if(table[i][j]==1){
                      
                    float centerX = tableX + j*cellSize + cellSize / 2;
                    float centerY = tableY + i*cellSize + cellSize / 2;
                    DrawCircle(centerX, centerY, 20, GREEN);
                }
                // Dibujar comida
                if (table[i][j]==2)
                {
                    float centerX = tableX + j*cellSize + cellSize / 2;
                    float centerY = tableY + i*cellSize + cellSize / 2;
                    DrawCircle(centerX, centerY, 12, RED);
                }
            }
            
            DrawBody();
            // Puntaje en pantalla
            char t[64];
            sprintf(t, "POINTS: %d", FCont);
            DrawText(t, 100, 100, 30, GREEN);   
            
            //Lineas de ejes
            //DrawLine(SCREENWIDTH / 2, 0, SCREENWIDTH / 2, SCREENHEIGHT, RED);
            //DrawLine(0, SCREENHEIGHT / 2, SCREENWIDTH, SCREENHEIGHT / 2, RED);
        }

        EndDrawing();
    };
    CloseWindow();

    return 0;
}
