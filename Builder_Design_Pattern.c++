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


 
