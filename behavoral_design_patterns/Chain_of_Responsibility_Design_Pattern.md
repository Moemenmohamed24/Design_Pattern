
# التعريف:
 بدل ما تبعت الطلب لجهة واحدة محددة، بتعدّيه على سلسلة من المعالجات ، وكل واحد يقرر
•	يعالج الطلب أو يمرّره للي بعده 

# **** ملخص:
و برضه علشان ما ابعتش request  لكل الناس او لكل اللي في الشركه لو انا موظف ومثلا لو انا بعت لتلاته , التلاته هيرضو بنفس الرد او برد مختلف  المهم اني هخليهم يردوا , او انا موظف عايز حاجه من الشركه بدال ما اعمل Request  علي كل اللي في الشركه واقولهم او سالهم عن طلبي واللي يعرف يرد , او كلهم يرضو , لا انا مش بعمل كده , انا بعمل او بخلي الطلب يعدي بالدور علي كل اللي في الشركه واللي عارف الحل او عنده المسئوليه انو يساعدني فهيساعدني بس كده 


# **** ملخص:

 هي الفكره اني بدال مانا مبعت مثلا الريكوويست لكل اللي في الشركه يعني ابعت نفس الريكويست للمدير والسي يي او والديريكتور لا  انا ببعت ريسبونس واحد بس وهو عن طريق الشين ريبسونسيبيلتي بيتعامل هي دي بقا فكره التايت كابلنج في المشكله انا ببقي عارف اصلا اني فيه مدير ومدير تنفيذي وديريكتور علشان كده انا ببعت لكله انما هنا انا ببعت ريكويست واحد بس ومش عارف اصلا مين اللي جوا يقدر يهندل الريكويست ده

# مثال علي عدم استخددام ال chain: 

<img width="975" height="372" alt="image" src="https://github.com/user-attachments/assets/268e4ee7-e036-4ab1-88da-77a1b5025376" />
شكلها بسيطة، بس فيها كذا مشكلة حقيقية لو الكود كبر وده اللي خلى الناس تخترع الباترن لان اكيد مش هيخترعوا حاجه الا لو كان فيه مشكله قبلها , وعلشان نفهم اي حاجه في الدنيا لازم نعرف المشكله الاساسيه اللي هيبتحلها او كان قبلها ايه وهي جات عملت ايه او بالاختصار نعمل root causes analysis



# ايه المشاكل اللي بتحصل لما مش بنستخدمه ؟
## اول مشكله هي انتهاك  Open/Closed Principle (OCP) : 
الكود يكون مفتوح للإضافة (Open for Extension) لكن مغلق للتعديل (Closed for Modification). 
يعني لما ييجي Requirement جديد، المفروض أضيف كود جديد، مش أروح أعدل في كود قديم شغال ومجرب.

<img width="563" height="406" alt="image" src="https://github.com/user-attachments/assets/2306bfed-5a2f-4c12-bad4-c84ba7dcc735" />


هتضطر تعدل الدالة نفسها او مثلا قال هنحط منصب جديد اسمه Regional Manager بين Director و VP

<img width="505" height="463" alt="image" src="https://github.com/user-attachments/assets/9700efec-7154-497b-92ce-d449f82d5ac9" />




# الكود كله متلخبط في مكان واحد (انتهاك Single Responsibility) المشكلة الثانية

مبدأ SRP بيقول: كل جزء من الكود لازم يكون له سبب واحد للتغيير
يعني: الـ Manager له مسؤولية واحدة , الـ Director له مسؤولية واحدة , الـ VP له مسؤولية واحدة 
غلط ان كلهم يتحطوا في نفس المكان مش كلهم يتحطوا في نفس المكان.


<img width="819" height="403" alt="image" src="https://github.com/user-attachments/assets/4fc4db1f-a603-418e-8b84-13e983b45348" />


### فين المشكلة هنا؟ الدالة دي دلوقتي مش مسؤولة عن حاجة واحدة دي مسؤولة عن 3 حاجات:






# المشكلة الثالثة: الـ Client لازم يعرف كل تفاصيل المعالجين:

قبل Chain of Responsibility
الـ Client بنفسه يعرف كل الناس اللي ممكن تعالج الطلب:


```c++

public class LeaveRequest
{
    public int Days { get; set; }
}

public class Manager
{
    public bool Handle(LeaveRequest request)
    {
        if (request.Days <= 3)
        {
            Console.WriteLine("Manager Approved");
            return true;
        }

        return false;
    }
}



public class Director
{
    public bool Handle(LeaveRequest request)
    {
        if (request.Days <= 7)
        {
            Console.WriteLine("Director Approved");
            return true;
        }

        return false;
    }
}

public class CEO
{
    public bool Handle(LeaveRequest request)
    {
        Console.WriteLine("CEO Approved");
        return true;
    }
}





class Program
{
    static void Main()
    {
        var request = new LeaveRequest
        {
            Days = 5
        };

        var manager = new Manager();
        var director = new Director();
        var ceo = new CEO();

        // Client هو اللي عارف كل الناس
        // وهو اللي بيقرر الترتيب

        if (!manager.Handle(request))
        {
            if (!director.Handle(request))
            {
                ceo.Handle(request);
            }
        }
    }
```

ايه المشكله اللي هنا :
 1. Strong Coupling ارتباط شديد

- الـ Main مربوط مباشرة بـ:

-	Manager 
-	Director 
-	CEO 

- يعني أي تغيير في الهيكل الإداري هيأثر على الـ Client. زي اضافه عضو جديد

- var manager = new Manager();
- var director = new Director();
- var ceo = new CEO();





# المثال الكامل لحل المشاكل دي كلها مع استخدام chain responsibility : 

```c++

// Handler Interface
class LeaveHandler {
public:
    virtual void handleRequest(int days) = 0;
    virtual void setNextHandler(LeaveHandler* nextHandler) = 0;
};




//دول اللي بيعملوا بروسيس بقا للريكويست نفسه , يعني مره هيجي ريكويست لو مالقاش الطلب بتاعه عند حد فيهم يروح للتاني  و ملقاش يروح للتالت وهكذا
// Concrete Handlers

class Manager : public LeaveHandler {
private:
    LeaveHandler* nextHandler = nullptr;

public:
    //الداله دي هي اللي بتاخد الاوبجيكت اللي عليه الدور لو في الكلاس  ده ماعرفش يعمل بروسيس للريكويست ,
    // يعني لو معرفش الداله دي بتاخد المكان التاني اللي ممكن يعمل البروسيس علي الريكةيست ده 
    void setNextHandler(LeaveHandler* nextHandler) override {
        this->nextHandler = nextHandler;
    }

    //الداله دي هي اللي بتعل البروسيس نفسها علي اليوم اللي جاي
    void handleRequest(int days) override {
        if (days <= 3) {
            cout << "Manager approved " << days << " days leave." << endl;
        }//هنا بقا لو الرقم اكبر من 3 هينزل هنا وهيكون الاوبجيكت نيكيست هانديلير ده فيه بوليميرفيزم مبعوت من تحت, 
        //يعني لما تشغل الاوبجيكت ده هيشغل الداله بتاعه اللي معمول ليها اوفيررايد, مثال لو انا باعت الاوبجيكت ده وكان بيأشر علي الديريكتورر يبقي داله الهانديل ريكويست بتاعه الديريكتور هي النيكيست هانديلير اللي هتشتغل 
        else if (nextHandler != nullptr) {
            nextHandler->handleRequest(days);
        }
    }
};

class Director : public LeaveHandler {
private:
    LeaveHandler* nextHandler = nullptr;

public:
    void setNextHandler(LeaveHandler* nextHandler) override {
        this->nextHandler = nextHandler;
    }

    void handleRequest(int days) override {
        if (days <= 7) {
            cout << "Director approved " << days << " days leave." << endl;
        }
        else if (nextHandler != nullptr) {
            nextHandler->handleRequest(days);
        }
    }
};



class CEO : public LeaveHandler {
public:
    void setNextHandler(LeaveHandler* nextHandler) override {
        // CEO آخر واحد في السلسلة
    }

    void handleRequest(int days) override {
        cout << "CEO approved " << days << " days leave." << endl;
    }
};

// Main Function

int main() {


    //هنا بعمل بقا البوليمير فيزم 
    LeaveHandler* manager = new Manager();
    LeaveHandler* director = new Director();
 
    LeaveHandler* ceo = new CEO();


•	manager نوعه LeaveHandler* لكنه يشير إلى كائن Manager. 
•	director نوعه LeaveHandler* لكنه يشير إلى كائن Director. 
•	ceo نوعه LeaveHandler* لكنه يشير إلى كائن CEO. 
البوليمورفيزم يظهر فعليًا عندما تستدعي دالة virtual من خلال مؤشر الأب:



    //هنا انا بقول ان النيكيست هانديلير هو الديريكتور لو المانيجير مش هيعمل البروسيس
    manager->setNextHandler(director);
    //هنا انا بقول ان النيكيست هانديلير هو السي اي او لو الديريكتور مش هيعمل البروسيس
    director->setNextHandler(ceo);

    manager->handleRequest(2);
    manager->handleRequest(5);
    manager->handleRequest(15);

    delete manager;
    delete director;
    delete ceo;

    return 0;
}






