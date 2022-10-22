/* sort example: sort a random list of numbers*/

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>


void print(float random_list[], int list_size);
void sort(float random_list[], int list_size);
//Tarea
void sort_HW(float random_list[], int list_size);
void swap(float* var_a, float* var_b);
void quickSort(float random_list[], int start, int list_size);
int segment (float random_list[], int start, int list_size);


int main()
{
    const int list_size=100;//1000
    float random_list[list_size];
    float random_list_HW[list_size];
    int experiments=2000;//2000
    double time_sort=0.0;
    double time_sort_HW=0.0;

    clock_t begin;
    clock_t end;

    clock_t begin_HW;
    clock_t end_HW;

    srand(time(NULL));

    for (int exp=0; exp < experiments; exp++)
    {

        for (int idx=0; idx< list_size; idx++)
        {
            random_list[idx]=float(rand())/float(RAND_MAX);
            random_list_HW[idx]=random_list[idx];

        }
        //print(random_list,list_size);
        begin=clock();
        sort(random_list,list_size);
        end=clock();
        time_sort+=float(end -begin)/CLOCKS_PER_SEC;


        begin_HW=clock();
        sort_HW(random_list_HW,list_size);
        end_HW=clock();
        time_sort_HW+=float(end_HW -begin_HW)/CLOCKS_PER_SEC;

    }
    std::cout << "Time sort: " <<  time_sort/experiments << "\n";
    std::cout << "Time sort_HW: " <<  time_sort_HW/experiments << "\n";

    //print(random_list_HW,list_size);
    
    return 0;   
}




void sort(float random_list[], int list_size)
{
    for (int idx=0; idx<list_size; idx++)
    {
        for(int idy=idx+1; idy<list_size;idy++)
        {
            if (random_list[idx]> random_list[idy])
            {
            float temporal= random_list[idx];
            random_list[idx]=random_list[idy];
            random_list[idy]= temporal;
            }
        }
    }
}

void swap(float* var_a, float* var_b) 
{ 
    float temporal = *var_a; 
    *var_a = *var_b; 
    *var_b = temporal; 
} 

void sort_HW(float random_list[], int list_size)
{
   int indx_last=list_size-1;
   int indx_first=0;

   quickSort(random_list, indx_first,indx_last);


}



void quickSort(float random_list[], int start, int list_size) 
{ 
   if (start < list_size) 
   { 
      int idx_pivote = segment(random_list, start, list_size); 
  
      int idx_low=idx_pivote - 1;
      int idx_high=idx_pivote + 1;

      //segmento bajo del primer valor hasta uno menos del pivote
      quickSort(random_list, start,idx_low); 
      //segmento alto del valor despues del pivote al ultimo de la lista
      quickSort(random_list, idx_high, list_size); 

   } 
} 

int segment (float random_list[], int start, int list_size) 
{ 
   float pivote = random_list[start]; // pivote 
   int idx = list_size+1; 
   int idy = list_size;
   int final_number=start+1;

    //Compara los numeros desde el ultimo de la lista hasta el 
    //primero de esta

   do{
      if (random_list[idy] > pivote) 
        { 
            idx--; 
            swap(&random_list[idx], &random_list[idy]); 
        } 
      idy--;
   }while (idy >= final_number);//Ultimo valor antes del pivote
   
   /*acomodo de pivote, a su izquierda menores,
   a su derecha mayores a el */

   int idx_pivot=idx - 1;//Nuevo pivote para la siguiente iteracion
   swap(&random_list[idx_pivot], &random_list[start]);
  

   return (idx_pivot); 
} 


void print(float random_list[], int list_size)
{
   for(int idx=0; idx<list_size; idx++)
   {
      std::cout << random_list[idx] <<" ";
   }
   std::cout <<" \n";
}


