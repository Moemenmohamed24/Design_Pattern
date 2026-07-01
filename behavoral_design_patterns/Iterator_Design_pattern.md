# يعني ايه Iterator:

الفكره : اني بلف او بعدي علي كل العناصر اللي في اي data structure  من غير مااعرف هو التخزين بتاعه جواه عامل ازاي , يعني بعدي علي اي data structure من غير مااعرف هي مثلا بتخزن عن طريق index .زي ال array ولا عن طريق pop and push زي stack  , ولا زي المؤشرات زي ال linkdlist 


الـ Iterator هو Design Pattern بيديك طريقة تمشي (Traverse) على عناصر أي Collection زي Array أو Vector أو List أو Tree أو Graph من غير ما تعرف هي متخزنة إزاي من جوه.
يعني بدل ما أنت تدخل جوه الـ Data Structure وتعرف تفاصيلها، الـ Iterator هو اللي يمشي عليها نيابة عنك.





# المشاكل اللي كانت موجوده علشان كده اخترعوا ال iterator :
# المشكله الاولي : 
لما عندك أنواع مختلفة من Collections (Array, LinkedList, Tree, Stack) كل واحدة ليها طريقة تنقل مختلفة
```c++
// Array: بتتنقل بـ index
 for (int i = 0; i < size; i++) arr[i];

 // LinkedList: بتتنقل بـ pointer
 Node* curr = head;
 while (curr) { curr = curr->next; }

 // Tree: بتتنقل بـ Recursion
void traverse(Node * root) { ... }
```
# المشكلة 2: تكرار كود الـ Traversal في كل مكان:

نفس منطق التنقل مكرر في 3 أماكن مختلفة

```c++
    void printNumbers(int* arr, int size) {
    for (int i = 0; i < size; i++) // منطق التنقل هنا
        cout << arr[i];
}

void sumNumbers(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) // نفس منطق التنقل هنا تاني
        sum += arr[i];
}

void findMax(int* arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) // ونفسه هنا تاني
        if (arr[i] > max) max = arr[i];
}


```
 لو قررت تغير طريقة التخزين هتغير كود في 3 أماكن مش واحدة
    يعني : لو في Bug في منطق التنقل هتدور عليه في كل الكود, يعني الفكره هنا في ان فيه كذا loop كلهم بيعتمدوا علي طريقه التخزين , لو التخزين اتغير هتضطر تغير كل ال loop , لان اصلا الطريقه اتغيرت




