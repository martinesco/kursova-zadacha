#include "HeadHead.h"

/*List* loadData();
void menu();
void addToList(List* list, Menu* menu);
void addMenuToFile(Menu* menu);
void printMenu(List* list);
int nodesCounter(List* list);
void deleteMenu(List* list);
void saveListToFile(List* list);
void printMenu(Menu* menu);
void makeOrder(List*list, uint64_t table_number);
double orderList();*/

char fileName[30];

int Menu(){

    unsigned int option;

    printf("MENU\n");
    printf("1.Load file\n");
    printf("2.List menu\n");
    printf("3.Make an order\n");
    printf("4.See orders\n");
    printf("5.See turnover \n");     //demek oborot
    printf("6.Save data\n");
    printf("7.Add new item in the menu\n");
    printf("0.Exit\n");

    do{
		printf("SELECT OPTION: ");
		fflush(stdin);
		scanf("%d", &option);
	} while (option < 0 || option > 7);

	return option;
}
int main() {
    t_node* head = NULL;

	while (1){
		system("cls");
		switch (Menu()){
			case 1: loadFile(&head);
				break;
            case 2: printNode(&head);
                break;
			case 3: makeOrder(&head);
				break;
			case 4: //listOrders();//addNode(&head, initMENU(head), 1);
				break;
			case 5: //turnover();//printNode(&head);
				break;
			case 6: saveFile(head);
				break;
            case 7: addNode(&head, initMenu(head), 1);
				break;
			default:
				return 0;
		}
		system("pause");
	}
}
char* getFileName(){
	char *fileName = (char*)malloc(51 * sizeof(char));

	printf("\nEnter file name: ");
	getstr(fileName, 51);

	if (!strchr(fileName, '.')){
		strcat(fileName, ".dat");
	}

	return fileName;
}

void loadFile(t_node** head){
	FILE* fp;
	menu data;
	char *fileName;

	fileName = getFileName();

	if (!(fp = fopen(fileName, "rb"))){
		fprintf(stderr, "Error loading file!\a\n");
		free(fileName);
		return;
	}

	if (*head)
		deleteNode(head);

	while (1){
		if (!fread(&data, sizeof(data), 1, fp))
			break;

		addNode(head, data, 2);
	}

	fclose(fp);

	if (!(*head))
		printf("No data loaded from \"%s\"\n", fileName);
	else
		printf("Info loaded successfully from \"%s\"\n", fileName);

	free(fileName);
}

menu initMenu(t_node* head){
	menu newItem;

	printf("Enter Name: ");
	getstr(newItem.name, 51);
	do{
		printf("Enter Price: ");
		fflush(stdin);
		scanf("%f", &newItem.price);
	} while (newItem.price <= 0);
	do{
		printf("Enter Quantity: ");
		fflush(stdin);
		scanf("%lg", &newItem.quantity);
	} while (newItem.quantity < 0 || newItem.quantity > 999);

	return newItem;
}

void printMenu(menu data){
	printf("Name: %s\n", data.name);
	printf("Price: %f\n", data.price);
	printf("Quantity: %lg\n", data.quantity);
}

void makeOrder(t_node** head) {
    //printNode(&head);

    char nameItem[30];
    double quantityItem = 0;
	int poss = 1, count = 0;
	t_node* temp = (*head);

	if (!(*head)){
		printf("List is Empty!\n");
		return;
	}
	printf("Enter Name: ");
	getstr(nameItem, 30);

	while (temp){
		if (!strCmpIgnoreCase(nameItem, temp->data.name)){
			printf("\nItem: %d\n", ++count);
			printMenu(temp->data);
		}
		temp = temp->next;
	}
	if (!count){
		printf("No items Found!");
		return;
	}

	printf("\nEnter Quantity: ");
	scanf("%lg", &quantityItem);

	temp = (*head);
	while (temp){
		if (!strCmpIgnoreCase(nameItem, temp->data.name)){
			(temp->data.quantity) = (temp->data.quantity) - quantityItem;
            printf("You bought %lg of %s\n", quantityItem, nameItem);
            printf("There are %lg amount available\n", temp->data.quantity);
            if(temp->data.quantity<=0) {
                printf("Item %s is used up!\n");
                deleteNodeAtPoss(head, poss);
            }
			temp = temp->next;
		}
		else{
			temp = temp->next;
			++poss;
		}
	}

}

int isEmpty(t_node* head){
	if (head)
		return 0;
	printf("List is empty!\n");
	return 1;
}

unsigned int nodesCounter(t_node* head){
	unsigned int n = 0;
	while (head){
		++n;
		head = head->next;
	}

	return n;
}

void printNode(t_node** head)	{
	int i = 0;
	t_node* temp = (*head);

	if (isEmpty(*head))
		return;

	while (temp){
		printf("\nItem %d\n", ++i);
		printMenu(temp->data);

		temp = temp->next;
	}
}

void addNode(t_node** head, menu data, int mode){
	t_node* temp = (t_node*)malloc(sizeof(t_node));
	t_node* temp2 = *head;

	temp->data = data;
	temp->next = NULL;

	if (!(*head)){
		*head = temp;
		if (mode == 1)
			printf("First item added successfully!\n");
		return;
	}

	while (temp2->next){
		temp2 = temp2->next;
	}

	temp2->next = temp;
	if (mode == 1)
		printf("New item added successfully!\n");
}

void deleteNode(t_node** head){
	t_node* temp;

	while (*head){
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void deleteNodeAtPoss(t_node** head, int poss){
	int i;
	t_node *temp1 = (*head), *temp2;

	if (poss == 1){
		(*head) = temp1->next;
		free(temp1);
		return;
	}

	for (i = 0; i < poss - 2; i++){
		temp1 = temp1->next;
		//temp1 pointst to (n-1)th possition;
	}
	temp2 = temp1->next;//temp2 points to n-th poss Node;
	temp1->next = temp2->next;
	free(temp2);
}

void saveFile(t_node* head){
	FILE* fp;
	char *fileName;

	if (isEmpty(head)){
		printf("Add some items int the menu first!\n");
		return;
	}

	fileName = getFileName();

	if (!(fp = fopen(fileName, "wb"))){
		exit(1);
	}

	while (head){
		if (fwrite(&head->data, sizeof(menu), 1, fp) != 1){
			printf("Error occured while writing on file\n");
			exit(1);
		}
		head = head->next;
	}

	fclose(fp);

	printf("Info saved successfully to \"%s\"\n", fileName);
	free(fileName);
}

void getstr(char* str, int maxLen){
	fflush(stdin);
	fgets(str, maxLen * sizeof(char), stdin);
	str[strlen(str) - 1] = '\0';
}

int strCmpIgnoreCase(char* str1, char* str2){
	char str1upper[51];
	char str2upper[51];
	unsigned i;

	strcpy(str1upper, str1);
	strcpy(str2upper, str2);

	for (i = 0; i < strlen(str1); i++){
		str1upper[i] = toupper(str1upper[i]);
	}
	for (i = 0; i < strlen(str2); i++){
		str2upper[i] = toupper(str2upper[i]);
	}

	if (!strcmp(str1upper, str2upper)){
		return 0;
	}
	return -1;
}
/*List* loadData(){
  FILE* fp = fopen(fileName, "r");
  if(fp == NULL){
    printf("Problem with openning file\n");
    return NULL;
  }
  List* list  = malloc(sizeof(List));
  list->menu = NULL;
  list ->next = NULL;
  List* current = list;
  List* prev;
  Menu* menu;

  while (!feof(fp)) {
    menu = malloc(sizeof(Menu));
    prev = current;
    current->next = malloc(sizeof(List));
    current = current->next;
    current->next = NULL;
    if(!fread(menu, sizeof(Menu), 1, fp)){
      prev->next = NULL;
      free(current);
      free(menu);
      break;
    }
    current->menu = menu;
  }
  current = list;
  fclose(fp);
  return list;
}

void makeOrder(List*list, uint64_t table_number) {
    List* current = list->next;
    List* prev = list;

    double totalamount = 0;
	char product_name[10];
	uint64_t quantity_number = 0;

    listMenu(list);
    printf("You have chosen table: %u\n", table_number);

    /* Products are chosen based on their name
	printf("Enter the name of the product:");
	while (getchar() != '\n') {}
	  gets(product_name);

	/* Enter the quantity of the product
	printf("Enter quantity for the product:");
	scanf("%u", &quantity_number);

    while (current != NULL) {
      if (strcmp(current->menu->name, product_name) == 0) {
        if (prev) {
          prev->next = current->next;
          current->menu->quantity -= quantity_number;
          totalamount = (current->menu->price * quantity_number);
          current = prev->next;
        }
      } else {
        prev = current;
        current = current->next;
      }
    }
    printf("total amount orders: %lg\n", totalamount);
    //orderList();

}

void addToList(List* list, Menu* menu){
  List* current = list;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = malloc(sizeof(List));
  current = current->next;
  current->next = NULL;
  current->menu = menu;
}

void addMenuToFile(Menu* menu){
  FILE* fp = fopen(fileName, "a");
  if(fp == NULL){
    printf("problem with updating!\n" );
    return;
  }
  fwrite(menu, sizeof(Menu), 1, fp);
  fclose(fp);
}

void listMenu(List* list){

  //bubbleSortByYear(list);

  List* current = list  ->next;
  printf("| NAME | PRICE | QUANTITY |\n");
  while (current != NULL) {
    if(current->menu !=NULL){
      printMenu(current->menu);
      current = current->next;
    }
  }
}

void printMenu(Menu* menu){
  printf("| %s | %f | %u |\n", menu->name, menu->price, menu->quantity);
}

int nodesCounter(List* list){
  int i  = 0;
  List* current = list;
  while (current != NULL) {
    i++;
    current = current->next;
  }
  return i;
}

void deleteMenu(List* list, char Name){
    List* current = list->next;
    List* prev = list;

    while (current != NULL) {
      if (strcmp(current->menu->name, Name) == 0) {
        if (prev) {
          prev->next = current->next;
          free(current);
          current = prev->next;
        }
      }else {
        prev = current;
        current = current->next;
      }
    }
    saveListToFile(list);
}

void saveListToFile(List* list){
  List* current = list->next;
  FILE* fp = fopen(fileName, "w");
  if(fp == NULL){
    printf("Problem with adding to file!\n" );
    return;
  }
  while (current != NULL) {
    fwrite(current->menu, sizeof(Menu), 1, fp);
    current = current->next;
  }
  fclose(fp);
}*/
