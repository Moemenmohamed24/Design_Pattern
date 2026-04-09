# يعني إيه Bridge Design Pattern؟
هو Design Pattern بيستخدم علشان يفصل بين الـ abstractionالفكرة العامة و الـ implementation طريقة التنفيذ بحيث يقدروا يتغيروا بشكل مستقل


#ايه المشكلة لو الـ abstraction والـ implementation مربوطين ببعض؟

1. مشكلة High Coupling (ترابط عالي)
```cpp
class SamsungAndroid {
public:
    void installApp(string app) {
        cout << "[Samsung + Android] Installing " << app << "\n";
    }
};

class SamsungiOS {
public:
    void installApp(string app) {
        cout << "[Samsung + iOS] Installing " << app << "\n";
    }
};

1.	المشكلة
الكلاس SamsungAndroid مربوط بشكل كامل بـ Android. : 
	الكلاس SamsungiOS مربوط بشكل كامل بـ iOS. 
أي تغيير في النظام → لازم تغير في  الكلاس SamsungAndroid او SamsungiOS وده بينتهك مبدا o/c principle


•	أي تعديل للكود → يمكنه فقط تغييره compile-time وليس runtime. 
•  Scalability problem 
•	لو عندك أكثر من جهاز (Huawei, iPhone) وأكثر من OS → كل كلاس يحتاج تعديل إذا أردت دعم OS جديد. 
•	لو عدلت كلاس واحد فقط → باقي الأجهزة لا تزال مربوطة بالـ OS القديم → لا حل عام.

```



#الحل معBridge؟
1.	Abstraction → الواجهة الأساسية اللي بيتم 
2.	Refined Abstraction → التفاصيل الخاصة بكل نوع
3.	Implementor → العقد 
4.	Concrete Implementor → التنفيذ 

```cpp

// implamantor
//ده الكلاس الاساسي بتاع نظم التشغيل
class OperatingSystem
{
public:

    virtual void InstallApp(string app) = 0;
    virtual string Getname() = 0;
};



// impamantation
//ده الكلاس اللي بيطبق دوال الكلاس الاساسي
class Android :  public OperatingSystem
{
    //5
    void InstallApp(string app) override
    {
        cout << "Android installs " << app << "\n";
    }

    string Getname() override
    {
        return "Android \n";
    }
};



// impamantation
//ده الكلاس اللي بيطبق دوال الكلاس الاساسي
class Ios : public OperatingSystem
{
    void InstallApp(string app) override
    {
        cout << "Ios installs " << app << "\n";
    }

    string Getname() override
    {
        return "Ios \n";
    }

};










// Abstraction
//ده الكلاس الاساسي لكل انوع التيليفونات 
class Mobile
{
protected:
    OperatingSystem *OS;
public:
    //3
    Mobile(OperatingSystem *os) : OS(os) {}

    virtual void Install(string app)
    {
        OS->InstallApp(app);
    }

    //هنا بيحصل  تبديل للنظم في الرن تايم 
    void Switching(OperatingSystem* newOS)
    {
        OS = newOS;
    }
};


//  Refined Abstractions
//ده بقا الجهاز نفسه
class Samsung : public Mobile
{
public:
                                     //2
    Samsung(OperatingSystem* os) : Mobile(os) {}

    //4
    void Install(string app) override
    {
        cout << "[Samsung] ";
        OS->InstallApp(app);
    }
};



class Huawei : public Mobile
{
public:

    Huawei(OperatingSystem* os) : Mobile(os) {}

    void Install(string app) override
    {
        cout << "[Samsung] ";
        OS->InstallApp(app);
    }


};




int main() {
   
    
    Android android;
    Ios ios;

    //-----------------طريقه السير----------------
    //1->2->3->4->5
    // 
    //1
    Samsung phone(&android);
    phone.Install("whatsApp");
    

    Huawei phone(&ios);
    phone.Install("whatsApp");

    //The pointer os changes from &android to &ios
    phone.Switching(&ios);
    phone.Install("whatsApp");

    return 0;
}
```

#امتى تستخدم Bridge Design Pattern؟ 
هل عندي حاجتين مستقلين؟

زي:


1.	Mobile + OS 
2.	Shape + Renderer 
3.	Remote + Device 



في Class Explosion 
لقيت نفسك بتعمل:

1.	SamsungAndroid 
2.	SamsungIOS 
3.	HuaweiAndroid 
4.	HuaweiIOS 


