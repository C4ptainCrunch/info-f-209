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
    int calc=0;
    for (int i = 0; i<width;++i){
        for (int j=0; j<lenght;++j){
            matrix[i][j] = 0;
            float result = pow(i-width/2.0, 2)/pow(46.0*width/100.0, 2);
            result+= pow(j-lenght/2.0, 2)/pow(46.0*lenght/100, 2);
            if (i%2 !=0){
                result -= 1/2;
            }
            if (result>1){
                matrix[i][j] = 1;
                calc++;
            }
    //----------------------------GOALS---------------------------------
            if( i == width/2){
                if (j==lenght/15+lenght/20 or j==14*lenght/15-lenght/20){
                    matrix[i][j] = 2;
                }
            }
            if (i == width/2-width/15 or i==width/2+width/15){
                if(j==2*lenght/15 or j==13*lenght/15){
                    matrix[i][j] = 2;
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

