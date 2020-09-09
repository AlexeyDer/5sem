package ru.Eltex;

public class Application {
    public static int M = 0;
    public static int C = 0;

    public static void bubbleSort(int a[]) {
        int n = a.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                ++C;
                if (a[j] > a[j + 1]) {
                    int t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                    ++M;
                }
            }
        }
    }

    public static void selectSort(int a[]) {
        int n = a.length;

        for (int i = 0; i < n; i++) {
            int min = i;

            for (int j = i + 1; j < n; j++) {
                ++C;
                if (a[min] > a[j]) {
                    min = j;
                }
            }
            ++C;
            if (a[min] < a[i]) {
                int t = a[i];
                a[i] = a[min];
                a[min] = t;
                ++M;
            }
        }
    }

    public static void mergeSort(int arr[]) {
        int n = arr.length;
        int temp[] = new int[n];

        for (int size = 1; size < n; size = size * 2) {
            int l1 = 0;
            int k = 0;

            while (l1 + size < n) {
                int h1 = l1 + size - 1;
                int l2 = h1 + 1;
                int h2 = l2 + size - 1;

                if (h2 >= n)
                    h2 = n - 1;

                int i = l1;
                int j = l2;

                while (i <= h1 && j <= h2) {
                    ++C;
                    ++M;
                    if (arr[i] <= arr[j])
                        temp[k++] = arr[i++];
                    else
                        temp[k++] = arr[j++];
                }

                while (i <= h1) {
                    temp[k++] = arr[i++];
                    ++M;
                }
                while (j <= h2) {
                    temp[k++] = arr[j++];
                    ++M;
                }

                l1 = h2 + 1;
            }

            for (int i = l1; k < n; i++) {
                temp[k++] = arr[i];
                ++M;
            }

            for (int i = 0; i < n; i++)
                arr[i] = temp[i];

        }

    }

    public static void print(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            System.out.print(arr[i] + " ");
        }
    }

    public static void main(String[] args) {
        int n = 64;
        int[] a = new int[n];

        System.out.println("-------Bubble Sort-------");
        System.out.println("Массив до сортировки: ");
        for (int i = 0; i < n; i++) {
            a[i] = (int) (Math.random() * 10) + 1;
            System.out.print(a[i] + " ");
        }
        System.out.println();
        System.out.println("Массив после сортировки: ");

        bubbleSort(a);

        print(a, n);
        System.out.println("\nКоличество перестановок: " + M);
        System.out.println("Количество сравнений: " + C);
        System.out.println("-----------------------");

        M = 0;
        C = 0;

        System.out.println("-------Select Sort-------");
        System.out.println("Массив до сортировки: ");
        for (int i = 0; i < n; i++) {
            a[i] = (int) (Math.random() * 10) + 1;
            System.out.print(a[i] + " ");
        }
        System.out.println();
        System.out.println("Массив после сортировки: ");

        selectSort(a);

        print(a, n);
        System.out.println("\nКоличество перестановок: " + M);
        System.out.println("Количество сравнений: " + C);
        System.out.println("-----------------------");

        M = 0;
        C = 0;

        System.out.println("-------Merge Sort-------");
        a = new int[n];

        System.out.println("Массив до сортировки: ");
        for (int i = 0; i < n; i++) {
            a[i] = (int) (Math.random() * 10) + 1;
            System.out.print(a[i] + " ");
        }
        System.out.println();
        System.out.println("Массив после сортировки: ");

        mergeSort(a);

        print(a, n);
        System.out.println("\nКоличество перестановок: " + M);
        System.out.println("Количество сравнений: " + C);
        System.out.println("-----------------------");
    }
}
