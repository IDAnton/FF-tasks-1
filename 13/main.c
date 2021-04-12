#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_FORMAT ".dat"

typedef struct date{
    int day;
    int month;
    int year;
}date;

typedef struct data{
    char phone[12];
    char name[255];
    char surname[255];
    date date;
}data;

typedef struct CPeople{
    data data;
    struct CPeople* next;
}CPeople;

void add_new_record(CPeople** head, data data){
    CPeople* new = malloc(sizeof(CPeople));
    new->data = data;
    new->next = *head;
    *head = new;
}

//void delete_by_id(CPeople** head, CPeople* record_to_delete){
//    CPeople* tmp = *head;
//    if (record_to_delete == *head){
//        *head = (*head)->next;
//        free(record_to_delete);
//        return;
//    }
//    while(tmp->next != record_to_delete){
//        tmp = tmp->next;
//    }
//    tmp->next = record_to_delete->next;
//    free(record_to_delete);
//}

int delete_by_id(CPeople** head, int id){
    CPeople* tmp = *head;
    if (id <= 0)
        return -1;
    if (id == 1){
        *head = (*head)->next;
        free(tmp);
        return 0;
    }
    for(int i=1; i<(id-1); i++){
        if (tmp->next == NULL)
            return -1;
        tmp = tmp->next;
    }
    CPeople* record_to_delete = tmp->next;
    tmp->next = tmp->next->next;
    free(record_to_delete);
    return 0;
}

void free_list(CPeople** head){
    CPeople* tmp_p;
    while(*head != NULL){
        tmp_p = *head;
        *head = (*head)->next;
        free(tmp_p);
    }
    *head = NULL;
}

void print_list(CPeople* head){
    if(head == NULL)
        return;
    CPeople* pointer = head;
    printf("%2s   %11s%15s%15s%19s\n\n", "ID","PHONE","NAME","SURNAME","BIRTHDAY");
    int i = 1;
    while(pointer != NULL) {
        printf("%2d   %11s%15s%15s%15d-%02d-%02d\n", i, pointer->data.phone, pointer->data.name, \
        pointer->data.surname, pointer->data.date.year, pointer->data.date.month, \
        pointer->data.date.day);
        pointer = pointer->next;
        i++;
    }
    printf("\n");
}

int save_to_file(CPeople* head, FILE* file, char* file_name){
    CPeople* pointer = head;
    while(pointer != NULL) {
        fprintf(file,"%s %s %s %d %d %d\n", pointer->data.phone, pointer->data.name, \
        pointer->data.surname, pointer->data.date.year, pointer->data.date.month, \
        pointer->data.date.day);
        pointer = pointer->next;
    }
    fclose(file);
    printf("Book saved to %s\nPress any key to continue\n", file_name);
    char tmp;
    scanf_s(" %c", &tmp);
    return 0;
}

void load_from_file(CPeople** head, FILE* file){
    data record;
    while (fscanf(file, "%s %s %s %d %d %d",\
    record.phone, record.name, record.surname,\
    &record.date.year, &record.date.month, &record.date.day) != EOF)
                  add_new_record(head, record);

}

void flip_records(CPeople* p1, CPeople* p2){
    data tmp = p1->data;
    p1->data = p2->data;
    p2->data = tmp;
}

int compare_by_name(char* name1, char* name2, int order){
    int i = 0;
    while (name1[i] != '\0'){
        if(name1[i] < name2[i]){
            if (order)
                return 0;
            else
                return 1;
        }
        if(name1[i] > name2[i]){
            if (order)
                return 1;
            else
                return 0;
        }
        i++;
    }
    return 0;
}

int compare_by_date(date date1, date date2, int order){
    int res = 0;
    if (date1.year > date2.year)
        res = 1;
    else if (date1.year < date2.year)
        res = 0;
    else if (date1.month > date2.month)
        res = 1;
    else if (date1.month < date2.month)
        res = 0;
    else if (date1.day > date2.day)
        res = 1;
    else if (date1.day < date2.day)
        res = 0;

    if(order){
        if (res)
            return 0;
        else
            return 1;
    }
    return res;

}

int compare(data data1, data data2, int type ,int order){
    if (type == 0)
        return compare_by_name(data1.name, data2.name, order);
    if (type == 1)
        return compare_by_name(data1.surname, data2.surname, order);
    if (type == 2)
        return compare_by_date(data1.date, data2.date, order);
}

void sort_list(CPeople* head, int type, int order){
    CPeople* pointer_i = head;
    CPeople* pointer_j;
    while(pointer_i->next != NULL){
        pointer_j = head;
        while (pointer_j->next != NULL){
            if (compare(pointer_j->data, pointer_j->next->data, type, order)) {
                flip_records(pointer_j, pointer_j->next);
            }
            pointer_j = pointer_j->next;
        }
        pointer_i = pointer_i->next;
    }
}

int book_menu(char* book_name, CPeople** list) {
    int input;
    char tmp;
    while (1) {
        system("cls");
        printf("Book - %s\n\n", book_name);
        printf("1) Add new record\n");
        printf("2) Delete record\n");
        printf("3) Sort\n");
        printf("4) Save to file\n");
        printf("5) Back to main menu\n\n");
        print_list(*list);
        scanf_s("%d", &input);
        if (input == 1) {
            system("cls");
            printf("Enter phone number (11 digits)\n");
            char phone[12], name[255], surname[255];
            date birth_date;
            data new_data;
            scanf_s("%11s", new_data.phone, 12);
            printf("Enter name\n");
            scanf_s("%254s", new_data.name, 255);
            printf("Enter surname\n");
            scanf_s("%254s", new_data.surname, 255);
            printf("Enter birth date (year month day)\n");
            scanf_s("%d %d %d", &(birth_date.year), &(birth_date.month), &(birth_date.day));
            new_data.date = birth_date;
            add_new_record(list, new_data);
        }
        if (input == 2){
            system("cls");
            printf("How you want to delete record?\n");
            printf("1)By ID\n");
            printf("2)By Name\n");
            printf("3)Back\n\n");
            scanf_s("%d", &input);
            if(input == 1){
                system("cls");
                print_list(*list);
                printf("Enter ID to delete ");
                scanf_s("%d", &input);
                int res = delete_by_id(list, input);
                if(res == -1){
                    system("cls");
                    printf("ERROR - no such ID, try again\nPress any key to continue\n");
                    scanf_s(" %c", &tmp);
                }
            }
            continue;
        }
        if (input == 3) {
            int sort_type;
            int sort_order;
            system("cls");
            printf("1) Sort by name\n");
            printf("2) Sort by surname\n");
            printf("3) Sort by birthday\n");
            scanf_s("%d", &sort_type);
            system("cls");
            printf("1) Ascending sort\n");
            printf("2) Descending sort\n");
            scanf_s("%d", &sort_order);
            sort_type--;
            sort_order--;
            sort_list(*list, sort_type, sort_order);
        }
        if (input == 4) {
            system("cls");
            if (*list == NULL) {
                printf("Can't save, book is empty\nPress any key to continue\n");
                scanf_s(" %c", &tmp);
                continue;
            }
            FILE *file;
            char file_name[255];
            memset(file_name, 0, sizeof(file_name));
            strcat(file_name, book_name);
            strcat(file_name, FILE_FORMAT);
            file = fopen(file_name, "r");
            if (file != NULL) {
                fclose(file);
                printf("This book already exists\n1)Overwrite\n2)Back\n");
                scanf_s("%d", &input);
                if (input == 1) {
                    file = fopen(file_name, "w");
                    save_to_file(*list, file, file_name);
                }
                continue;
            }
            file = fopen(file_name, "w");
            save_to_file(*list, file, file_name);
        }
        if (input == 5)
            return 0;
    }
}

void main_menu(CPeople** list){
    int input;
    char tmp;
    char book_name[255];
    while (1) {
        system("cls");
        printf("PHONE BOOK MAIN MENU\n");
        printf("1) Create new book\n");
        printf("2) Open book from file\n");
        printf("3) Exit\n");
        scanf_s("%d", &input);
        free_list(list);
        if (input == 1) {
            system("cls");
            printf("Enter name of new book\n");
            scanf_s("%254s", book_name, 255);
            book_menu(book_name, list);
        }
        if (input == 2){
            system("cls");
            printf("Enter name of the book to open\n");
            scanf_s("%254s", book_name, 255);
            char file_name[255];
            memset(file_name, 0, sizeof(file_name));
            strcat(file_name, book_name);
            strcat(file_name, FILE_FORMAT);
            FILE* file;
            file = fopen(file_name, "r");
            if (file == NULL){
                printf("No such book in the directory\nPress any key to continue\n");
                scanf_s(" %c",&tmp);
                continue;
            }
            load_from_file(list, file);
            book_menu(book_name, list);
        }
        if (input == 3)
            break;
    }
}

int main() {
    CPeople *list = NULL;

    main_menu(&list);

//    date date1 = {2, 3, 2000};
//    data first = {"89137134830","Anton", "Ivanov", date1};
//    add_new_record(&list, first);
//    date1.day = 30;
//    data second = {"89137432831", "Ivan", "Borow", date1};
//    add_new_record(&list, second);
//    date1.month = 4;
//    date1.year = 1999;
//    data third = {"89114432831", "Petr", "Big", date1};
//    add_new_record(&list, third);
//    data four = {"89494432331", "Vaska", "Ukrainchev", date1};
//    add_new_record(&list, four);
//    print_list(list);
//    printf("\n");
//    print_list(list);


//    sort_list(list);
//      char a[10]="abc", b[10]="bca";
//      printf("%d",compare_by_name(a,b,0));
//    print_list(list);

    return 0;
}
