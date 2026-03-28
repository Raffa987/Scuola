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
---
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

---
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

---
#### Merge Sort
Algoritmo che usa il paradigma Divide Et Impera, opera ricorsivamente su array di lunghezza n/2

```C++
#include <vector>

template <typename T>
void MergeSortHelper(std::vector <T>& array, int left, int right){
    if(left >= right) return;
    
    int mid = left + (right - left) / 2;
    MergeSortHelper(array, left, mid);
    MergeSortHelper(array, mid + 1, right);
 
    int size = right - left + 1;
    std::vector <T> tmp(size);

    int i = left;       
    int j = mid + 1;    
    int k = 0;          

    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            tmp[k] = array[i];
            i++;
        } else {
            tmp[k] = array[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        tmp[k] = array[i];
        i++;
        k++;
    }

    while (j <= right) {
        tmp[k] = array[j];
        j++;
        k++;
    }

    for (int idx = 0; idx < tmp.size(); idx++) {
        array[left + idx] = tmp[idx];
    }
}

template <typename T>
void MergeSort(std::vector <T>& array){
    if(array.empty()) return;
    MergeSortHelper(array, 0, array.size() - 1);
}
```

---
#### Quick Sort
Il  Quicksort  è  l’algoritmo  di  ordinamento  più  efficiente.  Si  basa sulla divisione del vettore in tre partizioni: <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;• Centrale: contenente un solo elemento detto pivot<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2• Sinistra: contenente tutti gli elementi minori del pivot<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;• Destra: contenente tutti gli elementi maggiori del pivot<br>
Usa il partizionamento di Hoare

```C++
#include <vector>

template <typename T>
void QuickSort(std::vector <T>& array, int n){
    QuickSort(array, 0, n - 1);
}
template <typename T>
void QuickSort(std::vector <T>& v, int s, int d){
    //s = sinistra, d = destra
    int i = s, j = d;
    T tmp;
    //scegliamo l'elemento a metà come Pivot
    T pivot = v[(s + d) / 2];

    //il ciclo continuerà fino a quando gli indici non arrivano al Pivot
    while(i <= j){
        //i aumenta fino a quando non incontar un elemento più grande del Pivot
        while(v[i] < pivot) i++;
        //j aumenta fino a quando non incontar un elemento più piccolo del Pivot
        while(v[j] > pivot) j--;

        //se i e j non si sono ancora incontrati vengono scambiati di posto gli elementi
        //da loro indicati
        if (i <= j) {
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--;
        }
    }

    if(s < j)
    QuickSort(v, s, j);
    if(i < d)
    QuickSort(v, i, d);
}
```