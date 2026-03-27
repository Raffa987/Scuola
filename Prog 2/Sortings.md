# Algoritmi di Ordinamento
Per la preview `Ctrl+Shift+V`
#### Bubble Sort
```C++
//Gli elementi "salgono" alla posizione corretta come fossero bolle
#include <vector>

template<typename T>
void BubbleSort(std::vecotr<T> &array){
    int l = array.size();

    bool swapped = true;
    while(swapped){
        swapped = false;
        for(int i = 0; i < l -1; i++){
            //Oridno l'array in ordine crescente
            if(array[i] > array[i + 1]){
                swap(array, i);
                swapped = true;
            }
        }
    }    
}
```
#### Insertion Sort
#### Selection Sort
#### Merge Sort
#### Quick Sort