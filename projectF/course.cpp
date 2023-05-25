#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include <cstdlib>
#include<algorithm>
#include<sstream>

class course;
class classroom;

using namespace std;





//tabdil string be bool 
bool stringToBool(string temp){
    bool check{true};
    if(temp == "true" || temp == "True" || temp == "TRUE")
        check = true;
    else if(temp == "false" || temp == "False" || temp == "FALSE" )
        check = false;
    return check;

}

course min(course a , course b){

    if(a.courseTime.st<b.courseTime.st)
        return a;
    else
        return b;
}

course max(course a , course b){

    if(a.courseTime.st>b.courseTime.st)
        return a;
    else
        return b;
}

//class date: braye neshan dadan tarikh va saat dars va kelas
class date{
   // friend auto calcuteTime(date object);
    friend void sortDay(course temp[4]);
    friend course checkTime(course temp , course dayOfWeek);
private:
    /*int day;
    int month;
    int year;*/
    int hourStart;
    int minStart;
    int hourEnd;
    int minEnd;
    int durationMin;
    int durationHour;
    string day;
public:
    double st,et;
    /*date(int d = 1 , int m = 1 , int y = 1401 ,int hS = 0 , int mS = 0 , int duH = 0 , int duM = 0 ){
        day = d;
        month = m;
        year = y;
        hourStart = hS;
        minStart = mS;
        hourEnd = 0;
        minEnd = 0;
        durationMin = duM;
        durationHour = duH;

    }*/

    void set_HS(int a = 0)
    {
        hourStart = a;
    }
    void set_MS(int a = 0)
    {
        minStart = a;
    }
    void set_DH(int a = 0)
    {
        durationHour = a;
    }
    void set_DM(int a = 0)
    {
        durationMin = a;
    }
    void set_Day(string days){
        day = days;
    }

   void calcuteTime()
    {


        minEnd = minStart + durationMin;
        if(minEnd > 59)
        {
            minEnd -=60;
            hourEnd =1;
        }

        hourEnd += hourStart + durationHour;
        if(hourEnd>23)
            minEnd -=24;


        st=hourStart+(0.01*minStart);
        et=hourEnd+(0.01*minEnd);
    }

   

};
 course checkTime(course temp , course dayOfWeek){
        course A = min(temp , dayOfWeek);
        course B = max(temp , dayOfWeek);
        if (!(A.courseTime.st < B.courseTime.st && A.courseTime.et < B.courseTime.et && A.courseTime.et < B.courseTime.st))
            {
                if(A.courseTime.st == temp.courseTime.st)
                    return A;

                if(B.courseTime.st == temp.courseTime.st)
                    return B;    

            }

    }




// baraye mohasebe saat payan dars kelas
/*
auto calcuteTime(date object)
{

    object.minEnd = object.minStart + object.durationMin;
    if(object.minEnd > 59)
    {
        object.minEnd -=60;
        object.hourEnd =1;
    }

    object.hourEnd += object.hourStart + object.durationHour;
    if(object.hourEnd>23)
        object.minEnd -=24;

    array<int , 2> timeEnd = {object.hourEnd , object.minEnd};
    return timeEnd;
}
*/



//class classroom : etalaat kelas
class classroom{
    friend void mothercheck(course temp[4]);
   // friend void check();
   // friend void inputClassroom(classroom& temp ,string help);
private:
    string idClass;
    int capacityClass;
    bool videoprojector;
    //date dateClass;
    //string idCourse;


public:


    void show(){
        cout<<boolalpha;
        cout<<idClass<<endl<<capacityClass<<endl<<videoprojector<<endl;
    }

    void inputClassroom(string help){
    /*char auxiliary[80];
    char assist[80];*/
	string auxiliary;
	string assist;
    fstream classtemp;
    classtemp.open("proj.txt" , ios::in);
    if(classtemp.fail()){
        cout<<"fail\the file has a problem"<<endl;
    }
    int j;
    for(j = 1; !classtemp.eof(); j++ ){
			getline(classtemp,assist);
        if(assist == help)
            break;
    }

    
    classtemp.close();
    classtemp.open("proj.txt" , ios::in);

    for(int i{1}; !classtemp.eof(); i++){
        getline(classtemp,auxiliary);
        if(i>=j-1 && i<=j+6){

            if(i == j)
                idClass = auxiliary;
            if(i == j+1){
			const char* x = auxiliary.c_str();
                capacityClass = atoi(x);}
            if(i == j+2)
                videoprojector = stringToBool(auxiliary);


            /* if(i == j+5)
             {
                 const char* x = auxiliary;
                 temp.capacityCourse = atoi(x);
             }*/


        }

    }
    classtemp.close();
}

};



//class course: etelaat dars
class course{
    friend course great(course a , course b);
    friend void sortDay(course temp[4]);
    friend void mothercheck(course temp[4]);

    //friend void inputCourse(course&temp , string help);
private:
    string idCourse;
    string name;
    string teachername;
    bool videoprojector[2];
    bool temprary;
    int capacityCourse[2];
    
    //vector<int>studentList;
    int* studentList{new int[capacityCourse[0]]};

public:
    classroom location; 
    date courseTime;
    void show(){
        cout<<boolalpha;
        cout<<idCourse<<endl<<name<<endl<<teachername<<endl<<videoprojector[0]<<endl<<temprary<<endl<<capacityCourse[0]<<endl;
        cout<<"student list : ";
        for(int i=0;i<capacityCourse[0];i++){
            cout<<studentList[i]<<" ";
        }
    }

 void inputCourse(string help){

    /*char auxiliary[80];
    char assist[80];*/
    string auxiliary;
    string assist;

    fstream coursetemp;
    coursetemp.open("proj.txt" , ios::in);
    if(coursetemp.fail()){
        cout<<"fail\the file has a problem"<<endl;
    }

    int j;
    for(j = 1;!coursetemp.eof();j++)
    {
        getline(coursetemp,assist);
        if(assist == help)
            break;
    }

    coursetemp.close();

    coursetemp.open("proj.txt" , ios::in);

    for(int i{1};!coursetemp.eof();i++){


       getline(coursetemp,auxiliary);

       if(i>=j-1 && i<=j+11){

            if(i == j)
                idCourse = auxiliary;
            if(i == j+1)
                name = auxiliary;
            if(i == j+2)
                teachername = auxiliary;
            if(i == j+3)
                videoprojector[0] = stringToBool(auxiliary);
            if(i == j+4)
                temprary = stringToBool(auxiliary);
            if(i == j+5){
                const char* x = auxiliary.c_str();
                capacityCourse[0] = atoi(x);
            }
            
            if(i == j+6){
                const char* x = auxiliary.c_str();
                courseTime.set_HS(atoi(x));
            }
            if(i == j+7){
                const char* x = auxiliary.c_str();
                courseTime.set_MS(atoi(x));
            }
            if(i == j+8){
                const char* x = auxiliary.c_str();
                courseTime.set_DH(atoi(x)); 
            }
            if(i == j+9){
                const char* x = auxiliary.c_str();
                courseTime.set_DM(atoi(x));
            }
            if(i == j+10){
                courseTime.set_Day(auxiliary);

            }

            if(i == j+11){
                istringstream helping(auxiliary);
                for(int k=0; k<capacityCourse[0] ;k++){
                    helping>>studentList[k];
                    coursetemp.ignore(1,' ');
                }

            }

        }

    }
    coursetemp.close();
    

}

};


/*template <typename T>
T stringToInteger(string str){
    T result;
    istringstream convert(str);
    if ( !(convert >> result) )
        throw "Can not convert";

    return result;}*/




//hanooz kamel nashode vali baraye moshakhas kardan mahal ya hamoon kelase
void specify(course temp[4])
{
   /* course AdvanceProgramming;
    course Math;
    course physics;
    course workshop*/
    bool check;
    cout<<"you want to determine the location of each course yourself (enter 1)| the program specifies the location of each course (enter 0) "<<endl; 
    cin>>check; 
    if(check){
     for(int i{0}; i<4; i++){
        string questionForCourse;
        string questionForClassroom; 
        cout<<"to determine the classroom , enter the desired course : ";
        //getline(cin , questionForCourse);
        cin>>questionForCourse;
        if(questionForCourse == "AdvanceProgramming")
        {
            //AdvanceProgramming.inputCourse("AP101");
            temp[0].inputCourse("AP101");
            cout<<"enter the desired classroom for the Advance Programming course : ";
            //getline(cin , questionForClassroom);
            cin>>questionForClassroom;
            //(AdvanceProgramming.location).inputClassroom(questionForClassroom);
            (temp[0].location).inputClassroom(questionForClassroom);
        }   

        if(questionForCourse == "Math")
        {
           // Math.inputCourse("MH101");
            temp[1].inputCourse("MH101");
            cout<<"enter the desired classroom for the Math course : ";
            //getline(cin , questionForClassroom);
            cin>>questionForClassroom;
            //(Math.location).inputClassroom(questionForClassroom);
            (temp[1].location).inputClassroom(questionForClassroom);    
        }

         if(questionForCourse == "Physics")
         {
            //Physics.inputCourse("PH101");
            temp[2].inputCourse("PH101");
            cout<<"enter the desired classroom for the Phycsics course : ";
            //getline(cin , questionForClassroom);
            cin>>questionForClassroom;
            //(Physics.location).inputClassroom(questionForClassroom);
            (temp[2].location).inputClassroom(questionForClassroom);    
        }

         if(questionForCourse == "Workshop")
         {
            //workshop.inputCourse("WH101");
            temp[3].inputCourse("HH101");
            cout<<"enter the desired classroom for the Workshop course : ";
            //getline(cin , questionForClassroom);
            cin>>questionForClassroom;
            //(workshop.location).inputClassroom(questionForClassroom);
            (temp[3].location).inputClassroom(questionForClassroom);    
        }
     }
    }

}

course week[7][4];

void sortDay(course temp[4])
{
    course saturday[4];
    course sunday[4];
    course monday[4];
    course tuesday[4];
    course wednesday[4];
    course thurday[4];
    course friday[4];
    int j{0};int z{0};int w{0};int k{0};int y{0};int m{0};int n{0};
    for(int i =0; i<4; i++){
        if(temp[i].courseTime.day == "saturday")
        {
          //  for(int j=0; j<4; j++)
             saturday[j] = temp[i];
             j++;
        }
        week[0][4]=saturday[4];
        if(temp[i].courseTime.day == "sunday")
        {
            //for(int j=0; j<4; j++)
                 sunday[z] = temp[i];
                 z++;
        }
        week[1][4]= sunday[4];
        if(temp[i].courseTime.day == "monday")
        {
           // for(int j=0; j<4; j++)
                 monday[w] = temp[i];
                 w++;
        }
        week[2][4]=monday[4];
        if(temp[i].courseTime.day == "tuesday")
        {
            //for(int j=0; j<4; j++)
                 tuesday[k] = temp[i];
                 k++;
        }
        week[3][4]=tuesday[4];
        if(temp[i].courseTime.day == "wednesday")
        {
           // for(int j=0; j<4; j++)
                 wednesday[y] = temp[i];
                 y++;
        }
        week[4][4]=wednesday[4];
        if(temp[i].courseTime.day == "thurday")
        {
           // for(int j=0; j<4; j++)
                 thurday[m] = temp[i];
                 m++;
        }
        week[5][4]=thurday[4];
        if(temp[i].courseTime.day == "friday")
        {
           // for(int j=0; j<4; j++)
                 friday[n] = temp[i];
                 n++;
        }
        week[6][4]=friday[4];
    }
}


//template <typename T>


course stackForTime[4];
course stackForTeacher[4];
course stackForStudent[4];


void mothercheck(course temp[4])
{

    for (int i = 0; i < 4; ++i)
    {
        if (temp[i].capacityCourse[0]>temp[i].location.capacityClass)
        {
            temp[i].capacityCourse[1]=1;

        }
        if (temp[i].videoprojector[0]==temp[i].location.videoprojector)
        {
            temp[i].videoprojector[1]=1;
        }
       int j{0};

        for(int j=0 ; j < 4 ; j++)
        {
            for (int k = 0; k < 4 ; ++k)
            {
                int c = 0;
                int t = 0;
                int m = 0;
                if ((temp[i].location.idClass == week[j][k].location.idClass) && (temp[i].name != week[j][k].name))
                {
                    /*course A = min(temp[i], week[j][k]);
                    course B = max(temp[i], week[j][k]);
                    if (!(A.courseTime.st < B.courseTime.st && A.courseTime.et < B.courseTime.et && A.courseTime.et < B.courseTime.st))
                    {
                        if (A.courseTime.st == temp[i].courseTime.st)
                        {
                            stack[c] = temp[i];
                            c++;
                        }
                        if (B.courseTime.st == temp[i].courseTime.st)
                        {
                            stack[c] = temp[i];
                            c++;
                        }

                    }*/
                    stackForTime[c] = checkTime(temp[i] , week[j][k]);
                    c++;
                }


                if((temp[i].teachername == week[j][k].teachername) && (temp[i].name != week[j][k].name)){
                    stackForTeacher[t] = checkTime(temp[i] , week[j][k]);
                    t++;
                }



            }
        }
    }
}
/*( !( (temp[i].courseTime.st>saturday[j].courseTime.st)&&(temp[i].courseTime.et>saturday[j].courseTime.et)&&(temp[i].courseTime.st>saturday[j].courseTime.et) ) ||
!( (temp[i].courseTime.st < saturday[j].courseTime.st)&&(temp[i].courseTime.et < saturday[j].courseTime.et)&&(temp[i].courseTime.et < saturday[j].courseTime.st) )  )*/

int main()
{
    cout<<"run program :"<<endl;

   /* date temp(8,2,1401,8,30,1,30);
    array<int , 2>myarr{calcuteTime(temp)};
    for(int i=0 ; i<2; i++){
        cout<<myarr[i]<<":";


    }
    cout<<endl;
    */
    course advp;
    course math; 
    course  physics; 
    course workshop; 
    course courses[4] = {advp , math , physics , workshop};
    specify(courses);


/*
    course math;
    math.courseTime.set_DH(1);
    math.courseTime.set_DM(45);
    math.courseTime.set_HS(16);
    math.courseTime.set_MS(00);
    array<int , 2>myarr = calcuteTime(math.courseTime);
    for(int i =0; i<2; i++)
        cout<<myarr[i]<<'\t';*/
    cout<<"------------------------------------------------------------------------\ntesting for show :\n";
    course AdvanceProgramming;
    classroom a101;
    //inputCourse(AdvanceProgramming , "MH101");
    AdvanceProgramming.inputCourse("AP101");
    AdvanceProgramming.show();


   return 0;
    
    }








