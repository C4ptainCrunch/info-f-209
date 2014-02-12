#include <iostream>
#include <cmath>

using namespace std;

int width = 35;
int lenght = 70;

// void initMatrix(int* matrix){
//  for (int i = 0; i<width;++i){
//      for (int j; j<lenght;++i){
//          matrix[i][j] = 0;
//      }
//  }
// }

// void printMat(int matrix[width][]){
//  for (int i = 0; i<width;++i){
//      for (int j; j<lenght;++i){
//          cout<< matrix[i][j]<< " ";
//      }
//      cout<<endl;
//  }
// }



int main(int argc, char const *argv[])
{

    //-------------------------MATINIT---------------------
    int matrix[width][lenght];
    int calc=0;//Nombre de cases utilisables
    float diameterFactor = 46.0/100.0;// Normalement c'est la moitié de la longueur/largeur 
    int delta = 1/2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice

    for (int i = 0; i<width;++i){
        for (int j=0; j<lenght;++j){
            matrix[i][j] = 0;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            float result = pow(i-width/2.0, 2)/pow(diameterFactor*width, 2);
            result+= pow(j-lenght/2.0, 2)/pow(diameterFactor*lenght, 2);
            if (i%2 !=0){
                result -= delta;
            }
            if (result>1){//Si on est à l'extérieur de l'ellipse
                matrix[i][j] = 1;
                calc++;
            }
    //----------------------------GOALS---------------------------------
            if( i == width/2){
                if (j == lenght/15 + lenght/20 or j == lenght*14/15 - lenght/20){
                    matrix[i][j] = 2;//goal central
                }
            }
            if (i == width/2 - width/15 or i== width/2 + width/15){
                if(j == 2 * lenght/15 or j == 13 * lenght/15){
                    matrix[i][j] = 2;//goals latéraux
                }
            }
        }
    }
    //---------------------------PRINT----------------------------
    for (int i = 0; i<width;++i){
        if (i%2 != 0){
            cout<<" ";
        }
        for (int j=0; j<lenght;++j){

            if (matrix[i][j] == 0){
                cout<< "\u2B21"<<" ";
            }
            else{
                cout <<"\u2B22"<<" ";
            }

            //cout<< matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<calc<<endl;//nbre de cases utilisables
    return 0;
}

