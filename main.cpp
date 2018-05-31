#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101                    //подключение макросов (реализованных на железе) о переполнении... и ошибках памяти...
#define OUT_OF_MEMORY   -102

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

typedef struct node {
    string value;
    struct node *next;
    struct node *back;
} node;
typedef node* list;

//============стек==================
class Stek{
public:
    int inic(list *root);                       //инициализация
    int push(list *head, string value);         //добавление нового элемента
    int print(list *lst);                       //печать
    int pop(node **head);                       //удаление
    int destroy(list *root);                    //деструктор (очистка стека)
};
//==========очередь================
class Ochered{
    node *head,*tail;
public:
    Ochered():head(NULL),tail(NULL){};          //инициализация
    ~Ochered();                                 //деструктор
    void add(string value);                     //добавление нового элемента
    void print();                               //печать
    void del();                                 //изъятие из очереди
};
//==============дэк================
class Deque{
    node *head,*tail;
public:
    Deque():head(NULL),tail(NULL){};            //инициализация
    ~Deque();                                   //деструктор
    void PushFront(string value);               //добавление в начало дека
    void PushBack(string value);                //добавление в конец дека
    void print();                               //печать
    void output();                              //вывод в файл
    void print_konsol();                        //отображение в консоли
    string popFront();                          //изъятие из очереди с начала
    string popBack();                           //изъятие из очереди с конца
    void sort();
};

//==============описание=функцций===============//

//====================стек======================//
int Stek::inic(list *root){                     //инициализация
    *root = NULL;
    return 1;
}
int Stek::push(list *head, string value){          //добавление элемента наверх
    list tmp=new node;
    if(tmp==NULL) exit(STACK_OVERFLOW);
    tmp->next=*head;
    tmp->value=value;
    *head = tmp;
    return 1;
}
int Stek::pop(node **head) {                    //удаление элемента
    node *out;
    if (*head == NULL) exit(STACK_UNDERFLOW);
    out = *head;
    *head = (*head)->next;
    delete out;
    return 1;
}
int Stek::destroy(list *root) {                 //очистка очереди
    list next;
    while (*root != NULL) {
        next = *root;
        *root = (*root)->next;
        delete next;
    }
    return 1;
}
int Stek::print(list *lst) {                    //вывод
    list temp = *lst;
    cout<<"\tStek: \t\t";
    while (temp != NULL) {
        cout<<temp->value<<" ";
        temp = temp->next;
    }
    cout<<endl;
    return 1;
}
//====================стек======================//

//==================очередь=====================//
Ochered::~Ochered(){
    node *temp=head;                            //Временный указатель на начало очереди
    while (temp!=NULL){
        temp=head->next;                        //Резерв адреса на следующий элемент очереди
        delete head;                            //Освобождение памяти от первого элемента очереди
        head=temp;                              //Сдвиг начала на следующий адрес, который берем из резерва
    }
}
void Ochered::add(string value){
    node *temp=new node;                        //Выделение памяти для нового звена очереди
    temp->value=value;                          //Запись принятого параметра value
    temp->next=NULL;                            //Указание, что следующее звено новосозданной структуры пока пустое

    if (head!=NULL){                            //Если очередь не пуста
        tail->next=temp;                        //Указание, что следующее звено списка, это новосозданная структура
        tail=temp;
    }
    else head=tail=temp;                        //Если очередь пуста, добавление первого элемента
}
void Ochered::print(){
    node *temp=head;                            //Временный указатель на начало очереди
    cout<<"\tOchered':\t";
    while (temp!=NULL){                         //Пока в очереди что-то встречается
        cout<<temp->value<<" ";                 //Выводим значения из списка на экран
        temp=temp->next;                        //Сдвигаем указатель на адрес следующего элемента
    }
    cout<<endl;
}
void Ochered::del(){
    if (head!=NULL){                            //Если очередь не пуста
        node *temp=head;                        //Обращаемся к началу очереди с помощью вспомогательного указателя
        head=head->next;                        //Сдвиг начала очереди
        delete temp;                            //Освобождение памяти от предыдущего звена очереди
    }
}
//==================очередь=====================//


//====================дэк=======================//
Deque::~Deque(){                    //деструктор
    node *temp=head;                            //Временный указатель на начало дека
    while (temp!=NULL){
        temp=head->next;                        //Резерв адреса на следующий элемент дека
        delete head;                            //Освобождение памяти от первого элемента дека
        head=temp;                              //Сдвиг начала на следующий адрес, который берем из резерва
    }
}
void Deque::PushFront(string value){   //вставка в начало
    node *temp=new node;                        //Выделение памяти для нового звена дека
    temp->value=value;                          //Запись принятого параметра value
    temp->next=NULL;                            //Указание, что следующее звено новосозданной структуры пока пустое

    if (head!=NULL){                            //Если дек не пуст
        tail->next=temp;                        //Указание, что следующее звено дека, это новосозданная структура
        tail=temp;                              //Указание, что конец дека - последний элемент
        node *tmp=head;
        while(tmp->next->next!=NULL){           //поиск предпоследнего элемента
            tmp=tmp->next;
        }
        temp->back=tmp;                         //Запись в последний элемент ссылки на предыдущий
    }
    else {                                      //Если дек пуст, добавление первого элемента
        head=tail=temp;
        head->back=NULL;
        head->next=NULL;
        tail->back=NULL;
        tail->next=NULL;
    }
}
void Deque::PushBack(string value){    //вставка в конец
    node *temp=new node;                        //Выделение памяти для нового звена дека
    temp->value=value;                          //Временное запоминание принятого параметра value
    temp->next=NULL;                            //Указание, что следующее звено новосозданной структуры пока пустое

    if (tail!=NULL){                            //Если дек не пуст
        tail->next=temp;
        temp->back=tail;                        //Указание, на предыдущее звено
        tail=temp;
    }
    else{                                       //Если дек пуст, добавление первого элемента
        tail=head=temp;
        head->back=NULL;
        head->next=NULL;
        tail->back=NULL;
        tail->next=NULL;
    }
}
void Deque::print(){                //вывод
    node *temp=head;                            //Временный указатель на начало дека
    cout<<"\tDek:\t\t";
    while (temp!=NULL){                         //Пока в дека что-то встречается
        cout<<temp->value<<" ";                 //Выводим значения из дека на экран
        temp=temp->next;                        //Сдвигаем указатель на адрес следующего элемента
    }
    cout<<endl;
}
void Deque::print_konsol(){                //вывод
    node *temp=head;                            //Временный указатель на начало дека
    cout<<"\tDek:"<<endl;
    while (temp!=NULL){                         //Пока в дека что-то встречается
        cout<<"\t\t"<<temp->value<<endl;    //Выводим значения из дека на экран
        temp=temp->next;                        //Сдвигаем указатель на адрес следующего элемента
    }
    cout<<endl;
}
void Deque::output(){                //вывод
    node *temp=head;                            //Временный указатель на начало дека
    ofstream fout("E:\\Vyhod_timp2.txt");
    while (temp!=NULL){                         //Пока в дека что-то встречается
        fout<<temp->value<<endl;                //Выводим значения из дека на экран
        temp=temp->next;                        //Сдвигаем указатель на адрес следующего элемента
    }
    fout.close();
    cout<<" Vse vypolneno. Prover'te po pyti: E:\\Vyhod_timp2.txt\n"<<endl;
}
string Deque::popFront(){             //удаление с начала
    if (head!=NULL){                            //Если дек не пустой
        node *temp=head;                        //Обращаемся к началу дека с помощью вспомогательного указателя
        string stroka=head->value;
        head=head->next;                        //Сдвиг начала дека
        delete temp;                            //Освобождение памяти от предыдущего звена дека
        return stroka;
    }
    else return 0;
}
string Deque::popBack(){              //удаление с конца
    if (tail!=NULL){                            //Если дек не пустой
        node *temp=tail;                        //Обращаемся к концу дека с помощью вспомогательного указателя
        string stroka=tail->value;
        tail=tail->back;                        //Сдвиг конца дека
        tail->next=NULL;                        //Удаление ссылки на следующий элемент
        delete temp;                            //Освобождение памяти от последнего звена дека
        return stroka;
    }
    else return 0;
}

void Deque::sort(){// node *head_deque1, node *tail_deque1, node *head_deque2, node *tail_deque2
    for(int nomer=0;nomer<1;nomer++){
        node *head_deque1=head;
        Deque temp;
        int min=256, max=-256;                      //256 потому что это "края" таблицы
        int razmer=0;                               //количество строк в дэке
        while(head_deque1->next!=NULL){             //пока не конец дэка
            razmer++;                                                                                   //потом инкреметировать!!
            if(int(head_deque1->value[nomer])<min)     min=int(head_deque1->value[nomer]);//поиск минимумаи максимума
            if(int(head_deque1->value[nomer])>max)     max=int(head_deque1->value[nomer]);
            head_deque1=head_deque1->next;          //смотрим следующий элемент
        }
        while(razmer>=0){                                    //пока размер больше 0
            head_deque1=head;
            int min_sim=256, poloj_min;
            for(int i=0;i<=razmer;i++){                         //ищем первую букву из встречающихся
                if(int(head_deque1->value[nomer])<min_sim){
                    min_sim = int(head_deque1->value[nomer]);       //ищем строку... по первой букве...
                    poloj_min = i;
                }
                head_deque1=head_deque1->next;                  //смотрим следующий элемент
            }
            for(int i=0;i<=razmer;i++){
                if(i==poloj_min){
                    temp.PushBack(head->value);
                    popFront();
                    razmer--;
                }
                else {                                          //перенос элемента из начала в конец
                    PushBack(head->value);
                    popFront();
                }
            }
        }
        while(temp.head!=NULL){
            PushFront(temp.head->value);
            temp.popFront();
        }
        print_konsol();
        output();
        temp.~Deque();
    }
}
//====================дэк=======================//


int main() {
    srand(time(0));                                             //для работы рандома
    list head;
    Stek stek;                                                  //инициализация стека
    Ochered ochered;                                            //инициализация очереди
    stek.inic(&head);
    Deque deque;                                                //инициализация дэка
    int n, x, d, nd, dd;

    cout<<" Vvedite kol-vo elementov: "; cin>>n;                //кол-во элементов в структурах
    cout<<" Iz nih bydyt zapisany v nachalo  deka: "; cin>>nd;  //кол-во элементов, которые убдут записаны в начало дека
    if (n > 0 && (nd>=0 && nd<=n)) {                            //если всё в пределах разумного
        //cout<<" Vvedite "<<n<<" elementov:\n ";           //если надо вводить вручную - убрать коментарии
        for(int i=0;i<n;i++){                               // -//-                     - поставить коментарии тут и
            x=rand()%(2*n)+1;                               //
            stek.push(&head, to_string(x));                 //
            ochered.add(to_string(x));                      //                          (в начало строки)
            if(i<nd)deque.PushFront(to_string(x));          //
            else deque.PushBack(to_string(x));              //

            stek.print(&head);                              //              //если надо вывести лишь результат
            ochered.print();                                //              // то
            deque.print();                                  //              //закоментить тут!
            cout<<endl;                                     //              //
        }                                                   //                          - тут
        /*          //вывод
        stek.print(&head);
        ochered.print();
        deque.print();
        */
        cout<<"\n Vvedite kol-vo elementov dlya ydaleniya: ";cin>>d;    //кол-во элементов для удаления из структур
        cout<<" Iz nih bydyt ydaleny iz nachala  deka: "; cin>>dd;      //кол-во элементов, которое будет удалено из начала дэка
        if((d<n && d>0) && (dd>=0 && dd<n)){                          //если всё ок
            for(int i=0;i<d;i++){
                stek.pop(&head);                                        //удаление из стека
                ochered.del();                                          //удаление из очереди
                if(i<dd)deque.popFront();                               //удаление из начала дэка
                else deque.popBack();                                   //удаление из конца дэка

                stek.print(&head);                              //              //если надо вывести лишь результат
                ochered.print();                                //              // то
                deque.print();                                  //              //закоментить тут!
                cout<<endl;                                     //              //
            }
        }
        else cout<<"\tTakoe sdelat' nevozmojno!!!"<<endl;               //сообщение, если введено на удаление число, больше, чем элементов в структуре
    }
    /*                                                                    //вывод
    stek.print(&head);
    ochered.print();
    deque.print();
    */
    else cout<<"\tChto?!"<<endl;                                        //сообщение, если введено кол-во элементов в структуре отрицательное или равное 0
    stek.destroy(&head);
    ochered.~Ochered();
    deque.~Deque();
    //=============сортировка======================
    cout<<"\n\nSortirovka vypolnyaetsya...\n"<<endl;
    Deque sort1;
    string s;
    ifstream fin("E:\\Vhod_timp2.txt");                             //путь документа
    while(getline(fin,s)){
        sort1.PushBack(s);
    }
    fin.close();
    sort1.sort();
    sort1.~Deque();
    system("pause");
    return 0;
}
