# Algoritmi di Ordinamento
Per la preview `Ctrl+Shift+V`<br>
Tutti gli ordinamenti verrano fatti in ordne crescente
#### Bubble Sort
```C++
//Gli elementi "salgono" alla posizione corretta come fossero bolle
#include <vector>

template<typename T>
void BubbleSort(std::vecotr<T>& array){
    int l = array.size();    
    bool swapped = true;

    while(swapped){
        swapped = false;
        int new_l = 0;

        for(int i = 0; i < l -1; i++){
            if(array[i] > array[i + 1]){
                swap(array, i);
                swapped = true;

                //accorcia il ciclo in modo che non vado a rivisitare gli elementi già ordinati
                new_l = i + 1;
            }
            l = new_l;
        }
    }    
}
```
#### Insertion Sort

```C++

```

#### Selection Sort

```C++
//Seleziona l'elemnto minimo nell'array e lo mette al primo posto
//Il secondo elemento più piccolo al secono posto...
#include <vecotr>

template <typename T>

void InsertionSort(std::vectore <T>& array){
    int l = array.size();
    int min;

    for(int index = 0; index < l - 1; i++){
        min = index;

        //ricerca il minimo
        for(int i = index; i < l - 1; i++){
            if(array[i] < array[min]){
                min = i;
            }

            swap(array, i);
        }
    }
}
```
#### Merge Sort
#### Quick Sort