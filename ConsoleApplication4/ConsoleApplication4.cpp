#include <iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

typedef struct info // struct med variabler
{
	string day, place;
	double avgtem;
	double avghum;
	int mold;
	info() : day("0"), place("0"), avgtem(0), avghum(0), mold(0) {}
}info;

void swap(info* a, info* b) //Swap 
{
	info temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort (vector<info> &vec)				//Sortering av medeltemperatur med Bubblesort 
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = 0; j < vec.size() -1; j++)
		{
			if (vec[j].avgtem > vec[j + 1].avgtem)
				swap(&vec[j], &vec[j + 1]);  //Stoppa i swap 
		}
	}
}
void PrintVector(vector<info> vec)									//Skriv ut 5 kallaste och warmaste dagar 
{
	cout << "   5 coldest days    " << endl;		
	cout << "=====================" << endl;
	for (int i = 0; i < 5; i++)										//for loop för att gå igenom dem 5 första värden i vector
	{
		cout << vec[i].day << "\t" << vec[i].avgtem << endl;

	}
	cout << "   5 hotest days     " << endl;
	cout << "=====================" << endl;
	vector<int>::size_type n = vec.size();
	for (int i = n - 1; i > 125; --i)
	{
		cout << vec[i].day << "\t" << vec[i].avgtem << endl;
		
	}
}

void moldUte(vector<info>& vec)							// mögelrisk
{
	
		
	for (size_t i = 0; i < vec.size(); i++)
	{
		
		if ((vec[i].avgtem >= 15 && vec[i].avgtem <50) && vec[i].avghum > 78)
		{
			vec[i].mold = (vec[i].avghum - 78) / 2.2;
		}
		 if ((vec[i].avgtem >= 0 && vec[i].avgtem < 15) && vec[i].avghum > 78)
		{
			 vec[i].mold = (((vec[i].avghum - 78) * (vec[i].avgtem / 15)) / 2.2);
		}
		else
		{
			vec[i].mold = 0;
		}
	}
}
void BubbleSortmold(vector<info>& vec) //Sortering av mögelrisk med Bubblesort 
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = 0; j < vec.size() - 1; j++)
		{
			if (vec[j].mold > vec[j + 1].mold)
				swap(&vec[j], &vec[j + 1]);
		}
	}
}
void PrintVectormold(vector<info> vec)						 //Skriv ut mögelrisk 
{
	for (size_t i = 0; i < vec.size(); i++)
	{ 
		if (vec[i].mold != 0)
		{
			cout << vec[i].day << "\t" << vec[i].avgtem << "\t" << vec[i].avghum << "\t" << vec[i].mold << endl;
		}

	}
}

void BubbleSorthum(vector<info>& vec)					 //Sortering av medelluffuktighet med Bubblesort 
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = 0; j < vec.size() - 1; j++)
		{
			if (vec[j].avghum > vec[j + 1].avghum)
				swap(&vec[j], &vec[j + 1]);
		}
	}
}
void PrintVectorhum(vector<info> vec) //Skriv ut medelluffuktighet
{
	cout << "   5 driest days     " << endl;
	cout << "=====================" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << vec[i].day << "\t" << vec[i].avghum << endl;

	}cout << endl;
	cout << "   5 humidest days   " << endl;
	cout << "=====================" << endl;
	vector<int>::size_type n = vec.size();
	for (int i = n - 1; i > 125; --i)
	{
		cout << vec[i].day << "\t" << vec[i].avghum << endl;

	}
}

void Printwinter(vector<info>& vec) {					//meterologisk vinter
	bool founwinter = false;
		for (size_t i = 0; i < vec.size(); i++)
		{

			if (vec[i].avgtem < 0 && vec[i+1].avgtem < 0 && vec[i+2].avgtem < 0 && vec[i+3].avgtem < 0 && vec[i+4].avgtem < 0)
			{
				founwinter = true;
				cout << vec[i].day << endl;
			}
			
		}
		if (founwinter == false)
			{
			cout << "Ingen meterologisk vinter" << endl;
			}
}
void Printautumn(vector<info>& vec) {					//meterologisk höst
	
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i].avgtem >= 0 && vec[i].avgtem <= 10  && vec[i+1].avgtem <= 10 && vec[i+2].avgtem <= 10 &&  vec[i+3].avgtem <= 10 && vec[i+4].avgtem <= 10)
		{
			if (vec[i].avgtem >= vec[i+1].avgtem && vec[i+1].avgtem >= vec[i+2].avgtem && vec[i+2].avgtem >= vec[i+3].avgtem && vec[i+3].avgtem >= vec[i+4].avgtem)
			{
					cout << vec[i].day << endl;
					break;
			}			
		}

	}
}

void ShowMenu();

int main()
{
	string date, time, inOut, temperature, humidity;
	ifstream file("tempdata4.txt");						//läser in fillen
	
	vector<info>Inne;									// Skapar två vectorer (Inne och Ute)
	vector<info>Ute;
	
	if (!file.is_open())
	{
		exit(EXIT_FAILURE);								//om fillen öppnas inte då stäng programmet
	}
	else
	{
		cout << "Your data is loading ... "<< endl;
		
		string currentDate = " ";
		string checkDate = " ";
		int  incount = 0;
		int  outcount = 0;
		int  count = 0;
		double tempsumin = 0;
		double humsumin = 0;
		double tempsumut = 0;
		double humsumut = 0;

		info in;
		info ut;

		while (!file.eof())							//Stoppar in alla information i deklarerade variabler
		{

			getline(file, date, ' ');
			getline(file, time, ',');
			getline(file, inOut, ',');
			getline(file, temperature, ',');
			getline(file, humidity);



			if (date == checkDate)
			{
				if (inOut == "Inne")
				{
					tempsumin += stod(temperature);
					humsumin += stod(humidity);
					incount++;
				}
				else if (inOut == "Ute")
				{
					tempsumut += stod(temperature);
					humsumut += stod(humidity);
					outcount++;
				}
				currentDate = date;
				count++;
			}
			else
			{
				checkDate = date;
				if (count != 0)
				{
					in.avgtem = round((tempsumin / incount) * 10) /10;	
					in.avghum = round((humsumin / incount) * 10) / 10;
					in.day = currentDate;
					in.place = "Inne";
					Inne.push_back(in);											//spara inne information i vector Inne
					in.avgtem = 0; in.avghum = 0; incount = 0; tempsumin = 0; humsumin = 0; in.mold = 0;

					ut.avgtem = round((tempsumut / outcount) * 10) /10 ;
					ut.avghum = round((humsumut / outcount) * 10) / 10;
					ut.day = currentDate;
					ut.place = "Ute";
					Ute.push_back(ut);											//spara ute information i vector ute
					ut.avgtem = 0; ut.avghum = 0; outcount = 0; tempsumut = 0; humsumut = 0;
				}
			}
		}
		
		int Choice;
		system("CLS");
		do												//do while till menyn
		{
			
			ShowMenu();
			cin >> Choice;
			system("CLS");
			if (Choice == 1)							//om valet är 1 då skriv ut medeltemperatur och medelluftfuktighet för valt datum
			{
				cout << "write your date: " << endl;
				cin >> checkDate;
				for (size_t i = 0; i < Ute.size(); i++)
				{
					if (Ute[i].day == checkDate)
					{
						cout << "The average temperature of " << checkDate << " - " << " for outside is " << Ute[i].avgtem << endl;
						cout << "The average humidity of " << checkDate << " - " << " for outside is " << Ute[i].avghum << endl;
					}
				}
			}
			if (Choice == 2)
			{
				cout << "   Date   " << "\t" << "Place " << "AvgTemp " << " AvgHum " << endl;
				cout << "==========" << "\t" << "===== " << "======= " << " ====== " << endl;
				for (size_t i = 0; i < Ute.size(); i++)
				{
					cout << Ute[i].day << "\t" << Ute[i].place << "\t" << Ute[i].avgtem << "\t" << Ute[i].avghum << endl;
				}
			}
			if (Choice == 3)
			{
				BubbleSort(Ute);
				PrintVector(Ute);
			}
			if (Choice == 4)
			{
				BubbleSorthum(Ute);
				PrintVectorhum(Ute);
			}
			if (Choice == 5)
			{
				moldUte(Ute);
				BubbleSortmold(Ute);
				PrintVectormold(Ute);
			}
			if (Choice == 6)
			{
				cout << "write your date: " << endl;
				cin >> checkDate;

				for (size_t i = 0; i < Inne.size(); i++)
				{
					if (Inne[i].day == checkDate)
					{
						cout << "The average temperature of " << checkDate << " - " << " for Inside is " << Inne[i].avgtem << endl;
						cout << "The average humidity of " << checkDate << " - " << " for Inside is " << Inne[i].avghum << endl;
					}
				}
			}

			if (Choice == 7)
			{
				cout << "   Date   " << "\t" << "Place " << "AvgTemp " << " AvgHum " << endl;
				cout << "==========" << "\t" << "===== " << "======= " << " ====== " << endl;
				for (size_t i = 0; i < Inne.size(); i++)
				{
					cout << Inne[i].day << "\t" << Inne[i].place << "\t" << Inne[i].avgtem << "\t" << Inne[i].avghum << endl;
				}
			}

			if (Choice == 8)
			{
				BubbleSort(Inne);
				PrintVector(Inne);
			}
			if (Choice == 9)
			{
				BubbleSorthum(Inne);
				PrintVectorhum(Inne);
			}
			
			if (Choice == 10)
			{
				Printwinter(Ute);				
			}
			if (Choice == 11)
			{			
				Printautumn(Ute);
			}
			

		} while (Choice == 1 || Choice == 2 || Choice == 3 || Choice == 4 || Choice == 5 || Choice == 6 || Choice == 7 || Choice == 8 || Choice == 9 || Choice == 10 || Choice == 11);
				
	}
}
void ShowMenu() 
{	
	cout << "\n======================================= Outside ================================\n" << endl;
	cout << "1.Sort outside temperature for chosen date:" << endl;
	cout << "2.Sort outside temperature by date:" << endl;
	cout << "3.Sort of hottest and coldest days according to average temperature per day:" << endl;
	cout << "4.Sorting of the driest and the humidest days according to average humidity per day:" << endl;
	cout << "5.Sorting of the high risk of mold:" << endl;
	cout << "\n====================================== Inside ==================================\n" << endl;
	cout << "6.Sort inside temperature for chosen date:" << endl;
	cout << "7.Sort inside temperature by date:" << endl;
	cout << "8.Sort of hottest and coldest days, according to average temperature per day:" << endl;
	cout << "9.Sorting of the driest and the humidest days according to average humidity per day:" << endl;
	cout << "10.Meterological Winter" << endl;
	cout << "11.Meterological Autumn" << endl;
	cout << "0.Exit" << endl;
	cout << "Enter a number: "; 

}


				