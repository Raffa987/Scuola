# Algoritmi di Ordinamento
Per la preview `Ctrl+Shift+V`<br>
Tutti gli ordinamenti verrano fatti in ordne crescente
#### Bubble Sort
Gli elementi "salgono" alla posizione corretta come fossero bolle
```C++
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
Gli elementi vengono inseriti in un sotto array ordinato<br>
Complessità O(n<sup>2</sup>)
```C++
#include <vector>

template<typename T>
void BinaryInsertionSort(std::vector<T>& array) {
    int l = array.size();

    for(int i = 1; i < l; i++) {
        T key = array[i];

        int left = 0;
        int right = i - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (array[mid] > key) {
                //Se l'elemento centrale è più grande, cerchiamo nella metà sinistra
                right = mid - 1;
            } else {
                //Altrimenti cerchiamo nella metà destra
                left = mid + 1;
            }
        }
        
        //Alla fine di questo ciclo, 'left' conterrà l'indice esatto 
        //in cui la nostra 'key' deve essere inserita.

        // Spostiamo tutti gli elementi da 'left' a 'i-1' di una posizione verso destra
        for (int j = i; j > left; j--) {
            array[j] = array[j - 1];
        }

        array[left] = key;
    }
}

```

#### Selection Sort
Seleziona l'elemnto minimo nell'array e lo mette al primo posto<br>
Il secondo elemento più piccolo al secono posto...
```C++
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