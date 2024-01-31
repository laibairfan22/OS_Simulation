#include<iostream>
#include <fstream>
using namespace std;
int main()
{
	char text[900];
fstream new_file; 
new_file.open("new_file.txt",ios::out);  
if(!new_file) 
{
cout<<"File creation failed";
}
else
{
cout<<"New file created\n\n";
cin.getline(text, sizeof(text));
new_file<<text<<endl;
new_file.close(); // Step 4: Closing file
}
return 0;
}
