//============================================================================
// Name        : DealNoDeal.cpp
// Author      : Jobith M Basheer
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Box
{

  public:
	int no;
	int money;
	int isOpened;
	int chosen;

	Box(){
		no = 0;
		money = 0;
		isOpened = 0;
		chosen = 0;
	}

    Box(int n, int m){
    	no = n;
    	money = m;
    	isOpened = 0;
    	chosen = 0;
    }

	void show(){
		cout<<"you have opened the box : "<<no<<" with money : "<<money<<" opened = "<<isOpened<<endl;
	}


};

struct node
{
    Box moneyBox;
    struct node *next;

}*start;

class single_llist
{
    public:
        node* create_node(Box);

        void insert_last(Box);
        //void delete_pos();
        int search(int);
        void update(int);
        void display();

        single_llist()
        {
            start = NULL;
        }
};


/* Global Variables */

	int prizes[] = {1, 5, 10, 20, 50, 100, 250, 500, 1000, 2500};
	int data[] =  {0, 1, 2,  3,  4,  5,   6,   7,   8,    9};
	int size   =  sizeof(data)/sizeof(data[0]);
	int i,offer;
	single_llist sl;


/* End of Global Variables */
int getRandom(int, int) ;
void shuffleData(int [], int);
void initialize();
void showGameBoard();
void playerMove(int);
void makeOffer();
int remBoxes();
void myBox();
void chooseBox();
void dealOrNoDeal();


int main()
{
	initialize();
	system("clear");
	showGameBoard();
	chooseBox();

	do
	{
		system("clear");

		if(remBoxes() != 10)
			makeOffer();
		else
			cout<<"Deal or NoDeal !"<<endl;

		showGameBoard();

		if(remBoxes() != 10)
			dealOrNoDeal();

		playerMove(1);


	}while(remBoxes()>=2);

	system("clear");
	showGameBoard();
	makeOffer();
	cout<<endl<<"Your Box has = ";
	myBox();

	cout<<endl<<endl;
	return 0;;
}

int getRandom(int min, int max)
{
   static bool first = true;
   if ( first )
   {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}

void shuffleData(int d[], int s)
{
   static bool first_shuffle = true;
   if ( first_shuffle )
   {
	  std::srand(time(NULL)); //seeding for the first time only!
	  first_shuffle = false;
   }
   std::random_shuffle(d, d + s);
}

void initialize()
{
	for(i=0;i<=getRandom(1,8);i++)
		shuffleData(data, size);

	start = NULL;

	for(i=0;i<10;i++)
		sl.insert_last(Box(i+1,prizes[data[i]]));

	//sl.display();
	cout<<"Boxes initialized, Ready for rendering the Boxes!"<<endl;
}

void showGameBoard()
{

	struct node *temp;
	if (start == NULL)
	{
		cout<<"The List is Empty"<<endl;
		return;
	}
	temp = start;
	while (temp != NULL)
	{
		if(!temp->moneyBox.isOpened && !temp->moneyBox.chosen)
			cout<<"[ "<<temp->moneyBox.no<<" ]";
		else if(temp->moneyBox.isOpened && !temp->moneyBox.chosen)
			cout<<"[ $"<<temp->moneyBox.money<<" ]";
		else if(temp->moneyBox.chosen)
			cout<<"[ *"<<temp->moneyBox.no<<" ]";

		temp = temp->next;
	}
	cout<<endl;
}

void playerMove(int n)
{
	int ch;

	for(i=1;i<=n;i++)
	{
		cout<<"Enter the Box no. to open : ";
		cin>>ch;

		struct node *temp;
		if (start == NULL)
		{;}
		temp = start;
		while (temp != NULL)
		{

			if(temp->moneyBox.no == ch){
				if(!temp->moneyBox.chosen)
				{

					temp->moneyBox.isOpened = 1;
					break;
				}
				else
					cout<<"Cannot open chosen box!"<<endl;

			}
			temp = temp->next;
		}
}

}

int remBoxes()
{
	int cnt = 0 ;
	struct node *temp;
	if (start == NULL)
	{
		//cout<<"The List is Empty"<<endl;
		return cnt;
	}
	temp = start;
	//cout<<"Elements of list are: "<<endl;
	while (temp != NULL)
	{
		if(!temp->moneyBox.isOpened)
			cnt++;
		temp = temp->next;
	}

	return cnt;
}

void myBox(){
	struct node *temp;
	if (start == NULL)
	{
		//cout<<"The List is Empty"<<endl;
	}
	temp = start;
	//cout<<"Elements of list are: "<<endl;
	while (temp != NULL)
	{
		if(!temp->moneyBox.isOpened){
			break;
		}
		temp = temp->next;
	}
	cout<<temp->moneyBox.money;
}

void makeOffer()
{
	int sum = 0, cnt = 0;

	struct node *temp;
	if (start == NULL)
	{
		//cout<<"The List is Empty"<<endl;
	}
	temp = start;
	//cout<<"Elements of list are: "<<endl;
	while (temp != NULL)
	{
		if(!temp->moneyBox.isOpened){
			sum += temp->moneyBox.money;
			cnt++;
		}
		temp = temp->next;
	}

	offer = (sum/cnt);
	cout<<"Offer is $"<<offer<<endl;


}

void dealOrNoDeal()
{
	char res;
	cout<<endl<<"Deal or NoDeal ?? (D/N):: ";
	cin>>res;
	if(res=='D'||res=='d'){
		cout<<endl<<"You have won : $"<<offer<<endl<<endl;
		//exit(0);
	}

}
void chooseBox()
{
	cout<<"Choose your Box No. : ";
	int mybox;
	cin>>mybox;

	struct node *temp;
	if (start == NULL)
	{;}
	temp = start;
	while (temp != NULL)
	{
		if(temp->moneyBox.no == mybox){
			temp->moneyBox.chosen = 1;
			break;
		}
		temp = temp->next;
	}

}
/*  Creating Node  */
node *single_llist::create_node(Box b)
{
    struct node *temp;
    temp = new(struct node);
    if (temp == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        temp->moneyBox.no = b.no;
        temp->moneyBox.money = b.money;
        temp->next = NULL;
        return temp;
    }
}

/*  Insert at Last  */
void single_llist::insert_last(Box b)
{
    struct node *temp, *s;

    temp = create_node(b);

    if (start == NULL)
	{
		start = temp;
		start->next = NULL;
		//start->moneyBox.show();
	}
    else
    {
		s = start;
		while (s->next != NULL)
		{
			s = s->next;
		}

		s->next = temp;
		//s->moneyBox.show();
    }
    //temp->moneyBox.show();
    //cout<<"Element Inserted at last"<<endl;
}


/* Update a given Node */
void single_llist::update(int pos)
{
    int i;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }


    struct node *s;
    s = start;
    if (pos == 1)
    {
        start->moneyBox.isOpened = 1;
    }
    else
    {
        for (i = 1;i < pos; i++)
        {
            if (s == NULL)
            {
                cout<<"There are less than "<<pos<<" elements";
                return;
            }
            s = s->next;
        }
        s->moneyBox.isOpened = 1;
        //s->moneyBox.show();
    }

}


/*  Searching an element  */
int single_llist::search(int value)
{
    int pos = 0;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return 0;
    }

    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->moneyBox.no == value)
        {
            flag = true;
            //cout<<"Element "<<value<<" is found at position "<<pos<<endl;
        }
        s = s->next;
    }

    if(flag)
    	return pos;
    else
    	return 0;

}

/* Display Elements of a link list */
void single_llist::display()
{
    struct node *temp;
    if (start == NULL)
    {
        cout<<"The List is Empty"<<endl;
        return;
    }
    temp = start;
    cout<<"Elements of list are: "<<endl;
    while (temp != NULL)
    {
        temp->moneyBox.show();
        temp = temp->next;
    }

}
