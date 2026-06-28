# Algoritmi di Ordinamento
Per la preview `Ctrl+Shift+V`<br>
Tutti gli ordinamenti verrano fatti in ordne crescente
#### Bubble Sort
Gli elementi adiacenti vengono scambiati se sono nell'ordine sbagliato, facendo "salire" gli elementi più grandi verso la fine dell'array a ogni iterazione.<br>
Complessità asintotica: $O(n^2)$ nel caso pessimo e medio, $O(n)$ nel caso ottimo.
```C++
#include <vector>
#include <utility> // Per std::swap

template<typename T>
void BubbleSort(std::vector<T>& array) {
    int l = array.size();    
    bool swapped = true;

    while (swapped) {
        swapped = false;
        int new_l = 0;

        for (int i = 0; i < l - 1; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;

                // Accorcia il ciclo per non rivisitare gli elementi già ordinati
                new_l = i + 1;
            }
        }
        l = new_l;
    }    
}
```
---
#### Insertion Sort
Gli elementi vengono inseriti uno ad uno all'interno di un sotto-array logicamente ordinato. Questa implementazione sfrutta la ricerca binaria per trovare il punto di inserimento.<br>

Complessità asintotica: $O(n^2)$ nel caso pessimo e medio. Sebbene la ricerca binaria riduca il numero di confronti a $O(\log n)$, gli spostamenti in memoria (shift) richiedono comunque $O(n)$ per inserimento.
```C++
#include <vector>

template<typename T>
void BinaryInsertionSort(std::vector<T>& array) {
    int l = array.size();

    for (int i = 1; i < l; i++) {
        T key = array[i];

        int left = 0;
        int right = i - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (array[mid] > key) {
                // Se l'elemento centrale è più grande, cerchiamo nella metà sinistra
                right = mid - 1;
            } else {
                // Altrimenti cerchiamo nella metà destra
                left = mid + 1;
            }
        }
        
        // Alla fine di questo ciclo, 'left' conterrà l'indice esatto 
        // in cui la nostra 'key' deve essere inserita.

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
L'algoritmo seleziona l'elemento minimo nella porzione non ordinata dell'array e lo scambia con il primo elemento non ordinato.<br>
Complessità asintotica: $O(n^2)$ in tutti i casi (ottimo, medio e pessimo), poiché esegue sempre la scansione completa della parte rimanente.
```C++
#include <vector>
#include <utility>

template <typename T>
void SelectionSort(std::vector<T>& array) {
    int l = array.size();

    for (int index = 0; index < l - 1; index++) {
        int min_idx = index;

        // Ricerca l'indice dell'elemento minimo
        for (int i = index + 1; i < l; i++) {
            if (array[i] < array[min_idx]) {
                min_idx = i;
            }
        }

        // Esegue lo scambio solo se il minimo trovato non è già nella posizione corretta
        if (min_idx != index) {
            std::swap(array[index], array[min_idx]);
        }
    }
}
```

---
#### Merge Sort
Algoritmo che usa il paradigma Divide Et Impera, opera ricorsivamente dividendo l'array in due metà, ordinandole separatamente e fondendole insieme.<br>
Complessità asintotica: $O(n \log n)$ nel caso ottimo, medio e pessimo.<br>
Complessità spaziale: $O(n)$ per la necessità di allocare vettori temporanei durante la fusione.

```C++
#include <vector>

template <typename T>
void MergeSortHelper(std::vector<T>& array, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    MergeSortHelper(array, left, mid);
    MergeSortHelper(array, mid + 1, right);
 
    int size = right - left + 1;
    std::vector<T> tmp(size);

    int i = left;       
    int j = mid + 1;    
    int k = 0;          

    // Fusione delle due metà ordinate
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

    // Copia degli eventuali elementi rimanenti
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

    // Copia del vettore temporaneo ordinato nell'array originale
    for (int idx = 0; idx < tmp.size(); idx++) {
        array[left + idx] = tmp[idx];
    }
}

template <typename T>
void MergeSort(std::vector<T>& array) {
    if (array.empty()) return;
    MergeSortHelper(array, 0, array.size() - 1);
}
```

---
#### Quick Sort
Si basa sul Divide Et Impera e sul partizionamento in loco (in-place). Divide l'array in partizioni rispetto a un elemento detto pivot. In questa versione si usa il partizionamento di Hoare.<br>
Complessità asintotica: $O(n \log n)$ nel caso ottimo e medio. Raggiunge $O(n^2)$ nel caso pessimo (quando l'array è già ordinato o ordinato in modo inverso, se non si mitiga la scelta del pivot).
```C++
#include <vector>
#include <utility>

template <typename T>
void QuickSortHelper(std::vector<T>& v, int s, int d) {
    // s = sinistra, d = destra
    int i = s;
    int j = d;
    
    // Scegliamo l'elemento a metà come Pivot
    T pivot = v[(s + d) / 2];

    // Il ciclo continuerà fino a quando gli indici non si incrociano
    while (i <= j) {
        // i aumenta fino a quando non incontra un elemento più grande o uguale al Pivot
        while (v[i] < pivot) i++;
        // j diminuisce fino a quando non incontra un elemento più piccolo o uguale al Pivot
        while (v[j] > pivot) j--;

        // Se i e j non si sono incrociati, scambiamo gli elementi
        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    // Chiamate ricorsive per le due sotto-partizioni
    if (s < j) {
        QuickSortHelper(v, s, j);
    }
    if (i < d) {
        QuickSortHelper(v, i, d);
    }
}

template <typename T>
void QuickSort(std::vector<T>& array) {
    if (array.empty()) return;
    QuickSortHelper(array, 0, array.size() - 1);
}
```