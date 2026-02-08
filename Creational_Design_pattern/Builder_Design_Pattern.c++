 Builder Pattern:  

Builder Pattern : مش مجرد طريقة لعمل object.
هو فصل خطوات إنشاء object معقد عن تمثيله النهائي.
يعني:
•	الـ Client يحدد الخطوات أو المكونات،
•	Builder يتولى تنفيذها خطوة خطوة،
•	Object النهائي يتجمع في النهاية.


الفكرة الأساسية:
لو عندك object كبير/معقد، أو فيه optional fields كتير، أو خطواته بتتغير، متبقاش مضطر تعمل constructor ضخم أو overloads كتيرة.

 الفكرة الجوهرية:
بدل ما يكون عندك Constructor واحد كبير فيه 10-15 parameter، بتبني الـ object خطوة بخطوة باستخدام واجهة واضحة ومرنة.


 نبدا بالمشكله !!
المثال بدون Builder - كل المشاكل الكارثية!:

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person {
private:
    // Basic Info
    string firstName;
    string lastName;
    int age;
    string gender;
    string nationality;
    
    // Contact Info
    string email;
    string phone;
    string address;
    string city;
    string country;
    
    // Professional Info
    string jobTitle;
    string company;
    int yearsOfExperience;
    double salary;
    
    // Personal Info
    string maritalStatus;
    int numberOfChildren;
    string bloodType;
    double height;
    double weight;
    
    // Preferences
    bool smoker;
    string religion;
    vector<string> hobbies;

public:
    //كل لما تعوز تزود حاجه الكونستراكتور  هيزيد اكتر 
    Person(string firstName, string lastName, int age, string gender,
           string nationality, string email, string phone, string address,
           string city, string country, string jobTitle, string company,
           int yearsOfExperience, double salary, string maritalStatus,
           int numberOfChildren, string bloodType, double height,
           double weight, bool smoker, string religion, vector<string> hobbies)
        : firstName(firstName), lastName(lastName), age(age), gender(gender),
          nationality(nationality), email(email), phone(phone), address(address),
          city(city), country(country), jobTitle(jobTitle), company(company),
          yearsOfExperience(yearsOfExperience), salary(salary),
          maritalStatus(maritalStatus), numberOfChildren(numberOfChildren),
          bloodType(bloodType), height(height), weight(weight),
          smoker(smoker), religion(religion), hobbies(hobbies) {}
};


المشكلة 2: سهولة الخطأ في الترتيب!

 //   بدلت الترتيب
Person person(
    "أحمد",
    "محمد",
    25,
    "مصري",        //  المفروض gender مش nationality!
    "ذكر",         // المفروض nationality مش gender!
 );


Person person(
    "سارة", "أحمد", 28, "أنثى", "مصرية",
    "sara@email.com", "01098765432",
    "شارع الجامعة", "الإسكندرية", "مصر",
    "مصممة", "وكالة الإبداع", 5, 12000.0,
    "متزوجة", 2, "A+",
    65.0,      // ❌ المفروض دي height بس حطيت weight!
    168.0,     // ❌ المفروض دي weight بس حطيت height!
    false, "مسلمة",
    {"رسم", "موسيقى"}
);
 
// لكن سارة دلوقتي طولها 65 سم ووزنها 168 كيلو! 


المشكلة 5: Default Values

// مضطر تحط قيم افتراضية فارغة
Person student(
    "محمد", "حسن", 20, "ذكر", "مصري",
    "mohamed@email.com", "01055555555",
    "شارع الجامعة", "طنطا", "مصر",
    "",             //  مفيش وظيفة - string فاضي
    "",             //  مفيش شركة - string فاضي
    0,              //  سنوات خبرة = 0 
    0.0,            //  راتب = 0
    "أعزب",
    0,
    "B+",
    170.0,
    70.0,
    false,
    "مسلم",
    {"كرة قدم"}
);


Builder  بيحل إيه؟ (المشكلة اللي بيعالجها)
•	يعزل عملية البناء عن الاستخدام:
o	Client يقرر “ماذا يريد”، Builder ينفذ “كيف يُبنى”.
•	يحسن readability:
o	كل خطوة واضحة بإسمها.
•	يسمح بالـ optional fields بسهولة:
o	مش لازم تعمل constructor لكل combination.
•	يسهل التوسعة:
o	لو ضفت خاصية جديدة، ما تكسرش أي حاجة موجودة.
•	يمكن عمل objects immutable:
o	بعد الـ build، ما يتغيرش.

مثال :


 #include <iostream>
#include <vector>


using namespace std;

class PersonBuilder;
class Person
{

private:
	const string firstName;
	const string lastName;
	const int    age;

	const string gender;
	const string nationality;


	const string email;
	const string phone;
	const string country;

	const string jop;



private:

	Person(const PersonBuilder& builder);


	friend class PersonBuilder;



	const string& getFirstName() const {
		return firstName;
	}

	const string& getLastName() const {
		return lastName;
	}

	int getAge() const {
		return age;
	}

	const string& getGender() const {
		return gender;
	}

	const string& getNationality() const {
		return nationality;
	}


	const string& getEmail() const {
		return email;
	}

	const string& getPhone() const {
		return phone;
	}

	const string& getCountry() const {
		return country;
	}


	const string& getJob() const {
		return jop;
	}
public:

	void Display()
	{
		cout << "firstName = " << firstName << endl;

		cout << "lastName = " << lastName << endl;

		cout << "age = " << age << endl;

		cout << "gender = " << gender << endl;

		cout << "nationality = " << nationality << endl;

		cout << "email = " << email << endl;

		cout << "phone = " << phone << endl;

		cout << "country = " << country << endl;

		cout << "jop = " << jop << endl;

	}

};


class PersonBuilder
{
private:
	string _firstName;
	string _lastName;
	int _age;

	string gender = "";
	string nationality;


	string email = "";
	string phone = "";
	string country = "";

	string jop = "";

public:

	//the main info that be in any person
	PersonBuilder(string firstName, string lastName, int age) : _firstName(firstName), _lastName(lastName), _age(age) {}


public:

	PersonBuilder& setgender(string gender)
	{
		this->gender = gender;
		return *this;
	}

	PersonBuilder setnationality(string nationality)
	{
		this->nationality = nationality;
		return *this;
	}

	PersonBuilder setemail(string email)
	{
		this->email = email;
		return *this;
	}

	PersonBuilder setphone(string phone)
	{
		this->phone = phone;
		return *this;
	}

	PersonBuilder setcountry(string country)
	{
		this->country = country;
		return *this;
	}

	PersonBuilder setjop(string jop)
	{
		this->jop = jop;
		return *this;
	}

	Person builder()
	{
		if (_age < 18 && _age > 60)
		{
			throw invalid_argument("age is not correct");
		}

		if (nationality == "israel")
		{
			throw invalid_argument("there is not country that have this name , just Palestine");
		}


		if (!email.empty() || email.find("@"))
		{
			throw invalid_argument("email is not correct");
		}

		//وممكن اكمل اني اعمل اي تحقيق علي اي حاجه مهما كانت علشان لو حاجه واحده بس غلط ما اعملش اوبجيكت 

		return Person(*this);
	}

	friend class Person;
};
//بعمل الحته دي او بحط كل المتغيرات المتوفره اللي عملتها في البيرسون وعلي حسب بقا اللي جاي من البلدر المتغيرات اللي جايه من البلدر بتتحط هنا والباقي مش بيستخدم 
Person::Person(const PersonBuilder& builder) :
	firstName(builder._firstName),
	lastName(builder._lastName),
	age(builder._age),
	gender(builder.gender),
	nationality(builder.nationality),
	email(builder.email),
	phone(builder.phone),
	country(builder.country),
	jop(builder.jop) {
}




int main()
{
	PersonBuilder builder = PersonBuilder("Moemen ", " mohamed", 20);
	builder.setemail("mohamed@student.com");
	builder.setcountry("egypt");
	builder.setgender("mail");
	builder.setjop("SWE");
	builder.setnationality("egyption");
	builder.setphone("0173354665");


	Person student = builder.builder();
	student.Display();
}



